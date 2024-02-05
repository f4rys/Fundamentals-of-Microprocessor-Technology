#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 12, 3, 0, 5, 1);

const int relay_pins[] = {A8, A9, A10, A11, A12};
const int relays = 5;
const int delay_value = 500;

void setup() {

  for (int i = 0; i < relays; i++) {
    pinMode(relay_pins[i], OUTPUT);
    digitalWrite(relay_pins[i], LOW);
  }

  pinMode(A14, OUTPUT);
  pinMode(A7, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

digitalWrite(A14, HIGH);

}

void loop() {

  delay(delay_value);

  double voltage = read_voltage(A15);

  if (voltage < 2.5) {
    for (int i = 5; 2.5 > read_voltage(A15); i--) {
      activate_relay(i);
      delay(delay_value);
    }
    double scaled_voltage = voltage * pow(2, relays);
    print_voltage(scaled_voltage);
  }
  else {
	delay(delay_value);    
	activate_all_relays();
  }
}

double read_voltage(int pin) {

  float sensor_voltage = analogRead(A6) * (5.0 / 1023.0); 
	
  //the circuit will not close and no measurement will be made
	//if the voltage is not safe
	if(sensor_voltage < 0.294){
	digitalWrite(A14, LOW);
	delay(delay_value);
	  int sensor_value = analogRead(pin);
	digitalWrite(A14, HIGH);
	  float voltage = sensor_value * (5.0 / 1023.0); 
	  return voltage;
	}
	else{
  //if a dangerous voltage is detected
	//all resistors are connected to reduce it
	activate_all_relays();
	}
}

void print_voltage(float voltage) {
  lcd.setCursor(0, 0); 
  lcd.clear();
  lcd.print(voltage);
  lcd.print("V");
}

void activate_relay(int relay_index) {
  digitalWrite(relay_pins[relay_index], HIGH);
}

void activate_all_relays() {
  for (int i = 0; i < relays; i++) {
    digitalWrite(relay_pins[i], LOW);
	delay(delay_value);
  }
}