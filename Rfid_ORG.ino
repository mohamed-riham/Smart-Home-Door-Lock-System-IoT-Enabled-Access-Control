#include <dummy.h>

// Smart Home RFID Door Lock System

#define BLYNK_TEMPLATE_ID "TMPL6mygql6J-"
#define BLYNK_TEMPLATE_NAME "RFID"

#include <SPI.h>
#include <MFRC522.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define SS_PIN 4
#define RST_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
char auth[] ="NtPYCcb-amd2IlL7_TJAvCJdsQJmedAf"; //replace with your Auth code here

const char* ssid = "Rajasath A12"; // with Your SSID
const char* password = "2003168121080";  // with your wifi Password

#include <Servo.h> 
Servo myServo; //define servo name

#define BUZZER 15 //buzzer pin


SimpleTimer timer;
int fflag = 0; 
int eflag = 0; 
int jflag = 0; 

WidgetTerminal terminal(V2);
void setup() 

{

  Serial.begin(9600);   // Initiate a serial communication
      Blynk.begin(auth, ssid, password);
  SPI.begin();      // Initiate  SPI bus
    myServo.attach(2); //servo pin D4
  myServo.write(0); //servo start position
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);

  
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put your card to the reader...");
  Serial.println();
  timer.setInterval(1000L, iot_rfid);

}

void loop() 

{


    timer.run(); // Initiates SimpleTimer
  Blynk.run();


}

void iot_rfid(){


  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 

  {

    return;

  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 

  {

    return;

  }

  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 

  {

     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], DEC);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], DEC));

  }

  Serial.println();
  if( (content.substring(1) == "173 653 32 39")  && (fflag == 1))
  {
         Serial.println("Moahamed");
         Blynk.virtualWrite(V2, "Moahamed" );
digitalWrite(BUZZER, HIGH);
    delay(250);
     digitalWrite(BUZZER, LOW);
          Serial.println("Mohamed Access The Door");
          Blynk.logEvent("mohamed", "Mohamed Access The Door");
          myServo.write(180);
          delay(3000);
          myServo.write(0);

        }

          if( (content.substring(1) == "175 61 23 28") && (eflag == 1))
  {
         Serial.println("Niskan");
         Blynk.virtualWrite(V2, "Niskan" );
digitalWrite(BUZZER, HIGH);
    delay(250);
     digitalWrite(BUZZER, LOW);
          Serial.println("Niskan Access The Door");
          Blynk.logEvent("niskan", "Niskan Access The Door");
          myServo.write(180);
          delay(3000);
          myServo.write(0);


        }

          if( (content.substring(1) == "04 175 215 00") && (jflag == 1))

  {
         Serial.println("Rajasath");
         Blynk.virtualWrite(V2, "Rajasath" );
digitalWrite(BUZZER, HIGH);
    delay(250);
     digitalWrite(BUZZER, LOW);
          Serial.println("Rajasath Access The Door");
          Blynk.logEvent("rajasath", "Rajasath Access The Door");
          myServo.write(180);
          delay(3000);
          myServo.write(0);

 
        }
                else 

        Serial.println("Unregistered user");
          Blynk.logEvent("unregistered_user", "Unregistered user");
         digitalWrite(BUZZER, HIGH);
    delay(1500);
      digitalWrite(BUZZER, LOW);  

  }

// in Blynk app writes values to the Virtual Pin 3
BLYNK_WRITE(V3)

{

   fflag = param.asInt(); // assigning incoming value from pin V3 to a variable
  // Blynk.virtualWrite(V2, fflag );

}
 
// in Blynk app writes values to the Virtual Pin 4
BLYNK_WRITE(V4)

{

   eflag = param.asInt(); // assigning incoming value from pin V4 to a variable

}

BLYNK_WRITE(V5)

{
   jflag = param.asInt(); // assigning incoming value from pin V5 to a variable

}
