#define zolte 22
#define pieszy_czerwone 0
#define pieszy_zielone 1
#define kierowca_czerwone 3
#define kierowca_zielone 5
#define przelacznik_trybu_nocnego 2
#define przerwanie 21
#define swiatla_przycisku 18

boolean tryb_pieszego = 0;

void setup() {
	pinMode(zolte, OUTPUT);
	pinMode(pieszy_czerwone, OUTPUT);
	pinMode(pieszy_zielone, OUTPUT);
	pinMode(kierowca_czerwone, OUTPUT);
	pinMode(kierowca_zielone, OUTPUT);
	
	pinMode(przerwanie, INPUT_PULLUP);
	pinMode(swiatla_przycisku, OUTPUT);
	
	interrupts();
	
	pinMode(przelacznik_trybu_nocnego, INPUT_PULLUP);
	
	attachInterrupt(2, interrupt, FALLING);
	test_swiatel();
}

void loop() {
	if(tryb_pieszego == 0){
		if(digitalRead(przelacznik_trybu_nocnego) != 0){
			tryb_kierowca_zielone();
		}
		else{
			tryb_nocny();
		}
	}
	else{
		digitalWrite(swiatla_przycisku, HIGH);
		tryb_pieszy_zielone();
		tryb_pieszego = 0;
	}
}

void test_swiatel(){
	digitalWrite(zolte, HIGH);
	digitalWrite(pieszy_czerwone, HIGH);
	digitalWrite(pieszy_zielone, HIGH);
	digitalWrite(kierowca_czerwone, HIGH);
	digitalWrite(kierowca_zielone, HIGH);
	
	delay(2000);
	
	digitalWrite(zolte, LOW);
	digitalWrite(pieszy_czerwone, LOW);
	digitalWrite(pieszy_zielone, LOW);
	digitalWrite(kierowca_czerwone, LOW);
	digitalWrite(kierowca_zielone, LOW);
}

void tryb_kierowca_zielone(){
	digitalWrite(kierowca_zielone, HIGH);
	digitalWrite(pieszy_czerwone, HIGH);
	delay(2000);
}
	
void tryb_pieszy_zielone(){

	//zolte swiatlo dla kierowcow, potem czerwone dla kierowcow
	//oraz zielone dla pieszych
	digitalWrite(kierowca_zielone, LOW);
	digitalWrite(zolte, HIGH);
	delay(1000);
	digitalWrite(zolte, LOW);
	digitalWrite(kierowca_czerwone, HIGH);
	delay(1000);
	digitalWrite(pieszy_czerwone, LOW);
	digitalWrite(pieszy_zielone, HIGH);

	delay(5000);
	
	//migotanie swiatla zielonego i wylaczenie go
	for(int i=0; i<3; i++){
	digitalWrite(pieszy_zielone, LOW);
	delay(500);
	digitalWrite(pieszy_zielone, HIGH);
	delay(500);
	}
	
	digitalWrite(pieszy_zielone, LOW);
	digitalWrite(pieszy_czerwone, HIGH);
	delay(1000);
	
	//czerwone swiatlo dla pieszych, zolte i zielone dla kierowcow
	digitalWrite(zolte, HIGH);
	delay(1000);
	digitalWrite(zolte, LOW);
	digitalWrite(kierowca_czerwone, LOW);
	digitalWrite(kierowca_zielone, HIGH);
	digitalWrite(swiatla_przycisku, LOW);
	
}

void tryb_nocny(){
	digitalWrite(pieszy_czerwone, LOW);
	digitalWrite(kierowca_zielone, LOW);
	
	//migotanie swiatla zoltego
	for(int i=0; i<3; i++){
	delay(500);
	digitalWrite(zolte, HIGH);
	delay(500);
	digitalWrite(zolte, LOW);
	}
}

void interrupt(){
	tryb_pieszego = 1;
}

























