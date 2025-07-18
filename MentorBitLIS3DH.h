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
        obtenerPosiciones -> Función que permite obtener los valores de rotación de los ejes
        obtenerPosicionX -> Función que permite obtener el valor de rotación del eje X
        obtenerPosicionY -> Función que permite obtener el valor de rotación del eje Y
        obtenerPosicionZ -> Función que permite obtener el valor de rotación del eje Z

*/

#ifndef MentorBitLIS3DH_h
#define MentorBitLIS3DH_h

#include <arduino.h>
#include <MentorPort.h>
#include <Wire.h>
#include <MPU6050.h>
#include <I2Cdev.h>

class MentorBitLIS3DH : public MentorPort
{
    public: 

        MentorBitLIS3DH();
        bool begin(uint8_t i2c_addr = 0x68);
        void obtenerAceleraciones(int x_value, int y_value, int z_value);
        int obtenerAceleracionX();
        int obtenerAceleracionY();
        int obtenerAceleracionZ();
        void obtenerPosiciones(int x_value, int y_value, int z_value);
        int obtenerPosicionX();
        int obtenerPosicionY();
        int obtenerPosicionZ();
        void configPort(const Port& port) override;

    private:

        Port _port;
        uint8_t _i2c_addr;
        MPU6050 _sensor;

};

#endif