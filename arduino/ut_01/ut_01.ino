

/*
 * IO assignment on board LoraSpectre 201808_r1.0
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
    delay(1000);

    // speaker
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(SPK, channel);
    

    Serial.printf("Start testing...\n");
    
    // flash leds in 10s
    for(uint8_t i=0; i<10; i++) {
      if(i%2) {
        digitalWrite(LED1, !digitalRead(LED1));
      } else {
        digitalWrite(LED2, !digitalRead(LED2));
      }
      delay(500);
      Serial.printf("Testing...\n");
    }

    
    ledcWriteTone(channel, 2400);
    delay(2000);
    ledcWrite(channel, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BTN) == LOW) {
    digitalWrite(LED1, !digitalRead(LED1));
    ledcWrite(channel, 127);
    delay(50);
    ledcWrite(channel, 0);
  }
  delay(300);
  digitalWrite(LED2, !digitalRead(LED2));

}

