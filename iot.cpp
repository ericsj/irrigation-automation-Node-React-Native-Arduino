// // start wifi module configs
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

#define IRRIGATION_TEST_DELAY 1000 // in milliseconds
#define TEST_INTERVAL 1 // in seconds
#define IRRIGATION_MAX_DURATION 10 // in seconds
#define RELAY_PIN 2
#define RED_LED_PIN 6
#define GREEN_LED_PIN 5
#define MOISTURE_SENSOR_PIN A3

long LOW_MOISTURE_PROBLEM_INDICATOR = 60;
long HIGH_MOISTURE_PROBLEM_INDICATOR = 90;
long LOWER_MOISTURE_LIMIT = 70;
long IRRIGATION_STOP_MOISTURE = 85;
long irrigation_start_time = 0;
long moisture_before_irrigation_analog = 0;
int moisture_before_irrigation = 0;
long current_moisture_analog = 0;
int current_moisture = 0;
long irrigation_timer = 0;

void send_irrigation_metrics_to_api (long moisture_before_irrigation,
  long current_moisture, int irrigation_time, String system_status) {
  String endpoint = "/irrigation-metrics/1";
  String data =
    "{ \"initialMoisture\":" + String(moisture_before_irrigation) + "," +
    "\"finalMoisture:\"" +  String(current_moisture) + "," +
    "\"duration:\"" +  String(irrigation_timer) + "," +
    "{ \"status\": " + system_status + " }";
  Serial.println("Sending irrigation metrics to api: " + data);
  make_http_request(endpoint, data);
}

void make_http_request(String endpoint, String data) {
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, endpoint);

    // Specify content-type header
    http.addHeader("Content-Type", "application/json");
    // Data to send with HTTP POST
    String httpRequestData = data;           
    // Send HTTP POST request
    int httpResponseCode = http.PUT(httpRequestData);
    
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
      
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

void set_server_connection() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  // Wifi/server settings
  set_server_connection();
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, HIGH);
}

void change_led_status(bool error) {
  if (error == true) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  } else {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
}

void loop() {
    moisture_before_irrigation_analog = analogRead(MOISTURE_SENSOR_PIN) check current moisture by Soil Moisture Sensor
    moisture_before_irrigation = map(moisture_before_irrigation_analog, 1023, 0, 0, 100); // percentage irrigation
    irrigation_start_time = millis();
    Serial.println("Moisture before irrigation: " + String(moisture_before_irrigation));
    current_moisture = moisture_before_irrigation;
    while(current_moisture < IRRIGATION_STOP_MOISTURE &&
        irrigation_timer < IRRIGATION_MAX_DURATION * 1000) {
        digitalWrite(RELAY_PIN, HIGH);
        delay(IRRIGATION_TEST_DELAY);
        current_moisture_analog = analogRead(MOISTURE_SENSOR_PIN) check current moisture by Soil Moisture Sensor
        current_moisture = map(current_moisture_analog, 1023, 0, 0, 100);
        Serial.println("Current moisture: " + String(current_moisture));        
        irrigation_timer = millis(); - irrigation_start_time;
    }
    digitalWrite(RELAY_PIN, LOW);
    if (current_moisture < LOW_MOISTURE_PROBLEM_INDICATOR){
        change_led_status(true);
        send_irrigation_metrics_to_api(moisture_before_irrigation, current_moisture,
          irrigation_timer, "Soil moisture below lower limit");
    } else if (current_moisture > HIGH_MOISTURE_PROBLEM_INDICATOR) {
        change_led_status(true);
        send_irrigation_metrics_to_api(moisture_before_irrigation, current_moisture,
          irrigation_timer, "Soil moisture above upper limit");
    } else {
        change_led_status(false);
        send_irrigation_metrics_to_api(moisture_before_irrigation, current_moisture,
          irrigation_timer, "");
    }
	delay(TEST_INTERVAL * 1000);
}
