#include <Keypad.h>
#include <Servo.h>  // Ajouter la bibliothèque pour contrôler le servo moteur

// Dimensions du clavier
const byte ROWS = 4; // 4 lignes
const byte COLS = 4; // 4 colonnes

// Disposition des touches dans l'ordre que tu as donné
char keys[ROWS][COLS] = {
  {'D','C','B','A'},    // Première ligne : D C B A
  {'#','9','6','3'},    // Deuxième ligne : # 9 6 3
  {'0','8','5','2'},    // Troisième ligne : 0 8 5 2
  {'*','7','4','1'}     // Quatrième ligne : * 7 4 1
};

// Connexions des lignes et des colonnes
byte rowPins[ROWS] = {2, 3, 4, 5}; // Lignes 1 à 4
byte colPins[COLS] = {6, 7, 8, 9}; // Colonnes 1 à 4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String correctPassword = "2505";  // Mot de passe valide
String enteredPassword = "";  // Ce que l'on entre

const int greenLEDPin = 10;  // LED verte
const int redLEDPin = 11;    // LED rouge
const int servoPin = 12;     // Broche pour le contrôle du servo

Servo myServo;  // Créer une instance du servo moteur

void setup() {
  Serial.begin(9600);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  myServo.attach(servoPin);  // Attacher le servo à la broche 12
  myServo.write(0);  // Placer le servo à la position initiale (0°)
  Serial.println("Entrez le code...");
}

void loop() {
  char key = keypad.getKey(); // Lire la touche appuyée

  if (key != NO_KEY) {  // Si une touche est pressée
    Serial.print("Touche pressée : ");
    Serial.println(key);

    if (key == '#') { // Validation du mot de passe
      if (enteredPassword == correctPassword) {
        Serial.println("Code correct !");
        digitalWrite(greenLEDPin, HIGH);  // Allumer la LED verte
        myServo.write(90);  // Déplacer le servo à 90° (mouvement du moteur)
        delay(1000);         // Attendre 1 seconde
        myServo.write(0);   // Revenir à la position initiale (0°)
        delay(500);          // Attendre avant de pouvoir entrer un autre code
        digitalWrite(greenLEDPin, LOW);   // Éteindre la LED verte
      } else {
        Serial.println("Code incorrect !");
        digitalWrite(redLEDPin, HIGH);  // Allumer la LED rouge
        delay(1000);                    // Garder la LED allumée pendant 1 seconde
        digitalWrite(redLEDPin, LOW);   // Éteindre la LED rouge
      }
      enteredPassword = "";  // Réinitialiser l'entrée
    }
    else if (key == '*') {  // Si on appuie sur '*' pour annuler
      enteredPassword = "";  // Effacer le mot de passe
      Serial.println("Mot de passe effacé.");
    }
    else {
      enteredPassword += key;  // Ajouter la touche à l'entrée
    }
  }
}
