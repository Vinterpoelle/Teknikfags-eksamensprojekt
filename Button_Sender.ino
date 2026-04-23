#include <esp_now.h>
#include <WiFi.h>

//Recieverens MAC addresse
uint8_t broadcastAddress[] = {0x88,0x57,0x21,0x79,0x94,0x74};

//Knappernes pin-setup
int buttonPin1 = 23; //Kan ændres ift. hvilken pin
int buttonPin2 = 19; //Kan ændres ift. hvilken pin
int buttonPin3 = 35; //Kan ændres ift. hvilken pin
int buttonPin4 = 26; //Kan ændres ift. hvilken pin
int buttonPin5 = 21; //Kan ændres ift. hvilken pin

//Struktur med variabler til at holde knappernes data
typedef struct struct_message {
  int button1Data = 0;
  int button2Data = 0;
  int button3Data = 0;
  int button4Data = 0;
  int button5Data = 0;
} struct_message;

//Struktur med variablerne, der holder det senest gemte data samt id, der kan sendes 
typedef struct struct_message2 {
  int id; //Den er unik for hver sender med ESP NOW
  int button1Data = 0;
  int button2Data = 0;
  int button3Data = 0;
  int button4Data = 0;
  int button5Data = 0;
} struct_message2;

//Strukturen bliver gemt i variablen myData
struct_message myData;
struct_message2 previousState;

bool start = 1;

//Laver variabel til at gemme paringsenhedens data
esp_now_peer_info_t peerInfo;

//Callback funktion når data er sendt, som giver besked om det lykkedes eller ej
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  //Initialiser Serial Monitor
  Serial.begin(115200);

  //Sæt den som en Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Knapperne sat til at være INPUTS_PULLUP
  pinMode(buttonPin1,INPUT_PULLUP);
  pinMode(buttonPin2,INPUT_PULLUP);
  pinMode(buttonPin3,INPUT_PULLUP);
  pinMode(buttonPin4,INPUT_PULLUP);
  pinMode(buttonPin5,INPUT_PULLUP);

  //Initialiser ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //Når ESP-NOW er successfuldt initialiseret, registrer callback funktionen, der sendes
  esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));
  
  //Registrer paringsenheden
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  //Tilføj paringsenheden, så det er den reciever, der bliver parret med
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  //Det der sendes
  previousState.id = 2; //Ændre til hvilken sender det er. Det er enten 1 eller 2

  //Ved startup, gem et sæt data af knappernes status
  if(start == 1) {
    previousState.button1Data = digitalRead(buttonPin1);
    previousState.button2Data = digitalRead(buttonPin2);
    previousState.button3Data = digitalRead(buttonPin3);
    previousState.button4Data = digitalRead(buttonPin4);
    previousState.button5Data = digitalRead(buttonPin5);
    
    start = 0; //Sørg for det ikke gentages ved at lave start til false
    }

  //Læs nye data fra knapperne konstant
  myData.button1Data = digitalRead(buttonPin1);
  myData.button2Data = digitalRead(buttonPin2);
  myData.button3Data = digitalRead(buttonPin3);
  myData.button4Data = digitalRead(buttonPin4);
  myData.button5Data = digitalRead(buttonPin5);

  //Tjek om der sker en ændring af knappernes status og gem det
  if(myData.button1Data != previousState.button1Data || myData.button2Data != previousState.button2Data || myData.button3Data != previousState.button3Data || myData.button4Data != previousState.button4Data || myData.button5Data != previousState.button5Data) {
    previousState.button1Data = myData.button1Data;
    previousState.button2Data = myData.button2Data;
    previousState.button3Data = myData.button3Data;
    previousState.button4Data = myData.button4Data;
    previousState.button5Data = myData.button5Data;

   //Print gemt data i egen konsol
   Serial.print(previousState.button1Data);
   Serial.print(",");
   Serial.print(previousState.button2Data);
   Serial.print(" ");
   Serial.print(previousState.button3Data);
   Serial.print(",");
   Serial.print(previousState.button4Data);
   Serial.print(" ");
   Serial.print(previousState.button5Data);
   Serial.print(" ");
    
    //Send beskeden med gemt data via ESP NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &previousState, sizeof(previousState));

    if (result == ESP_OK) {
    Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }

    delay(50);
  }
}
