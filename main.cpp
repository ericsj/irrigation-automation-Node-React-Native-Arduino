// // start wifi module configs
// #include "WiFiEsp.h"

// // Emulate Serial1 on pins 6/7 if not present
// #ifndef HAVE_HWSERIAL1
// #include "SoftwareSerial.h"
// SoftwareSerial Serial1(6, 7); // RX, TX
// #endif

// String ssid = "SSID";            // your network SSID (name)
// String pass = "PASSWORD";        // your network password
// int status = WL_IDLE_STATUS;     // the Wifi radio's status

// String server = "192.168.3.5";

// Initialize the Ethernet client object
// WiFiEspClient client;
// end wifi module configs

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

// mocks
long start_moisture_mock = 1000;
long current_moisture_mock = 150;
long current_time = 0;
long irrigation_timer = 0;


void send_irrigation_data_to_api (long moisture_before_irrigation, long current_moisture, int irrigation_time) {
  String endpoint = "/irrigation-data";
  String data = "\"moisture_before_irrigation\":" + String(moisture_before_irrigation) + "," +
    "\"current_moisture:\"" +  String(current_moisture) + "," +
    "\"irrigation_timer:\"" +  String(irrigation_timer) + "}";
  Serial.println("Sending irrigation data to api: " + data);
//   make_http_request(endpoint, data);
}

void notify_problem_to_api (String type) {
  String endpoint = "/irrigation-problem";
  String data = "{\"problem_type:\"" + type + "}";
  Serial.println("Notifying problem to api: " + data);
//   make_http_request(endpoint, data);
}

// void make_http_request(String endpoint, String data) {
//   client.print(
//   "HTTP/1.1 200 OK\r\n"
//   "Content-Type: application/json\r\n"
//   "Connection: close\r\n"  // the connection will be closed after completion of the response
//   "Refresh: 20\r\n"        // refresh the page automatically every 20 sec
//   "\r\n");
//   client.print(data + "\r\n");
// }

// void connect_to_wifi() {
//   // configure wifi
//   // initialize serial for debugging
//   Serial.begin(115200);
//   // initialize serial for ESP module
//   Serial.begin(9600);
//   // initialize ESP module
//   WiFi.init(&Serial1);
//   // check for the presence of the shield
//   if (WiFi.status() == WL_NO_SHIELD) {
//     Serial.println("WiFi shield not present");
//     // don't continue
//     while (true);
//   }
//   // attempt to connect to WiFi network
//   while ( status != WL_CONNECTED) {
//     Serial.print("Attempting to connect to WPA SSID: ");
//     Serial.println(ssid);
//     // Connect to WPA/WPA2 network
//     status = WiFi.begin(ssid, pass);
//   }
//   // you're connected now, so print out the data
//   Serial.println("You're connected to the network");
//   Serial.println();
// }

// void connect_to_server() {
//   Serial.println("Starting connection to server...");
//   // if you get a connection, report back via serial
//   if (client.connect(server, 80)) {
//     Serial.println("Connected to server");
//   }
// }

// void check_client_connection () {
//   // if the server's disconnected, stop the client
//   if (!client.connected()) {
//     Serial.println();
//     Serial.println("Disconnecting from server...");
//     client.stop();
//     // do nothing forevermore
//   }
// }

void setup() {
  // Wifi settings
//   connect_to_wifi()
//   connect_to_server()
  // End wifi settings
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, HIGH);
}

void loop() {
    // check_client_connection()
    moisture_before_irrigation_analog = start_moisture_mock; // analogRead(MOISTURE_SENSOR_PIN) check current moisture by Soil Moisture Sensor
    moisture_before_irrigation = map(moisture_before_irrigation_analog, 1023, 0, 0, 100); // percentage irrigation
    irrigation_start_time = millis();
    Serial.println("Moisture before irrigation: " + String(moisture_before_irrigation));
    current_moisture = moisture_before_irrigation;
    while(current_moisture < IRRIGATION_STOP_MOISTURE &&
        irrigation_timer < IRRIGATION_MAX_DURATION * 1000) {
        digitalWrite(RELAY_PIN, HIGH);
        delay(IRRIGATION_TEST_DELAY);
        current_moisture_analog = current_moisture_mock; // analogRead(MOISTURE_SENSOR_PIN) check current moisture by Soil Moisture Sensor
        current_moisture = map(current_moisture_analog, 1023, 0, 0, 100);
        Serial.println("Current moisture: " + String(current_moisture));        
        current_time = millis(); // get current timestamp
        irrigation_timer = current_time - irrigation_start_time;
    }
    digitalWrite(RELAY_PIN, LOW);
    send_irrigation_data_to_api(moisture_before_irrigation, current_moisture, irrigation_timer);
    if (current_moisture < LOW_MOISTURE_PROBLEM_INDICATOR){
        digitalWrite(RED_LED_PIN, HIGH);
        digitalWrite(GREEN_LED_PIN, LOW);
        notify_problem_to_api("below lower limit");
    } else {
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, HIGH);
    }
    if (current_moisture > HIGH_MOISTURE_PROBLEM_INDICATOR){
        digitalWrite(RED_LED_PIN, HIGH);
        digitalWrite(GREEN_LED_PIN, LOW);
        notify_problem_to_api("above upper limit");
    } else {
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, HIGH);
    }
	delay(TEST_INTERVAL * 1000);
}
