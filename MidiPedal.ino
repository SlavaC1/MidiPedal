
const int NUM_OF_BUTTONS = 4;

const int Buttons     [NUM_OF_BUTTONS] = {3, 4, 5, 6};   // Buttons input pins
const int Leds        [NUM_OF_BUTTONS] = {8, 9, 10, 11}; // Leds output pins
const int MidiCommands[NUM_OF_BUTTONS] = {81, 82, 83, 84};

int LedsState[NUM_OF_BUTTONS]    = {LOW, LOW, LOW, LOW}; // Init all to leds OFF. Actually activation state
int PrevBtnState[NUM_OF_BUTTONS] = {LOW, LOW, LOW, LOW};

int ActiveLed = 0;

// For testing
const int LedPin    = 8;

void setup()
{	
	for(int i = 0; i < NUM_OF_BUTTONS; i++)
	{
		pinMode(Buttons[i], INPUT);
		pinMode(Leds[i], OUTPUT);

		// Turn OFF all leds
		digitalWrite(Leds[i], LedsState[i]); 
		
		// Init button states
		PrevBtnState[i] = digitalRead(Buttons[i]); 
	}	

	Serial.begin(31250);
	//Serial.begin(115200);
}

void loop()
{	
	for(int i = 0; i < NUM_OF_BUTTONS; i++)
	{
		int BtnReading = digitalRead(Buttons[i]);
		
		// Repeating button pressing does not effect the led state
		if(LedsState[i] == HIGH)
		{
			PrevBtnState[i] = BtnReading;
			continue;
		}	

		if(BtnReading != PrevBtnState[i])					
		{		   
			// Turn OFF currently active led
			digitalWrite(Leds[ActiveLed], LOW);
			LedsState[ActiveLed] = LOW;

			// Update the led and button state
			ActiveLed       = i;			
			PrevBtnState[i] = BtnReading;
			
			// Turn ON the led
			digitalWrite(Leds[i], HIGH);
			LedsState[i] = HIGH;

			// Send MIDI command to the PC
			MidiSend(0x90, MidiCommands[i], 127);						
		}		
	}

	//PlayMDBSong();
}

void MidiSend(char cmd, char pitch, char velocity) 
{
	Serial.write(cmd);	
	Serial.write(pitch);
	Serial.write(velocity);	  
}

void Blink()
{
	digitalWrite(LedPin, HIGH);
	delay(300);
	digitalWrite(LedPin, LOW);
	delay(300);
}

void PlayMDBSong()
{
	// MDB - Cry Of Mankind
	// --------------------------------
	MidiSend(0x90,93,127);
	delay(400);
	MidiSend(0x90,86,127);
	delay(400);
	MidiSend(0x90,89,127);
	delay(400);
	MidiSend(0x90,88,127);
	delay(400);
	MidiSend(0x90,81,127);
	delay(400);
	MidiSend(0x90,84,127);
	delay(400);
	// --------------------------------
}

