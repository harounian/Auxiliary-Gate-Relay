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

//read dip switch values
bool dip_1_Value = !digitalRead(dip_1);
bool dip_2_Value = !digitalRead(dip_2);
bool dip_3_Value = !digitalRead(dip_3);
bool dip_4_Value = !digitalRead(dip_4);

int mode = (dip_1_Value << 3) | (dip_2_Value << 2) | (dip_3_Value << 1) | dip_4_Value; //concatenate binary values to base 10

switch(mode) {
  case 0:
    wait = 0;
    break;

   case 1:
    wait = 2000;
    break;

   case 2:
    wait = 4000;
    break;

   case 3:
    wait = 6000;
    break;

   case 4:
    wait = 8000;
    break;

   case 5:
    wait = 10000;
    break;
    
   case 6:
    wait = 12000;
    break;

   case 7:
    wait = 14000;
    break;

   case 8:
    wait = 16000;
    break;

   case 9:
    wait = 18000;
    break;

   case 10:
    wait = 20000;
    break;

   case 11:
    wait = 22000;
    break;

   case 12:
    wait = 24000;
    break;

   case 13:
    wait = 26000;
    break;

   case 14:
    wait = 28000;
    break;

   case 15:
    wait = 30000;
    break;
  }

digitalWrite(status_LED, HIGH); //blink LED for 2 seconds
delay(2000);
digitalWrite(status_LED, LOW);
    
Serial.print("Delay set to: ");
Serial.println(wait);
}

void loop() {
  if (digitalRead(gate_movement) == HIGH) { //trigger relay sequence when gate starts to move
    digitalWrite(status_LED, HIGH); //blink LED when gate is moving
    delay(150);
    digitalWrite(status_LED, LOW);   
    delay(150); 
    Serial.println("Gate Moving...");

    delay(15000);//wait for open
    
    //on sequence
    Serial.println("Relay On");
    digitalWrite(relay, HIGH);
    digitalWrite(status_LED, HIGH);
    Serial.print("Waiting: ");
    Serial.println(wait);
    delay(wait);     
    digitalWrite(relay, LOW);
    digitalWrite(status_LED, LOW);
    Serial.println("Relay Off");
    
    delay(10000);//wait for close    
  } 
}
