#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
int buzzPin=8;
int dt1=1;
int dt2=2;
int j;
int light_jalao_pin=7;

void buzzer_bazao() {
  unsigned long startTime = millis();
  while (millis() - startTime <= 1000) {
    digitalWrite(buzzPin, HIGH);
    delay(dt1);
    digitalWrite(buzzPin, LOW);
    delay(dt1);
  }
  digitalWrite(buzzPin, LOW);
}

void light_jalao(){
  digitalWrite(light_jalao_pin, HIGH);
  delay(1000);
  digitalWrite(light_jalao_pin, LOW);
}


void setup(){
  pinMode(buzzPin, OUTPUT);
  pinMode(light_jalao_pin, OUTPUT);
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Kindly place ID card: ");
  Serial.println();
	// lcd.begin();
	// lcd.backlight_jalao();
	// lcd.print("JAI SHREE RAM !");
}

void loop(){
  if ( ! mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()){
    return;
  }
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
  // buzzer_bazao();
  // light_jalao();  


////////////////////////////////////////////////////////////////////////////////////////  

  if(content.substring(1) == "83 85 93 04"){
    buzzer_bazao();
    light_jalao();
    lcd.begin();
	  lcd.backlight();
	  lcd.print("***22BCE1460****");
  }
  if(content.substring(1) == "EF 82 EE 19"){
    buzzer_bazao();
    light_jalao();
    lcd.begin();
	  lcd.backlight();
	  lcd.print("***22BLC1208****");
  }
  if(content.substring(1) == "31 0A 99 F0"){
    buzzer_bazao();
    light_jalao();
    lcd.begin();
	  lcd.backlight();
	  lcd.print("***22BEC1082****");
  }
  if(content.substring(1) == "93 F9 C1 03"){
    buzzer_bazao();
    light_jalao();
    lcd.begin();
	  lcd.backlight();
	  lcd.print("***22BCE1614****");
  }
  if(content.substring(1) == "81 1D 9A DF"){
    buzzer_bazao();
    light_jalao();
    Serial.println("Name: Devesh Kumar Bhagwani");
    Serial.println("Previous illness: Mild fever, headache");
    Serial.println("Prescribed treatment: Paracetamol tablet 3 times a day followed by bedrest");
    lcd.begin();
	  lcd.backlight();
	  lcd.print("***22BLC1160****");
  }
  //digitalWrite(light_jalao_pin, HIGH);
  if(content.substring(1) != "83 85 93 04" && content.substring(1) != "EF 82 EE 19" && content.substring(1) != "31 0A 99 F0" && content.substring(1) != "93 F9 C1 03" && content.substring(1) != "81 1D 9A DF"){
    lcd.begin();
	  lcd.backlight();
	  lcd.print("");
  }
}
























