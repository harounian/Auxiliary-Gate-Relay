int dip_1 = 2;
int dip_2 = 3;
int dip_3 = 4;
int dip_4 = 5;

int relay = 7; 
int status_LED = 12;
int gate_movement = 6;

int wait = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("Start");

    pinMode(dip_1, INPUT_PULLUP);
    pinMode(dip_2, INPUT_PULLUP);
    pinMode(dip_3, INPUT_PULLUP);
    pinMode(dip_4, INPUT_PULLUP);

    pinMode(gate_movement, INPUT);
    pinMode(relay, OUTPUT);
    pinMode(status_LED, OUTPUT);

    // Read DIP switch values and determine mode
    int mode = readDIP();
    wait = mode * 2000; // Sets wait time based on mode (0-15)

    Serial.print("Delay set to: ");
    Serial.println(wait);

    blinkLED(2000); // Blink LED for 2 seconds at startup
}

void loop() {
    static unsigned long relayTimer = 0; 
    static bool gateMoving = false;

    if (digitalRead(gate_movement) == HIGH && !gateMoving) {
        gateMoving = true;
        Serial.println("Gate Moving...");
        blinkLED(300);

        delay(15000); // Simulated time for gate open

        // Relay ON sequence
        Serial.println("Relay On");
        digitalWrite(relay, HIGH);
        digitalWrite(status_LED, HIGH);
        relayTimer = millis(); 
    }

    // Turn off relay after wait time
    if (gateMoving && millis() - relayTimer >= wait) {
        Serial.println("Relay Off");
        digitalWrite(relay, LOW);
        digitalWrite(status_LED, LOW);
        gateMoving = false;

        delay(10000); // Simulated gate close time
    }
}

//Read DIP switches and return base 10 num
int readDIP() {
    int mode = 0;
    int dipPins[] = {dip_4, dip_3, dip_2, dip_1};
    for (int i = 0; i < 4; i++) {
        mode |= (!digitalRead(dipPins[i])) << i;
    }
    return mode;
}

//Blink LED for a specified duration
void blinkLED(int duration) {
    digitalWrite(status_LED, HIGH);
    delay(duration / 2);
    digitalWrite(status_LED, LOW);
    delay(duration / 2);
}
