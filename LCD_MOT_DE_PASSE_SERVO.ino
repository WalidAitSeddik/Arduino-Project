#include <Keypad.h>
#include <Servo.h>  // Ajouter la bibliothèque pour contrôler le servo moteur
#include <LiquidCrystal.h>  // Ajouter la bibliothèque pour le LCD

// Dimensions du clavier
const byte ROWS = 4; // 4 lignes
const byte COLS = 4; // 4 colonnes

// Disposition des touches dans l'ordre que tu as donné
char keys[ROWS][COLS] = {
  {'1','2','3','A'},    // Première ligne : D C B A
  {'4','5','6','B'},    // Deuxième ligne : # 9 6 3
  {'7','8','9','C'},    // Troisième ligne : 0 8 5 2
  {'*','0','#','D'}     // Quatrième ligne : * 7 4 1
};

// Connexions des lignes et des colonnes
byte rowPins[ROWS] = {2, 3, 4, 5}; // Lignes 1 à 4
byte colPins[COLS] = {6, 7, 8, 9}; // Colonnes 1 à 4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String correctPassword = "2505";  // Mot de passe valide
String enteredPassword = "";  // Ce que l'on entre

const int greenLEDPin = 51;  // LED verte

const int servoPin = 12;     // Broche pour le contrôle du servo

Servo myServo;  // Créer une instance du servo moteur

// Initialiser l'écran LCD (broches 22 à 27)
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

void setup() {
  Serial.begin(9600);
  pinMode(greenLEDPin, OUTPUT);
  
  myServo.attach(servoPin);  // Attacher le servo à la broche 12
  myServo.write(0);  // Placer le servo à la position initiale (0°)

  // Initialiser le LCD
  lcd.begin(16, 2);  
  lcd.print("Entrez le code");
  Serial.println("Entrez le code...");
}

void loop() {
  char key = keypad.getKey(); // Lire la touche appuyée

  if (key != NO_KEY) {  // Si une touche est pressée
    Serial.print("Touche pressée : ");
    Serial.println(key);

    // Afficher une étoile sur l'écran LCD pour chaque chiffre entré
    if (key != '#' && key != '*') {  // Ne pas afficher * ou # sur le LCD
      enteredPassword += key;  // Ajouter la touche à l'entrée
      lcd.setCursor(enteredPassword.length() - 1, 1);  // Positionner le curseur
      lcd.print('*');  // Afficher une étoile pour chaque chiffre
    }

    // Si la touche # est appuyée pour valider
    if (key == '#') { 
      if (enteredPassword == correctPassword) {
        Serial.println("Code correct !");
        lcd.clear();
        lcd.print("Bienvenue chez vous!");
        digitalWrite(greenLEDPin, HIGH);  // Allumer la LED verte
        myServo.write(90);  // Déplacer le servo à 90° (mouvement du moteur)
        delay(1000);         // Attendre 1 seconde
        myServo.write(0);   // Revenir à la position initiale (0°)
        delay(500);          // Attendre avant de pouvoir entrer un autre code
        digitalWrite(greenLEDPin, LOW);   // Éteindre la LED verte
      } else {
        Serial.println("Code incorrect !");
        lcd.clear();
        lcd.print("Code erroné");
        lcd.setCursor(0, 1);
        lcd.print("Veuillez réessayer");
        delay(1000);                    // Garder la LED allumée pendant 1 seconde
      }
      enteredPassword = "";  // Réinitialiser l'entrée
      lcd.clear();
      lcd.print("Entrez le code");
    }

    // Si on appuie sur * pour annuler l'entrée
    if (key == '*') {  
      enteredPassword = "";  // Effacer le mot de passe
      lcd.clear();
      lcd.print("Mot de passe effacé.");
      delay(1000);  // Attendre un instant avant de recommencer
      lcd.clear();
      lcd.print("Entrez le code");
    }
  }
}
