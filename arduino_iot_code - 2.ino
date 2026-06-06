#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>  // BMP280 sensor

#define BLYNK_TEMPLATE_ID "TMPL3GZG8BIWF"
#define BLYNK_TEMPLATE_NAME "Disaster"
#define BLYNK_AUTH_TOKEN "vb-Z0BbEZNqcZDHeFLxUcOT77CGnTNTE"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// === WiFi Credentials ===
const char* ssid = "iot";
const char* password = "12345678";

// === Server URL ===
const char* serverName = "http://iotcloud22.in/disaster_detection/post_value.php";
WiFiClient client;
HTTPClient http;

// === DHT11 Sensor ===
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// === BMP280 (I2C) ===
#define I2C_SDA 21
#define I2C_SCL 22
Adafruit_BMP280 bmp;

// === Sensor Pins ===
#define trigPin 5
#define echoPin 18
#define vibrationPin 35
#define flamePin 33
#define gasPin 34
#define soilMoisturePin 36

// === Output Pins ===
#define buzzerPin 23
#define redLED 19
#define greenLED 2

// === GSM Serial ===
HardwareSerial gsm(2);
#define GSM_TX 17
#define GSM_RX 16

void setup() {
  Serial.begin(115200);
  gsm.begin(9600, SERIAL_8N1, GSM_RX, GSM_TX);
  dht.begin();

  Blynk.begin(auth, ssid, password);

  Wire.begin(I2C_SDA, I2C_SCL);
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found!");
    while (1)
      ;
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(greenLED, HIGH);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int gas = analogRead(gasPin);
  int vibrationValue = analogRead(vibrationPin);
  int flameValue = analogRead(flamePin);
  int soilValue = analogRead(soilMoisturePin);
  float pressure = bmp.readPressure() / 100.0F;

  long duration;
  float distance;

  // Ultrasonic Water Level Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;


  Serial.println("---- Sensor Values ----");
  Serial.printf("Temp: %.1f °C, Humidity: %.1f%%\n", temp, hum);
  Serial.printf("Gas: %d%, Vibration: %d, Flame: %d%%\n%", gas / 10, vibrationValue, (int)((1 - (float)flameValue / 4095) * 100));
  // Serial.printf("Gas: %d, Vibration: %d, Flame: %d\n", gas/10, vibrationValue, flameValue);
  Serial.printf("Water Distance: %.2f cm, Soil Moisture: %d, Pressure: %.2f hPa\n", distance, soilValue, pressure);

  bool danger = false;
  String disaster = "Normal";
  Serial.println(danger);

  if (distance < 4.0) {
    disaster = "FLOOD";
    sendSMS("Flood Detected!");
    danger = true;
  } else if (vibrationValue > 500) {
    disaster = "EARTHQUAKE";
    sendSMS("Earthquake Detected!");
    danger = true;
  } else if (flameValue < 500) {
    disaster = "FIRE";
    sendSMS("Fire Detected!");
    danger = true;
  } else if (gas > 1000) {
    disaster = "GAS LEAK";
    sendSMS("Gas Leak Detected!");
    danger = true;
  } else if (temp > 45 && hum < 20) {
    disaster = "HIGH TEMP";
    sendSMS("High Temperature Warning!");
    danger = true;
  } else if (pressure < 10) {
    disaster = "STORM";
    sendSMS("Storm Warning - Low Pressure!");
    danger = true;
  } else if (soilValue < 1200) {  // Dry soil warning
    disaster = "LANDSLIDE";
    sendSMS("Landslide Warning - Wet Soil Detected!");
    danger = true;
  }

  sendToServer(temp, hum, gas, vibrationValue, flameValue, distance, pressure, soilValue, disaster);

  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);

  Blynk.run();
  // Output Actions
  if (danger) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    delay(15000);  // 15 seconds delay
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
  }

  // Send data to cloud


  delay(500);
}

void sendToServer(float temp, float hum, int gas, int vibration, int flame, float distance, float pressure, int soil, String disaster) {
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "value1=" + String(temp) + "&value2=" + String(hum) + "&value3=" + String(gas) + "&value4=" + String(vibration) + "&value5=" + String(flame) + "&value6=" + String(distance) + "&value7=" + String(pressure) + "&value8=" + String(soil) + "&value9=" + disaster;

    Serial.print("POST Data: ");
    Serial.println(postData);

    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void sendSMS(String msg) {
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+918610117563\"");
  delay(1000);
  gsm.println("ALERT     ");
  gsm.print(msg);
  gsm.write(26);  // Ctrl+Z
  delay(1000);
}
