#include "LoRaWan_APP.h"
#include "Arduino.h"

/*
 * set LoraWan_RGB to Active,the RGB active in loraWan
 * RGB red means sending;
 * RGB purple means joined done;
 * RGB blue means RxWindow1;
 * RGB yellow means RxWindow2;
 * RGB green means received done;
 */

/*LoraWan Class*/
DeviceClass_t  CLASS=LORAWAN_CLASS;
/*OTAA or ABP*/
bool OVER_THE_AIR_ACTIVATION = LORAWAN_NETMODE;
/*ADR enable*/
bool LORAWAN_ADR_ON = LORAWAN_ADR;
/* set LORAWAN_Net_Reserve ON, the node could save the network info to flash, when node reset not need to join again */
bool KeepNet = LORAWAN_Net_Reserve;
/*LoraWan REGION*/
LoRaMacRegion_t REGION = ACTIVE_REGION;

/* Indicates if the node is sending confirmed or unconfirmed messages */
bool IsTxConfirmed = true;
/*!
* Number of trials to transmit the frame, if the LoRaMAC layer did not
* receive an acknowledgment. The MAC performs a datarate adaptation,
* according to the LoRaWAN Specification V1.0.2, chapter 18.4, according
* to the following table:
*
* Transmission nb | Data Rate
* ----------------|-----------
* 1 (first)       | DR
* 2               | DR
* 3               | max(DR-1,0)
* 4               | max(DR-1,0)
* 5               | max(DR-2,0)
* 6               | max(DR-2,0)
* 7               | max(DR-3,0)
* 8               | max(DR-3,0)
*
* Note, that if NbTrials is set to 1 or 2, the MAC will not decrease
* the datarate, in case the LoRaMAC layer did not receive an acknowledgment
*/
uint8_t ConfirmedNbTrials = 8;

/* Application port */
uint8_t AppPort = 2;

/*the application data transmission duty cycle.  value in [ms].*/
uint32_t APP_TX_DUTYCYCLE = 15000;

/* Prepares the payload of the frame */
static void PrepareTxFrame( uint8_t port )
{
    AppDataSize = 4;//AppDataSize max value is 64
    AppData[0] = 0x00;
    AppData[1] = 0x01;
    AppData[2] = 0x02;
    AppData[3] = 0x03;
}


void setup() {
    BoardInitMcu();
    Serial.begin(115200);
#if(AT_SUPPORT)
    Enable_AT();
#endif
    DeviceState = DEVICE_STATE_INIT;
    LoRaWAN.Ifskipjoin();
}

void loop()
{
	switch( DeviceState )
	{
		case DEVICE_STATE_INIT:
		{
#if(AT_SUPPORT)
      getDevParam();
#endif
			printDevParam();
			Serial.printf("LoRaWan Class%X  start! \r\n",CLASS+10);   
			LoRaWAN.Init(CLASS,REGION);
			DeviceState = DEVICE_STATE_JOIN;
			break;
		}
		case DEVICE_STATE_JOIN:
		{
			LoRaWAN.Join();
			break;
		}
		case DEVICE_STATE_SEND:
		{
			PrepareTxFrame( AppPort );
			LoRaWAN.Send();
			DeviceState = DEVICE_STATE_CYCLE;
			break;
		}
		case DEVICE_STATE_CYCLE:
		{
			// Schedule next packet transmission
			TxDutyCycleTime = APP_TX_DUTYCYCLE + randr( 0, APP_TX_DUTYCYCLE_RND );
			LoRaWAN.Cycle(TxDutyCycleTime);
			DeviceState = DEVICE_STATE_SLEEP;
			break;
		}
		case DEVICE_STATE_SLEEP:
		{
			LoRaWAN.Sleep();
			break;
		}
		default:
		{
			DeviceState = DEVICE_STATE_INIT;
			break;
		}
	}
}
