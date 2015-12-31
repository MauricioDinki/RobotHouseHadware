/*
* Variables
*/

/* The time when the sensor outputs a low impulse */
long unsigned int lowIn;

/* The amount of milliseconds the sensor has to be low
   before we assume all motion has stopped */
long unsigned int pause = 3000;

boolean lockLow = true;
boolean takeLowTime;

int calibrationTime = 10;  /* Calibration time */
int pirPin = 7;    /* PIR sensor pin */

/*
* Setup
*/

void setup(){
  /* Start serial monitor and the PIR sensor */
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  /* Calibrating */
    for(int i = 0; i < calibrationTime; i++){
      delay(1000);
      }
    delay(50);
  }

/*
* Loop
*/
void loop(){

     if(digitalRead(pirPin) == HIGH){
       if(lockLow){
         /* Makes sure we wait for a transition to LOW before any
            further output is made */
         lockLow = false;
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec");
         delay(50);
         }
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){
       if(takeLowTime){
        lowIn = millis();          /* Save the time of the transition from high to LOW */
        takeLowTime = false;       /* Make sure this is only done at the start of a LOW phase */
        }
       /* If the sensor is low for more than the given pause,
          we assume that no more motion is going to happen */
       if(!lockLow && millis() - lowIn > pause){
           /* makes sure this block of code is only executed again after
              a new motion sequence has been detected */
           lockLow = true;
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
  }
