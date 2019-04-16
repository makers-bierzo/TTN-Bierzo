# Primeros pasos con LoRA y LoRaWAN

Todo esto empezó leyendo los blogs de [Bricolabs](https://bricolabs.cc/wiki/guias/lora_ttn) y de Akirasan sobre [LoRa](http://akirasan.net/tag/lora/), y el objetivo es adquirir y compartir conocimientos sobre [LoRa](https://github.com/makers-bierzo/TTN-Bierzo/tree/master/TTN_Microcontrolador/LoRa) y [LoRaWAN](https://github.com/makers-bierzo/TTN-Bierzo/tree/master/TTN_Microcontrolador/LoRaWAN) usando [The Things Network](https://www.thethingsnetwork.org/).

LoRa es el tipo de modulación en radiofrecuencia patentado por Semtech para comunicaciones a grandes distancias con poco consumo de energía.

LoRaWAN es un protocolo de red que usa la tecnología LoRa para comunicar y administrar dispositivos LoRa. 

[Haciendo IoT con LoRa](https://medium.com/beelan/haciendo-iot-con-lora-cap%C3%ADtulo-1-qu%C3%A9-es-lora-y-lorawan-8c08d44208e8) es un artículo de Sabas que explica muy claramente que es LoRa y LoRaWAN. 

También este vídeo [LoRa (1): Introducción y conceptos](https://www.youtube.com/watch?v=qs7Lz9g-mgg) de biblioman09 nos aporta mucha teoría sobre esta tecnología. 

## Herramientas de desarrollo

Para todos los programas voy a usar como editor de código [Visual Studio Code](https://code.visualstudio.com/) con [PlatformIO](https://platformio.org/), lo considero el editor del futuro de Arduino. 

Aconsejo el canal de Youtube [biblioman09](https://www.youtube.com/channel/UC9OHtNnklTrMj9pDu4XiVRQ) y mas concretamente este vídeo, [Como programar los ESP32 con el IDE de PlatformIO](https://www.youtube.com/watch?v=TNWt_dXdoIU), para empezar a usar este entorno de desarrollo. 

También [Andreas Spiess](https://www.youtube.com/channel/UCu7_D0o48KbfhpEohoP7YSQ) en este vídeo, [PlatformIO for Arduino, ESP8266, and ESP32 Tutorial](https://www.youtube.com/watch?v=0poh_2rBq7E), muestra el uso de PlatformIO.


## Instalación de librerías en PlatformIO

La instalación de librerías es una algo que tenemos que dominar para poder usar programas que otros compañeros comparten. 

Toda la documentación [librarymanager](https://docs.platformio.org/en/latest/librarymanager/index.html) está en la página oficial de PlatformIO.  

El proceso es muy sencillo usando el entorno gráfico cuando la librería que buscas aparece en los resultados de la busqueda.  

Pero que sucede si queremos instalar una librería que no aparece en los resultados. Pues para esto podemos usar la linea de comandos [CLI](https://docs.platformio.org/en/latest/librarymanager/quickstart.html#cli-guide) relacionados con la gestión de librerías, con los que podremos realizar instrucciones más avanzadas.


El que me interesa en este momento es el comando [platformio lib install](https://docs.platformio.org/en/latest/userguide/lib/cmd_install.html#usage) donde se explica como se pueden instalar librerías de otras maneras. 


Con estas herramientas nos ponemos manos a la obra.

