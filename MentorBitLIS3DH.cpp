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
        

    Autor: Digital Codesign
    Version: 1.0.0
    Fecha de creación: Julio de 2025
    Fecha de version: Julio de 2025
    Repositorio: https://github.com/DigitalCodesign/MentorBit-LIS3DH
    Descripcion: 
        Esta libreria esta especificamente diseñada para ser utilizada junto con 
        el modulo MentorBit Acelerometro.
    Metodos principales:
        MentorBitAcelerometro -> Constructor de la clase
        begin -> Inicializador de la clase para el uso del acelerometro
        obtenerAceleraciones -> Función que permite obtener las aceleraciones de todos los ejes
        obtenerAceleracionX -> Función que permite obtener la aceleración del eje X
        obtenerAceleracionY -> Función que permite obtener la aceleración del eje Y
        obtenerAceleracionZ -> Función que permite obtener la aceleración del eje Z

*/

#include "MentorBitLIS3DH.h"

/**
 * @brief Constructor de la clase
 */
MentorBitLIS3DH::MentorBitLIS3DH();

/**
 * @brief Inicializa la comunicación con el sensor.
 * @param i2c_addr Dirección I2C del sensor, 0x19 por defecto.
 * @return true si el sensor fue inicializado correctamente, false en caso contrario.
 */
bool MentorBitLIS3DH::begin(uint8_t i2c_addr = 0x19);

/**
 * @brief Configura el rango de medición del acelerómetro.
 * @param rango Valor del rango a configurar según los registros del LIS3DH.
 */
void MentorBitLIS3DH::configurarRango(uint8_t rango);

/**
 * @brief Configura la tasa de muestreo de datos del sensor.
 * @param frecuencia Frecuencia de muestreo deseada en Hz.
 */
void MentorBitLIS3DH::configurarTasaMuestreo(uint16_t frecuencia);

/**
 * @brief Pone el sensor en modo de bajo consumo para ahorrar batería.
 */
void MentorBitLIS3DH::ponerEnReposo();

/**
 * @brief Reactiva el sensor desde el modo de reposo a su estado normal de medición.
 */
void MentorBitLIS3DH::despertar();

/**
 * @brief Lee las aceleraciones físicas en los tres ejes (X, Y, Z).
 * @param x_value Referencia donde se almacenará la aceleración del eje X.
 * @param y_value Referencia donde se almacenará la aceleración del eje Y.
 * @param z_value Referencia donde se almacenará la aceleración del eje Z.
 */
void MentorBitLIS3DH::obtenerAceleraciones(float &x_value, float &y_value, float &z_value);

/**
 * @brief Obtiene la configuración actual del rango de medición del sensor.
 * @return El valor del rango configurado.
 */
uint8_t MentorBitLIS3DH::obtenerRango();

/**
 * @brief Obtiene la aceleración actual en el eje X.
 * @return Valor de la aceleración en el eje X.
 */
float MentorBitLIS3DH::obtenerAceleracionX();

/**
 * @brief Obtiene la aceleración actual en el eje Y.
 * @return Valor de la aceleración en el eje Y.
 */
float MentorBitLIS3DH::obtenerAceleracionY();

/**
 * @brief Obtiene la aceleración actual en el eje Z.
 * @return Valor de la aceleración en el eje Z.
 */
float MentorBitLIS3DH::obtenerAceleracionZ();

/**
 * @brief Calcula y obtiene el ángulo de inclinación frontal/trasera.
 * @return Ángulo de cabeceo en grados.
 */
float MentorBitLIS3DH::obtenerPitch();

/**
 * @brief Calcula y obtiene el ángulo de inclinación lateral.
 * @return Ángulo de alabeo en grados.
 */
float MentorBitLIS3DH::obtenerRoll();

/**
 * @brief Detecta si ha ocurrido un evento de toque simple.
 * @return true si se detectó un toque, false en caso contrario.
 */
bool MentorBitLIS3DH::detectarToque();

/**
 * @brief Detecta si ha ocurrido un evento de doble toque rápido.
 * @return true si se detectó un doble toque, false en caso contrario.
 */
bool MentorBitLIS3DH::detectarDobleToque();

/**
 * @brief Detecta si el sensor se encuentra actualmente en estado de caída libre.
 * @return true si está en caída libre, false en caso contrario.
 */
bool MentorBitLIS3DH::detectarCaidaLibre();

/**
 * @brief Verifica si el sensor está físicamente conectado y responde en el bus I2C.
 * @return true si la comunicación es exitosa, false si el sensor no responde.
 */
bool MentorBitLIS3DH::estaConectado();

/**
 * @brief Configura el puerto de hardware asociado al sensor.
 * @param port Estructura constante por referencia con la configuración del puerto.
 */
void MentorBitLIS3DH::configPort(const Port& port) {

_port.type = port.type;
_port.location = port.location;
_port.gpios[0] = port.gpios[0];
_port.gpios[1] = port.gpios[1];

pinMode(_port.gpios[0], OUTPUT);

}

/**
 * @brief Escribe un valor en un registro específico del sensor vía I2C.
 * @param register Dirección de memoria del registro a escribir.
 * @param value Valor que se escribirá en el registro.
 */
void MentorBitLIS3DH::_writeRegisters(uint8_t register, uint8_t value);

/**
 * @brief Lee los datos en crudo (raw) directamente de los registros de hardware de los tres ejes.
 * @param x Referencia para almacenar el valor crudo del eje X.
 * @param y Referencia para almacenar el valor crudo del eje Y.
 * @param z Referencia para almacenar el valor crudo del eje Z.
 */
void MentorBitLIS3DH::_readAccelerationsRaw(int16_t &x, int16_t &y, int16_t &z);

/**
 * @brief Lee el valor de un registro específico del sensor vía I2C.
 * @param register Dirección de memoria del registro a leer.
 * @return El valor contenido en dicho registro.
 */
uint8_t MentorBitLIS3DH::_readRegister(uint8_t register);
