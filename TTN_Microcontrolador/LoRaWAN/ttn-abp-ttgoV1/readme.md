# Nodo ABP en TTGO LORA32 OLED V1

## Descripción 

Este código forma parte de las primeras pruebas para crear un nodo ABP(Activation-by-personalisation) que se conecte a [The Things Network](https://www.thethingsnetwork.org/) para enviar un mensaje.

Se ha adaptado el ejemplo [ttn-abp](https://github.com/matthijskooijman/arduino-lmic/blob/master/examples/ttn-abp/ttn-abp.ino) de la librería [lmic library](https://github.com/matthijskooijman/arduino-lmic) para que funcione en una placa TTGO LoRa32 Oled V1 usando PlatformIO en Visual Studio Code. 

De momento esta pensado para transmitir datos a un Gateway de un solo canal.

La librería está muy bien documentada y se recomienda leerla detenidamente para comprender su uso. 

También ha sido de gran ayuda el repositorio de [Germán Martín](https://github.com/gmag11/thethingnetwork_madrid_taller_gateway_nodo_single_channel/tree/master/Nodo/TTGO_ESP32_v1/ttn-abp)


## Resultado

![code_abp_v1](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRaWAN/img/code_abp_v1.png)

![ttn_abp_v1](https://raw.githubusercontent.com/makers-bierzo/TTN-Bierzo/master/TTN_Microcontrolador/LoRaWAN/img/ttn_abp_v1.png)


