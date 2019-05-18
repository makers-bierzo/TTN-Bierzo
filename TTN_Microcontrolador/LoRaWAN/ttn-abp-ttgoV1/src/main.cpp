#include <Arduino.h>

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <U8x8lib.h>

#define SINGLE_CHANNEL 1 // Set to 1 to force single channel node

// the OLED used
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8 (/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);

// LoRaWAN
// LoRaWAN NwkSKey, network session key
// This is the default Semtech key, which is used by the early prototype TTN
// network.
// Change this address for every node!
static const PROGMEM u1_t NWKSKEY[16] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

// LoRaWAN AppSKey, application session key
// This is the default Semtech key, which is used by the early prototype TTN
// network.
// Change this address for every node!
static const u1_t PROGMEM APPSKEY[16] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

// LoRaWAN end-device address (DevAddr)
static const u4_t DEVADDR = 0xFFFFFFFF; // <-- Change this address for every node!

// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

static uint8_t mydata[] = "Hello, world!";
static osjob_t sendjob;

// Schedule TX every this many seconds (might become longer due to duty
// cycle limitations).
const unsigned TX_INTERVAL = 300;

// Pin mapping for TTGO ESP32 v1
const lmic_pinmap lmic_pins = {
	.nss = 18,
	.rxtx = LMIC_UNUSED_PIN,
	.rst = 14,
	.dio = {/*dio0*/ 26, /*dio1*/ 33, /*dio2*/ 32 }
};

void do_send (osjob_t* j) {
	// Check if there is not a current TX/RX job running
	if (LMIC.opmode & OP_TXRXPEND) {
		Serial.println (F ("OP_TXRXPEND, not sending"));
		u8x8.drawString (0, 7, "OP_TXRXPEND, not sent");
	}
	else {
		// Prepare upstream data transmission at the next possible time.
		LMIC_setTxData2 (1, mydata, sizeof (mydata) - 1, 0);
		Serial.println (F ("Packet queued"));
		u8x8.drawString (0, 7, "PACKET QUEUED");
	}
	// Next TX is scheduled after TX_COMPLETE event.
}


void onEvent (ev_t ev) {
	Serial.print (os_getTime ());
	Serial.print (": ");

	u8x8.setCursor (0, 3);
	u8x8.printf ("%0x", LMIC.devaddr);
	u8x8.setCursor (0, 5);
	u8x8.printf ("TIME %lu", os_getTime ());

	switch (ev) {
	case EV_SCAN_TIMEOUT:
		Serial.println (F ("EV_SCAN_TIMEOUT"));
		u8x8.drawString (0, 7, "EV_SCAN_TIMEOUT");
		break;
	case EV_BEACON_FOUND:
		Serial.println (F ("EV_BEACON_FOUND"));
		u8x8.drawString (0, 7, "EV_BEACON_FOUND");
		break;
	case EV_BEACON_MISSED:
		Serial.println (F ("EV_BEACON_MISSED"));
		u8x8.drawString (0, 7, "EV_BEACON_MISSED");
		break;
	case EV_BEACON_TRACKED:
		Serial.println (F ("EV_BEACON_TRACKED"));
		u8x8.drawString (0, 7, "EV_BEACON_TRACKED");
		break;
	case EV_JOINING:
		Serial.println (F ("EV_JOINING"));
		u8x8.drawString (0, 7, "EV_JOINING    ");
		break;
	case EV_JOINED:
		Serial.println (F ("EV_JOINED"));
		u8x8.drawString (0, 7, "EV_JOINED     ");
		break;
	case EV_RFU1:
		Serial.println (F ("EV_RFU1"));
		u8x8.drawString (0, 7, "EV_RFUI");
		break;
	case EV_JOIN_FAILED:
		Serial.println (F ("EV_JOIN_FAILED"));
		u8x8.drawString (0, 7, "EV_JOIN_FAILED");
		break;
	case EV_REJOIN_FAILED:
		Serial.println (F ("EV_REJOIN_FAILED"));
		u8x8.drawString (0, 7, "EV_REJOIN_FAILED");
		break;
	case EV_TXCOMPLETE:
		Serial.println (F ("EV_TXCOMPLETE (includes waiting for RX windows)"));
		u8x8.drawString (0, 7, "EV_TXCOMPLETE");
		if (LMIC.txrxFlags & TXRX_ACK) {
			Serial.println (F ("Received ack"));
			u8x8.drawString (0, 7, "Received ACK");
		}
		if (LMIC.dataLen) {
			Serial.println (F ("Received "));
			Serial.println (LMIC.dataLen);
			Serial.println (F (" bytes of payload"));
			u8x8.drawString (0, 6, "RX ");
			u8x8.setCursor (4, 6);
			u8x8.printf ("%i bytes", LMIC.dataLen);
			u8x8.setCursor (0, 7);
			u8x8.printf ("RSSI %d SNR %.1d", LMIC.rssi, LMIC.snr);
		}
		// Schedule next transmission
		os_setTimedCallback (&sendjob, os_getTime () + sec2osticks (TX_INTERVAL), do_send);
		break;
	case EV_LOST_TSYNC:
		Serial.println (F ("EV_LOST_TSYNC"));
		u8x8.drawString (0, 7, "EV_LOST_TSYNC");
		break;
	case EV_RESET:
		Serial.println (F ("EV_RESET"));
		u8x8.drawString (0, 7, "EV_RESET");
		break;
	case EV_RXCOMPLETE:
		// data received in ping slot
		Serial.println (F ("EV_RXCOMPLETE"));
		u8x8.drawString (0, 7, "EV_RXCOMPLETE");
		break;
	case EV_LINK_DEAD:
		Serial.println (F ("EV_LINK_DEAD"));
		u8x8.drawString (0, 7, "EV_LINK_DEAD");
		break;
	case EV_LINK_ALIVE:
		Serial.println (F ("EV_LINK_ALIVE"));
		u8x8.drawString (0, 7, "EV_LINK_ALIVE");
		break;
	default:
		Serial.println (F ("Unknown event"));
		u8x8.setCursor (0, 7);
		u8x8.printf ("UNKNOWN EVENT %d", ev);
		break;
	}
}


void setup () {
	Serial.begin (115200);
	Serial.println (F ("Starting"));
	u8x8.begin ();
	u8x8.setFont (u8x8_font_chroma48medium8_r);
	u8x8.drawString (0, 1, "LoRaWAN LMiC");

	// LMIC init
	os_init ();
	// Reset the MAC state. Session and pending data transfers will be discarded.
	LMIC_reset ();

	// Set static session parameters. Instead of dynamically establishing a session
	// by joining the network, precomputed session parameters are be provided.
#ifdef PROGMEM
// On AVR, these values are stored in flash and only copied to RAM
// once. Copy them to a temporary buffer here, LMIC_setSession will
// copy them into a buffer of its own again.
	uint8_t appskey[sizeof (APPSKEY)];
	uint8_t nwkskey[sizeof (NWKSKEY)];
	memcpy_P (appskey, APPSKEY, sizeof (APPSKEY));
	memcpy_P (nwkskey, NWKSKEY, sizeof (NWKSKEY));
	LMIC_setSession (0x13, DEVADDR, nwkskey, appskey);
#else
// If not running an AVR with PROGMEM, just use the arrays directly
	LMIC_setSession (0x13, DEVADDR, NWKSKEY, APPSKEY);
#endif

#if defined(CFG_eu868)
	// Set up the channels used by the Things Network, which corresponds
	// to the defaults of most gateways. Without this, only three base
	// channels from the LoRaWAN specification are used, which certainly
	// works, so it is good for debugging, but can overload those
	// frequencies, so be sure to configure the full frequency range of
	// your network here (unless your network autoconfigures them).
	// Setting up channels should happen after LMIC_setSession, as that
	// configures the minimal channel set.
#if SINGLE_CHANNEL == 1
	LMIC_setupChannel (0, 868100000, DR_RANGE_MAP (DR_SF12, DR_SF7), BAND_CENTI);      // g-band
	LMIC_setupChannel (1, 868100000, DR_RANGE_MAP (DR_SF12, DR_SF7), BAND_CENTI);      // g-band
	LMIC_setupChannel (2, 868100000, DR_RANGE_MAP (DR_SF12, DR_SF7), BAND_CENTI);      // g-band
	LMIC_setupChannel (3, 868100000, DR_RANGE_MAP (DR_SF12, DR_SF7), BAND_CENTI);      // g-band
	LMIC_setupChannel (4, 868100000, DR_RANGE_MAP (DR_SF12, DR_SF7), BAND_CENTI);      // g-band
	LMIC_setupChannel (5, 868100000, DR_RANGE_MAP (DR_SF12, DR_SF7), BAND_CENTI);      // g-band
	LMIC_setupChannel (6, 868100000, DR_RANGE_MAP (DR_SF12, DR_SF7), BAND_CENTI);      // g-band
	LMIC_setupChannel (7, 868100000, DR_RANGE_MAP (DR_SF12, DR_SF7), BAND_CENTI);      // g-band
	LMIC_setupChannel (8, 868100000, DR_RANGE_MAP (DR_SF12, DR_SF7), BAND_CENTI);      // g2-band
#else
	LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
	LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band
	// TTN defines an additional channel at 869.525Mhz using SF9 for class B
	// devices' ping slots. LMIC does not have an easy way to define set this
	// frequency and support for class B is spotty and untested, so this
	// frequency is not configured here.
#endif //SINGLE_CHANNEL
#elif defined(CFG_us915)
	// NA-US channels 0-71 are configured automatically
	// but only one group of 8 should (a subband) should be active
	// TTN recommends the second sub band, 1 in a zero based count.
	// https://github.com/TheThingsNetwork/gateway-conf/blob/master/US-global_conf.json
	LMIC_selectSubBand (1);
#endif

	// Disable link check validation
	LMIC_setLinkCheckMode (0);

	// TTN uses SF9 for its RX2 window.
	LMIC.dn2Dr = DR_SF9;

	// Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
	LMIC_setDrTxpow (DR_SF7, 14);

	// Start job
	do_send (&sendjob);
}

void loop () {
	os_runloop_once ();
}
