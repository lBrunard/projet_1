//Projet de groupe n°1
//Participants : Emilien DRON, Iman El Azzouzi, Luis Brunard
//Groupe n° 25
//Projet : Systeme de refroidissement en fonction d'une sonde de température
//Réalistation du projet en physique
// Commentaire :
//                Le projet est quelque peut different dans la réalité car la sonde de température n'est pas la meme
//                De plus, je ne peux pas faire varier la température de mon local aussi facilement que sur tinkercad, 
//                j'utilise donc principalement le potentiometre faisant varier le seuil pour actionner le mécanisme
//                Au final la base du projet reste quand meme équivalente



    //Initaisation des bibliotheques donc celle de la sonde de température qui est une sonde DHT11 digital de chez velleman
#include <Servo.h>
#include <DHT.h>
#define DHTPIN 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
Servo serv;

int red = 5;
int green = 3;
int orange = 2;
int buzzer = 7;
int pot = 0;
int moteur = 8;

int data_pot;
int seuil;

void setup(){
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(orange, OUTPUT);
  pinMode(moteur, OUTPUT);
  Serial.begin(9600);
  Serial.println("TEST");
  dht.begin();
  serv.attach(4);
}

void loop(){
  float t = dht.readTemperature();

  
  int data_pot = analogRead(pot);
  int seuil = data_pot;
    seuil = map(seuil, 0, 1024, 0, 50);
  int seuil_alerte = seuil + 5;

  int angle = t;
  serv.write(angle);
  
  if (isnan(t)){
      Serial.println(F("Failed to read sensor form DHT !!"));
      delay(500);
      return;
  }
  if (isnan(pot)){
    Serial.println(F("Failed to read pot1 !!"));
    delay(500);
    return;
  }
  if (t > seuil_alerte){
    digitalWrite(moteur, HIGH);
    digitalWrite(orange, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    Serial.print("Le seuil est de : ");
    Serial.println(seuil);
    Serial.print(t);
    Serial.println(" : STOP !!!"); 
    delay(500);
    tone(buzzer, 1000, 500);
    delay(500);
    noTone(buzzer );
  }
  else if (t > seuil){
    digitalWrite(moteur, HIGH);
    digitalWrite(orange, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    Serial.print("Le seuil est de : ");
    Serial.println(seuil);
    Serial.print(t);
    Serial.println(" : SURCHAUFFE !!");
    delay(500);
  }
  else{ 
    digitalWrite(moteur, LOW);
    digitalWrite(orange, LOW);
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    Serial.print("Le seuil est de : ");
    Serial.println(seuil);
    Serial.print("Temperature : ");
    Serial.println(t);
    delay(500);
  }
}
