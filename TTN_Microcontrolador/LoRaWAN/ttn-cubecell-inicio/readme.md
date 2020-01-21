# CubeCell Dev-Board

CubeCell es una buena opción para las aplicaciones de nodo LoRaWAN, que proporcionan las siguientes características principales:

1. Totalmente compatible con Arduino;
2. Diseño de potencia ultra-baja, puede alcanzar 3.5uA en modo de reposo profundo (con reloj RTC funcionando);
3. Bajo costo;
4. Algoritmo de cifrado integrado, por ejemplo, un producto basado en CubeCell, si alguien copió el firmware dentro del flash y el programa en un hardware de clonación, no se ejecutará;
5. Un ASR650x, es un PSoC4000 y un SX1262 dentro de un chip, hace que el circuito de aplicación tenga un tamaño más pequeño;
6. Soporte de panel solar;
7. Soporte de protocolo LoRaWAN;
8. Soporte de comando AT para la configuración;


# Instalar el Framework Arduino CubeCell.
Hay dos métodos para instalar el Framework CubeCell, elija uno de ellos.

## Usando el Gestor de tarjetas Arduino 
Abrir el IDE de Arduino, y clic en Archivo => Preferencias 

![captura1](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRaWAN/ttn-cubecell-inicio/img/Captura1.PNG)

En la pestaña de Ajustes, introducir la siguiente URL de JSON en el Gestor de URLs Adicionales de Tarjetas:

https://docs.heltec.cn/download/package_CubeCell_index.json

![captura2](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRaWAN/ttn-cubecell-inicio/img/Captura2.PNG)

Después Clic en Herramientas => Placa: => Gestor de tarjetas... 

![captura4](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRaWAN/ttn-cubecell-inicio/img/Captura4.PNG)

Buscar Heltec cubecell en el cuadro de dialogo, seleccionar la ultima versión y clic en instalar. 

![captura5](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRaWAN/ttn-cubecell-inicio/img/Captura5.PNG)

## Usando Git 

Toda información en este [enlace](https://github.com/HelTecAutomation/ASR650x-Arduino#installation-instructions)

# Ejecutando un ejemplo LoRaWAN OTAA/ABP con TTN

## Crear la aplicación y el dispositivo en The Things Network

En [TTN](https://www.thethingsnetwork.org/) debemos tener una cuenta. Creamos una aplicación y dentro de ella un dispositivo con el método de activación [OTAA o ABP](https://medium.com/beelan/haciendo-iot-con-lora-capitulo-2-tipos-y-clases-de-nodos-3856aba0e5be).

Además necesitaremos una puerta de enlace LoRaWAN estándar con al menos 8 canales cercana. Asegúrese de que esa puerta de enlace próxima esté [conectada](https://ttnmapper.org/) .

## Configuraciones de la placa.

Conecte su placa CubeCell a la computadora a través de un cable Micro USB.  
Tememos las siguientes opciones en el menú Herramientas de Arduino:

- Placa: Elija el hardware correcto conectado a su computadora;
- LORAWAN\_REGION: Definición de región de protocolo LoRaWAN, siga estrictamente los parámetros regionales de LoRaWAN 1.1; 
- LORAWAN\_CLASS: Ahora es compatible con clase A y clase C;
- LORAWAN\_NETMODE: OTAA o ABP;
- LORAWAN\_ADR: Enciende o apaga ADR (Adaptive Data Rate);
- LORAWAN\_Net\_Reservation: Esta es una característica fuera del protocolo LoRaWAN, solo válida en modo OTAA. Si esta opción está habilitada, cuando se produce un reinicio del sistema no necesita unirse nuevamente.
- LORAWAN\_AT\_SUPPORT: Los comandos AT proporcionará muchas funciones útiles, por ejemplo, los usuarios pueden usar el puerto serie para configurar LoRa Node’s DevEui, AppKey o hacer que el nodo se suspenda, restablezca, etc.
- LORAWAN\_RGB: Luz RGB para el estado LoRaWAN:
    - Púrpura: Unirse;
    - Azul: primera ventana RX;
    - Amarillo: segunda ventana de RX;
    - Verde: Unión hecha.
- Puerto: El puerto serie del dispositivo en su computadora.

**Nota**:  
LORAWAN\_Net\_Reservation se usa por ejemplo en un corte de energía a gran escala en la ciudad. Cuando se restablece la alimentación, miles de dispositivos se conectan a la red al mismo tiempo, lo que puede provocar que falle la puerta de enlace o el servidor LoRa. Habilitar esta función evitará esta situación. **Al habilitar LORAWAN\_Net\_Reservation debe deshabilitar el contador de tramas (fCnt) en el servidor LoRa.**

Aquí sólo cambiamos a la región europea en LORAWAN\_REGION seleccionando REGION\_EU868 y elegimos el método de activación OTAA o ABP.

**Nota**:  
**Las configuraciones del menú de herramientas deben coincidir con las configuraciones en la aplicación de The Things Network.**


## Seleccionamos un ejemplo. 

En la ruta "LoRa" de ejemplos para CubeCell-Board, todos los ejemplos nombrados con el formato "LoRaWAN_xxx" son los ejemplos con el protocolo LoRaWAN, elija uno de ellos. 

Nosotros elegimos el primero: LoRaWan que enviará un payload:00 01 02 03. Lo compilamos y lo subimos a la tarjeta CubeCell. 

No importa qué plataforma de gestión de LoRa se use, se necesitan parámetros DevEui, AppKey, etc. Y asegúrese de que sea coherente con la configuración relevante en el servidor.

Los siguientes parámetros son esenciales para el modo **OTAA**:  
    -**DevEui**: dispositivo Mote IEEE EUI (big endian), 8 bytes;  
    -**AppEui**: Aplicación IEEE EUI (big endian), 8 bytes;  
    -**AppKey**: Clave de aplicación de cifrado / descifrado AES, 16 bytes;  

Los siguientes parámetros son esenciales para el modo **ABP**:  
    -**NwkSKey**: clave de sesión de red de cifrado / descifrado AES, 16 bytes;  
    -**AppSKey**: clave de sesión de la aplicación de cifrado / descifrado AES, 16 bytes;  
    -**DevAddr**: dirección del dispositivo en la red (big endian), uint32_t;

Existen tres métodos para configurar los parámetros de red LoRaWAN, elija uno de ellos.

### Directamente fijado en el código fuente

Los parámetros importantes de la red LoRaWAN se encuentran en esta ruta:

ASR650X-ARDUINO / bibliotecas / LoRa / src / Commissioning.h

Cambie el código fuente y compile / cargue nuevamente.

### A través de comandos AT

Para usar el comando AT, necesita habilitar el comando AT en el menú "Herramientas" antes de cargarlo.

Configuración del Puerto Serie:  
    
    Baud rate: 115200  
    Stop bit: 1  
    Data bits: 8  
    DTR, RTS requirement: None  
    Ending characters: None

**Nota:**  
**Asegúrese de que NO haya caracteres finales o una nueva línea en la configuración de su monitor serie**

Con soporte de comando AT, el CubeCell está durmiendo por defecto. Cualquier contenido a través del puerto serie lo despertará. Significa que el primer comando a través del puerto serie solo activa el sistema.

Por ejemplo, si envía algún contenido como hola, obtendrá esta respuesta:

ASR is Waked,LowPower Mode Stopped

#### Parámetros OTAA  

Tomamos todo cero solo para el ejemplo y estos serían los comandos para OTAA

**DevEui**  
Configure DevEui en "0000000000000000", envíe el siguiente comando a través del puerto serie:

    AT+DevEui=0000000000000000

El comando que se ejecuta correctamente responderá:  

    +OK  
    +DevEui=0000000000000000(For OTAA Mode)  

**AppEui**
Configure AppEui en "0000000000000000", envíe el siguiente comando a través del puerto serie:

    AT+AppEui=0000000000000000

El comando que se ejecuta correctamente responderá:

    +OK
    +AppEui=0000000000000000(For OTAA Mode)

**AppKey**  
Configure AppKey a “00000000000000000000000000000000”, envíe el siguiente comando a través del puerto serie:

    AT+AppKey=00000000000000000000000000000000

El comando que se ejecuta correctamente responderá:

    +OK
    +AppKey=00000000000000000000000000000000(For OTAA Mode)


#### Parámetros ABP  

Tomamos todo cero solo para el ejemplo y estos serían los comandos para ABP  

**NwkSKey**
Configure NwkSKey a “00000000000000000000000000000000”, envíe el siguiente comando a través del puerto serie:

    AT+NwkSKey=00000000000000000000000000000000

El comando que se ejecuta correctamente responderá:

    +OK
    +NwkSKey=00000000000000000000000000000000(For ABP Mode)

**AppSKey**
Configure AppSKey a “00000000000000000000000000000000”, envíe el siguiente comando a través del puerto serie:

    AT+AppSKey=00000000000000000000000000000000

El comando que se ejecuta correctamente responderá:

    +OK
    +AppSKey=00000000000000000000000000000000(For ABP Mode)

**DevAddr**

Configure DevAddr a “00000000”, envíe el siguiente comando a través del puerto serie:

    AT+DevAddr=00000000

El comando que se ejecuta correctamente responderá:

    +OK
    +DevAddr=00000000(For ABP Mode)


**Duty Cycle**  
El período de envío de datos predeterminado del nodo LoRa es de 15 segundos, cambie este período a 60 segundos:

    AT+DutyCycle=60000

**Restablecer CubeCell**  
Los parámetros de LoRaWAN deben restablecerse a activos, CubeCell puede restablecerse mediante tres métodos:

     Presione la tecla RST;
     Utilice el comando AT: AT+RESET=1
     Proporcione una señal BAJA ≥10ms al pin RST.

¿Buscas más comandos AT? Consulte la lista de comandos de CubeCell [AT](https://heltec-automation-docs.readthedocs.io/en/latest/cubecell/config_parameter.html#via-at-command).

### Via Configurador CubeCell  

[RaySteam](https://github.com/raystream/CubeCell_Getting_Started) creó un configurador para CubeCell, ahora solo tiene soporte para Windows®.


# Fuente de información
Toda esta documentación no es más que una traducción de la documentación aportada por Heltec en [Github](https://github.com/HelTecAutomation/HeltecDocs)
