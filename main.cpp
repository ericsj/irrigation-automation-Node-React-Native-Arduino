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


void send_irrigation_data_to_api (long moisture_before_irrigation, long current_moisture, char irrigation_timer[]) {
  Serial.println("Sending irrigation data to api");
}

void notify_problem_to_api (char type[]) {
  Serial.println("Notifying problem to api");
}

void setup() {
    Serial.begin(9600);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    digitalWrite(GREEN_LED_PIN, HIGH);
}

void loop() {
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
