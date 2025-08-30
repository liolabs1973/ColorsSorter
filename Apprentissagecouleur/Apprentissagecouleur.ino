#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <LiquidCrystal_I2C.h>

// Initialisation du capteur avec les paramètres de gain et d'intégration
Adafruit_TCS34725 capteur = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

// Écran LCD I2C à l'adresse 0x3F
LiquidCrystal_I2C lcd(0x3f, 20, 4);

// Structure pour stocker les couleurs de référence
struct CouleurRef {
  uint16_t r;
  uint16_t g;
  uint16_t b;
};

//CouleurRef roseRef, vertRef, bleuRef, blancRef, brunRef, , jauneRef, grisRef, orangeRef, noirRef;
CouleurRef bleuRef, noirRef, mauveRef, vertRef, rougeRef;
// Définition du bouton poussoir de confirmation
int pinBouton = 7;
int etatBouton;

void setup() {
  
  pinMode(pinBouton,INPUT_PULLUP);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Trieur module ++");
  lcd.setCursor(0, 1);
  lcd.print("Projet realise par");
  lcd.setCursor(0, 2);
  lcd.print("Louis Paul 6EQMA");

  delay (3000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Init. TCS347725");
  Serial.println("");
  Serial.println("Init. TCS347725");
   lcd.setCursor(0, 1);
  if (capteur.begin()) {
    lcd.print("Capteur TCS34725 OK");
    Serial.println("Capteur TCS34725 OK !");
  } else {
    lcd.print("Erreur TCS34725");
    Serial.println("Erreur TCS34725.");
    while (1);
  }
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Blue Module");
  lcd.setCursor(0, 2);
  lcd.print("Press a key");
  Serial.println("Place une couleur bleu devant le capteur et appuie sur une touche...");
  while (!Serial.available());
  calibrerCouleur(bleuRef);
  lcd.setCursor(0, 0);
  lcd.print("Remove Blue Module");

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Green Module");
  lcd.setCursor(0, 2);
  lcd.print("Press a key");
  Serial.println("Place une couleur verte devant le capteur et appuie sur une touche...");
  while (!Serial.available());
  calibrerCouleur(vertRef);
  lcd.setCursor(0, 0);
  lcd.print("Remove Green Module");

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Purple Module");
  lcd.setCursor(0, 2);
  lcd.print("Press a key");
  Serial.println("Place une couleur mauve devant le capteur et appuie sur une touche...");
  while (!Serial.available());
  calibrerCouleur(mauveRef);
  lcd.setCursor(0, 0);
  lcd.print("Remove purple Module");

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Red Module");
  lcd.setCursor(0, 2);
  lcd.print("Press a key");
  Serial.println("Place une couleur rouge devant le capteur et appuie sur une touche...");
  while (!Serial.available());
  calibrerCouleur(rougeRef);
  lcd.setCursor(0, 0);
  lcd.print("Remove Red Module");

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Black Module");
  lcd.setCursor(0, 2);
  lcd.print("Press a key");
  Serial.println("Place une couleur noir devant le capteur et appuie sur une touche...");
  while (!Serial.available());
  calibrerCouleur(noirRef);
  lcd.setCursor(0, 0);
  lcd.print("Remove Black Module");
  Serial.println("Calibration terminée !");
}

void loop() {
  uint16_t r, g, b, c;
  capteur.getRawData(&r, &g, &b, &c);

  Serial.print("Lecture actuelle - R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.println(b);

  String couleur = detecterCouleur(r, g, b);
  Serial.println("Couleur détectée : " + couleur);
  delay(2000);
}

void calibrerCouleur(CouleurRef &ref) {
  uint16_t r, g, b, c;
  capteur.getRawData(&r, &g, &b, &c);
  ref.r = r;
  ref.g = g;
  ref.b = b;
  Serial.println("Valeurs enregistrées !");
  Serial.read(); // vider le buffer
}

String detecterCouleur(uint16_t r, uint16_t g, uint16_t b) {
  if (estProche(r, g, b, vertRef)) return "Vert";
  if (estProche(r, g, b, bleuRef)) return "Bleu";
  if (estProche(r, g, b, mauveRef)) return "Mauve";
  if (estProche(r, g, b, rougeRef)) return "Rouge";
  if (estProche(r, g, b, noirRef)) return "Noir";
  return "Inconnue";
}

bool estProche(uint16_t r, uint16_t g, uint16_t b, CouleurRef ref) {
  int seuil = 1000; // tolérance
  return abs(r - ref.r) < seuil && abs(g - ref.g) < seuil && abs(b - ref.b) < seuil;
}
