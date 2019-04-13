# Primeros pasos con LoRA


Para todos los programas voy a usar Visual Studio Code con PlatformIO y el hardware del que dispongo actualmente es TTGO LoRa32 OLED V1.0 y TTGO LoRa32 OLED V2.0. 

Intentaré volcar software de conexión punto a punto en cada una de las versiones de placas. 

## Instalación de librerías en PlatformIO

En todos los programas que otros compañeros comparten para la comunicación Punto a Punto con LoRa, se usan librerias.  

Concretamente en este caso necesito librerias para manejar el Oled y LoRa, por eso, voy a documentar las diversas formas de instalar librerias en platformio.  

Toda la documentación está en la página oficial de platformio. 
https://docs.platformio.org/en/latest/librarymanager/index.html

El proceso es muy sencillo usando el entorno grafico cuando la libreria que buscas aparece en los resultados de la busqueda. Pero que sucede si queremos instalar una libreria que no aparece en los resultados:

Para esto podemos usar la linea de comandos (CLI) con los que podremos realizar instrucciones más avanzadas.
https://docs.platformio.org/en/latest/userguide/lib/index.html

Los comandos relacionados con la gestión de librerias son:  

platformio lib builtin  
platformio lib install  
platformio lib list  
platformio lib register  
platformio lib search  
platformio lib show  
platformio lib stats  
platformio lib uninstall  
platformio lib update  


El que me interesa en este momento es el comando platformio lib install:
https://docs.platformio.org/en/latest/userguide/lib/cmd_install.html#usage  

Aquí se explica como se pueden instalar librerías de otras maneras. 


## Fuentes de información 

Todo empezo con  

Blog de Bricolabs
https://bricolabs.cc/wiki/guias/lora_ttn  

Blog de Akirasan  
http://akirasan.net/tag/lora/  
https://github.com/osresearch/esp32-ttgo


https://github.com/YogoGit/TTGO-LORA32-V1.0  

https://github.com/LilyGO/TTGO-LORA32-V2.0/tree/LilyGO-868-V1.0  

https://github.com/LilyGO/TTGO-LORA32-V2.0  


Siéntanse libres de probar otras opciones, aquí dejo el enlace a otras opciones:  

Biblioman09  
https://github.com/CaptIgmu/Arduino/tree/master/esp32/TTGO_LoRa32_OLED  
https://github.com/olikraus/U8g2_Arduino


