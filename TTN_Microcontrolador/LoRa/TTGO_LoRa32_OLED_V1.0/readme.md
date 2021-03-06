# Empezando con TTGO LoRa32 v1.0 y LoRa

## Descripción

El objetivo en este apartado es dar los primeros pasos con el hardware elegido, [TTGO LoRa32 OLED V1.0](https://tienda.bricogeek.com/arduino-compatibles/1122-ttgo-lora32-esp32-con-oled-900-mhz.html) y volcar los primeros programas de envío y recepción de datos LoRa.


## Fuente de información 

Buscando en la red programas de envío y recepción de datos usando TTGO LoRa32 OLED V1.0 me he encontrado, entre otros, estos dos:  

[Repositorio YogoGit](https://github.com/YogoGit/TTGO-LORA32-V1.0)

[Repositorio LilyGO](https://github.com/LilyGO/TTGO-LORA32-V2.0/tree/LilyGO-868-V1.0)  


## Pasos

Siguiendo como referencia el repositorio de YogoGit, traslade ese código a un nuevo proyecto realizado con Visual Studio Code y PlatformIO.

![Visual Studio Code con PlatformIO](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRa/TTGO_LoRa32_OLED_V1.0/Img/Cap_01.png)


### Instalación de las librerías 

[ThingPulse ESP8266 OLED SSD1306](https://github.com/ThingPulse/esp8266-oled-ssd1306)

![Libreria Oled](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRa/TTGO_LoRa32_OLED_V1.0/Img/Cap_03.png)


[Arduino LoRa](https://github.com/sandeepmistry/arduino-LoRa)

![libreria LoRA](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRa/TTGO_LoRa32_OLED_V1.0/Img/Cap_04.png)


### Primeras pruebas con ejemplos de la librería Oled 

Primero envié a la placa unos ejemplos de la librería Oled para comprobar que todo funcionaba correctamente. 

![Test Oled](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRa/TTGO_LoRa32_OLED_V1.0/Img/Cap_07.png)


### Programa receptor 

Cree un proyecto en PlatformIO para esa placa de desarrollo y use el código [receptor](https://github.com/YogoGit/TTGO-LORA32-V1.0/tree/master/Receiver) del repositorio de YogoGit, cambiando tan solo la frecuencia a 868. 
![Crear receptor](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRa/TTGO_LoRa32_OLED_V1.0/Img/Cap_02.png)  

![Build receptor](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRa/TTGO_LoRa32_OLED_V1.0/Img/Cap_05.png)


### Programa transmisor

Cree un proyecto en PlatformIO para esa placa de desarrollo y use el código [transmisor](https://github.com/YogoGit/TTGO-LORA32-V1.0/tree/master/Transmitter) del repositorio de YogoGit, cambiando tan solo la frecuencia a 868.  

![Crear transmisor](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRa/TTGO_LoRa32_OLED_V1.0/Img/Cap_08.png)  

![Build receptor](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRa/TTGO_LoRa32_OLED_V1.0/Img/Cap_06.png)  


¡Todo funcionó a la primera!  






















