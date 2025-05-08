#include <Keypad.h>

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

void setup() {
  Serial.begin(9600);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
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
        delay(1000);                      // Garder la LED allumée pendant 1 seconde
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
