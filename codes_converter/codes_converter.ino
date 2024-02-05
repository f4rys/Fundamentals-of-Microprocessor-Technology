void setup() {
	pinMode(31, INPUT_PULLUP);
	pinMode(33, INPUT_PULLUP);
	pinMode(35, INPUT_PULLUP);
	
	pinMode(0, INPUT_PULLUP);
	pinMode(1, INPUT_PULLUP);
	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);
	pinMode(4, INPUT_PULLUP);
	pinMode(5, INPUT_PULLUP);
	pinMode(6, INPUT_PULLUP);
	pinMode(7, INPUT_PULLUP);
	
	pinMode(A15, OUTPUT);
	pinMode(A14, OUTPUT);
	pinMode(A13, OUTPUT);
	pinMode(A12, OUTPUT);
	pinMode(A11, OUTPUT);
	pinMode(A10, OUTPUT);
	pinMode(A9, OUTPUT);
	pinMode(A8, OUTPUT);
	
	pinMode(A7, OUTPUT);
	pinMode(A6, OUTPUT);
	pinMode(A5, OUTPUT);
	pinMode(A4, OUTPUT);
	pinMode(A3, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A0, OUTPUT);
	
	pinMode(21, OUTPUT);
	pinMode(20, OUTPUT);
	pinMode(19, OUTPUT);
	pinMode(18, OUTPUT);
	pinMode(17, OUTPUT);
	pinMode(16, OUTPUT);
	pinMode(15, OUTPUT);
	pinMode(14, OUTPUT);
}

void loop() {
	decoder();
	delay(100);
	clear();
}

void decoder(){
	bool input[8];
	bool decoder_binary[3];
	int decoder_decimal = 0;
	
	int decimal = 0;
	int hundreds = 0;
	int tens = 0;
	int ones = 0;
	
	bool hundreds_bcd[4] = {0,0,0,0};
	bool tens_bcd[4] = {0,0,0,0};
	bool ones_bcd[4] = {0,0,0,0};
	
	char tens_hex = "0";
	char ones_hex = "0";
	
	bool first_nibble[4] = {input[0], input[1], input[2], input[3]};
	bool second_nibble[4] = {input[4], input[5], input[6], input[7]};

	uint8_t hundreds_pins[7] = {A15, A14, A13, A12, A11, A10, A9};
	uint8_t tens_pins[7] = {A6, A5, A4, A3, A2, A1, A0};
	uint8_t ones_pins[7] = {21, 20, 19, 18, 17, 16, 15};
	
	for(int i=0; i<8; i++){
		input[i] = !digitalRead(i);
	}
	
	decoder_binary[0] = !digitalRead(31);
	decoder_binary[1] = !digitalRead(33);
	decoder_binary[2] = !digitalRead(35);
	
	for (int i = 0; i < 3; ++i) {
		decoder_decimal = (decoder_decimal << 1) | decoder_binary[i];
	}
	
	if(decoder_decimal == 0){
	//binary to BCD
		decimal = binary8bit(input);
		
		hundreds = decimal / 100;
		tens = (decimal / 10) % 10;
		ones = decimal % 10;
		
		decimal_to_bcd(hundreds, hundreds_bcd);
		decimal_to_bcd(tens, tens_bcd);
		decimal_to_bcd(ones, ones_bcd);
		
		bcd_display(hundreds_bcd, hundreds_pins);
		bcd_display(tens_bcd, tens_pins);
		bcd_display(ones_bcd, ones_pins);
		
	}
	else if(decoder_decimal == 1){
	//gray to BCD
		decimal = gray8bit(input);
		
		hundreds = decimal / 100;
		tens = (decimal / 10) % 10;
		ones = decimal % 10;
		
		decimal_to_bcd(hundreds, hundreds_bcd);
		decimal_to_bcd(tens, tens_bcd);
		decimal_to_bcd(ones, ones_bcd);
		
		bcd_display(hundreds_bcd, hundreds_pins);
		bcd_display(tens_bcd, tens_pins);
		bcd_display(ones_bcd, ones_pins);
	}
	else if(decoder_decimal == 2){
	//binary to HEX
		tens_hex = decimal_to_hex(binary4bit(first_nibble));
		ones_hex = decimal_to_hex(binary4bit(second_nibble));
		hex_display(tens_hex, tens_pins);
		hex_display(ones_hex, ones_pins);

	}
	else if(decoder_decimal == 3){
	//gray to HEX
		tens_hex = decimal_to_hex(gray4bit(first_nibble));
		ones_hex = decimal_to_hex(gray4bit(second_nibble));
		
		hex_display(tens_hex, tens_pins);
		hex_display(ones_hex, ones_pins);

	}
	else if(decoder_decimal == 4){
	//aiken to BCD
		decimal_to_bcd(aiken(first_nibble), tens_bcd);
		decimal_to_bcd(aiken(second_nibble), ones_bcd);
		bcd_display(tens_bcd, tens_pins);
		bcd_display(ones_bcd, ones_pins);
	}
	else if(decoder_decimal == 5){
	//aiken to HEX
		tens_hex = decimal_to_hex(aiken(first_nibble));
		ones_hex = decimal_to_hex(aiken(second_nibble));
		hex_display(tens_hex, tens_pins);
		hex_display(ones_hex, ones_pins);
	}
	else if(decoder_decimal == 6){
	//johnson to BCD
		decimal = johnson(input);
			
		tens = (decimal / 10) % 10;
		ones = decimal % 10;
		
		decimal_to_bcd(tens, tens_bcd);
		decimal_to_bcd(ones, ones_bcd);
		
		bcd_display(tens_bcd, tens_pins);
		bcd_display(ones_bcd, ones_pins);
	}
	else if(decoder_decimal == 7){
	//johnson to HEX
		ones_hex = decimal_to_hex(johnson(input));
		
		hex_display(ones_hex, ones_pins);
	}
}

int binary4bit(bool input[4]){
    int decimal = 0;
    int power = 1;

    for (int i = 3; i >= 0; i--) {
        if (input[i] == true) {
            decimal += power;
        }
        power *= 2;
    }

    return decimal;
}

int binary8bit(bool input[8]){
    int decimal = 0;
    int power = 1;

    for (int i = 7; i >= 0; i--) {
        if (input[i] == true) {
            decimal += power;
        }
        power *= 2;
    }

    return decimal;
}

int gray4bit(bool input[4]){
	bool binary[4] = {input[0], false, false, false};
	
	for (int i = 1; i < 4; i++) {
		binary[i] = input[i] ^ binary[i - 1];
	}
	
	int decimal = 0;
	int power = 1;
	
	for (int i = 3; i >= 0; i--) {
		if (binary[i] == true) {
			decimal += power;
		}
		
		power *= 2;
	}
	return decimal;
}


int gray8bit(bool input[8]){
    bool binary[8] = {input[0], false, false, false, false, false, false, false};
    
    for (int i = 1; i < 8; i++) {
        binary[i] = input[i] ^ binary[i - 1];
    }
    
    int decimal = 0;
    int power = 1;
    
    for (int i = 7; i >= 0; i--) {
        if (binary[i] == true) {
            decimal += power;
        }
        power *= 2;
    }
    
    return decimal;
}

int aiken(bool input[4]){
    int decimal;
    decimal = input[0]*2 + input[1]*4 + input[2]*2 + input[3]*1;

    return decimal;
}

int johnson(bool input[8]){
    int decimal = 8;

    if(input[0] == 0){
        for(int i=0; i<8; i++){
            if(input[i]==0){
                decimal -= 1;
            }
        }
    }
    else{
        for(int i=0; i<8; i++){
            if(input[i]==0){
                decimal += 1;
            }
        }
    }

    return decimal;
}

void decimal_to_bcd(int decimal, bool bcd[4]){
	for (int i = 3; i >= 0; --i) {
		bcd[i] = decimal % 2;
		decimal /= 2;
	}
}

char decimal_to_hex(int decimal){
	if (decimal >= 0 && decimal <= 9) {
		return (char)(decimal + '0');
	} 
	else if (decimal >= 10 && decimal <= 15) {
		return (char)(decimal - 10 + 'A');
	}
}

void bcd_display(bool bcd[4], uint8_t pins[7]){
	bool segments[7];
	const bool SEVEN_SEGMENT[10][7] = {
	    {1, 1, 1, 1, 1, 1, 0}, // 0
	    {0, 1, 1, 0, 0, 0, 0}, // 1
	    {1, 1, 0, 1, 1, 0, 1}, // 2
	    {1, 1, 1, 1, 0, 0, 1}, // 3
	    {0, 1, 1, 0, 0, 1, 1}, // 4
	    {1, 0, 1, 1, 0, 1, 1}, // 5
	    {1, 0, 1, 1, 1, 1, 1}, // 6
	    {1, 1, 1, 0, 0, 0, 0}, // 7
	    {1, 1, 1, 1, 1, 1, 1}, // 8
	    {1, 1, 1, 1, 0, 1, 1}  // 9
	};

	int index = (bcd[0] ? 8 : 0) + (bcd[1] ? 4 : 0) + (bcd[2] ? 2 : 0) + (bcd[3] ? 1 : 0);
	if(index < 10){
	    for (int i = 0; i < 7; i++) {
        segments[i] = SEVEN_SEGMENT[index][i];}

		for(int i=0; i<7; i++){
			if(segments[i]){
				analogWrite(pins[i], 255);
			}
		}
		
		 for (int i = 0; i < 7; i++) {
        segments[i] = SEVEN_SEGMENT[index][i];}

		for(int i=0; i<7; i++){
			if(segments[i]){
				analogWrite(pins[i], 255);
			}
		}
	}
}

void hex_display(char hex, uint8_t pins[7]){
	bool segments[7];
    bool segmentTable[16][7] = {
	    {1, 1, 1, 1, 1, 1, 0}, // 0
	    {0, 1, 1, 0, 0, 0, 0}, // 1
	    {1, 1, 0, 1, 1, 0, 1}, // 2
	    {1, 1, 1, 1, 0, 0, 1}, // 3
	    {0, 1, 1, 0, 0, 1, 1}, // 4
	    {1, 0, 1, 1, 0, 1, 1}, // 5
	    {1, 0, 1, 1, 1, 1, 1}, // 6
	    {1, 1, 1, 0, 0, 0, 0}, // 7
	    {1, 1, 1, 1, 1, 1, 1}, // 8
	    {1, 1, 1, 1, 0, 1, 1},  // 9
        {1, 1, 1, 0, 1, 1, 1}, // A
        {0, 0, 1, 1, 1, 1, 1}, // B
        {1, 0, 0, 1, 1, 1, 0}, // C
        {0, 1, 1, 1, 1, 0, 1}, // D
        {1, 0, 0, 1, 1, 1, 1}, // E
        {1, 0, 0, 0, 1, 1, 1}  // F
    };

    int index;
    if (hex >= '0' && hex <= '9') {
        index = hex - '0';
    } else if (hex >= 'A' && hex <= 'F') {
        index = hex - 'A' + 10;
    } else if (hex >= 'a' && hex <= 'f') {
        index = hex - 'a' + 10;
    } else {
        return;
    }

    for (int i = 0; i < 7; ++i) {
        segments[i] = segmentTable[index][i];
    }

    for (int i = 0; i < 7; i++) {
        if(segments[i]){
			analogWrite(pins[i], 255);
		}
    }
}

void clear(){
	analogWrite(A15, 0);
	analogWrite(A14, 0);
	analogWrite(A13, 0);
	analogWrite(A12, 0);
	analogWrite(A11, 0);
	analogWrite(A10, 0);
	analogWrite(A9, 0);	
	analogWrite(A8, 0);
	
	analogWrite(A7, 0);
	analogWrite(A6, 0);
	analogWrite(A5, 0);
	analogWrite(A4, 0);
	analogWrite(A3, 0);
	analogWrite(A2, 0);
	analogWrite(A1, 0);	
	analogWrite(A0, 0);
	
	analogWrite(21, 0);
	analogWrite(20, 0);
	analogWrite(19, 0);
	analogWrite(18, 0);
	analogWrite(17, 0);
	analogWrite(16, 0);
	analogWrite(15, 0);	
	analogWrite(14, 0);
}