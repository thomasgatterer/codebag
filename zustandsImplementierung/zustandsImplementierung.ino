// Quelle: https://www.youtube.com/watch?v=32FkQvnlMcc&t=2696s
// zustandsdiagramm in www.draw.io

//author: Daniel Rainer (DR)
//created: 19/02/2019
//updated by Thomas Gatterer (TG) on 18.04.2019

//DR
/*
 * This program monitors buttons connected to the ATMega328p chip it is running on.
 * If a connection is interrupted it activates an alert,
 * except the connection is the one specified in the sequenceOfButtons.
 * If all buttons were opened in the right sequence feedback is auditive given.
 * Upon closing the buttons again the program will reset.
 * Taking too long to unlock the buttons also causes the alert to be triggered.
 * 
 * How to connect everything:
 * 
 *       - +
 * ||||||||||||||
 * ) ATMega328p
 * ||||||||||||||
 *   B   +-  B BS
 *   
 * Legend:
 * -: GND
 * +: +5V
 * B: button (connect each button to GND)
 * S: speaker/sound (connect the speaker to GND)
 */
 
//the pin the speaker is connected to
const byte soundPin = 8;
//the number of buttons used
const byte numberOfButtons = 3;
//the pins the buttons are attached to, in the order the must be opened for success
//length of array must be equal to number of buttons
const byte sequenceOfButtons[] = {5, 1, 7};
//true if all buttons were opened in correct sequence, otherwise false
boolean unlocked = false;

//settings for the alert sound
//the number of tones used
byte numberOfAlertTones = 4;
//the frequency of the tones in Hertz, length must be equal to numberOfAlertTones
int alertTones[] = {400, 300, 200, 100};
//the duration of the tones in milliseconds, length must be equal to numberOfAlertTones
int alertTonesDurations[] = {200, 200, 200, 200};

//settings for the success sound
//the number of tones used
byte numberOfSuccessTones = 4;
//the frequency of the tones in Hertz, length must be equal to numberOfSuccessTones
int successTones[] = {600, 700, 800, 900};
//the duration of the tones in milliseconds, length must be equal to numberOfAlertTones
int successTonesDurations[] = {100, 100, 100, 100};

// Quelle: https://www.youtube.com/watch?v=32FkQvnlMcc&t=2696s
//TG
typedef enum {STATE_ON, STATE_COUNT, STATE_OFF, STATE_A, STATE_B, STATE_C} STATES;

STATES currentState = STATE_OFF, lastState = STATE_COUNT;

const byte LED_OUT = 13;

const byte WECHSLER_IN = 12;
const byte ONOFF_IN = 12;

void setup() {
  //sets each button pin to INPUT_PULLUP, meaning that digitaRead will return false if it is connected to GND, otherwise true
  for(byte i = 0; i < numberOfButtons; i++){
    pinMode(sequenceOfButtons[i], INPUT_PULLUP);
  }
  //sets the soundPin to OUTPUT
  pinMode(soundPin, OUTPUT);
}

void loop() {
  //read all pins (no changes during processing)


  if(currentState == STATE_ON)
  {
    // ENTRY
    if (lastState != currentState)
    {
      digitalWrite(LED_OUT, HIGH);
    }
    //DO
    if (!digitalRead(WECHSLER_IN))
    {
    }
  }
  else if (currentState == STATE_A)
  {
    //ENTRY
    //DO
    //EXIT
  }
  else if (currentState == STATE_B)
  {
  }
  else if (currentState == STATE_C)
  {
  }
  
}

//this function is called after an illegal action was committed
//it plays the alert sound and resets the sequence once all buttons are closed
void alert(){
  playSound(numberOfAlertTones, alertTones, alertTonesDurations);
}

//this function is called after all buttons were opened in the correct order
//the function plays the alert sound and resets the sequence once all buttons are closed
void success(){
  playSound(numberOfSuccessTones, successTones, successTonesDurations);
}

//used for playing sound
//takes the number of tones, 
//followed by an array containing the frequency of each individual tone in Hertz,
//followed by an array containing the duration of each individual tone in milliseconds
void playSound(byte numberOfTones, int tones[], int durations[]){
  for(byte i = 0; i < numberOfTones; i++){
    //starts to put out a signal on the pin with the number indicated by soundPin
    //with the frequency defined by the second argument
    tone(soundPin, tones[i]);
    //the tone is played for this many milliseconds
    delay(durations[i]);
    //stops the tone
    noTone(soundPin);
  }
}

