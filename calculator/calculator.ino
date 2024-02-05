#include <LiquidCrystal.h>

const int ROWS = 4;
const int COLS = 4;

byte col_pins[ROWS] = {0,1,2,3};
byte row_pins[COLS] = {4,5,6,7};

char keys[ROWS][COLS] = {
  {'+','=','0', 'R'},
  {'-','3','2', '1'},
  {'*','6','5', '4'},
  {'/','9','8', '7'}
};

LiquidCrystal lcd(19, 18, 17, 16, 15, 14);

double num1 = 0;
double num2 = 0;

char op = 'X';

double result = 0;

bool num1_flag = 0;
bool num2_flag = 0;
bool num1_negative = 0;
bool num2_negative = 0;
bool first_char = 0;
bool calculated = 0;
bool error = 0;
bool op_flag = 0;

void setup() {
	
	for (byte i = 0; i < ROWS; i++) {
		pinMode(row_pins[i], OUTPUT);
		digitalWrite(row_pins[i], HIGH);
	}

	for (byte i = 0; i < COLS; i++) {
		pinMode(col_pins[i], INPUT_PULLUP);
	}

	lcd.begin(16, 4);
	lcd.setCursor(0, 0);
}

void loop() {

	char key = get_key();
	
	if(key && calculated){
		lcd.clear();
		lcd.setCursor(0, 0);
		calculated = 0;
	}
	
	if(key == '-' && !first_char){
		first_char = 1;
		num1_negative = 1;
		lcd.print(key);
	}
	
	if(key == '-' && num1_flag && !num2_flag && !num2_negative && op_flag){
		num2_negative = 1;
		lcd.print(key);
	}

	if(key == '=' && num1_flag){
		
		if(num1_negative){
			num1 = num1 * -1;
		}
		if(num2_negative){
			num2 = num2 * -1;
		}
		
		if(op == '+'){
			result = num1 + num2;
		}
		else if(op == '-'){
			result = num1 - num2;
		}
		
		else if(op == '*'){
			result = num1 * num2;
		}
		else if(op == '/'){
			if(num2 == 0){
				error = 1;
			}
			else{
				result = num1 / num2;
			}
		}
		else if(op == 'X'){
			result = num1;
		}
		
		display(result);
	}
	else if(key-'0' <= 9 && key-'0' >= 0){
		first_char = 1;
		
		if(op_flag){
			num2_flag = 1;
			num2 = num2 * 10 + (key-'0');
			lcd.print(key);
		}
		else{
			num1_flag = 1;
			num1 = num1 * 10 + (key-'0');
			lcd.print(key);	
		}
	}
	else if((key == '+' || key == '-' || key == '*' || key == '/') && !op_flag && first_char && num1_flag){
		op = key;
		op_flag = 1;
		lcd.print(key);
	}
	else if(key == 'R' && !op_flag && num1_flag){
		if(!num1_negative){
			result = sqrt(num1);
		}
		else{
			error = 1;
		}
		
		display(result);
	}
}

void display(double result){
	lcd.setCursor(0, 1);
	
	if(!error){
		lcd.print(result);
	}
	else{
		lcd.print("Error");
	}
	
	result = 0;
	num1_flag = 0;
	num1 = 0;
	num2 = 0;
	op = 'X';
	calculated = 1;
	error = 0;
	num1_negative = 0;
	num2_negative = 0;
	first_char = 0;
	num2_flag = 0;
	op_flag = 0;
}

char get_key() {

	for (byte col = 0; col < COLS; col++) {
		digitalWrite(row_pins[col], LOW);
		
		for (byte row = 0; row < ROWS; row++) {
			if (digitalRead(col_pins[row]) == LOW) {
				while (digitalRead(col_pins[row]) == LOW); 
					digitalWrite(row_pins[col], HIGH);
			return keys[row][col];
			}
		}
		
		digitalWrite(row_pins[col], HIGH);
	}
	
	return 0; 
}