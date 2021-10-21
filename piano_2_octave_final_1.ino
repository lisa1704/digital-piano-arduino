#define analogInPin1 A3
#define analogInPin2 A4
#define analogInPin3 A5
#define speaker 8
#define EASY 2
#define MED 3
#define HARD 4
#define merah 5 
#define hijau 6
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 10, 9, 13, 7);
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int easyques[4]={};
int easyanswer[4]={};
int medques[6]={};
int medanswer1[4]={};
int medanswer2[4]={};
int hardques[4]={};
int hardanswer1[4]={};
int hardanswer2[4]={};
int hardanswer3[4]={};
int i,j,k;
bool fault = false;

int length = 28; // the number of notes

char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";
char prNotes[]="GGA4GCB4 GGA4GD4c";
char bottomnotes[]="GEC#4B4A4 FFECD4C";
char wrong[]="Wrong Note";
char success[]="Congratulations!";
char loadingmessage[]="Loading";
char complete[]="Please Complete Tune";
char selectmode[]= "Select Mode";

int easy[]={261,294,312,349};
char easyNotes[]= "C D4 D#4 F";
int beats[] = { 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8,8, 16, 1, 2,2,8,8,8,8,16, 1,2,2,8,8,8,16 };

int tempo = 200;

char frequency_noteS[] = {'C4', 'C#4', 'D4', 'D#4', 'E4', 'F4', 'F#4', 'G4', 
                   'G#4', 'A4', 'A#4', 'B4', 'C5', 'C#5', 'D5', 'D#5', 
                   'E5', 'F5', 'F#5', 'G5', 'G#5', 'A5', 'A#5', 'B5', 'C6'};

int frequency[] = {261, 278, 294, 312, 330, 349, 371, 392, 
                   416, 440, 467, 493, 523, 554, 587, 622, 
                   660, 698, 739, 783, 830, 880, 932, 987, 1046};

char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           

                 'c', 'd', 'e', 'f', 'g', 'a', 'b',

                 'x', 'y' };

char medNotes[]= "C D4 D#4 G";
char medBottomNotes[]= "A4 B4";
int med[]={261, 294 ,312, 392 , 440, 493};

int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,

                 956,  834,  765,  593,  468,  346,  224,

                 655 , 715 };

int upperLimit[] = {50, 150, 300, 450, 650, 
                    800, 900, 960, 1000};

int lowerLimit[] = {0, 51, 151, 301, 451, 
                    651, 801, 901, 961};

void setup() {
    lcd.begin(16, 2);
  // Print a message to the LCD.
 lcd.print("Digital Piano");
  loading();
  lcd.clear();
  pinMode (EASY,INPUT);
  pinMode (MED,INPUT);
  pinMode (HARD,INPUT);
  pinMode (speaker, OUTPUT);
  pinMode (hijau, OUTPUT);
  pinMode (merah, OUTPUT);
    lcd.print(selectmode);

  lcd.setCursor(0, 1);

  lcd.print("Mode");
	
  Serial.begin(9600);
}

void loading () {
  lcd.setCursor(0, 1);
  lcd.print(loadingmessage);

  for (int i = 0; i < 9; i++) {
    delay(500);
    lcd.print(".");
  }
}

void loop() {

  if(digitalRead(EASY)== LOW){
  easyquestion();
  easyquestioncheck();
  }
  else if(digitalRead(MED)== LOW){
  medquestion();
  medquestioncheck();
  }
  else if(digitalRead(HARD)== LOW){
  hardquestion();
  hardquestioncheck();
  }
  else {
    readMelody();
  }
  

  Serial.println(frequency[i]);
}


void readMelody() {    
  sensorValue1 = analogRead(analogInPin1);   
  for(int i = 0; i<8; i++)
  {
    if (sensorValue1 < upperLimit[i]  && sensorValue1 >= lowerLimit[i]){
      tone(speaker,frequency[i],100);
    }
  }
  sensorValue2 = analogRead(analogInPin2);   
  for(int i = 0; i<8; i++)
  {
    if (sensorValue2 < upperLimit[i]  && sensorValue2 >= lowerLimit[i]){
      tone(speaker,frequency[i+8],100);
    }
  }
  sensorValue3 = analogRead(analogInPin3);   
  for(int i = 0; i<9; i++)
  {
    if (sensorValue3 < upperLimit[i]  && sensorValue3 >= lowerLimit[i]){
      tone(speaker,frequency[i+16],100);
    }
  } 
  
}

void easyquestion(){
  	lcd.clear();
  	lcd.print("Easy Mode");
    	

   for(int j =0;j<4;j++){
    digitalWrite(speaker,HIGH);
    int randomfrequency = frequency[random(7)];
    char randomnote = frequency_noteS[random(7)];
    easyques[j]=easy[j];
    tone(speaker,randomfrequency,300);
  
 
    digitalWrite(speaker,LOW);
    delay(500);
	
   }	lcd.clear();
    	lcd.print(easyNotes);


 }

void easyquestioncheck(){
  for(k =0;k<4;k++){
    sensorValue1=1023;
      while (sensorValue1==1023){
      sensorValue1 = analogRead(analogInPin1);   
        for(i = 0; i<8; i++)
        {
          if (sensorValue1 < upperLimit[i]  && sensorValue1 >= lowerLimit[i]){
            tone(speaker,frequency[i],60);
            easyanswer[k]=frequency[i];
          }
        }
      }
    if(easyanswer[k] == easyques[k]){
    digitalWrite(hijau,HIGH);
    delay(200);
    digitalWrite(hijau,LOW);
    }
    if(easyanswer[k] != easyques[k]){
    fault = true;
    digitalWrite(merah,HIGH);
       lcd.clear();
    lcd.print(wrong);
    delay(200);
     
      lcd.clear();
      	lcd.print(easyNotes);

    digitalWrite(merah,LOW);
    }
  }
  
  if(fault)
  {
    lcd.clear();
    lcd.print("Try Again");
        delay(300);
    
     lcd.clear();
    lcd.print("Select MODE");

  }
  
  else{
    lcd.clear();
    lcd.print("CONGRATULATIONS");
        lcd.setCursor(0,1);
    lcd.print("Passed Easy Mode");
        delay(500);
    
     lcd.clear();
    lcd.print("Select MODE");
  }
  fault = false;
}

void medquestion(){
  lcd.clear();
  	lcd.print("Medium Mode");
  for(int j =0;j<7;j++){
      digitalWrite(speaker,HIGH);
      medques[j]=med[j];
      tone(speaker,medques[j],300);
      digitalWrite(speaker,LOW);
      delay(500);
      Serial.println(medques[j]); 
   }
  
  lcd.clear();
        	lcd.print(medNotes);

    	lcd.setCursor(0,1);
    	lcd.print(medBottomNotes);


  
}

void medquestioncheck(){
   
  for(k =0;k<6;k++){
    sensorValue1=1023;
    sensorValue2=1023;
      while (sensorValue1==1023&&sensorValue2==1023){
        sensorValue1 = analogRead(analogInPin1);   
        for(i = 0; i<8; i++)
        {
          if (sensorValue1 < upperLimit[i]  && sensorValue1 >= lowerLimit[i]){
            tone(speaker,frequency[i],100);
            medanswer1[k]=frequency[i];
          }
          sensorValue2 = analogRead(analogInPin2);   
          for(int i = 0; i<8; i++)
          {
            if (sensorValue2 < upperLimit[i]  && sensorValue2 >= lowerLimit[i]){
              tone(speaker,frequency[i+8],100);
              medanswer2[k]=frequency[i+8];
            }
          }
        }
      }
    if(medanswer1[k] == medques[k]|| medanswer2[k] == medques[k]){
      digitalWrite(hijau,HIGH);
      delay(200);
      digitalWrite(hijau,LOW);
    }
    if(medanswer1[k] != medques[k]&& medanswer2[k] != medques[k]){
       lcd.clear();
		
      lcd.print(medques[k]);
      digitalWrite(merah,HIGH);
      	fault= true;
        lcd.setCursor(0, 1);
		
      	lcd.print(wrong);
      delay(200);
      lcd.clear();
      	lcd.print(medNotes);

    	lcd.setCursor(0,1);
    	lcd.print(medBottomNotes);
      digitalWrite(merah,LOW);
    }
  }
  
  if(fault)
  {
    lcd.clear();
    lcd.print("Try Again");
        delay(300);
    
     lcd.clear();
    lcd.print("Select MODE");

  }
  
  else{
    lcd.clear();
    lcd.print("CONGRATULATIONS");
    lcd.setCursor(0,1);
    lcd.print("Passed Medium Mode");
        delay(400);
    
     lcd.clear();
    lcd.print("Select MODE");
  }
}
void playTone(int tone, int duration) {

for (long i = 0; i < duration * 1000L; i += tone * 2) {

    digitalWrite(speaker,HIGH);

   delayMicroseconds(tone);

    digitalWrite(speaker,LOW);

   delayMicroseconds(tone);

}

}
void playNote(char note, int duration) {

char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           

                 'c', 'd', 'e', 'f', 'g', 'a', 'b',

                 'x', 'y' };

int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,

                 956,  834,  765,  593,  468,  346,  224,

                 655 , 715 };

int SPEE = 5;

// play the tone corresponding to the note name

for (int i = 0; i < 17; i++) {

   if (names[i] == note) {
    int newduration = duration/SPEE;
     playTone(tones[i], newduration);

   }

}

}
void hardquestion(){
   lcd.clear();
  	lcd.print("Hard Mode");
 
for (int i = 0; i < 28; i++) {

   if (notes[i] == ' ') {

     delay(beats[i] * tempo); // rest

   } else {

     playNote(notes[i], beats[i] * tempo);

   }

   // pause between notes

   delay(tempo);
 
  
}
    lcd.clear();
   lcd.print(prNotes);
  	lcd.setCursor(0,1);
     lcd.print(bottomnotes);

}
void hardquestioncheck(){
  for(k =0;k<4;k++){
    sensorValue1=1023;
    sensorValue2=1023;
    sensorValue3=1023;
      while (sensorValue1==1023&&sensorValue2==1023&&sensorValue3==1023){
        sensorValue1 = analogRead(analogInPin1);   
        for(i = 0; i<8; i++)
        {
          if (sensorValue1 < upperLimit[i]  && sensorValue1 >= lowerLimit[i]){
            tone(speaker,frequency[i],60);
            hardanswer1[k]=frequency[i];
          }
          sensorValue2 = analogRead(analogInPin2);   
          for(int i = 0; i<8; i++)
          {
            if (sensorValue2 < upperLimit[i]  && sensorValue2 >= lowerLimit[i]){
              tone(speaker,frequency[i+8],60);
              hardanswer2[k]=frequency[i+8];
            }
          }
          sensorValue3 = analogRead(analogInPin3);   
          for(int i = 0; i<9; i++)
          {
            if (sensorValue3 < upperLimit[i]  && sensorValue3 >= lowerLimit[i]){
              tone(speaker,frequency[i+16],60);
              hardanswer3[k]=frequency[i+16];
            }
          } 
        }
      }
    if(hardanswer1[k] == hardques[k]|| hardanswer2[k] == hardques[k]|| hardanswer3[k] == hardques[k]){
      digitalWrite(hijau,HIGH);
      delay(200);
      digitalWrite(hijau,LOW);
    }
    if(hardanswer1[k] != hardques[k]&& hardanswer2[k] != hardques[k]&& hardanswer3[k] != hardques[k]){
      digitalWrite(merah,HIGH);
      delay(200);
      digitalWrite(merah,LOW);
    }
  }
}