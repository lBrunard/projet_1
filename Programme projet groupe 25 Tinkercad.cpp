//Projet de groupe n°1
//Participants : Emilien DRON, Iman El Azzouzi, Luis Brunard
//Groupe n° 25
//Projet : Systeme de refroidissement en fonction d'une sonde de température
//Réalistation du projet sur simulateur Tinkercad
// Lien du projet Tinkercad :
//                            https://www.tinkercad.com/things/4IH2eJjZ9rW-lcd-lux-temp/editel




       //Biblioteques
#include<Servo.h>
#include<LiquidCrystal.h>


        // analogique
int tempcellPin = 1; //Pin capteur analo TEMP
int pot1 = 0; //Pin  pot analo 1

        // sorties
int red = 6;
int green = 8;
int orange = 7;
const int buzzer = 10;
Servo serv1;
int moteur = 13;
int bouton = A2;

        //data
int data_pot1; //data servo
int tempcell_data; // data TEMP en volt
int angle = 0;

        //ecran init
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(void) { 
  pinMode(buzzer, OUTPUT); 
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(orange, OUTPUT);
  pinMode(moteur,OUTPUT);
  pinMode(A2, INPUT_PULLUP);
  // J'initatlise le bouton en pin analogique alors qu'a la base c'est digital
  //C'est pourquoi je rajoute "PULLUP", (plus assez de place sur les pin digitales)
  serv1.attach(9);      //Je defini le servo en pin 9
  Serial.begin(9600);
  lcd.begin(16,2);      //je set les dimensions de l'écran
  lcd.print("Test");    // je teste l'écran a chaque fois que le programme se lance

}
void loop(void) {

    //conversion des entrées analog en data
    int tempcell_data = analogRead(tempcellPin);
    int data_pot1 = analogRead(pot1);

   //convertisseur volt vers temp réel
    float volt = tempcell_data * 5.0;
    volt /= 1024.0;
    float temperature = (volt - 0.5) * 100;

    // Servo 
    int angle = tempcell_data; 
    // On "re-scale" la valeur pour l'avoir dans 180°
    angle = map(angle, 0, 1023, 0, 511);
    serv1.write(angle);
  
  	//Bouton
  	int bouton_data = digitalRead(bouton);
    if(bouton_data == 0){
   	digitalWrite(moteur, HIGH);
    }
    else{
   	digitalWrite(moteur, LOW); 
    }

    //MOTEUR 
  	// On "re-scale la valeure du potentio de 0 a 125"
    int seuil = (data_pot1 / 8.192);
    Serial.print("Votre seuil est de : ");
    Serial.println(seuil);

    if (temperature > seuil){
        digitalWrite(moteur, HIGH);
    }
  
  	//Ecran
  	  lcd.setCursor(0, 0);
      lcd.print("Temp : ");
      lcd.print(temperature);
      lcd.setCursor(0, 1);
  	  lcd.print("Seuil : ");
  	  lcd.setCursor(8, 1);
  	  lcd.print(seuil);
  	
    
    // LED + BUZZER
    int seuil_alerte = seuil + 10;
    if (temperature > seuil_alerte){
    digitalWrite(red, HIGH);
      tone(buzzer, 1000, 500);
      delay(500);
      digitalWrite(red, LOW);
      noTone(buzzer);
      Serial.print(temperature);
      Serial.println(" : STOP !!!");
      delay(500);
 

    }
    else if (temperature > seuil){
      digitalWrite(orange, HIGH);
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      Serial.print(temperature);
      Serial.println(" : SURCHAUFFE !!");
      delay(1000);
 
    }
    else{ 
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);
      digitalWrite(orange, LOW);
      Serial.print("Temperature : ");
      Serial.println(temperature);
      delay(1000);
    }

}
