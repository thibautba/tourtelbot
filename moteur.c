#include <Dynamixel2Arduino.h>

// Définition de l'ID des moteurs
const uint8_t LEFT_SERVO_ID = 2;  
const uint8_t RIGHT_SERVO_ID = 1;
const float DXL_PROTOCOL_VERSION = 2.0;

// Définition des broches et des ports série
#define DXL_SERIAL   Serial3
#define DXL_DIR_PIN  84

// Initialisation Dynamixel2Arduino
Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

void setup() {
  // Initialisation de la communication série pour les moteurs
  DXL_SERIAL.begin(57600);
  dxl.begin(DXL_SERIAL, DXL_DIR_PIN);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  // Initialisation de la communication série pour le moniteur série
  Serial.begin(9600);
  while (!Serial) {
    ; // Attendre que le port série soit prêt
  }

  // Définition du mode des moteurs (Position Control Mode par défaut)
  dxl.torqueOff(LEFT_SERVO_ID);
  dxl.torqueOff(RIGHT_SERVO_ID);
  dxl.setOperatingMode(LEFT_SERVO_ID, OP_POSITION);
  dxl.setOperatingMode(RIGHT_SERVO_ID, OP_POSITION);
  dxl.torqueOn(LEFT_SERVO_ID);
  dxl.torqueOn(RIGHT_SERVO_ID);

  Serial.println("Entrez les positions des moteurs (format: gauche droite):");
}

void loop() {
  // Vérifier si des données sont disponibles sur le port série
  if (Serial.available() > 0) {
    // Lire l'entrée de l'utilisateur
    String input = Serial.readStringUntil('\n');
    input.trim(); // Supprimer les espaces inutiles

    // Séparer les valeurs entrées
    int spaceIndex = input.indexOf(' ');
    if (spaceIndex > 0) {
      String leftPositionStr = input.substring(0, spaceIndex);
      String rightPositionStr = input.substring(spaceIndex + 1);

      // Convertir les chaînes de caractères en entiers
      int32_t leftPosition = leftPositionStr.toInt();
      int32_t rightPosition = rightPositionStr.toInt();

      // Envoyer les commandes aux moteurs
      dxl.setGoalPosition(LEFT_SERVO_ID, leftPosition);
      dxl.setGoalPosition(RIGHT_SERVO_ID, rightPosition);

      Serial.print("Moteur gauche positionné à : ");
      Serial.println(leftPosition);
      Serial.print("Moteur droit positionné à : ");
      Serial.println(rightPosition);
    } else {
      Serial.println("Erreur: Veuillez entrer deux valeurs séparées par un espace.");
    }
  }
}
