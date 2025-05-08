#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

// PIR et buzzer
const int pirPin = 11;
const int buzzerPin = 13;
bool motionDetected = false;

// LCD (broches de commande)
const int lcdPowerPin = 53;
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
bool lcdOn = false;
unsigned long lcdTimer = 0;

// Clavier 4x4
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Mot de passe
const String correctPassword = "2505";
String enteredPassword = "";

// LED verte et rouge
const int greenLEDPin = 51;
const int redLEDPin = 50;

// Servo
Servo myServo;
const int servoPin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(lcdPowerPin, OUTPUT);
  digitalWrite(lcdPowerPin, LOW); // LCD éteint au début

  myServo.attach(servoPin);
  myServo.write(0); // Position initiale
}

void loop() {
  int pirState = digitalRead(pirPin);

  // Si mouvement détecté
  if (pirState == HIGH && !motionDetected) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    motionDetected = true;

    digitalWrite(lcdPowerPin, HIGH);
    lcd.begin(16, 2);
    lcd.print("Entrez le code");
    lcdOn = true;
  }

  if (pirState == LOW) {
    motionDetected = false;
  }

  // Gestion clavier
  if (lcdOn) {
    char key = keypad.getKey();
    if (key != NO_KEY) {
      Serial.print("Touche : ");
      Serial.println(key);

      if (key != '#' && key != '*') {
        enteredPassword += key;7

        
        lcd.setCursor(enteredPassword.length() - 1, 1);
        lcd.print('*');
      }

      if (key == '#') {
        if (enteredPassword == correctPassword) {
          lcd.clear();
          lcd.print("Bienvenue chez vous");
          digitalWrite(greenLEDPin, HIGH);
          myServo.write(150);
          delay(5000); // Reste à 90° pendant 5 sec
          myServo.write(0);
          digitalWrite(greenLEDPin, LOW);
          lcdTimer = millis();
        } else {
          lcd.clear();
          lcd.print("Code errone");
          lcd.setCursor(0, 1);
          lcd.print("Reessayez");
          digitalWrite(redLEDPin, HIGH);
          delay(1000);
          digitalWrite(redLEDPin, LOW);
          lcd.clear();
          lcd.print("Entrez le code");
        }
        enteredPassword = "";
      }

      if (key == '*') {
        enteredPassword = "";
        lcd.clear();
        lcd.print("Efface...");
        delay(1000);
        lcd.clear();
        lcd.print("Entrez le code");
      }
    }

    // Éteindre l’écran 2 secondes après code accepté
    if (lcdTimer > 0 && millis() - lcdTimer > 2000) {
      digitalWrite(lcdPowerPin, LOW);
      lcdOn = false;
      lcdTimer = 0;
    }
  }
}
