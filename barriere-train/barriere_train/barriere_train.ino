#include <Servo.h>
Servo monServo;
int photocellPin = 0; // the cell and 10K pulldown are connected to a0
int photocellReading; // the analog reading from the analog resistor divider
int nReadStart;
int barrierestate=3;
unsigned long  nCloseBarriereTime = 0;
void setup()
{
    monServo.attach(2, 1000, 2000);
 //   monServo.write(90);
    Serial.begin(9600);
    nReadStart = analogRead(photocellPin);
    FermerBarriere();
    
}

void ouvrirBarriere(){
  if (barrierestate != 0){
    Serial.println("Ouvrir  ");
    barrierestate = 0;
    monServo.write(10);
  }
}

void FermerBarriere(){
  if (barrierestate != 1){
    Serial.println("Fermer  ");
    barrierestate = 1;
    monServo.write(180);
  }
}
 
void loop()
{
  /*
  delay(10000);
  monServo.write(10);
  delay(3000);
    monServo.write(180);
    */
  photocellReading = analogRead(photocellPin);
  if( abs (photocellReading - nReadStart) > 100){
    //delay(1000);
    ouvrirBarriere();
    nCloseBarriereTime = 0;
  }
  else{
    if (nCloseBarriereTime == 0){
    nCloseBarriereTime = millis() + 1000;
    Serial.println("set close timer"  );
    }
     
    
  }
  if (millis() > nCloseBarriereTime 
       && nCloseBarriereTime != 0){
         FermerBarriere();
       }
  
   Serial.print(abs (photocellReading - nReadStart) );
      Serial.print(" " );
      Serial.print(nCloseBarriereTime );
      Serial.print(" " );
      Serial.print(barrierestate );
      Serial.print(" " );
      Serial.println(" " );
 
   
   
  
  delay(100);
}
