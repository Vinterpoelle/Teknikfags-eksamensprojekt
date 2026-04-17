#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "noooo";
const char* password = "nononononono";

const char* serverNameConsole1 = "http://192.168.4.1/Server1";

#define PIN       5
#define NUMPIXELS 17
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

String console1;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(115200);

  //Tjek om lyset overhovedet tænder
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(128, 0, 0));
  pixels.show();
  delay(2000);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval) {

     //Tjek WiFi forbindelses status
    if(WiFi.status()== WL_CONNECTED ){ 
      console1 = httpGETRequest(serverNameConsole1); //Hvis der er en besked, så print den
      Serial.println("Console1 Data: " + console1);
      
      //Gem den seneste HTTP GET anmodning
      previousMillis = currentMillis;
    } 
    else {
      Serial.println("WiFi Disconnected");
    }
  }

  if(console1.indexOf( "Button 1: 1") >= 0) button1();
  if(console1.indexOf( "Button 2: 1") >= 0) button2();
  if(console1.indexOf( "Button 3: 1") >= 0) button3();
  if(console1.indexOf( "Button 4: 1") >= 0) button4();
  if(console1.indexOf( "Button 5: 1") >= 0) button5();
}

void setColour(uint8_t r,uint8_t g, uint8_t b){
  for(int i=0; i<NUMPIXELS; i++) { //For hver pixel...
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
}

String httpGETRequest(const char* serverName) {
  HTTPClient http;
    
  http.begin(serverName);
  
  //Send HTTP anmodning
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if(httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  //Free resources
  http.end();

  return payload;
}

void button1(){
  //Tændt 2,4,8,12,15
  pixels.setPixelColor(4, pixels.Color(128, 0, 0));
  pixels.setPixelColor(2, pixels.Color(128, 0, 0));
  pixels.setPixelColor(8, pixels.Color(128, 0, 0));
  pixels.setPixelColor(15, pixels.Color(128, 0, 0));
  pixels.setPixelColor(12, pixels.Color(128, 0, 0));

  //Slukket 11,16
  pixels.setPixelColor(11, pixels.Color(0, 0, 0));
  pixels.setPixelColor(16, pixels.Color(0, 0, 0));

  pixels.show();
}
void button2(){
  //Tænder 0,1,9,14
  pixels.setPixelColor(0, pixels.Color(128, 0, 0));
  pixels.setPixelColor(1, pixels.Color(128, 0, 0));
  pixels.setPixelColor(14, pixels.Color(128, 0, 0));
  pixels.setPixelColor(9, pixels.Color(128, 0, 0));

  //Slukker 4,16
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(16, pixels.Color(0, 0, 0));

  pixels.show();
}
void button3(){
  //Tænder 1,7,10,14
  pixels.setPixelColor(1, pixels.Color(128, 0, 0));
  pixels.setPixelColor(10, pixels.Color(128, 0, 0));
  pixels.setPixelColor(14, pixels.Color(128, 0, 0));
   pixels.setPixelColor(7, pixels.Color(128, 0, 0));

  //Slukker 9,11,12,15
  pixels.setPixelColor(9, pixels.Color(0, 0, 0));
  pixels.setPixelColor(11, pixels.Color(0, 0, 0));
  pixels.setPixelColor(15, pixels.Color(0, 0, 0));
  pixels.setPixelColor(12, pixels.Color(0, 0, 0));

  pixels.show();
}
void button4(){
  //Tænder 6,9,12,13,16
  pixels.setPixelColor(9, pixels.Color(128, 0, 0));
  pixels.setPixelColor(16, pixels.Color(128, 0, 0));
  pixels.setPixelColor(13, pixels.Color(128, 0, 0));
  pixels.setPixelColor(6, pixels.Color(128, 0, 0));
  pixels.setPixelColor(12, pixels.Color(128, 0, 0));

  //Slukker 1,5,7,8,11
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(11, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));

  pixels.show();
}
void button5(){
  //Tænder 3,5,15,16,11
  pixels.setPixelColor(3, pixels.Color(128, 0, 0));
  pixels.setPixelColor(5, pixels.Color(128, 0, 0));
  pixels.setPixelColor(15, pixels.Color(128, 0, 0));
  pixels.setPixelColor(16, pixels.Color(128, 0, 0));
  pixels.setPixelColor(11, pixels.Color(128, 0, 0));

  pixels.show();
}
