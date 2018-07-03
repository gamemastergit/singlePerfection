#include <elapsedMillis.h>
elapsedMillis timeElapsed; 
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>


uint8_t scrollSpeed = 25;
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_CENTER;
uint16_t scrollPause = 2000;
#define  BUF_SIZE  75
char curMessage[BUF_SIZE] = { "GO!" };
bool newMessageAvailable = true;

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

#define MAX_DEVICES 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// Hardware SPI connection
//MD_Parola P = MD_Parola(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
// Arbitrary output pins
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


void setup() {
  
P.begin();
pinMode(A2, OUTPUT); //Relay
digitalWrite(A2, LOW); //Set the relay to LOW

pinMode(4, INPUT_PULLUP); //C1
pinMode(5, INPUT_PULLUP); //C2
pinMode(6, INPUT_PULLUP); //C3
pinMode(7, INPUT_PULLUP); //C4
pinMode(8, INPUT_PULLUP); //C5
pinMode(9, INPUT_PULLUP); //C6
pinMode(A1, INPUT_PULLUP); //C7
}
boolean count = false;
char buff[50];
char newbuff[50];
long time=60;
void loop() {
if(P.displayAnimate()){
    delay(100);
    unsigned long interval = 1000;
    long rtime = (long)time-(timeElapsed/interval);
    String stringTime = String(rtime);
    stringTime.toCharArray(buff, 50);
    char* point = buff;

    P.displayText(point, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);

    int go = 0;
    uint8_t pins[7]{4,5,6,7,8,A0,A1};
    for(int x = 0; x < 7; x++){
     int val = digitalRead(pins[x]);
     go += val;
    }
    if(go<1){
    P.displayText("YOU WON!", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    while(true){}
    }
    
    if(rtime < 1){
      digitalWrite(A2, HIGH);
      delay(50);
      digitalWrite(A2, LOW);
  }
  }
  
}
