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

/*  
    Constructor de la clase
*/
MentorBitLIS3DH::MentorBitLIS3DH(){

}

/*
    Esta función inicializa el acelerometro para su posterior uso
*/
bool MentorBitLIS3DH::begin(uint8_t i2c_addr = 0x68){
    Wire.begin();
    _i2c_addr = i2c_addr;
    _sensor.initialize();
}

/*
    Esta funcion devuelve por referencia el valor de las aceleraciones medidas por el sensor
*/
void MentorBitLIS3DH::obtenerAceleraciones(int x_value, int y_value, int z_value){
    _sensor.getAcceleration(&x_value, &y_value, &z_value);
}

/*
    Esta función devuelve el valor de la aceleración en el eje X
*/
int MentorBitLIS3DH::obtenerAceleracionX(){
    int x_value;
    int y_value;
    int z_value;
    _sensor.getAcceleration(&x_value, &y_value, &z_value);
    return x_value;
}

/*
    Esta función devuelve el valor de la aceleracion en el eje Y
*/
int MentorBitLIS3DH::obtenerAceleracionY(){
    int x_value;
    int y_value;
    int z_value;
    _sensor.getAcceleration(&x_value, &y_value, &z_value);
    return y_value;
}

/*
    Esta funcion devuelve el valor de la aceleracion en el eje Z
*/
int MentorBitLIS3DH::obtenerAceleracionZ(){
    int x_value;
    int y_value;
    int z_value;
    _sensor.getAcceleration(&x_value, &y_value, &z_value);
    return z_value;
}

void MentorBitLIS3DH::configPort(const Port& port) {

_port.type = port.type;
_port.location = port.location;
_port.gpios[0] = port.gpios[0];
_port.gpios[1] = port.gpios[1];

pinMode(_port.gpios[0], OUTPUT);

}
