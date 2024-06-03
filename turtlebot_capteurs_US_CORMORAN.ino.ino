//GROUPE CORMORAN 1A ASE: SCRIPT D'ACQUISITION DES DISTANCES POUR LES 3 CAPTEURS DU TURTLEBOT
//Carte OpenCR 1.0
//Auteurs : PEAUPARDIN Pierre
//          BAROTTIN Thibaut
//          TONDEUR Vlad           
//          NOTTER Nicolas
//
//date : 20/02/2024
//date modif n°[]: [...] (à compléter si modifications ultérieures)


//déclaration des Pins (voir datasheet pour correspondance) :

int trigPinCenter = BDPIN_GPIO_16;    // Trigger centre sur pin 18
int echoPinCenter = BDPIN_GPIO_15;    // Echo centre sur pin 17
int trigPinLeft = BDPIN_GPIO_18;    // Trigger gauche sur pin 20
int echoPinLeft = BDPIN_GPIO_17;    // Echo gauche sur pin 19
int trigPinRight = BDPIN_GPIO_14;    // Trigger droit sur pin 16
int echoPinRight = BDPIN_GPIO_13;    // Echo droit sur pin 15

//déclaration des variables utilisées
long durationCenter, durationLeft, durationRight, cmCenter, cmLeft, cmRight;

void setup() {
  Serial.begin (9600);
  //Définition des entrées/sorties
  
  //capteur central
  pinMode(trigPinCenter, OUTPUT);
  pinMode(echoPinCenter, INPUT);
  
  //capteur gauche
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  
  //capteur droit
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);

}

void loop() {

  //activation succéssives des différents capteurs par un HIGH pulse de 10
  //microsecondes, on effectue un court LOW pulse auparavant 
  //pour s'assurer que le HIGH pulse sera propre

  //!!!!ATTENTION!!!! On doit ici séparer en 3 étapes l'acquisition des signaux 
  // à cause du fonctionnement de la fonction PulseIn 
  // On évitera d'appeler la fonction PulseIn dans une interruption (friendly reminder)

  // activation du capteur central
  digitalWrite(trigPinCenter, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinCenter, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinCenter, LOW);

  //enregistrement de la mesure
  durationCenter = pulseIn(echoPinCenter, HIGH);

  // activation du capteur gauche
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, LOW);

  //enregistrement de la mesure
  durationLeft = pulseIn(echoPinLeft, HIGH);

  // activation du capteur droit
  digitalWrite(trigPinRight, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRight, LOW);

  //enregistrement de la mesure
  durationRight = pulseIn(echoPinRight, HIGH);

  //calcul des 3 distances en cm
  cmCenter = (durationCenter/2) / 29.1;
  cmLeft = (durationLeft/2) / 29.1;
  cmRight = (durationRight/2) / 29.1;

  //affichage dans le serial
  Serial.print("capteur droit : ");
  Serial.print(cmRight);
  Serial.println(" cm");

  Serial.print("capteur central : ");
  Serial.print(cmCenter);
  Serial.println(" cm");

  Serial.print("capteur gauche : ");
  Serial.print(cmLeft);
  Serial.println(" cm");
  
  Serial.println();

  //délai pour le temps d'affichage (peut être réduit si besoin)
  delay(250);

}
