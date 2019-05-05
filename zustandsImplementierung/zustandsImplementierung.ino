// Quelle: https://www.youtube.com/watch?v=32FkQvnlMcc&t=2696s
// zustandsdiagramm in www.draw.io https://www.draw.io/#G1oj2BH5IgK97ofaZLbmdGWQQ03IAkYIRX

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
 *ARD AAAAAA A 111
 *INO 543210-R+32109
 *ATMe22222222211111
 *gPin87654321098765
 *    ||||||||||||||
 *          - +
 *    ) ATMega328p
 *      B   +-  B BS
 *    ||||||||||||||
 *ATMe12345678901234
 *gPins        11111
 *ARD R01234+-CL5678
 *INO SDDDDD  OKDDDD
 * Legend:
 * -: GND
 * +: +5V
 * B: button (connect each button to GND)
 * S: speaker/sound (connect the speaker to GND)
 * TG Pin Conversion Arduino to Atmega: http://2.bp.blogspot.com/-AQF-uoqHQc8/VjrCdhMtz_I/AAAAAAAAOeg/oWabG7CbbXc/s1600/atmega328-arduino-pinout.jpg
 */
 
//the pin the speaker is connected to
const byte soundPin = 8;
//the number of buttons used
const byte numberOfButtons = 3;
//the pins the buttons are attached to, in the order the must be opened for success
//length of array must be equal to number of buttons
const byte sequenceOfButtons[] = {5, 2, 7};
//on every loop the states of Buttons get stored
boolean stateOfButtons[numberOfButtons];
//true if all buttons were opened in correct sequence, otherwise false
boolean unlocked = false;

//settings for the alert sound
//the number of tones used
byte numberOfAlertTones = 4;
//the frequency of the tones in Hertz, length must be equal to numberOfAlertTones
int alertTones[] = {400, 300, 100, 100};
//the duration of the tones in milliseconds, length must be equal to numberOfAlertTones
int alertTonesDurations[] = {200, 200, 200, 200};

//settings for the success sound
//the number of tones used
byte numberOfSuccessTones = 4;
//the frequency of the tones in Hertz, length must be equal to numberOfSuccessTones
int successTones[] = {600, 700, 800, 1000};
//the duration of the tones in milliseconds, length must be equal to numberOfAlertTones
int successTonesDurations[] = {100, 100, 100, 100};

// Quelle: https://www.youtube.com/watch?v=32FkQvnlMcc&t=2696s
//TG
typedef enum {STATE_CLOSED, STATE_FIRST_OPENED, STATE_SECOND_OPENED, STATE_OPEN, STATE_SEMI_OPENCLOSED} STATES;


STATES currentState = STATE_CLOSED, lastState = STATE_CLOSED;

void setup() {
  //sets each button pin to INPUT_PULLUP, meaning that digitaRead will return false if it is connected to GND, otherwise true
  for(byte i = 0; i < numberOfButtons; i++){
    pinMode(sequenceOfButtons[i], INPUT_PULLUP);
pinMode(3, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
pinMode(6, INPUT_PULLUP);
  }

  const int lowestPin = 2;
  const int highestPin = 13;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);


  /*/ Alternative output setting set pins 2 through 13 as INPUT_PULLUP exept Sound Pin:
  for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++) {
    if(thisPin!=soundPin)
    {
      Serial.print("Pin = ");
      Serial.println(thisPin);
      pinMode(sequenceOfButtons[thisPin], INPUT_PULLUP);
    }
  }*/
  
  //initialize all buttons
  for(byte i = 0; i < numberOfButtons; i++){
    stateOfButtons[i]=false;
  }  
  //sets the soundPin to OUTPUT
  pinMode(soundPin, OUTPUT);

  success();
}

void loop() {

  delay(300); // change to let it sleep for less power consumtion
   
  //read all pins (no changes during processing)
  for(byte i = 0; i < numberOfButtons; i++){
    stateOfButtons[i]=digitalRead(sequenceOfButtons[i]);
  } //true in stateOfButtons means is opened

Serial.print("Button a: "); Serial.print(stateOfButtons[0]);
Serial.print(" b: "); Serial.print(stateOfButtons[1]);
Serial.print(" c: "); Serial.print(stateOfButtons[2]);

Serial.print("  currentState: "); Serial.println(currentState);
  
  if(currentState == STATE_CLOSED)
  {
    // ENTRY
    if (lastState != currentState)
    {
      lastState = currentState;
    }
    //DO
    //EXIT
    if (stateOfButtons[0]==true)
    {
      currentState = STATE_FIRST_OPENED;
    }
    if (stateOfButtons[1]==true||stateOfButtons[2]==true)
    {
      alert();
      currentState = STATE_SEMI_OPENCLOSED;
    }
  }
  else if (currentState == STATE_FIRST_OPENED)
  {
    //ENTRY
    if (lastState != currentState)
    {
      lastState = currentState;
    }
    //DO
    if (stateOfButtons[1]==true)
    {
      currentState = STATE_SECOND_OPENED;
    }
    if (stateOfButtons[0]==false)
    {
      currentState = STATE_CLOSED;
    }
    //EXIT
    if (stateOfButtons[2]==true)
    {
      alert();
      currentState = STATE_SEMI_OPENCLOSED;
    }
  }
  else if (currentState == STATE_SECOND_OPENED)
  {
    // ENTRY
    if (lastState != currentState)
    {
      lastState = currentState;
    }
    //DO
    if (stateOfButtons[2]==true)
    {
      currentState = STATE_OPEN;
    }
    if (stateOfButtons[1]==false)
    {
      currentState = STATE_FIRST_OPENED;
    }
    //EXIT
  }
  else if (currentState == STATE_OPEN)
  {
    // ENTRY
    if (lastState != currentState)
    {
      success();
      lastState = currentState;
    }
    //DO
    if (stateOfButtons[0]==false||stateOfButtons[1]==false)
    {
      currentState = STATE_SEMI_OPENCLOSED;
    }
    if (stateOfButtons[2]==false)
    {
      currentState = STATE_SECOND_OPENED;
    }
    //EXIT
  }
  else if (currentState == STATE_SEMI_OPENCLOSED)
  {
    // ENTRY
    if (lastState != currentState)
    {
      lastState = currentState;
    }
    //DO
    if (stateOfButtons[0]==false&&stateOfButtons[1]==false&&stateOfButtons[2]==false)
    {
      currentState = STATE_CLOSED;
    }    
    //EXIT
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
