#define BLYNK_TEMPLATE_ID "TMPL6WgtegxGZ"
#define BLYNK_TEMPLATE_NAME "Vithuzha Riham Nisath"
#define BLYNK_AUTH_TOKEN "zJjzgaIf667c5d5ObCPlnTm-zghXabjp"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// ----- Configuration -----
#define SS_PIN D2         // RFID SDA
#define RST_PIN D1        // RFID RST
#define BUZZER D8         // Buzzer
#define SERVO_PIN D4      // Servo signal
#define COOLDOWN 1000     // 1 second cooldown per user

// ----- Wi-Fi Credentials -----
char ssid[] = "rhm";           
char pass[] = "00000000";       

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo;

struct User {
  String uid;
  String name;
  unsigned long lastAccessTime;
};

User users[] = {
  {"175 61 23 28", "Nisath", 0},
  {"4 175 215 0", "Riham", 0}
};

const int numUsers = sizeof(users) / sizeof(users[0]);

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  SPI.begin();
  mfrc522.PCD_Init();

  myServo.attach(SERVO_PIN);
  myServo.write(0); // Closed position

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  Serial.println("System ready. Place your RFID card...");
  Blynk.virtualWrite(V0, "System ready...\n");

  // Add this if you want to repeat any timed actions
  // timer.setInterval(1000L, someFunction);
}

void loop() {
  Blynk.run();
  timer.run();

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content += String(mfrc522.uid.uidByte[i]);
    if (i < mfrc522.uid.size - 1) content += " ";
  }

  Serial.print("UID: ");
  Serial.println(content);

  bool authorized = false;
  unsigned long currentTime = millis();

  for (int i = 0; i < numUsers; i++) {
    if (content == users[i].uid) {
      authorized = true;

      if (currentTime - users[i].lastAccessTime >= COOLDOWN) {
        grantAccess(users[i].name);
        users[i].lastAccessTime = currentTime;
      } else {
        Serial.println("Cooldown active for " + users[i].name);
        Blynk.virtualWrite(V0, "Cooldown active for " + users[i].name + "\n");
        buzz(2, 100);
      }
      break;
    }
  }

  if (!authorized) {
    Serial.println("Unregistered user.");
    Blynk.virtualWrite(V0, "Access denied: Unregistered UID: " + content + "\n");
    buzz(3, 300);
  }

  mfrc522.PICC_HaltA(); // Halt until next card
}

void grantAccess(String name) {
  Serial.println("Access granted: " + name);
  Blynk.virtualWrite(V0, "Access granted to: " + name + "\n");
  buzz(1, 200);

  myServo.write(180);  // Open
  delay(5000);         // Wait for 5 seconds
  myServo.write(0);    // Close
}

void buzz(int times, int duration) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(duration);
    digitalWrite(BUZZER, LOW);
    delay(100);
  }
}

// ---------- BLYNK VIRTUAL SWITCH ----------
// V1: Single switch to open/close door
BLYNK_WRITE(V1) {
  int value = param.asInt(); // 1 = ON, 0 = OFF

  if (value == 1) {
    // Switch turned ON → Open Door
    Serial.println("Blynk: Door opened (switch ON)");
    Blynk.virtualWrite(V0, "Door opened via Blynk\n");
    myServo.write(180);
    buzz(1, 200);
  } else {
    // Switch turned OFF → Close Door
    Serial.println("Blynk: Door closed (switch OFF)");
    Blynk.virtualWrite(V0, "Door closed via Blynk\n");
    myServo.write(0);
    buzz(1, 100);
  }
}

