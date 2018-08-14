

#include <SPI.h>
#include <LoRa.h>
/*
 * IO assignment on board LoraSpectre 201808_1.0
 * Test receiving node
 * Use lib https://github.com/sandeepmistry/arduino-LoRa
 */
// Led
#define LED1      2    // GPIO2, GREEN
#define LED2      15    // GPIO15, BLUE

// Button
#define BTN       39    // SENSOR_VN / GPIO39 / Input only

// Speaker
#define SPK       32    // GPIO32

// USB RESET
#define CP2012_RST    33

// SHT1x
#define SHT_SCK       23
#define SHT_DATA      22

// SPI Lora
#define LORA_RST      13
#define LORA_SS       14
#define LORA_MOSI     27
#define LORA_MISO     26
#define LORA_SCK      25
#define LORA_DIO012   12

int freq = 2400;
int channel = 0;
int resolution = 8;

void setup() {
    Serial.begin(115200);

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(BTN, INPUT);
    
    // init speaker
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(SPK, channel);
    
    Serial.printf("Raw Lora Receiver!\n");
    
    // test Leds, flash leds in 10s
    for(uint8_t i=0; i<10; i++) {
      if(i%2) {
        digitalWrite(LED1, !digitalRead(LED1));
      } else {
        digitalWrite(LED2, !digitalRead(LED2));
      }
      delay(300);
    }

    // test SPK
    ledcWriteTone(channel, 2400);
    delay(1000);
    ledcWrite(channel, 0);

    // setting SPI
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
    if (!LoRa.begin(433E6)) {
      Serial.println("Starting LoRa failed!");
      while (1);
    }
    LoRa.setSpreadingFactor(12);
    LoRa.setSignalBandwidth(125E3);
    LoRa.setCodingRate4(5);
    LoRa.setPreambleLength(8);
    LoRa.enableCrc();
}

void loop() {
   // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet:");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("\nRSSI: ");
    Serial.println(LoRa.packetRssi());
    
    digitalWrite(LED1, HIGH);   // OFF
    ledcWrite(channel, 127);
    delay(80);
    digitalWrite(LED1, LOW);    // ON
    ledcWrite(channel, 0);
  }
  
}

