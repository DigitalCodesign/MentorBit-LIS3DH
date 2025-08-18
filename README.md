# MentorBit-LIS3DH

Esta librería está diseñada para que puedas **medir aceleración, detectar movimiento, inclinación y vibraciones** utilizando tu placa MentorBit y el módulo de acelerómetro LIS3DH.

Si estás empezando en el mundo de la electrónica, ¡no te preocupes! MentorBit está pensado para que aprender sea fácil y divertido. Esta placa ya incluye un montón de componentes (LEDs, pulsadores, pantallas, etc.) y utiliza conectores especiales (JST) para que puedas añadir nuevos sensores y módulos sin tener que pelearte con un montón de cables. Pásate por nuestra web para saber más de MentorBit y nuestros productos [pinchando aquí](https://digitalcodesign.com/).

![Render del Módulo MentorBit de Acelerómetro.](https://github.com/DigitalCodesign/MentorBit-LIS3DH/blob/main/assets/Accelerometer_Module.png)

Con esta librería, podrás darles a tus proyectos la capacidad de sentir el movimiento y la orientación en el espacio, abriendo un mundo de posibilidades interactivas.

---

## Descripción

### ¿Qué es un sensor LIS3DH?

El **LIS3DH** es un acelerómetro de 3 ejes de alto rendimiento y bajo consumo. Este tipo de sensor mide la "aceleración propia" (fuerza G), que puede usarse para detectar la orientación de un objeto respecto a la gravedad, así como para sentir movimiento, golpes o vibraciones.

En resumen, le permite a tu proyecto saber si se está moviendo, en qué dirección y si está inclinado.

---

### ¿Qué hace esta librería?

La librería **MentorBit-LIS3DH** simplifica la interacción con el sensor LIS3DH. Se encarga de la comunicación I2C y de la configuración inicial, ofreciéndote funciones directas para obtener los valores de aceleración en los ejes X, Y y Z.

Está adaptada para que su uso con MentorBit sea lo más sencillo posible.

---

### ¿Qué puedes construir con este módulo?

- Un podómetro que cuente tus pasos.
- Un detector de caídas o golpes para un dispositivo o persona.
- Un controlador para juegos que reaccione a la inclinación de un mando.
- Un sistema de alarma que se active si alguien mueve un objeto protegido.

---

## Cómo empezar

### 1. **Conexión del Módulo**

Conecta el módulo LIS3DH al puerto marcado como I2C en la sección de comunicaciones de la placa MentorBit. Este sensor se comunica usando el protocolo I2C.

### 2. **Instalación de la Librería**

- Abre tu entorno de programación IDE de Arduino.
- Ve al menú *Programa -> Incluir Librería -> Administrar Librerías...*
- En el buscador, escribe ***MentorBit-LIS3DH*** y haz clic en "Instalar".
- El IDE también instalará las dependencias necesarias automáticamente.

![Ejemplo de búsqueda en el gestor de librerías del IDE de Arduino.](https://github.com/DigitalCodesign/MentorBit-LIS3DH/blob/main/assets/library_instalation_example.png)

---

## Ejemplo Básico: Leer aceleraciones

Este ejemplo lee los valores de aceleración en los tres ejes y los muestra en el monitor serie cada medio segundo.

```cpp
#include <MentorBitLIS3DH.h>

// Creamos el objeto para nuestro acelerómetro
MentorBitLIS3DH miAcelerometro;

void setup() {
    // Inicializamos el monitor serial
    Serial.begin(9600);

    // Inicializamos el sensor en su dirección I2C por defecto (0x19)
    if (!miAcelerometro.begin()) {
        Serial.println("No se pudo iniciar el LIS3DH. Revisa las conexiones.");
        while (1);
    }
    
    Serial.println("Sensor LIS3DH listo.");
}

void loop() {
    // Creamos tres variables para guardar los valores de los ejes
    float ax, ay, az;

    // Obtenemos los valores de aceleración (se pasan por referencia)
    miAcelerometro.obtenerAceleraciones(ax, ay, az);

    // Imprimimos los resultados
    Serial.print("Aceleración X: ");
    Serial.print(ax);
    Serial.print(" m/s^2, ");

    Serial.print("Y: ");
    Serial.print(ay);
    Serial.print(" m/s^2, ");

    Serial.print("Z: ");
    Serial.print(az);
    Serial.println(" m/s^2");

    delay(500);
}
```

---

## Funciones Principales

- `bool begin(uint8_t i2c_addr = 0x19)`  
  Inicializa el sensor y la comunicación I2C. Devuelve <code>true</code> si la inicialización fue exitosa.

- `void obtenerAceleraciones(float &x_value, float &y_value, float &z_value)`  
  Obtiene las lecturas de aceleración de los tres ejes a la vez. Los valores se devuelven por referencia en las variables que se le pasan como argumento. Las unidades están en metros por segundo al cuadrado (*m/s2*).

- `float obtenerAceleracionX()`  
  Devuelve la lectura de aceleración únicamente para el eje X.

- `float obtenerAceleracionY()`  
  Devuelve la lectura de aceleración únicamente para el eje Y.

- `float obtenerAceleracionZ()`  
  Devuelve la lectura de aceleración únicamente para el eje Z.

---

## Recursos Adicionales

- [Web del fabricante](https://digitalcodesign.com/)
- [Tienda Online de Canarias](https://canarias.digitalcodesign.com/shop)
- [Tienda Online de Península](https://digitalcodesign.com/shop)
- [Web Oficial de MentorBit](https://digitalcodesign.com/mentorbit)
- [Web Oficial del Módulo LIS3DH](https://canarias.digitalcodesign.com/shop/00040018-mentorbit-modulo-acelerometro-8722)
- [Manual de usuario del Módulo](https://drive.google.com/file/d/19nVRrOpDVUUWKhgI5Kc4xMzFr-6zQ6fY/view?usp=drive_link)
- [Modelo 3D del Módulo LIS3DH en formato .STEP](https://drive.google.com/file/d/1i_ow_5eBSxFOOkXbFAi51BHmzW0Pt0Og/view?usp=drive_link)
