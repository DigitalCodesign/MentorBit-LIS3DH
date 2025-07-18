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
        los valores de las aceleraciones de los tres ejes (X, Y, Z)

*/
// Se incluye la libreria MentorBitLIS3DH.h
#include <MentorBitLIS3DH.h>

MentorBitLIS3DH acelerometro; // Crear el objeto Acelerometro de la clase MentorBitLIS3DH

// Se declaran las variables en las que se van a almacenar los valores de aceleraciones
int aceleracionX = 0;
int aceleracionY = 0;
int aceleracionZ = 0;

void setup() {
    acelerometro.begin(0x68); // inicializar el módulo 
    Serial.begin(9600); // Inicializar el puerto serial a 9600 baudios
    delay(1000); // Espera 1 segundos
}

void loop() {
    // Imprimir los valores de aceleración de los ejes
    acelerometro.obtenerAceleraciones(&aceleracionX, &aceleracionY, &aceleracionZ);
    Serial.print("Valores de aceleración:  ");
    Serial.print(aceleracionX);
    Serial.print("  ||  ");
    Serial.print(aceleracionY);
    Serial.print("  ||  ");
    Serial.println(aceleracionZ);
}