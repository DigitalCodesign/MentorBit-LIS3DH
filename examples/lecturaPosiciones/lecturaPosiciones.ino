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
        Este sketch muestra un ejemplo sencillo de como programar el MentorBit para obtener
        los valores de las rotaciones de los tres ejes (X, Y, Z)

*/
// Se incluye la libreria MentorBitLIS3DH.h
#include <MentorBitLIS3DH.h>

MentorBitLIS3DH acelerometro; // Crear el objeto Acelerometro de la clase MentorBitLIS3DH

// Se declaran las variables en las que se van a almacenar los valores de rotacion
int posicionX = 0;
int posicionY = 0;
int posicionZ = 0;

void setup() {
    acelerometro.begin(0x68); // inicializar el módulo 
    Serial.begin(9600); // Inicializar el puerto serial a 9600 baudios
    delay(1000); // Espera 1 segundos
}

void loop() {
    // Imprimir los valores de aceleración de los ejes
    acelerometro.obtenerPosiciones(&posicionX, &posicionY, &posicionZ);
    Serial.print("Valores de aceleración:  ");
    Serial.print(posicionX);
    Serial.print("  ||  ");
    Serial.print(posicionY);
    Serial.print("  ||  ");
    Serial.println(posicionZ);
}