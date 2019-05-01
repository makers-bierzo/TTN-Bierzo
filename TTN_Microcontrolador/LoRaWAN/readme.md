# LoRaWAN

En este apartado agruparemos Nodos y Gateways, los dos elementos principales en las comunicaciones LoRaWAN, creados con microcontroladores.

## Gateways LoRA

En las redes LoRaWan, un Gateway es un dispositivo que se encarga de comunicarse de forma bidireccional a través de LoRa con los Nodos y reenviar la comunicación a Internet. 

Existe una gran variedad de Gateways en el mercado y con una gran variedad de características diferentes. Características comunes son:

 1. Para América y Europa chip SX301 (para 915 y 868 MHZ)
 2. 8 canales de recepción simultánea
 3. 1 canal de transmisión
 4. Sistema operativo basado en Linux

Dependiendo del Gateway podría soportar 62,500 nodos enviando información una vez al día o 1,000 nodos enviando información cada 30 segundos.

Con microcontroladores, solo se puede pretender hacer Gateways de un solo canal para pruebas de concepto. Tanto el chip LoRa como el microcontrolador no soportan una gran cantidad de nodos. 

Sin embargo [Pygate](https://pycom.io/product/pygate/) es una puerta de enlace LoRaWAN de 8 canales que te permite conectar un WiPy3.0, LoPy4 o un GPy a este escudo y luego conectar todos tus otros dispositivos Pycom y tener una pequeña red IoT ingeniosa de una sola vez. También intentaremos probarlo.


## Nodos LoRA

En modo LoRaWAN, los Nodos forzosamente se deben conectar a un Gateway. Son los dispositivos con sensores o actuadores, de los que queremos recibir o a los que queremos transmitir información.

Los Nodos trabajan en una conexión tipo estrella, se conectan al Gateway mas cercano y con mejor calidad de comunicación. 

En protocolo LoRaWAN existen tres tipos de clases de nodo dependiendo de su tiempo que dediquen a recibir datos:

### Clase A:

La más soportada en casi todos los dispositivos, este tipo de clase ofrece el mayor ahorro de energía debido a que solo entra en modo escucha (llamado ventana RX) después de enviar un datos hacia el Gateway, por eso es ideal para dispositivos que usan una batería.

### Clase B:

Este tipo de dispositivos tiene las ventanas de recepción con base a tiempos predeterminados con el Gateway, este tipo de nodos puede usar una batería o una fuente externa dependiendo de los tiempos asignados de escucha. 

### Clase C:

Este tipo de clase ofrece el menor ahorro de energía debido a que siempre esta en modo escucha y solo cuando es necesario en modo transmitir, la recomendación es usarlo en dispositivos que cuentan con una fuente externa de alimentación.

## Modos de conexión de los Nodos ABP y OTAA

Existen dos maneras de conectarse a una red LoRaWAN, para entrar a la red se requieren una serie de claves y número de identificación por parte del nodo. 

### Modo OTAA

El modo OTAA (Over-The-Air-Activation) es la manera más segura de conectarse a la red y los parámetros de configuración son:

**DevEUI**: Este es un identificador de fábrica, hace a cada dispositivo único. Esta configuración en algunos dispositivos se puede ajustar.

**AppEUI**: Identificador de aplicación único utilizado para agrupar objetos. Esta dirección de 64 bits se, utiliza para clasificar los dispositivos por aplicación. Esta Configuración se puede ajustar

**AppKey**: Es una clave secreta AES de 128bits compartida entre el dispositivo periférico y la red. Se utiliza para determinar las claves de sesión. Esta configuración se puede ajustar.

Con estos datos de manera simple la conexión se realiza de la siguiente manera:

1. El nodo solicita un join (o inicio de sesión) a la red con los datos de configuración y abre la ventana de recepción.
2. El Gateway recibe la solicitud y la envía al servidor.
3. El servidor verifica que el nodo este dado de alta y la llave de encriptación sea correcta.
4. Si es correcta asigna una sesión temporal y la envía por medio del Gateway al nodo, si los datos son incorrectos rechaza el join.
5. El nodo recibe la sesión temporal y puede enviar datos a la red.

La principal ventaja de la conexión tipo OTAA es la seguridad ya que la sesión se dice: “se crea en el aire” y se renueva cada vez que el dispositivo pierde la conexión, es apagado o reiniciado, esto dificulta que alguien pueda robar la sesión y clonar el dispositivo.

### Modo ABP

El modo ABP (Activation By Personalization) es el modo más sencillo de conexión, los parámetros de conexión son:

**DevAddress**: Dirección lógica (equivalente a una dirección IP) que se utilizará para toda comunicación posterior con la red.

**NetworkSessionKey**: Clave de cifrado entre el dispositivo y el operador utilizado para las transmisiones y para validar la integridad de los mensajes.

**ApplicationSessionKey**: Clave de cifrado entre el dispositivo y el operador (a través de la aplicación) utilizada para transmisiones y para validar la integridad de los mensajes.

Con estos parámetros la conexión se realiza de la siguiente manera:

1. El dispositivo envía datos hacia al Gateway  
2. El Gateway válida que los datos corresponda a la sesión  
3. Si es correcta la sesión se procesan los datos, sino se rechazan.  


La principal ventaja de este tipo de conexión es que no se requiere hacer un join a la red para poder enviar datos, la confirmación del lado del servidor no es necesaria ya que la sesión ya está manualmente asignada, 

Para dispositivos que están en movimiento o no tienen excelente recepción este tipo de conexión es idónea. La desventaja es que al encontrarse la llave de encriptación en el dispositivo pudiera ser extraída y clonada por una atacante.


## Fuentes de información

[Haciendo IoT con LoRa](https://medium.com/beelan/haciendo-iot-con-lora-capitulo-2-tipos-y-clases-de-nodos-3856aba0e5be
)

[LoRa del blog de akirasan](http://akirasan.net/tag/lora/)





