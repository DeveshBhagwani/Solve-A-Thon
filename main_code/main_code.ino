#include <SPI.h>
#include <MFRC522.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WiFiClient client;
const char* ssid = "VITC-PGM";
const char* password = "Pgm%$0910";
const char* serverName = "http://teamyatharth.000webhostapp.com//post-data.php";
String apiKeyValue = "6766";
String sensorName = "RFID sensor";
String sensorLocation = "Health centre";
#define SS_PIN D2
#define RST_PIN D1
MFRC522 mfrc522(SS_PIN, RST_PIN);  
String id, name,ad;

// --------------------------------------------------------------------
// --------------------------------------------------------------------
void setup() {
  Serial.begin(9600); 
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Kindly place ID: ");
  Serial.println();
  WiFi.begin(ssid, password);
  Serial.println("Connecting to the Wifi Network");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi is Connected at this IP Address : ");
  Serial.println(WiFi.localIP());
}
// --------------------------------------------------------------------
void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  if ( ! mfrc522.PICC_ReadCardSerial()) return;
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();

  if (content.substring(1) == "83 85 93 04"){//yadav_ji
    id = "headache";
    name = "kombiflame";
    ad = "none";
  }
  if (content.substring(1) == "EF 82 EE 19"){//Ujjwal
    id = "dengue";
    name = "hospitalisation";
    ad = "hives";
  }
  if (content.substring(1) == "31 0A 99 F0"){//kshitij
    id = "cough";
    name = "strepsil";
    ad = "warm water";
  }
  if (content.substring(1) == "93 F9 C1 03"){//Ishitva
    id = "none";
    name = "none";
    ad = "none";
  }
  if (content.substring(1) == "81 1D 9A DF"){//devesh
    id = "mild fever";
    name = "none";
    ad = "bed rest";
  }
//id-->past history
//name-->allergy
//ad-->advice
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin(client,serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    Serial.println(id);
    // Prepare HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&SensorData=" + sensorName + "&LocationData=" + sensorLocation + "&Past_History=" + id + "&Allergy=" + name + "&Advice=" + ad ;
     //String httpRequestData ="api_key=#54321&SensorData=distance sensor&LocationData=Aicpecf-office&value1=NULL&value2=NULL&value3=NULL";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData); 
    int httpResponseCode = http.POST(httpRequestData); 
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    } 
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  delay(1000);  

}

// --------------------------------------------------------------------