//DS, STCP, SHCP
uint8_t hours_pins[3] = {A0, A1, A2};
uint8_t minutes_pins[3] = {A5, A6, A7};
uint8_t seconds_pins[3] = {A8, A9, A10};

//in1, in2, in3, in4
int hours_stepper_pins[4] = {36, 34, 32, 30};
int minutes_stepper_pins[4] = {44, 46, 48, 50};
int seconds_stepper_pins[4] = {47, 49, 51, 53};
 
int hours_milis, minutes_milis, seconds_milis;
int hours, minutes, seconds;

int hours_step_number = 2;
int minutes_step_number = 2;
int seconds_step_number = 2;

int numbers[10][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1, 0}, // 2
  {1, 1, 1, 1, 0, 0, 1, 0}, // 3
  {0, 1, 1, 0, 0, 1, 1, 0}, // 4
  {1, 0, 1, 1, 0, 1, 1, 0}, // 5
  {1, 0, 1, 1, 1, 1, 1, 0}, // 6
  {1, 1, 1, 0, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1, 0}, // 8
  {1, 1, 1, 1, 0, 1, 1, 0}  // 9
};

void setup() {
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	
	pinMode(45, OUTPUT);
	pinMode(47, OUTPUT);
	pinMode(48, OUTPUT);
	pinMode(49, OUTPUT);
	
	pinMode(44, OUTPUT);
	pinMode(46, OUTPUT);
	pinMode(48, OUTPUT);
	pinMode(50, OUTPUT);
	
	pinMode(36, OUTPUT);
	pinMode(34, OUTPUT);
	pinMode(32, OUTPUT);
	pinMode(30, OUTPUT);
	
	digitalWrite(5, HIGH);
	delayMicroseconds(980);
	digitalWrite(5, LOW);
			
	digitalWrite(6, HIGH);
	delayMicroseconds(980);
	digitalWrite(6, LOW);
			
	digitalWrite(7, HIGH);
	delayMicroseconds(980);
	digitalWrite(7, LOW);
}

void loop() {

	hours_milis = 980;
	hours = 0;

	while(hours<12){
	
		display_number(hours, hours_pins);
	
		minutes_milis = 980;
		minutes = 0;
		
		step(hours_stepper_pins, hours_step_number, 12, -1);
		hours_step_number++;
		
		while(minutes<60){
		
		display_number(minutes, minutes_pins);
		
			seconds_milis = 980;
			seconds = 0;
			
			step(minutes_stepper_pins, minutes_step_number, 60, -1);
			minutes_step_number++;
			
			while(seconds<60){
			
				step(seconds_stepper_pins, seconds_step_number, 60, -1);
				seconds_step_number++;
			
				display_number(seconds, seconds_pins);
			
				seconds_milis+=17;
				seconds++;
				
				if(seconds == 5){
					digitalWrite(31, LOW);
				}
				
				digitalWrite(5, HIGH);
				delayMicroseconds(seconds_milis);
				digitalWrite(5, LOW);
				
				if(seconds == 60){
					digitalWrite(5, HIGH);
					delayMicroseconds(980);
					digitalWrite(5, LOW);
				}
				
				//change this to speed up or slow down the clock
				//1000 means real-time
				delay(1000);
			}
			
			digitalWrite(31, HIGH);
			
			minutes_milis+=17;
			minutes++;
			
			digitalWrite(6, HIGH);
			delayMicroseconds(minutes_milis);
			digitalWrite(6, LOW);
			
			if(minutes == 60){
				digitalWrite(6, HIGH);
				delayMicroseconds(980);
				digitalWrite(6, LOW);
			}
		}
		
		hours_milis+=85;
		hours++;
		
		digitalWrite(7, HIGH);
		delayMicroseconds(hours_milis);
		digitalWrite(7, LOW);

		if(hours == 12){
			digitalWrite(7, HIGH);
			delayMicroseconds(980);
			digitalWrite(7, LOW);
		}
	}
}

void display_number(int number, uint8_t pins[3]) {
	int tens = number / 10;
	int ones = number % 10;
	int combined = (numbers[ones][0] << 0) | (numbers[ones][1] << 1) | (numbers[ones][2] << 2) | (numbers[ones][3] << 3) | (numbers[ones][4] << 4) | (numbers[ones][5] << 5) | (numbers[ones][6] << 6) | (numbers[ones][7] << 7);
	  
	shiftOut(pins[0], pins[2], MSBFIRST, combined);
	  
	combined = (numbers[tens][0] << 0) | (numbers[tens][1] << 1) | (numbers[tens][2] << 2) | (numbers[tens][3] << 3) | (numbers[tens][4] << 4) | (numbers[tens][5] << 5) | (numbers[tens][6] << 6) | (numbers[tens][7] << 7);
	  
	shiftOut(pins[0], pins[2], MSBFIRST, combined);
	  
	digitalWrite(pins[1], LOW);
	digitalWrite(pins[1], HIGH);
}

void step(int stepper_pins[4], int step_count, int steps_per_revolution, int direction) {

    int full_step_sequence[4][4] = {
        {HIGH, LOW, LOW, LOW},
        {LOW, HIGH, LOW, LOW},
        {LOW, LOW, HIGH, LOW},
        {LOW, LOW, LOW, HIGH}
    };
    
    int step_index = (step_count * direction) % steps_per_revolution;
    if (step_index < 0) {
        step_index += steps_per_revolution;
    }

    int sequence_index = step_index % 4;

    for (int pin = 0; pin < 4; pin++) {
        digitalWrite(stepper_pins[pin], full_step_sequence[sequence_index][pin]);
    }
}