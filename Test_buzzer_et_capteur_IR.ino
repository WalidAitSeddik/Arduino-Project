const int pirPin = 11;
const int buzzerPin = 13;

unsigned long previousMillis = 0;
const long buzzerOnTime = 100; // 100 ms
bool buzzerState = false;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int pirState = digitalRead(pirPin);
  unsigned long currentMillis = millis();

  if (pirState == HIGH && !buzzerState) {
    digitalWrite(buzzerPin, HIGH); // Allume le buzzer
    buzzerState = true;
    previousMillis = currentMillis;
  }

  // Éteindre le buzzer après 100 ms
  if (buzzerState && currentMillis - previousMillis >= buzzerOnTime) {
    digitalWrite(buzzerPin, LOW);
    buzzerState = false;
  }
}
