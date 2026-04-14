//WIFI/Server setup
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

//const char* ssid = "Frederiks iPhone(2)";
//const char* password = "DASgruPPEshIt-/1224";

const char* ssid = "noooo";
const char* password = "nononononono";

AsyncWebServer server(80);

//Button setup
int buttonPin = 33;
int buttonPin2 = 21;
int buttonPin3 = 22;
int buttonPin4 = 18;
int buttonPin5 = 5;

int button1Data = 0;
int button2Data = 0;
int button3Data = 0;
int button4Data = 0;
int button5Data = 0;


void setup() {
  Serial.begin(115200);

  //WIFI Accespoint
  Serial.println("Starter Access Point...");
  WiFi.softAP(ssid, password); //Danner et WIFI Accespoint på det givet WIFI

  IPAddress localIP = WiFi.softAPIP(); //Henter IP-adressen fra Accespointet
  Serial.print("AP IP address: ");
  Serial.println(localIP);

  //Knapperne sat til at være INPUTS
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(buttonPin2,INPUT_PULLUP);
  pinMode(buttonPin3,INPUT_PULLUP);
  pinMode(buttonPin4,INPUT_PULLUP);
  pinMode(buttonPin5,INPUT_PULLUP);

  server.on("/Server1", HTTP_GET, [](AsyncWebServerRequest *request){
    String response = 
     "Button 1: " + String(button1Data) + "\n" + 
     "Button 2: " + String(button2Data) + "\n" +
     "Button 3: " + String(button3Data) + "\n" +
     "Button 4: " + String(button4Data) + "\n" +
     "Button 5: " + String(button1Data) + "\n";    

    request->send(200, "text/plain", response);
  });

  server.begin();
}

void loop() {

  //Registrere om knapperne er trykket på
  button1Data = digitalRead(buttonPin);
  button2Data = digitalRead(buttonPin2);
  button3Data = digitalRead(buttonPin3);
  button4Data = digitalRead(buttonPin4);
  button5Data = digitalRead(buttonPin5);

  delay(100);
}
