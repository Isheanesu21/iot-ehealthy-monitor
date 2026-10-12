#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ===== WiFi DETAILS =====
const char* ssid = "samhungu";
const char* password = "varsity153";
// ===== ThingSpeak =====
String apiKey = "904QKK84TXC4NN06";
const char* server = "http://api.thingspeak.com/update";

// DS18B20
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// LED & Buzzer
#define LED_PIN 2
#define BUZZER_PIN 18

unsigned long lastTime = 0;
unsigned long timerDelay = 15000; // ThingSpeak 15 sec limit

void setup() {
  Serial.begin(115200);

  sensors.begin();

  lcd.init();
  lcd.backlight();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // WiFi connect
  WiFi.begin(ssid, password);
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(2000);
  lcd.clear();
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  Serial.print("Temperature: ");
  Serial.println(tempC);

  // ===== LCD DISPLAY =====
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");

  if (tempC == -127.00) {
    lcd.print("Error   ");
    lcd.setCursor(0, 1);
    lcd.print("Check Sensor");

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
  else {
    lcd.print(tempC);
    lcd.print((char)223);
    lcd.print("C   ");

    // ===== CLASSIFICATION =====
    if (tempC < 35.0) {
      lcd.setCursor(0, 1);
      lcd.print("Hypothermia!");

      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, millis() % 200 < 100);
    }
    else if (tempC <= 36.4) {
      lcd.setCursor(0, 1);
      lcd.print("Low Temp     ");
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
    }
    else if (tempC <= 37.5) {
      lcd.setCursor(0, 1);
      lcd.print("Normal       ");
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
    }
    else if (tempC <= 38.0) {
      lcd.setCursor(0, 1);
      lcd.print("Mild Fever   ");
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
    }
    else if (tempC <= 39.0) {
      lcd.setCursor(0, 1);
      lcd.print("Fever        ");
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
    }
    else {
      lcd.setCursor(0, 1);
      lcd.print("HIGH FEVER!! ");

      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, millis() % 200 < 100);
    }

    // ===== THINGSPEAK UPLOAD =====
    if ((millis() - lastTime) > timerDelay) {

      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        String url = String(server) + "?api_key=" + apiKey +
                     "&field1=" + String(tempC);

        http.begin(url);
        int httpResponseCode = http.GET();

        Serial.print("ThingSpeak Response: ");
        Serial.println(httpResponseCode);

        http.end();
      }

      lastTime = millis();
    }
  }

  delay(1000);
}
