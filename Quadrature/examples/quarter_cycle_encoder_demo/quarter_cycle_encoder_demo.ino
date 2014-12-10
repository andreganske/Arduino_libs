/*
This is a demo play with code to handle quarter cycle rotary encoders.
There are two different samples.
First Rotary encoder onto pins 2 and 3.
Another rotary encoder onto pins 4 and 5.
If you are using quarter cycle encoders there will be 1 "up" (or down) per click.
If you get 2 "up" (or down) per click then they are half cycle encoders.
If there are 4 "up" (or down) per click then they are full cycle encoders.
For half cycle and full cycle you need to use the library and the samples attached.
If ,, while turning it the one way, you get a few 'wrong' readings ,, then replace the encoder with
a newer, better one or include a "debounce" system in the INO.

In use, you would replace the "up" and "down" with the desired simconnect codes from "link2fs_Multi".
In this demo,, the pins above pin 5 could be used for "keys" in the "Multi".
*/
int CodeIn;// used on all serial reads
int KpinNo; 
int Koutpin;
byte RE1;
String KoldpinStateSTR, KpinStateSTR, Kstringnewstate,Kstringoldstate;

void setup() 
{
  Kstringoldstate = "111111111111111111111111111111111111111111111111111111111111111111111";
  
  for (int KoutPin = 2; KoutPin <= 19; KoutPin++)// Get all the pins ready as imputs 
  {
    pinMode(KoutPin, INPUT);
    digitalWrite(KoutPin, HIGH);  
  }
 Serial.begin(115200);   
}//end of setup

void loop() {
  {INPUTPINS();} //Check the Simconnect and "keys" section
  if (Serial.available()) {
    CodeIn = getChar();
    //if (CodeIn == '=') {EQUALS();} // The first identifier is "="
   // if (CodeIn == '<') {LESSTHAN();}// The first identifier is "<"
    //if (CodeIn == '?') {QUESTION();}// The first identifier is "?"
    //if (CodeIn == '/') {SLASH();}// The first identifier is "/" (Annunciators)
  }
}//end of void loop

char getChar()// Get a character from the serial buffer
{
  while(Serial.available() == 0);// wait for data
  return((char)Serial.read());// Thanks Doug
}//end of getChar

void INPUTPINS() // Simconnect codes and "Keys" section (combined)
{
  Kstringnewstate = "";
  for (int KpinNo = 2; KpinNo <= 19; KpinNo++){ //set to the input pins. (pins 2 to 70 ,, change for Uno cards)
    KpinStateSTR = String(digitalRead(KpinNo)); 
    KoldpinStateSTR = String(Kstringoldstate.charAt(KpinNo - 2));// set to the first pin read (The 2)
    if (KpinStateSTR != KoldpinStateSTR)
    {     // check rotary encoder No.1 --------------------------------------- on pins 2 and 3
        if (KpinNo == 2){  // the first pin of rotary encoder no.1
         int otherPin = digitalRead(3);
         if (KpinStateSTR == "0"){
         if  (otherPin == HIGH){RE1 = 1;}else {RE1 = 2;}
         }else{ 
         if  (otherPin == LOW){RE1 = 1;}else {RE1 = 2;}
         }
         if (RE1 ==1)Serial.println("UP");
         if (RE1 ==2)Serial.println("down");
         } //end of RE1's first pin cycle
           
          if (KpinNo == 3){// the other pin of rotary encoder no.1
           int otherPin = digitalRead(2);
         if (KpinStateSTR == "0"){
         if  (otherPin == LOW){RE1 = 1;}else {RE1 = 2;}
         }else{ 
         if  (otherPin == HIGH){RE1 = 1;}else {RE1 = 2;}
         }
         if (RE1 ==1)Serial.println("UP.");
         if (RE1 ==2)Serial.println("down.");
          }//end of RE1's 'other' pin cycle 
          
       // check rotary encoder No.2 --------------------------------------- on pins 4 and 5
       if (KpinNo == 4){ // the first pin of rotary encoder no.2
          int otherPin = digitalRead(5);
         if (KpinStateSTR == "0"){
         if  (otherPin == LOW){Serial.println ("up.");}else {Serial.println ("down.");}
         }else{ 
         if  (otherPin == HIGH){Serial.println ("up.");}else {Serial.println ("down.");}
         }
         }//end of RE2's first pin cycle 
           
          if (KpinNo == 5){// the 'other' pin of rotary encoder no.2
           int otherPin = digitalRead(4);
         if (KpinStateSTR == "0"){
         if  (otherPin == HIGH){Serial.println ("up");}else {Serial.println ("down");}
         }else{ 
         if  (otherPin == LOW){Serial.println ("up");}else {Serial.println ("down");}
         }
         }//end of RE2's 'other' pin cycle 
         // ------------- now the "Keys" bit -------------------
         if (KpinNo > 5){//this number needs to be higher than the encoder pins
      Serial.print ("D"); 
      if (KpinNo < 10) Serial.print ("0");
      Serial.print (KpinNo);
      Serial.println (KpinStateSTR);
      }//end of the "keys" bit
      
    }//end of yes it's different       
    Kstringnewstate += KpinStateSTR;
  }//end of 'for' loop
  Kstringoldstate = Kstringnewstate;
}//end of inputpins void

