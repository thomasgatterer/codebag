/* 
  Button

  Turns on and off a light emitting diode(LED) connected to digital
  pin 13, when pressing a pushbutton attached to pin 2.


  The circuit:
   LED attached from pin 13 to ground
   pushbutton attached to pin 2 from +5V
   10K resistor attached to pin 2 from ground

   Note: on most Arduinos there is already an LED on the board
  attached to pin 13.


  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/

/*
  Melody

  Plays a melody

  circuit:
   8-ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://arduino.cc/en/Tutorial/Tone

*/

#include "pitches.h"

// constants won't change. They're used here to
// set pin numbers:
const int button1 = 1;     // the number of the pushbutton pin
const int button2 = 5;     // the number of the pushbutton pin
const int button3 = 7;     // the number of the pushbutton pin
const int button4 = 8;

const int speacker =  10;

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int oldButtonState1 = 0;         // to check if something has changed
int oldButtonState2 = 0;
int oldButtonState3 = 0;
int oldButtonState4 = 0;

// notes in the melody:
int melodyOk[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int melodyNok[] = {
  NOTE_C4, NOTE_G3, NOTE_C4, NOTE_G3, NOTE_C4, NOTE_G3, NOTE_C4, NOTE_G3,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurationsOk[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int noteDurationsNok[] = {
  4, 4, 4, 4, 4, 4, 4, 4
};

void playOk() {//SilendMode                 // wait for a second
  Serial.print("offen!!");
}
void playOkLaud() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDurationOk = 1000 / noteDurationsOk[thisNote];
    tone(speacker, melodyOk[thisNote], noteDurationOk);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDurationOk * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speacker);
  }
}

void playNokSilendMode() {
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(50);                       // wait for a second
  }
    Serial.print("lärm lärm lärm lärm ");
}
void playNok() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDurationNok = 1000 / noteDurationsNok[thisNote];
    tone(speacker, melodyNok[thisNote], noteDurationNok);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDurationNok * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speacker);
  }
}


int openigState = 0;//nothing done
//  openigState = 1;//first right knop opened
//  openigState = 2;//second right knop opened
//  openigState = 3;//third right knop opened
//  openigState = 4;//last right knop opened al ok nothing to do
// right sequence is 2134

int inputCount = 0;


void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(speacker, OUTPUT);

  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}


void checkState() {
  // Zustand 0 entspricht Knopf geschlossen

  if (openigState == 0 && buttonState2 == 1)
    openigState = 1;

  if (openigState == 0 && (buttonState1 == 1 ||
                           buttonState3 == 1 ||
                           buttonState4 == 1)) {
    openigState = 0;
    playNok();
  }
  //----------------------------
  if (openigState == 1 && buttonState1 == 1)
    openigState = 2;

  if (openigState == 1 && ( //buttonState2==0 ||
        buttonState3 == 1 ||
        buttonState4 == 1)) {
    openigState = 0;
    playNok();
  }
  //----------------------------
  if (openigState == 2 && buttonState3 == 1)
    openigState = 3;

  if (openigState == 2 && ( //buttonState1==0 ||
        buttonState3 == 1 ||
        buttonState4 == 1)) {
Serial.print("openigState "); Serial.print(openigState); Serial.print("buttonStates "); Serial.print(buttonState1); Serial.print(", "); Serial.print(buttonState2); Serial.print(", "); Serial.print(buttonState3); Serial.print(", "); Serial.print(buttonState4); Serial.print(", "); 
    openigState = 0;
    playNok();
  }
  //----------------------------
  if (openigState == 3 && buttonState4 == 1) {
    playOk();
    openigState = 0;
  }

  if (openigState == 3 && (buttonState1 == 0 ||
                           buttonState2 == 0
                           /* buttonState3==0*/)) {
    openigState = 0;
    playNok();
  }
  // right sequence is 2134
  

}

void printSome() {
  // Zustand 0 entspricht Knopf geschlossen
  Serial.print(buttonState1);
  Serial.print(",");
  Serial.print(buttonState2);
  Serial.print(",");
  Serial.print(buttonState3);
  Serial.print(",");
  Serial.print(buttonState4);
  Serial.print("--> ");
  Serial.print(openigState);
  Serial.print("\n");
}

void loop() {
  // read the state of 1the pushbutton value:
  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2);
  buttonState3 = digitalRead(button3);
  buttonState4 = digitalRead(button4);


  // if state changed check new Status
  if (oldButtonState1 != buttonState1 && buttonState1 == 1)
  {
    checkState();
    //printSome();
  }
  if (oldButtonState2 != buttonState2 && buttonState2 == 1)
  {
    checkState();
    //printSome();
  }
  if (oldButtonState3 != buttonState3 && buttonState3 == 1)
  {
    checkState();
    //printSome();
  }
  if (oldButtonState4 != buttonState4 && buttonState4 == 1)
  {
    checkState();
    //printSome();
  }
printSome();

  if (!buttonState1 && !buttonState2 && !buttonState3 && !buttonState4) {
    Serial.print("loked ");
    openigState = 0;
  }

  oldButtonState1 = buttonState1;
  oldButtonState2 = buttonState2;
  oldButtonState3 = buttonState3;
  oldButtonState4 = buttonState4;

  delay(100);
}

