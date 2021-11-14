#include <WiFi.h>
#include <ESP32Servo.h>
#include <FirebaseESP32.h>

#define FIREBASE_HOST "https://miniprojectfirebase71190-8942f-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "fOvcv4eaFszRLGXFHqmGcvugQpTCosZrGzpOxsCZ"
#define servoPin 14
#define ldrPin 36

Servo Servo1;

//Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Dua Bersaudara"
#define WIFI_PASSWORD "TanyaOrang2B"

/* 2. If work with RTDB, define the RTDB URL and database secret */
#define DATABASE_HOST "https://miniprojectfirebase71190-8942f-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define DATABASE_AUTH "fOvcv4eaFszRLGXFHqmGcvugQpTCosZrGzpOxsCZ"

/* 3. Define the Firebase Data object */
FirebaseData fbdo;

/* 4, Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* Define the FirebaseConfig data for config data */
FirebaseConfig config;

unsigned long dataMillis = 0;

void setup()
{
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the certificate file (optional) */
    //config.cert.file = "/cert.cer";
    //config.cert.file_storage = StorageType::FLASH;

    /* Assign the database URL and database secret(required) */
    config.database_url = DATABASE_HOST;
    config.signer.tokens.legacy_token = DATABASE_AUTH;

    Firebase.reconnectWiFi(true);

    /* Initialize the library with the Firebase authen and config */
    Firebase.begin(&config, &auth);

    //Or use legacy authenticate method
    //Firebase.begin(DATABASE_URL, DATABASE_SECRET);
    
    // Servo
    Servo1.attach(servoPin);
   
}

void loop()
{
  String power;
  String on = "ON";
  if (millis() - dataMillis > 2000)
  {
      Firebase.getString(fbdo,"node1/BTN");
      power = fbdo.stringData();
      dataMillis = millis();
      Serial.print("Power: ");
      Serial.print(power);
      Serial.println();
      int analogValue = analogRead(ldrPin);
      Serial.print("LDR: ");
      Serial.print(analogValue);
      Serial.println();
      if (Firebase.setFloat(fbdo, "node1/LDR", analogValue))
      {
        Serial.print("PASSED");
        Serial.print(" || PATH: " + fbdo.dataPath());
        Serial.print(" || TYPE: " + fbdo.dataType());
        Serial.println();
      }
      else
      {
        Serial.print("FAILED");
        Serial.print(" || REASON: " + fbdo.errorReason());
        Serial.println();
      }
      if(analogValue < 1000){
        Servo1.write(0);
      } else {
        Servo1.write(180);
      }
      delay(100);
  }   
}
