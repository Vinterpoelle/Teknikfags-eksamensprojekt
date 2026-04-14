#include <Adafruit_NeoPixel.h>
#define PIN        6
#define NUMPIXELS 17
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 
int buttonPin=2;
int buttonPin2=4;
int buttonPin3=5;
int buttonPin4=7;
int buttonPin5=8;
int buttonPin6Restart=3;

 
void setup() {
  pixels.begin();
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(buttonPin2,INPUT_PULLUP);
  pinMode(buttonPin3,INPUT_PULLUP);
  pinMode(buttonPin4,INPUT_PULLUP);
  pinMode(buttonPin5,INPUT_PULLUP);
  pinMode(buttonPin6Restart,INPUT_PULLUP);
}
 
void loop() {
  //If button pin is LOW -> Button is pressed.. maybe it's high?
  if(digitalRead(buttonPin)==HIGH) knap1();//setColour(255,0,0);
  if(digitalRead(buttonPin2)==HIGH) knap2();//setColour(255,0,0);
  if(digitalRead(buttonPin3)==HIGH) knap3();//setColour(255,0,0);
  if(digitalRead(buttonPin4)==HIGH) knap4();//setColour(255,0,0);
  if(digitalRead(buttonPin5)==HIGH) knap5();//setColour(255,0,0);
  if(digitalRead(buttonPin6Restart)==HIGH) knapRestart();//setColour(255,0,0);
  pixels.show();

  }
 
void setColour(uint8_t r,uint8_t g, uint8_t b){
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
 
 
}

//løsning 4,3,2,1,5
void knap1(){
  //tænt 2,4,8,12,15
  pixels.setPixelColor(4, pixels.Color(128, 0, 0));
  pixels.setPixelColor(2, pixels.Color(128, 0, 0));
  pixels.setPixelColor(8, pixels.Color(128, 0, 0));
  pixels.setPixelColor(15, pixels.Color(128, 0, 0));
  pixels.setPixelColor(12, pixels.Color(128, 0, 0));
  //slukket 11,16
  pixels.setPixelColor(11, pixels.Color(0, 0, 0));
  pixels.setPixelColor(16, pixels.Color(0, 0, 0));
}
void knap2(){
  //tænt 0,1,9,14
  pixels.setPixelColor(0, pixels.Color(128, 0, 0));
  pixels.setPixelColor(1, pixels.Color(128, 0, 0));
  pixels.setPixelColor(14, pixels.Color(128, 0, 0));
  pixels.setPixelColor(9, pixels.Color(128, 0, 0));
  //slukket 4,16
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(16, pixels.Color(0, 0, 0));
}
void knap3(){
  //tænt 1,7,10,14
  pixels.setPixelColor(1, pixels.Color(128, 0, 0));
  pixels.setPixelColor(10, pixels.Color(128, 0, 0));
  pixels.setPixelColor(14, pixels.Color(128, 0, 0));
   pixels.setPixelColor(7, pixels.Color(128, 0, 0));
  // slukket 9,11,12,15
  pixels.setPixelColor(9, pixels.Color(0, 0, 0));
  pixels.setPixelColor(11, pixels.Color(0, 0, 0));
  pixels.setPixelColor(15, pixels.Color(0, 0, 0));
   pixels.setPixelColor(12, pixels.Color(0, 0, 0));
}
void knap4(){
  //tænt 6,9,12,13,16
  pixels.setPixelColor(9, pixels.Color(128, 0, 0));
  pixels.setPixelColor(16, pixels.Color(128, 0, 0));
  pixels.setPixelColor(13, pixels.Color(128, 0, 0));
  pixels.setPixelColor(6, pixels.Color(128, 0, 0));
  pixels.setPixelColor(12, pixels.Color(128, 0, 0));
  //slukket 1,5,7,8,11
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(11, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
}
void knap5(){
  //tænd 3,5,15,16,11
  pixels.setPixelColor(3, pixels.Color(128, 0, 0));
  pixels.setPixelColor(5, pixels.Color(128, 0, 0));
  pixels.setPixelColor(15, pixels.Color(128, 0, 0));
  pixels.setPixelColor(16, pixels.Color(128, 0, 0));
  pixels.setPixelColor(11, pixels.Color(128, 0, 0));
}

void knapRestart(){
  //tænd 3,5,15,16,11
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(9, pixels.Color(0, 0, 0));
  pixels.setPixelColor(10, pixels.Color(0, 0, 0));
  pixels.setPixelColor(11, pixels.Color(0, 0, 0));
  pixels.setPixelColor(12, pixels.Color(0, 0, 0));
  pixels.setPixelColor(13, pixels.Color(0, 0, 0));
  pixels.setPixelColor(14, pixels.Color(0, 0, 0));
  pixels.setPixelColor(15, pixels.Color(0, 0, 0));
  pixels.setPixelColor(16, pixels.Color(0, 0, 0));
}
