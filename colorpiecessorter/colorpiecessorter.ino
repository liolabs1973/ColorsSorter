#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <LiquidCrystal_I2C.h>

// Capteur couleur
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

// Écran LCD I2C à l'adresse 0x3F
LiquidCrystal_I2C lcd(0x3f, 20, 4);

// Structure pour stocker les couleurs de référence
struct CouleurRef {
  uint16_t r;
  uint16_t g;
  uint16_t b;
};

CouleurRef noirRef, roseRef, vertRef, blancRef, brunRef, mauveRef, JauneRef, grisRef, OrangeRef;


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Trieur module + +");
  lcd.setCursor(0, 1);
  lcd.print("Projet realise par");
  lcd.setCursor(0, 2);
  lcd.print("Louis Paul 6EQMA");
  
  if (tcs.begin()) {
    Serial.println("Capteur TCS34725 OK");
  } else {
    Serial.println("Erreur capteur !");
    while (1); // Stop programme
  }
  delay(2000); // Laisse le message s'afficher
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  if (c > 50) { // Seuil de détection
    uint16_t colorTemp = tcs.calculateColorTemperature(r, g, b);
    uint16_t lux = tcs.calculateLux(r, g, b);

    // Affichage série
    Serial.print("R: "); Serial.print(r);
    Serial.print(" G: "); Serial.print(g);
    Serial.print(" B: "); Serial.print(b);
    Serial.print(" Lux: "); Serial.print(lux);
    Serial.print(" Temp: "); Serial.print(colorTemp);
    Serial.println(" K");

    // Affichage LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("R:"); lcd.print(r);
    lcd.print(" G:"); lcd.print(g);

    lcd.setCursor(0, 1);
    lcd.print("B:"); lcd.print(b);
    lcd.print(" C:"); lcd.print(c);

    lcd.setCursor(0, 2);
    lcd.print("Lux:"); lcd.print(lux);

    lcd.setCursor(0, 3);
    lcd.print("Temp:"); lcd.print(colorTemp);
    lcd.print("K");

  } else {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Pas de couleur");
    Serial.println("Pas de couleur détectée");
  }

  delay(2000); // Attente entre les mesures
}
