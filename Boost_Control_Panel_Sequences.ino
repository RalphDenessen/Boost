#include <LiquidCrystal.h>
#include <Servo.h>

// Declare LCD pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Declare Servo pin
int servoPin = 9;

// Servo as object
Servo Servo1;

// Eyes open character pixels
byte eyetopleft[8] = {
	0b11111,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10011,
	0b10011
};

byte eyetopright[8] = {
	0b11111,
	0b00001,
	0b00001,
	0b00001,
	0b00001,
	0b00001,
	0b11001,
	0b11001
};

byte eyebottomleft[8] = {
	0b10011,
	0b10011,
	0b10000,
	0b10000,
	0b10000,
  0b10000,
	0b10000,
	0b11111
};

byte eyebottomright[8] = {
	0b11001,
	0b11001,
	0b00001,
	0b00001,
	0b00001,
	0b00001,
	0b00001,
	0b11111
};

// Eyes blink character pixels
byte blinktop[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

byte blinkbottom[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11111,
	0b11111
};

// Eyes as hearts character pixels
byte heartbottomleft[8] = {
  0b01000,
  0b01000,
  0b00100,
  0b00010,
  0b00001,
  0b00000,
  0b00000,
  0b00000
};

byte heartbottommiddle[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100
};

byte heartbottomright[8] = {
  0b00010,
  0b00010,
  0b00100,
  0b01000,
  0b10000,
  0b00000,
  0b00000,
  0b00000
};

byte hearttopleft[8] = {
  0b00000,
  0b00011,
  0b00100,
  0b01000,
  0b01000,
  0b10000,
  0b10000,
  0b10000
};

byte hearttopmiddle[8] = {
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b01010,
  0b00100,
  0b00100,
  0b00000
};

byte hearttopright[8] = {
  0b00000,
  0b11000,
  0b00100,
  0b00010,
  0b00010,
  0b00001,
  0b00001,
  0b00001
};

void setup() {

  // Connection to Python (Control Panel)
  Serial.begin(9600);
  
  // Pin settings
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  Servo1.attach(servoPin); 

  // Set servo to 0 degrees
  Servo1.write(0);

  // LCD settings   
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Waiting for");
  lcd.setCursor(0,1);
  lcd.print("connection...");
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming command from the Control Panel
    String command = Serial.readString();

    // When connected
    if (command == "run_start_sequence") {
      lcd.clear();

      // Turn on green LED
      digitalWrite(7, HIGH);

      // Play: start melody
      tone(8, 1200, 100);
      delay(100);
      tone(8, 1500, 300);
      delay(500);
      tone(8, 1200, 100);
      delay(200);
      tone(8, 1200, 100);

      // Open eyes 
      eyesOnLCD();
      
    }

    // When disconnected
    if (command == "run_stop_sequence") {
      lcd.clear();

      // Play: stop melody
      tone(8, 600, 100);
      delay(150);
      tone(8, 400, 100);
      delay(150);
      tone(8, 200, 200);

      // Set waiting message
      lcd.setCursor(0,0);
      lcd.print("Waiting for");
      lcd.setCursor(0,1);
      lcd.print("connection...");

      // Turn off green LED
      digitalWrite(7, LOW);

    }

    // When "laugh" button is clicked (1, 5)  
    if (command == "run_laugh_sequence_1") {
      digitalWrite(13, HIGH);
      lcd.clear();
      
      // Text line one and two (Sequence _ Joke(1) or Pun(2) _ Line)
      String sequence_1_1_1 = "What do doggy";
      String sequence_1_1_2 = "robots do?";
      
      // Length of both lines  
      int sequence_1_1_Length = sequence_1_1_1.length() + sequence_1_1_2.length();

      lcd.setCursor(0,0);      

      // Print line one on LCD with tone
      for (int i = 0; i < sequence_1_1_1.length(); i++) {
        lcd.print(sequence_1_1_1.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(95);
      }
      
      lcd.setCursor(0, 1);

      // Print line two on LCD with tone
      for (int i = 0; i < sequence_1_1_2.length(); i++) {
        lcd.print(sequence_1_1_2.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(95);
      }

      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);

      // Text line one     
      String sequence_1_2_1 = "They byte."; 
      int sequence_1_2_Length = sequence_1_2_1.length();

      // Print line one on LCD with tone
      for (int i = 0; i < sequence_1_2_Length; i++) {
        lcd.print(sequence_1_2_1.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(95);
      }
      
      afterJoke();

    }

    if (command == "run_laugh_sequence_2") {
      digitalWrite(13, HIGH);
      lcd.clear( );
      
      // Text on line one and two -> Sequence _ Joke(1) or Pun(2) _ Line
      String sequence_2_1_1 = "How do robots";
      String sequence_2_1_2 = "pay for things?";

      // Length of both lines      
      int sequence_2_1_Length = sequence_2_1_1.length() + sequence_2_1_2.length();
      lcd.setCursor(0,0);

      // Print line one on LCD with tone
      for (int i = 0; i < sequence_2_1_1.length(); i++) {
        lcd.print(sequence_2_1_1.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(100);
      }
      
      lcd.setCursor(0, 1);

      // Print line two on LCD with tone
      for (int i = 0; i < sequence_2_1_2.length(); i++) {
        lcd.print(sequence_2_1_2.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(100);
      }
      delay(3000);

      // Reset LCD      
      lcd.clear();
      lcd.setCursor(0,0);

      // Text on line one and two
      String sequence_2_2_1 = "With cache,";
      String sequence_2_2_2 = "of course!";

      // Length of both lines  
      int msequence_2_2_Length = sequence_2_2_1.length() + sequence_2_2_2.length();

      // Print line one on LCD with tone
      for (int i = 0; i < sequence_2_2_1.length(); i++) {
        lcd.print(sequence_2_2_1.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(100);
      }
      
      lcd.setCursor(0, 1);

      // Print line two on LCD with tone
      for (int i = 0; i < sequence_2_2_2.length(); i++) {
        lcd.print(sequence_2_2_2.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(100);
      }

      // Continue sequence
      afterJoke();

    }

    if (command == "run_laugh_sequence_3") {
      digitalWrite(13, HIGH);
      lcd.clear( );
      
      // Text on line one and two -> Sequence _ Joke(1) or Pun(2) _ Line
      String sequence_2_1_1 = "How do robots";
      String sequence_2_1_2 = "exercise?";

      // Length of both lines      
      int sequence_2_1_Length = sequence_2_1_1.length() + sequence_2_1_2.length();
      lcd.setCursor(0,0);

      // Print line one on LCD with tone
      for (int i = 0; i < sequence_2_1_1.length(); i++) {
        lcd.print(sequence_2_1_1.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(100);
      }
      
      lcd.setCursor(0, 1);

      // Print line two on LCD with tone
      for (int i = 0; i < sequence_2_1_2.length(); i++) {
        lcd.print(sequence_2_1_2.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(100);
      }
      delay(3000);

      // Reset LCD      
      lcd.clear();
      lcd.setCursor(0,0);

      // Text on line one and two
      String sequence_2_2_1 = "Circuit";
      String sequence_2_2_2 = "training.";

      // Length of both lines  
      int msequence_2_2_Length = sequence_2_2_1.length() + sequence_2_2_2.length();

      // Print line one on LCD with tone
      for (int i = 0; i < sequence_2_2_1.length(); i++) {
        lcd.print(sequence_2_2_1.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(100);
      }
      
      lcd.setCursor(0, 1);

      // Print line two on LCD with tone
      for (int i = 0; i < sequence_2_2_2.length(); i++) {
        lcd.print(sequence_2_2_2.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(100);
      }

      // Continue sequence
      afterJoke();

    }

    if (command == "run_laugh_sequence_4") {
      digitalWrite(13, HIGH);
      lcd.clear( );
      
      // Sequence // Joke(1) or Pun(2) // Line
      String sequence_1_1_1 = "What is a robots";
      String sequence_1_1_2 = "favorite dance?";

      int sequence_1_1_Length = sequence_1_1_1.length() + sequence_1_1_2.length();
      
      lcd.setCursor(0,0);

      for (int i = 0; i < sequence_1_1_1.length(); i++) {
        lcd.print(sequence_1_1_1.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(95);
      }
      
      lcd.setCursor(0, 1);
  
      for (int i = 0; i < sequence_1_1_2.length(); i++) {
        lcd.print(sequence_1_1_2.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(95);
      }

      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);

      String sequence_1_2_1 = "The Roomba."; 
      int sequence_1_2_Length = sequence_1_2_1.length();
  
      for (int i = 0; i < sequence_1_2_Length; i++) {
        lcd.print(sequence_1_2_1.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(95);
      }
      
      afterJoke();

    }

    if (command == "run_laugh_sequence_5") {
      digitalWrite(13, HIGH);
      lcd.clear( );
      
      // Sequence // Joke(1) or Pun(2) // Line
      String sequence_1_1_1 = "What do robots";
      String sequence_1_1_2 = "eat for snacks?";

      int sequence_1_1_Length = sequence_1_1_1.length() + sequence_1_1_2.length();
      
      lcd.setCursor(0,0);

      for (int i = 0; i < sequence_1_1_1.length(); i++) {
        lcd.print(sequence_1_1_1.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(95);
      }
      
      lcd.setCursor(0, 1);
  
      for (int i = 0; i < sequence_1_1_2.length(); i++) {
        lcd.print(sequence_1_1_2.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(95);
      }

      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);

      String sequence_1_2_1 = "Micro-Chips."; 
      int sequence_1_2_Length = sequence_1_2_1.length();
  
      for (int i = 0; i < sequence_1_2_Length; i++) {
        lcd.print(sequence_1_2_1.charAt(i));
        int randFreq = random(700, 1100);
        tone(8, randFreq, 100);
        delay(95);
      }
      
      afterJoke();

    }

    // When "wink" button is clicked             
    if (command == "run_wink_sequence") {
      digitalWrite(13, HIGH);
      winkOnLCD();
      delay(1500);
      eyesOnLCD();
      digitalWrite(13, LOW);
    }
    
    // When "clap" button is clicked     
    if (command == "run_clap_sequence") {
      digitalWrite(13, HIGH);
        
      // Make servo go to 180 degrees 
      Servo1.write(180); 
        
      delay(1000);
      blinkOnLCD();
      delay(2000);
      eyesOnLCD();

      // Make servo go to 0 degrees 
      Servo1.write(0);
        
      digitalWrite(13, LOW);

    }

    // When "heart" button is clicked     
    if (command == "run_heart_sequence") {
      lcd.clear();
      heartOnLCD();
      heartbeat();
      lcd.clear();      
      eyesOnLCD();

    }
    
  }
}

void eyesOnLCD() {
  
	// Define character
	lcd.createChar(0, eyetopleft);
  lcd.createChar(1, eyetopright);
  lcd.createChar(2, eyebottomleft);
  lcd.createChar(3, eyebottomright);
 
	// Eyes (open) placement on LCD
	lcd.setCursor(0, 0);
  lcd.write(byte(0));
  
  lcd.setCursor(1, 0);
  lcd.write(byte(1));
  
  lcd.setCursor(0, 1);
  lcd.write(byte(2));
  
  lcd.setCursor(1, 1);
  lcd.write(byte(3));
  
  lcd.setCursor(14, 0);
  lcd.write(byte(0));
  
  lcd.setCursor(15, 0);
  lcd.write(byte(1));
  
  lcd.setCursor(14, 1);
  lcd.write(byte(2));
  
  lcd.setCursor(15, 1);
  lcd.write(byte(3));  
}

void blinkOnLCD() {
  
	// Define character
  lcd.createChar(4, blinktop);
  lcd.createChar(5, blinkbottom);
 
	// Eyes (blink) placement on LCD
  lcd.setCursor(0, 0);
  lcd.write(byte(4));
  
  lcd.setCursor(1, 0);
  lcd.write(byte(4));
  
  lcd.setCursor(0, 1);
  lcd.write(byte(5));
  
  lcd.setCursor(1, 1);
  lcd.write(byte(5));
  
  lcd.setCursor(14, 0);
  lcd.write(byte(4));
  
  lcd.setCursor(15, 0);
  lcd.write(byte(4));
  
  lcd.setCursor(14, 1);
  lcd.write(byte(5));
  
  lcd.setCursor(15, 1);
  lcd.write(byte(5));
}

void winkOnLCD() {

	// Define character
  lcd.createChar(4, blinktop);
  lcd.createChar(5, blinkbottom);
 
	// Wink placement on LCD (left)
  lcd.setCursor(14, 0);
  lcd.write(byte(4));
  
  lcd.setCursor(15, 0);
  lcd.write(byte(4));
  
  lcd.setCursor(14, 1);
  lcd.write(byte(5));
  
  lcd.setCursor(15, 1);
  lcd.write(byte(5));

}

void heartOnLCD() {
  
  // Define character
	lcd.createChar(6, hearttopleft);
  lcd.createChar(7, hearttopmiddle);
  lcd.createChar(8, hearttopright);
  lcd.createChar(9, heartbottomleft);
  lcd.createChar(10, heartbottommiddle);
  lcd.createChar(11, heartbottomright);
 
	// Heart placement on LCD
	lcd.setCursor(0, 0);
  lcd.write(byte(6));
  
  lcd.setCursor(1, 0);
  lcd.write(byte(7));

  lcd.setCursor(2, 0);
  lcd.write(byte(8));
  
  lcd.setCursor(0, 1);
  lcd.write(byte(9));

  lcd.setCursor(1, 1);
  lcd.write(byte(10));

  lcd.setCursor(2, 1);
  lcd.write(byte(11));
  
  lcd.setCursor(13, 0);
  lcd.write(byte(6));
  
  lcd.setCursor(14, 0);
  lcd.write(byte(7));

  lcd.setCursor(15, 0);
  lcd.write(byte(8));
  
  lcd.setCursor(13, 1);
  lcd.write(byte(9));
  
  lcd.setCursor(14, 1);
  lcd.write(byte(10));

  lcd.setCursor(15, 1);
  lcd.write(byte(11));

}

void afterJoke() {

  delay(2000);
  lcd.clear();
  eyesOnLCD();
  delay(300);      
  blinkOnLCD();
  delay(1000);
  eyesOnLCD();
  delay(500);
  blinkOnLCD();
  delay(1500);
  digitalWrite(13, LOW);
  eyesOnLCD();

}

void heartbeat() {

  digitalWrite(13, HIGH);
  tone(8, 400, 100);
  delay(300);
  digitalWrite(13, LOW);
  tone(8, 300, 100);
  delay(800);
  digitalWrite(13, HIGH);
  tone(8, 400, 100);
  delay(300);
  digitalWrite(13, LOW);
  tone(8, 300, 100);
  delay(800);
  digitalWrite(13, HIGH);
  tone(8, 400, 100);
  delay(300);
  digitalWrite(13, LOW);
  tone(8, 300, 100);
  delay(800);
  digitalWrite(13, HIGH);
  tone(8, 400, 100);
  delay(300);
  digitalWrite(13, LOW);
  tone(8, 300, 100);

}