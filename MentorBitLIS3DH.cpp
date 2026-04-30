/*


            ██████╗    ██╗    ██████╗    ██╗   ████████╗    █████╗    ██╗               
            ██╔══██╗   ██║   ██╔════╝    ██║   ╚══██╔══╝   ██╔══██╗   ██║               
            ██║  ██║   ██║   ██║  ███╗   ██║      ██║      ███████║   ██║               
            ██║  ██║   ██║   ██║   ██║   ██║      ██║      ██╔══██║   ██║               
            ██████╔╝   ██║   ╚██████╔╝   ██║      ██║      ██║  ██║   ███████╗          
            ╚═════╝    ╚═╝    ╚═════╝    ╚═╝      ╚═╝      ╚═╝  ╚═╝   ╚══════╝          
                                                                                        
     ██████╗    ██████╗    ██████╗    ███████╗   ███████╗   ██╗    ██████╗    ███╗   ██╗
    ██╔════╝   ██╔═══██╗   ██╔══██╗   ██╔════╝   ██╔════╝   ██║   ██╔════╝    ████╗  ██║
    ██║        ██║   ██║   ██║  ██║   █████╗     ███████╗   ██║   ██║  ███╗   ██╔██╗ ██║
    ██║        ██║   ██║   ██║  ██║   ██╔══╝     ╚════██║   ██║   ██║   ██║   ██║╚██╗██║
    ╚██████╗   ╚██████╔╝   ██████╔╝   ███████╗   ███████║   ██║   ╚██████╔╝   ██║ ╚████║
     ╚═════╝    ╚═════╝    ╚═════╝    ╚══════╝   ╚══════╝   ╚═╝    ╚═════╝    ╚═╝  ╚═══╝ 
        

    @author Digital Codesign
    @version 1.1.0
    @date Fecha de creación: Julio de 2025
    @date Fecha de versión: Abril de 2026
    @see Repositorio: https://github.com/DigitalCodesign/MentorBit-LIS3DH
    @brief Descripción: 
        Esta librería está específicamente diseñada para ser utilizada junto con 
        el módulo MentorBit Acelerómetro (basado en el LIS3DH). Implementa una 
        comunicación I2C directa y ligera, sin dependencias de terceros.
    @details Métodos principales:
        - MentorBitLIS3DH        -> Constructor de la clase.
        - begin                  -> Inicializa la comunicación I2C y configura el sensor.
        - obtenerAceleraciones   -> Obtiene las aceleraciones simultáneas de los ejes X, Y, Z.
        - obtenerAceleracionX    -> Obtiene la aceleración individual del eje X.
        - obtenerAceleracionY    -> Obtiene la aceleración individual del eje Y.
        - obtenerAceleracionZ    -> Obtiene la aceleración individual del eje Z.
    Métodos extendidos:
        - obtenerPitch / Roll    -> Calcula los ángulos de inclinación (cabeceo y alabeo).
        - detectarToque          -> Detecta impactos físicos o pulsaciones (Single/Double Tap).
        - detectarCaidaLibre     -> Detecta si el módulo se encuentra en estado de ingravidez.
        - configurarRango        -> Modifica la sensibilidad del sensor (±2g, ±4g, ±8g, ±16g).
        - ponerEnReposo          -> Reduce el consumo de energía al mínimo.

*/

#include "MentorBitLIS3DH.h"

constexpr uint8_t LIS3DH_REG_WHOAMI        = 0x0F;
constexpr uint8_t LIS3DH_REG_CTRL1         = 0x20;
constexpr uint8_t LIS3DH_REG_CTRL4         = 0x23;
constexpr uint8_t LIS3DH_REG_OUT_X_L       = 0x28;
constexpr uint8_t LIS3DH_REG_CLICK_CFG     = 0x38;
constexpr uint8_t LIS3DH_REG_CLICK_SRC     = 0x39;
constexpr uint8_t LIS3DH_REG_CLICK_THS     = 0x3A;
constexpr uint8_t LIS3DH_REG_TIME_LIMIT    = 0x3B;
constexpr uint8_t LIS3DH_REG_TIME_LATENCY  = 0x3C;
constexpr uint8_t LIS3DH_REG_TIME_WINDOW   = 0x3D;
constexpr uint8_t LIS3DH_REG_INT1_CFG      = 0x30;
constexpr uint8_t LIS3DH_REG_INT1_SRC      = 0x31;
constexpr uint8_t LIS3DH_REG_INT1_THS      = 0x32;
constexpr uint8_t LIS3DH_REG_INT1_DURATION = 0x33;

/**
 * @brief Constructor de la clase
 */
MentorBitLIS3DH::MentorBitLIS3DH() : i2c_addr(0x19) {}

/**
 * @brief Inicializa la comunicación con el sensor.
 * @param i2c_addr Dirección I2C del sensor, 0x19 por defecto.
 * @return true si el sensor fue inicializado correctamente, false en caso contrario.
 */
bool MentorBitLIS3DH::begin(uint8_t i2c_addr = 0x19) {

    _i2c_addr = i2c_addr;
    _working_freq = 400;
    Wire.begin();

    if (_readRegister(0x0F) != 0x33)
        return false;

    // Configuramos parámetros básicos
    configurarTasaMuestreo(_working_freq); // 400Hz
    configurarRango(0x00); // ±2g

    // Habilitamos y configuramos el detector de toques
    _writeRegisters(LIS3DH_REG_CLICK_CFG, 0x3F); // Activamos todos los modos de toque
    _writeRegisters(LIS3DH_REG_CLICK_THS, 0x30); // Valor estimado como threshold
    _writeRegisters(LIS3DH_REG_TIME_LIMIT, 10); // Límite de duración del toque en clicks, a 400Hz cada unidad son 2.5ms (25ms)
    _writeRegisters(LIS3DH_REG_TIME_LATENCY, 80); // Latencia antes de buscar el 2º toque (200ms)
    _writeRegisters(LIS3DH_REG_TIME_WINDOW, 120); // Tiempo máximo para dar el 2º toque (300ms)

    // Configuramos para detectar caídas libres
    _writeRegisters(LIS3DH_REG_INT1_THS, 0x16); // Umbral "casi cero" para considerar caída libre, a 400Hz unos 350mg
    _writeRegisters(LIS3DH_REG_INT1_DURATION, 0x0C); // Duración del estado de caída libre, a 400Hz unos 30ms
    _writeRegisters(LIS3DH_REG_INT1_CFG, 0x95); // Activamos evento AND y eventos LOW en X, Y, Z

    return true;

}

/**
 * @brief Configura el rango de medición del acelerómetro.
 * @param rango Valor del rango a configurar según los registros del LIS3DH.
 */
void MentorBitLIS3DH::configurarRango(uint8_t rango) {

    // Leemos el estado actual del registro para no borrar configuraciones previas
    uint8_t ctrl4 = _readRegister(LIS3DH_REG_CTRL4);
    // Limpiamos exclusivamente los bits 4 y 5
    ctrl4 &= ~(0x30);
    // Asignamos los nuevos bits según el rango solicitado
    if (rango == 16) ctrl4 = (0x03 << 4);
    else if (rango == 8) ctrl4 = (0x02 << 4);
    else if (rango == 4) ctrl4 = (0x01 << 4);
    else ctrl4 = (0x00 << 4);
    // Aseguramos que se mantenga el modo Alta Resolución con el bit 3 activado.
    ctrl4 |= 0x08;
    // Escribimos la nueva configuración en el sensor
    _writeRegisters(LIS3DH_REG_CTRL4, ctrl4);

}

/**
 * @brief Configura la tasa de muestreo de datos del sensor.
 * @param frecuencia Frecuencia de muestreo deseada en Hz.
 */
void MentorBitLIS3DH::configurarTasaMuestreo(uint16_t frecuencia) {

    // Leemos el estado actual del registro
    uint8_t ctrl1 = _readRegister(LIS3DH_REG_CTRL1);
    // Limpiamos exclusivamente los bits 4 al 7 correspondientes a la frecuencia
    ctrl1 &= ~(0xF0);
    // Determinamos el código correcto según la frecuencia solicitada
    uint8_t odr_bits = 0;
    if (frecuencia == 0) odr_bits = 0x00;
    else if (frecuencia <= 1) odr_bits = 0x01;
    else if (frecuencia <= 10) odr_bits = 0x02;
    else if (frecuencia <= 25) odr_bits = 0x03;
    else if (frecuencia <= 50) odr_bits = 0x04;
    else if (frecuencia <= 100) odr_bits = 0x05;
    else if (frecuencia <= 200) odr_bits = 0x06;
    else odr_bits = 0x07;
    // Desplazamos los bits a su posición correcta
    ctrl1 |= (odr_bits << 4);
    // Aseguramos que los ejes X, Y y Z estén habilitados (bits 0, 1 y 2)
    ctrl1 |= 0x07;
    // Guardamos la configuración en el sensor y en la variable interna
    _working_freq = frecuencia;
    _writeRegisters(LIS3DH_REG_CTRL1, ctrl1);

}

/**
 * @brief Pone el sensor en modo de bajo consumo para ahorrar batería.
 */
void MentorBitLIS3DH::ponerEnReposo() {

    // Apagamos el oscilador interno del sensor para ahorrar batería
    configurarTasaMuestro(0);

}

/**
 * @brief Reactiva el sensor desde el modo de reposo a su estado normal de medición.
 */
void MentorBitLIS3DH::despertar() {

    // Reactivamos el sensor asignándole una frecuencia de trabajo
    configurarTasaMuestro(_working_freq);

}

/**
 * @brief Lee las aceleraciones físicas en los tres ejes (X, Y, Z).
 * @param x_value Referencia donde se almacenará la aceleración del eje X.
 * @param y_value Referencia donde se almacenará la aceleración del eje Y.
 * @param z_value Referencia donde se almacenará la aceleración del eje Z.
 */
void MentorBitLIS3DH::obtenerAceleraciones(float &x_value, float &y_value, float &z_value) const {

    int16_t raw_x, raw_y, raw_z;
    // Obtenemos los valores puros del hardware
    _readAccelerationsRaw(raw_x, raw_y, raw_z);
    // Obtenemos el rango actual para saber qué sensibilidad aplicar
    uint8_t rango = obtenerRango();
    float sensibilidad_mg_por_digito = 1.0f; // Valor por defecto para ±2g
    // Sensibilidades extraídas del Datasheet
    if (rango == 16) sensibilidad_mg_por_digito = 12.0f;
    else if (rango == 8) sensibilidad_mg_por_digito = 4.0f;
    else if (rango == 4) sensibilidad_mg_por_digito = 2.0f;
    // Calculamos el factor de conversión final a m/s2
    // (mg -> g) * (gravedad de la tierra)
    const float gravedad = 9.80665f;
    float multiplicador = (sensibilidad_mg_por_digito / 1000.0f) * gravedad;
    // Aplicamos el multiplicador a los valores crudos
    x_value = raw_x * multiplicador;
    y_value = raw_y * multiplicador;
    z_value = raw_z * multiplicador;

}

/**
 * @brief Obtiene la configuración actual del rango de medición del sensor.
 * @return El valor del rango configurado.
 */
uint8_t MentorBitLIS3DH::obtenerRango() const {

    // Leemos el registro de control 4
    uint8_t ctrl4 = _readRegister(LIS3DH_REG_CTRL4);
    // Nos quedamos solamente con los bits 4 y 5
    uint8_t bits_rango = (ctrl4 & 0x30) >> 4;
    // Devolvemos el rango en Gs según bits
    if (bits_rango == 0x03) return 16;
    if (bits_rango == 0x02) return 8;
    if (bits_rango == 0x01) return 4;
    return 2; // Valor por defecto

}

/**
 * @brief Obtiene la aceleración actual en el eje X.
 * @return Valor de la aceleración en el eje X.
 */
float MentorBitLIS3DH::obtenerAceleracionX() const {

    float x, y, z;
    obtenerAceleraciones(x, y, z);
    return x;

}

/**
 * @brief Obtiene la aceleración actual en el eje Y.
 * @return Valor de la aceleración en el eje Y.
 */
float MentorBitLIS3DH::obtenerAceleracionY() const {

    float x, y, z;
    obtenerAceleraciones(x, y, z);
    return y;

}

/**
 * @brief Obtiene la aceleración actual en el eje Z.
 * @return Valor de la aceleración en el eje Z.
 */
float MentorBitLIS3DH::obtenerAceleracionZ() const {

    float x, y, z;
    obtenerAceleraciones(x, y, z);
    return z;

}

/**
 * @brief Calcula y obtiene el ángulo de inclinación frontal/trasera.
 * @return Ángulo de cabeceo en grados.
 */
float MentorBitLIS3DH::obtenerPitch() const {

    float x, y, z;
    obtenerAceleraciones(x, y, z);
    float magnitud_yz = sqrt((y * y) + (z * z));
    return atan2(-x / magnitud_yz) * 180.0 / PI;

}

/**
 * @brief Calcula y obtiene el ángulo de inclinación lateral.
 * @return Ángulo de alabeo en grados.
 */
float MentorBitLIS3DH::obtenerRoll() const {

    float x, y, z;
    obtenerAceleraciones(x, y, z);
    return atan2(y / z) * 180.0 / PI;

}

/**
 * @brief Detecta si ha ocurrido un evento de toque simple.
 * @return true si se detectó un toque, false en caso contrario.
 */
bool MentorBitLIS3DH::detectarToque() {

    // Leemos el registro fuente de los toques
    uint8_t click_src = _readRegister(LIS3DH_REG_CLICK_SRC);
    // Aislamos el bit 4, que indica toques simples
    return (click_src & 0x10) != 0;

}

/**
 * @brief Detecta si ha ocurrido un evento de doble toque rápido.
 * @return true si se detectó un doble toque, false en caso contrario.
 */
bool MentorBitLIS3DH::detectarDobleToque() {

    // Leemos el registro fuente de los toques
    uint8_t clicl_src = _readRegister(LIS3DH_REG_CLICK_SRC);
    // Aislamos el bit 5, que indica toques dobles
    return (click_src & 0x20) != 0;

}

/**
 * @brief Detecta si el sensor se encuentra actualmente en estado de caída libre.
 * @return true si está en caída libre, false en caso contrario.
 */
bool MentorBitLIS3DH::detectarCaidaLibre() {

    // Leemos el resgistro de estado de la interrupción 1
    uint8_t int1_src = _readRegister(LIS3DH_REG_INT1_SRC);
    // Aislamos el bit 6, que indica si la interrupción está activa
    return (int1_src & 0x40) != 0;

}

/**
 * @brief Verifica si el sensor está físicamente conectado y responde en el bus I2C.
 * @return true si la comunicación es exitosa, false si el sensor no responde.
 */
bool MentorBitLIS3DH::estaConectado() const {

    // Intentamos leer el registro de identidad del sensor
    return _readRegister(LIS3DH_REG_WHOAMI) == 0x33;

}

/**
 * @brief Escribe un valor en un registro específico del sensor vía I2C.
 * @param reg Dirección de memoria del registro a escribir.
 * @param value Valor que se escribirá en el registro.
 */
void MentorBitLIS3DH::_writeRegisters(uint8_t reg, uint8_t value) {

    Wire.beginTransmission(_i2c_addr);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();

}

/**
 * @brief Lee los datos en crudo (raw) directamente de los registros de hardware de los tres ejes.
 * @param x Referencia para almacenar el valor crudo del eje X.
 * @param y Referencia para almacenar el valor crudo del eje Y.
 * @param z Referencia para almacenar el valor crudo del eje Z.
 */
void MentorBitLIS3DH::_readAccelerationsRaw(int16_t &x, int16_t &y, int16_t &z) {

    Wire.beginTransmission(_i2c_addr);
    Wire.write(LIS3DH_REG_OUT_X_L | 0x80);
    Wire.endTransmission(false);
    Wire.requestFrom(_i2c_addr, (uint8_t)6);
    if (Wire.available() == 6) {

        uint8_t x_low  = Wire.read();
        uint8_t x_high = Wire.read();
        x = (int16_t)(x_low | (x_high << 8));

        uint8_t y_low  = Wire.read();
        uint8_t y_high = Wire.read();
        y = (int16_t)(y_low | (y_high << 8));

        uint8_t z_low  = Wire.read();
        uint8_t z_high = Wire.read();
        z = (int16_t)(z_low | (z_high << 8));

    } else {

        x = 0;
        y = 0;
        z = 0;

    }

}

/**
 * @brief Lee el valor de un registro específico del sensor vía I2C.
 * @param reg Dirección de memoria del registro a leer.
 * @return El valor contenido en dicho registro.
 */
uint8_t MentorBitLIS3DH::_readRegister(uint8_t reg) {

    Wire.beginTransmission(_i2c_addr);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(_i2c_addr, (uint8_t)1);
    if (Wire.available()) return Wire.read();
    return 0;

}
