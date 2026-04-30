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

#ifndef MentorBitLIS3DH_h
#define MentorBitLIS3DH_h

#include <Arduino.h>
#include <Wire.h>

class MentorBitLIS3DH : public MentorPort
{
    public: 

        MentorBitLIS3DH();
        bool begin(uint8_t i2c_addr = 0x19);
        void configurarRango(uint8_t rango);
        void configurarTasaMuestreo(uint16_t frecuencia);
        void ponerEnReposo();
        void despertar();
        void obtenerAceleraciones(float &x_value, float &y_value, float &z_value) const;
        uint8_t obtenerRango() const;
        float obtenerAceleracionX() const;
        float obtenerAceleracionY() const;
        float obtenerAceleracionZ() const;
        float obtenerPitch() const;
        float obtenerRoll() const;
        bool detectarToque();
        bool detectarDobleToque();
        bool detectarCaidaLibre();
        bool estaConectado();

    private:

        uint8_t _i2c_addr;
        uint16_t _working_freq;

        void _writeRegisters(uint8_t register, uint8_t value);
        void _readAccelerationsRaw(int16_t &x, int16_t &y, int16_t &z);
        uint8_t _readRegister(uint8_t register);

};

#endif