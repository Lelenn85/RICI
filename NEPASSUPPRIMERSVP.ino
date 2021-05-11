#include <IRremote.h>
const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);

decode_results results;
const int ON = 69;
const int OFF = 71;
const int valH = 24;
const int valB = 82;
const int valG = 8;
const int valD = 90;
const int valSTOP = 28;
const int valRAS = 0;
int valSignal = valRAS;
int trig = 2;
int echo = 3; //PWM
long lecture_echo;
long cm;
int ledR = 12;
int pontActif = 7;
int moteurGF = 10; //PWM
int moteurGB = 11; //PWM
int moteurDF = 9; //PWM
int moteurDB = 6; //PWM
int power = 100;

//------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); 
  irrecv.blink13(true);
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  pinMode(moteurGF,OUTPUT);
  pinMode(moteurGB,OUTPUT);
  pinMode(moteurDF,OUTPUT);
  pinMode(moteurDB,OUTPUT);
  pinMode(pontActif,OUTPUT);
}
//------------------------------------------------------------------------------------------------------------
void etat() {
    valSignal = irrecv.decodedIRData.command;
    Serial.println(valSignal);
  if (irrecv.decode()) {
    switch (valSignal) {
      case ON:
        valSignal == ON;
        delay(250);
      break;
      
      case OFF:
        valSignal == OFF;
        delay(250);
      break;
      
      
      case valH:
        valSignal == valH;
        delay(250);
      break;
 
      case valB:
        valSignal == valB;  
        delay(250);  
      break;
 
      case valG:
        valSignal == valG;
        delay(250);
      break;
 
      case valD:
        valSignal == valD;
        delay(250);
      break;

      case valSTOP:
        valSignal == valSTOP;
        delay(250);
      break;
    }
    
    irrecv.resume(); // Receive the next value
  }
}

//------------------------------------------------------------------------------------------------------------
void son(){

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    lecture_echo = pulseIn(echo,HIGH);
    cm = lecture_echo /58;
    Serial.print("Distance en cm :");
    Serial.println(cm);
    delay(250);
  if (cm <= 15){
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
void moteur(){
  
    digitalWrite(pontActif,HIGH);  
  if (valSignal == valH) {
    analogWrite(moteurGF,power);
    analogWrite(moteurGB,0);
    analogWrite(moteurDF,power);
    analogWrite(moteurDB,0);
  }
  else if (valSignal == valB) {
    analogWrite(moteurGF,0);
    analogWrite(moteurGB,power);
    analogWrite(moteurDF,0);
    analogWrite(moteurDB,power);
  }
  else if (valSignal == valG) {
    analogWrite(moteurGF,0);
    analogWrite(moteurGB,power);
    analogWrite(moteurDF,power);
    analogWrite(moteurDB,0);
  }
  else if (valSignal == valD) {
    analogWrite(moteurGF,power);
    analogWrite(moteurGB,0);
    analogWrite(moteurDF,0);
    analogWrite(moteurDB,power);
  }
  else if (valSignal == valSTOP) {
    analogWrite(moteurGF,0);
    analogWrite(moteurGB,0);
    analogWrite(moteurDF,0);
    analogWrite(moteurDB,0);
  }
    

  
}
//------------------------------------------------------------------------------------------------------------
void loop() {
 etat();
 moteur();
 son();

 
}
