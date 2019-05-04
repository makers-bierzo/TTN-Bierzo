# Gateway LoRA con LoPy4

El Gateway LoRa lo voy a hacer usando las herramientas de desarrollo de [Pycom](https://pycom.io/). Ya existen muchos tutoriales de como hacer un Gateway con TTGO LoRa32 y quiero comenzar a usar los productos de este fabricante para proyectos mas profesionales.  

De momento el Gateway será de un solo canal con un [LoPy4](https://pycom.io/product/lopy4/). En el futuro pienso usar el siguiente producto [Pygate](https://pycom.io/product/pygate/), que es una puerta de enlace LoRaWAN de 8 canales que permite conectar un WiPy3.0, LoPy4 o un GPy a esta placa y luego conectar todos tus otros dispositivos Pycom.

## Introducción

Recomendamos leer todas las secciones de la [documentación de Pycom](https://docs.pycom.io/) para familiarizarse con las diversas herramientas y funciones disponibles para ayudarlo a desarrollar con su módulo Pycom.


Y después comenzar con la [documentación de Lopy4](https://docs.pycom.io/datasheets/development/lopy4.html)


## Pasos Iniciales

Para ponerlo en funcionamiento, Pycom proporciona un conjunto de herramientas para ayudarlo a desarrollar y programar sus dispositivos Pycom.

1. Actualización del firmware de Pycom.

     [La utilidad de actualización de firmware de Pycom](https://docs.pycom.io/gettingstarted/installation/firmwaretool.html) automatiza el proceso de actualización del firmware de su dispositivo Pycom. Es importante que use esta herramienta antes de intentar usar su dispositivo. No solo para asegurarse de tener el firmware más estable y con más funciones, sino también para garantizar que todas las funciones de su dispositivo estén habilitadas. P.ej. esta herramienta también activa su conectividad sigfox gratuita durante dos años.

2. Instalación de Pymakr

     El entorno de desarrollo: Pymakr es un complemento para Atom y Visual Studio Code desarrollado por Pycom para hacer que el desarrollo de los módulos de Pycom sea muy fácil. Le permite usar su editor de texto favorito mientras simplifica el proceso de carga de código en el dispositivo.  

     [Instalación Pymark en Atom](https://docs.pycom.io/pymakr/installation/atom.html)  

     [Instalación Pymark en Visual Studio Code](https://docs.pycom.io/pymakr/installation/vscode.html)

3. Programación inicial de los módulos.
	
	Ahora que ha conectado y actualizado su módulo de Pycom e instalado todo el software requerido en su computadora, podemos comenzar a programar su módulo de Pycom.

	Si es la primera vez que usa un módulo Pycom, le recomendamos que lea las siguientes páginas:

    [Introducción a MicroPython](https://docs.pycom.io/gettingstarted/programming/micropython.html): esta página explicará qué es Micropython y su relación con Python.

    [Ejemplos de MicroPython](https://docs.pycom.io/gettingstarted/programming/micropython.html): También recomendamos que explore estos ejemplos breves de MicroPython para familiarizarse con su sintaxis. Esto no pretende ser una guía completa para la programación de MicroPython, sino una referencia para aquellos que ya conocen la programación. Si eres nuevo en Python, o estás programando todos juntos, te recomendamos que busques en Internet los tutoriales de Python. Hay muchos tutoriales muy buenos disponibles de forma gratuita y las habilidades que aprendas serán fácilmente transferibles a nuestra plataforma.


    [Su primer proyecto Pymakr](https://docs.pycom.io/gettingstarted/programming/first-project.html): una vez que entienda lo que es MicroPython, esta guía lo guiará a través de la configuración de su primer proyecto Pymakr para que parpadee el LED RGB incorporado. Esta guía explicará la estructura de un proyecto de MicroPython y cómo cargarlo en su módulo.


## LoRaWAN Nano-Gateway

Este ejemplo permite conectar un LoPy o LoPy4 a una red LoRaWAN con The Things Network (TTN) o Loriot para ser utilizado como nano-gateway.

Este ejemplo utiliza configuraciones específicas para conectarse a TTN dentro de la región europea de 868 MHz. Para configurar esto para su uso específico, consulte el archivo config.py.

Las versiones actualizadas de estos fragmentos se pueden encontrar en el siguiente repositorio de [GitHub](https://github.com/pycom/pycom-libraries/tree/master/examples/lorawan-nano-gateway).

El código de Nano-Gateway se divide en 3 archivos, main.py, config.py y nanogateway.py. Se utilizan para configurar y especificar cómo se conectará su puerta de enlace a su red preferida y cómo puede actuar como reenviador de paquetes.

### Main (main.py)

Este archivo se ejecuta en el arranque y llama a la biblioteca y a los archivos config.py para inicializar el nano-gateway. Una vez establecida la configuración, se inicia la nano-puerta de enlace.

### Configuración (config.py)

Este archivo contiene la configuración específica para el servidor y la red a la que se está conectando. Dependiendo de su región y provea (TTN, Loriot, etc.) estos variarán. Para configuraciones específicas, revise el foro para otros que pueden haber configurado su nano-gateway para diferentes configuraciones.

El ID de la puerta de enlace se genera en la secuencia de comandos mediante el proceso:


```
WIFI_MAC = ubinascii.hexlify(machine.unique_id()).upper()
# Set  the Gateway ID to be the first 3 bytes of MAC address + 'FFFE' + last 3 bytes of MAC address
GATEWAY_ID = WIFI_MAC[:6] + "FFFE" + WIFI_MAC[6:12]
```

Solo es necesario por el SSID y la contraseña del WiFi:

```
WIFI_SSID = 'my-wifi'
WIFI_PASS = 'my-wifi-password'
```

### Biblioteca (nanogateway.py)

La biblioteca nano-gateway controla toda la generación y el reenvío de paquetes para los datos LoRa. Esto no requiere ninguna configuración de usuario y la última versión de este código debe descargarse de la cuenta de Pycom [GitHub](https://github.com/pycom/pycom-libraries/tree/master/examples/lorawan-nano-gateway).


## Registrarse en TTN

Para configurar la puerta de enlace con The Things Network (TTN), vaya a su sitio web y cree / registre una cuenta. Deberá ingresar un nombre de usuario y una dirección de correo electrónico para verificar su cuenta en su plataforma.

Una vez que haya registrado una cuenta, puede iniciar el proceso de registro de su nano-gateway. Para hacer esto, tendrás que navegar a la página web de la Consola TTN.

### Registro de la puerta de enlace

Dentro de la consola TTN, tendrás dos opciones, aplicaciones y puertas de enlace. Seleccione las puertas de enlace y luego haga clic en registrar puerta de enlace. Esto le permitirá configurar y registrar una nueva nano-puerta de enlace.

En la página Registrar Gateway, deberá configurar los siguientes ajustes.

Estos son únicos para su puerta de enlace, ubicación y frecuencia definida por país. Verifique que tenga la configuración correcta, de lo contrario, la puerta de enlace no se conectará a TTN.

Debe marcar la casilla "Estoy usando el reenviador de paquetes heredado" para habilitar la configuración correcta. Esto se debe a que el Nano-Gateway utiliza el protocolo semtech UDP estándar "de facto".

```
Protocol = Packet Forwarder
Gateway EUI = User Defined (must match config.py)
Description = User Defined
Frequency Plan = Select Country (e.g. EU - 868 MHz)
Location = User Defined
Antenna Placement = Indoor or Outdoor 
```

El Gateway EUI debe coincidir con su ID de Gateway del archivo config.py.

Una vez que se haya aplicado la configuración, haga clic en Register Gateway. 

En este punto, llegará a la página de información general de la puerta de enlace donde se verán sus ajustes de configuración.  

A continuación, haga clic en Configuración de la puerta de enlace y configure la dirección del enrutador para que coincida con la de su puerta de enlace (predeterminado - router.eu.thethings.network).

La puerta de enlace debería estar ahora configurada. Ahora se pueden configurar uno o más nodos para usar la nano-puerta de enlace y se pueden construir aplicaciones TTN.

## Fuentes de información 

[Pycom](https://pycom.io/)  

[Información en The things Network con LoPy](https://www.thethingsnetwork.org/docs/devices/lopy/)


[Información el Pycom LoRaWAN Nano-Gateway](https://docs.pycom.io/tutorials/lora/lorawan-nano-gateway.html)


[Vídeo tutorial Pycom LoPy4 Nano Gateway for LoRaWAN](https://www.youtube.com/watch?v=d7CHfmqkVWc)

[Construir un LoRaWAN Nano Gateway to The Things Network](https://core-electronics.com.au/tutorials/building-a-lorawan-nano-gateway-to-the-things-network.html)



