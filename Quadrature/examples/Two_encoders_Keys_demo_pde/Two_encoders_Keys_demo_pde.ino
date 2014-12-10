/******************************************************************************
 *  quadrature_two_encoders
 *  Keith Neufeld
 *  July 4, 2008
 *  Modified by Jim NZ to input into my "Keys" program
 *  Read and decode two quadrature rotary encoders.
 *  Demo system has encoders connected to digital pins 2/3 and 4/5.
 
 *This is a demo for the "inOut" program
 *To use on the "multi" just change the 'Serial.print' to
 *Serial.println' and enter the simconnect codes to suit.
 
 ******************************************************************************/
#include "math.h"
#include "Quadrature.h"
Quadrature quad1(2, 3);
Quadrature quad2(4, 5);

long Xold1;// the first encoder "old" reading
long Xold2;// the second encoder "old" reading

void setup() {
  Serial.begin(115200);
}

void loop() { 
  long X1 =(quad1.position())/2;  // divide by 2 for half cycle encoders
    if (X1 != Xold1){  
      if (X1 > Xold1) {Serial.print("D740");} 
      if (X1 < Xold1) {Serial.print("D750");}
      Xold1 = X1;     // overwrites the old reading with the new one.
      }//end of quad1 read
    
  long X2 =(quad2.position());  // for full cycle encoders
    if (X2 != Xold2) {
      if (X2 > Xold2) {Serial.print("D760");} 
      if (X2 < Xold2) {Serial.print("D770");}
      Xold2 = X2;     // overwrites the old reading with the new one.
      }//end of quad2 read

}

