# Nodo ABP en TTGO LORA32 OLED V2 con sensor BME280

## Descripción 

Este código forma parte de las primeras pruebas para crear un nodo ABP(Activation-by-personalisation) que se conecte a [The Things Network](https://www.thethingsnetwork.org/) para enviar los datos de un sensor BME280.

Se ha adaptado el ejemplo [ttn-abp](https://github.com/matthijskooijman/arduino-lmic/blob/master/examples/ttn-abp/ttn-abp.ino) de la librería [lmic library](https://github.com/matthijskooijman/arduino-lmic) para que funcione en una placa TTGO LoRa32 Oled V2 usando PlatformIO en Visual Studio Code. 

De momento esta pensado para transmitir datos a un Gateway de un solo canal. 


## Esquema

![esquema_bme280](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRaWAN/img/esq_bme280.png)





## Integración con Thinger.io

Creamos un [DATA BUCKET](http://docs.thinger.io/sigfox/#steps-in-thingerio-create-a-data-bucket) y un [ACCESS TOKEN](http://docs.thinger.io/sigfox/#steps-in-thingerio-create-an-access-token), siguiendo para esto la guia de [Sigfox](http://docs.thinger.io/sigfox/#introduction)


URL es la dirección del endpoint de Thinger, direccionando al usuario y databucket especifico
https://api.thinger.io/v1/users/{user_id}/buckets/{bucket_id}/data

AUTORIZATION es el acceso token creado en Thinger, adicionando al comienzo la palabra clave

Berarer asi:

Bearer {access_token}







