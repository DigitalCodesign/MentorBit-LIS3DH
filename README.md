# MentorBit-LIS3DH

Librería para el uso del módulo de acelerómetro MentorBit LIS3DH

## Descripción

La librería `MentorBitLIS3DH` facilita el uso del módulo de acelerómetro LIS3DH compatible con MentorBit. Permite la obtención, tanto de forma conjunta, como individual, de los valores de aceleraciones y rotaciones de los tres ejes (X, Y, Z).

## Modo de Empleo

1.  **Instalación:**
    * Abre el IDE compatible con MentorBit.
    * Ve a "Herramientas" -> "Gestionar librerías..."
    * Busca "MentorBitLIS3DH" e instálala.

2.  **Ejemplo básico:**

    ```c++
    #include <MentorBitLIS3DH.h>

    MentorBitLIS3DH acelerometro; // Crear el objeto Acelerometro de la clase MentorBitLIS3DH

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
    ```

## Constructor y Métodos Públicos

### Constructor

* `MentorBitLIS3DH`: Crea un objeto `MentorBitLIS3DH`: No se debe indicar ningún valor adicional en el constructor. Sin embargo, se debe llamar a la función `begin(i2c_addr)` e indicarle la dirección I2C del módulo a utilizar.

### Métodos

* `void begin(uint8_t i2c_addr)`: Inicializador del módulo, se utiliza para inicializar las funciones de I2C.
* `void obtenerAceleraciones(int x_value, int y_value, int z_value)`: Sobreescribe las variables dadas con los valores de aceleración medidos en los ejes.
* `int obtenerAceleracionX()`: devuelve el valor de aceleración en el eje X.
* `int obtenerAceleracionY()`: devuelve el valor de aceleración en el eje Y.
* `int obtenerAceleracionZ()`: devuelve el valor de aceleración en el eje Z.
* `void obtenerPosiciones(int x_value, int y_value, int z_value)`: Sobreescribe las variables dadas con los valores de rotación medidos en los ejes.
* `int obtenerPosicionX()`: devuelve el valor de rotación en el eje X.
* `int obtenerPosicionY()`: devuelve el valor de rotación en el eje Y.
* `int obtenerPosicionZ()`: devuelve el valor de rotación en el eje Z.
