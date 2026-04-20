#include <esp_now.h>
#include <WiFi.h>

//NeoPixel setup
#include <Adafruit_NeoPixel.h>
#define PIN       5
#define NUMPIXELS 17
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Struktur med variabler, den får tilsendt
typedef struct struct_message {
  int id;
  int button1Data = 0;
  int button2Data = 0;
  int button3Data = 0;
  int button4Data = 0;
  int button5Data = 0;
}struct_message;

//Strukturen bliver gemt i variablen myData
struct_message myData;

//Her laves der variabler, som holder data for hver sender
struct_message board1;
struct_message board2;
struct_message board3;

//Laver et array med strukturne
struct_message boardsStruct[3] = {{board1}, {board2}, {board3}};


//Booleans for om knapperne er trykket
bool button1Pressed = 0;
bool button2Pressed = 0;
bool button3Pressed = 0;
bool button4Pressed = 0;
bool button5Pressed = 0;

//Callback funktion der bliver udført når data er modtaget
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.printf("Board ID %u: %u bytes\n", myData.id, len);

  
  //Opdater med det nye data
  boardsStruct[myData.id-1].button1Data = myData.button1Data;
  boardsStruct[myData.id-1].button2Data = myData.button2Data;
  boardsStruct[myData.id-1].button3Data = myData.button3Data;
  boardsStruct[myData.id-1].button4Data = myData.button4Data;
  boardsStruct[myData.id-1].button5Data = myData.button5Data;

  //Print data i konsollen
  Serial.printf("Button 1: %d \n", boardsStruct[myData.id-1].button1Data);
  Serial.printf("Button 2: %d \n", boardsStruct[myData.id-1].button2Data);
  Serial.printf("Button 3: %d \n", boardsStruct[myData.id-1].button3Data);
  Serial.printf("Button 4: %d \n", boardsStruct[myData.id-1].button4Data);
  Serial.printf("Button 5: %d \n", boardsStruct[myData.id-1].button5Data);
  Serial.println();
}
 
void setup() {
  //Initialiser Serial Monitor
  Serial.begin(115200);

  //Initialiser Neopixel
  pixels.begin();

  //Sæt enheden som en Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Initialiser ESP NOW
  if(esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //Registrer en callback funktion, når data er modtaget
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  //Starter med lys slukket
  start();
}
 
void loop() {
  //Variabler for hver boards data
  int board1X = boardsStruct[0].button1Data;
  int board1Y = boardsStruct[0].button2Data;
  int board1Z = boardsStruct[0].button3Data;
  int board1W = boardsStruct[0].button4Data;
  int board1Q = boardsStruct[0].button5Data;
  
  //Tænder lys og giver besked om knappen er trykket, når den er trykkket
  if(board1X == 1 && button1Pressed == 0) {
    button1Pressed = 1;
    button1();
  }

  if(board1Y == 1 && button2Pressed == 0) {
    button2Pressed = 1;
    button2();
  }

  if(board1Z == 1 && button3Pressed == 0) {
    button3Pressed = 1;
    button3();
  }

  if(board1W == 1 && button4Pressed == 0) {
    button4Pressed = 1;
    button4();
  }

  if(board1Q == 1 && button5Pressed == 0) {
    button5Pressed = 1;
    button5();
  }

  //Når knappen slippes, så nulstilles buttonPressed variablen til false
  if(board1X == 0) {
    button1Pressed = 0;
  }

  if(board1Y == 0) {
    button2Pressed = 0;
  }

  if(board1Z == 0) {
    button3Pressed = 0;
  }

  if(board1W == 0) {
    button4Pressed = 0;
  }

  if(board1Q == 0) {
    button5Pressed = 0;
  }
  delay(500);
}

//Registrer alle LED-lys i LED-strippen
void setColour(uint8_t r,uint8_t g, uint8_t b){
  for(int i=0; i<NUMPIXELS; i++) { //For hver pixel...
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
}

//Start funktionen, hvor alle lys er slukket
void start() {
   for(int i=0; i<=16; i++) { //For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
   }
  pixels.show();
}

//Knap 1's funktion
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

//Knap 2's funktion
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

//Knap 3's funktion
void button3(){
  //tændt 1,7,10,14
  pixels.setPixelColor(1, pixels.Color(128, 0, 0));
  pixels.setPixelColor(10, pixels.Color(128, 0, 0));
  pixels.setPixelColor(14, pixels.Color(128, 0, 0));
   pixels.setPixelColor(7, pixels.Color(128, 0, 0));
  // slukket 9,11,12,15
  pixels.setPixelColor(9, pixels.Color(0, 0, 0));
  pixels.setPixelColor(11, pixels.Color(0, 0, 0));
  pixels.setPixelColor(15, pixels.Color(0, 0, 0));
  pixels.setPixelColor(12, pixels.Color(0, 0, 0));

  pixels.show();
}

//Knap 4's funktion
void button4(){
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

  pixels.show();
}

//Knap 5's funktion
void button5(){
  //tænd 3,5,15,16,11
  pixels.setPixelColor(3, pixels.Color(128, 0, 0));
  pixels.setPixelColor(5, pixels.Color(128, 0, 0));
  pixels.setPixelColor(15, pixels.Color(128, 0, 0));
  pixels.setPixelColor(16, pixels.Color(128, 0, 0));
  pixels.setPixelColor(11, pixels.Color(128, 0, 0));

  pixels.show();
}
