/*
Petit programme de control du capteur de couleur
Avant de commencer, bien vérifier que la LED est allumée
*/

#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define SCL 15 // I2C clock signal serial data
#define SDA 14 // I2C serrial I/O


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Capteur de couleur :");
};

void loop() {
  // first with the raw datas
  tcs.setInterrupt(true);  // turn off LED
  uint16_t r, g, b, c, Temp, lux;
  tcs.getRawData(&r, &g, &b, &c);

  // second with getRGB
  /*float r, g, b;
  tcs.getRGB(&r, &g, &b);*/
  /*
  Serial.println("New Aquisition :");
  Serial.print("red = ");
  Serial.println(r);
  Serial.print("green = ");
  Serial.println(g);
  Serial.print("blue = ");
  Serial.println(b);
  Serial.print("lum = ");
  Serial.println(c);
  delay(500);*/
};
