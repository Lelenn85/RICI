#include <IRremote.h>
const int RECV_PIN = 4;  
IRrecv irrecv(RECV_PIN); // On définit le signal reçu par la PIN 4.

decode_results results; // Comande qui lit et enregistre la donnée envoyé.
// Les chiffres ci-dessous sont uniques, ils seront différents sur votre programme. Obtention des chiffres expliqué plus tard.
const int ON = 69;
const int OFF = 71;
const int valH = 24;
const int valB = 82;
const int valG = 8;
const int valD = 90;
const int valSTOP = 28;
const int valRAS = 0; 
int valSignal = valRAS; // Par défault le signal est nul donc "Valeur Rien A Signaler".
int trig = 2;
int echo = 3; //PWM
long lecture_echo;
long cm;
int pontActif = 7;
int moteurGF = 10; //PWM
int moteurGB = 11; //PWM
int moteurDF = 9; //PWM
int moteurDB = 6; //PWM
int power = 100;

//------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600); // Initialisation des baud à 9600.
  irrecv.enableIRIn(); // Initialisation de la transmition de données.
  irrecv.blink13(true); // Fait clignoter la led present sur l'arduino pour vérifier si l'on recoit le signal.
  pinMode(trig, OUTPUT); // Définit trig en sortie.
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT); // Définit echo en entrée.
  pinMode(moteurGF,OUTPUT); // Définit moteur gauche avancer en sortie.
  pinMode(moteurGB,OUTPUT); // Définit moteur gauche reculer en sortie.
  pinMode(moteurDF,OUTPUT); // Définit moteur droit avancer en sortie.
  pinMode(moteurDB,OUTPUT); // Définit moteur droit reculer en sortie.
  pinMode(pontActif,OUTPUT); // Définit trig en sortie.
}
//------------------------------------------------------------------------------------------------------------
void etat() {
    valSignal = irrecv.decodedIRData.command; //ValSignal sera égal au chiffre envoyé depuis la télécommande.
    Serial.println(valSignal); // Affiche valSignal dans le moniteur série.
  if (irrecv.decode()) { // Choisit un état selon la valeur reçu.
    switch (valSignal) {
      case ON:
        valSignal == ON;
        delay(100);
      break;
      
      case OFF:
        valSignal == OFF;
        delay(100);
      break;
      
      
      case valH:
        valSignal == valH;
        delay(100);
      break;
 
      case valB:
        valSignal == valB;  
        delay(100);  
      break;
 
      case valG:
        valSignal == valG;
        delay(100);
      break;
 
      case valD:
        valSignal == valD;
        delay(100);
      break;

      case valSTOP:
        valSignal == valSTOP;
        delay(100);
      break;
    }
    
    irrecv.resume(); // Reçoit les valeurs suivantes.
  }
}

//------------------------------------------------------------------------------------------------------------
void son(){ // Envoie une pulsation aller-retour pour évaluer la distance que le sépare d'un obstacle puis l'affiche sur le moniteur série.

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    lecture_echo = pulseIn(echo,HIGH);
    cm = lecture_echo /58;
    Serial.print("Distance en cm :");
    Serial.println(cm);
    delay(250);
  if (cm <= 15){ // Si la distance entre le robot et un obstacle  est inférieur à 15cm, le robot s'arrête, tourne vers la droite pendant 2s et réévalue la distance.
    valSignal == valSTOP;
    delay(1000);
    analogWrite(moteurGF,power);
    analogWrite(moteurGB,0);
    analogWrite(moteurDF,0);
    analogWrite(moteurDB,power);
    delay(2000);
  }
  
}
//------------------------------------------------------------------------------------------------------------
void moteur(){ // En fonction de l'état choisit préceddemment, on attribue une trajectoire aux moteurs (haut, bas, droite, gauche).
  
    digitalWrite(pontActif,HIGH); // "Pont" ici veut dire le passage de données et de courant pour permettre aux moteurs de fonctionner. 
  if (valSignal == valH) { // Avancer.
    analogWrite(moteurGF,power);
    analogWrite(moteurGB,0);
    analogWrite(moteurDF,power);
    analogWrite(moteurDB,0);
  }
  else if (valSignal == valB) { // Reculer.
    analogWrite(moteurGF,0);
    analogWrite(moteurGB,power);
    analogWrite(moteurDF,0);
    analogWrite(moteurDB,power);
  }
  else if (valSignal == valG) { // Gauche.
    analogWrite(moteurGF,0);
    analogWrite(moteurGB,power);
    analogWrite(moteurDF,power);
    analogWrite(moteurDB,0);
  }
  else if (valSignal == valD) { // Droite.
    analogWrite(moteurGF,power);
    analogWrite(moteurGB,0);
    analogWrite(moteurDF,0);
    analogWrite(moteurDB,power);
  }
  else if (valSignal == valSTOP) { // Arrêt.
    analogWrite(moteurGF,0);
    analogWrite(moteurGB,0);
    analogWrite(moteurDF,0);
    analogWrite(moteurDB,0);
  }
    

  
}
//------------------------------------------------------------------------------------------------------------
void loop() { 
moteur();
}
