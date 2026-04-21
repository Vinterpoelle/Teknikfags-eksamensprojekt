#include <esp_now.h>
#include <WiFi.h>

//Recieverens MAC addresse
uint8_t broadcastAddress[] = {0x88,0x57,0x21,0x79,0x94,0x74};

//Knappernes pin-setup
int buttonPin1 = 23;
int buttonPin2 = 19;
int buttonPin3 = 35;
int buttonPin4 = 26;
int buttonPin5 = 21;

//Struktur med variabler, der kan sendes til recieveren
typedef struct struct_message {
    int id; //Den er unik for hver sender med ESP NOW
    int button1Data = 0;
    int button2Data = 0;
    int button3Data = 0;
    int button4Data = 0;
    int button5Data = 0;
} struct_message;

//Strukturen bliver gemt i variablen myData
struct_message myData;

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

  //Knapperne sat til at være INPUTS
  pinMode(buttonPin1,INPUT_PULLUP);
  pinMode(buttonPin2,INPUT_PULLUP);
  pinMode(buttonPin3,INPUT);
  pinMode(buttonPin4,INPUT_PULLUP);
  pinMode(buttonPin5,INPUT_PULLUP);

  //Initialiser ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //Når ESP NOW er successfuldt initialiseret, registrer callback funktionen, der sendes
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
  myData.id = 2;
  myData.button1Data = digitalRead(buttonPin1);
  myData.button2Data = digitalRead(buttonPin2);
  myData.button3Data = digitalRead(buttonPin3);
  myData.button4Data = digitalRead(buttonPin4);
  myData.button5Data = digitalRead(buttonPin5);

  //Send beskeden via ESP NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
   //Print data i egen konsol
   Serial.print(myData.button1Data);
   Serial.print(",");
   Serial.print(myData.button2Data);
   Serial.print(" ");
   Serial.print(myData.button3Data);
   Serial.print(",");
   Serial.print(myData.button4Data);
   Serial.print(" ");
   Serial.print(myData.button5Data);
   Serial.print(" ");

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(1000);
}
