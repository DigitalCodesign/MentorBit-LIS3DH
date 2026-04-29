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
        el modulo MentorBit LIS3DH
    Metodos principales:
        MentorBitLIS3DH -> Constructor de la clase
        begin -> Inicializador de la clase para el uso del acelerometro
        obtenerAceleraciones -> Función que permite obtener las aceleraciones de todos los ejes
        obtenerAceleracionX -> Función que permite obtener la aceleración del eje X
        obtenerAceleracionY -> Función que permite obtener la aceleración del eje Y
        obtenerAceleracionZ -> Función que permite obtener la aceleración del eje Z

*/

#ifndef MentorBitLIS3DH_h
#define MentorBitLIS3DH_h

#include <Arduino.h>
#include <Wire.h>
#include <MentorPort.h>

class MentorBitLIS3DH : public MentorPort
{
    public: 

        MentorBitLIS3DH();
        bool begin(uint8_t i2c_addr = 0x19);
        void configurarRango(uint8_t rango);
        void configurarTasaMuestreo(uint16_t frecuencia);
        void ponerEnReposo();
        void despertar();
        void obtenerAceleraciones(float &x_value, float &y_value, float &z_value);
        uint8_t obtenerRango(); const;
        float obtenerAceleracionX() const;
        float obtenerAceleracionY() const;
        float obtenerAceleracionZ() const;
        float obtenerPitch(); const;
        float obtenerRoll(); const;
        bool detectarToque();
        bool detectarDobleToque();
        bool detectarCaidaLibre();
        bool estaConectado();
        void configPort(const Port& port) override;

    private:

        Port _port;
        uint8_t _i2c_addr;

        void _writeRegisters(uint8_t register, uint8_t value);
        void _readAccelerationsRaw(int16_t &x, int16_t &y, int16_t &z);
        uint8_t _readRegister(uint8_t register);

};

#endif