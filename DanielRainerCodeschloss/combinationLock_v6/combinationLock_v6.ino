/*
 * This program monitors buttons connected to the ATMega328p chip it is running on.
 * If a connection is interrupted it activates an alert in the form of a certain melody,
 * except the connection is the one specified in the openingSequence.
 * If all buttons were opened in the right order, feedback is given in the form of a certain melody.
 * If the button opened last is closed the sequence is set back by one,
 * meaning that this button must be reopened before continuing with the rest of the sequence.
 * If any other button is closed opening buttons is no longer allowed and will trigger the alarm.
 * The only way to open all of the buttons without triggering the alarm in this state
 * is to close all buttons before opening them in the correct order.
 *
 * How to connect everything:
 *
 *       - +
 * ||||||||||||||
 * ) ATmega328p
 * ||||||||||||||
 *   B   +-  B BS
 *
 * Legend:
 * -: GND
 * +: +5V
 * B: button (connect each button to GND)
 * S: speaker/sound (connect the speaker to GND)
 *
 * The button pins and the speaker pin can be changed in this code.
 * They are defined with Arduino pin numbers, which do not correspond to the pin numbers of the IC.
 * This image can be used to find out which Arduino pins correspond to which pins on the ATmega328:
 * http://www.hobbytronics.co.uk/image/data/tutorial/arduino-hardcore/atmega328-arduino-pinout.jpg
 */

/*
 * explaination of states:
 * Because defining a state for each combination the buttons can be in would mean a lot of hard-coding
 * and as there are 2^n possible states, n being the number of buttons used,
 * instead of treating each of those combinations individually
 * this program works with only four states:
 * STATE_OPENING:
 *    In this state it is possible to open the buttons
 *    This state will be entered if the previous state was STATE_CLOSING
 *    and all buttons are closed.
 *
 *    The next state will be:
 *    STATE_OPENING IF:
 *        nothing changes
 *      OR
 *        the next button defined in buttonPins is opened
 *        AND
 *        not all buttons are open
 *      OR
 *        the button last opened was closed (which will decrement the current position in the sequence)
 *    STATE_CLOSING IF:
 *      a button other than the one last opened was closed
 *    STATE_ALERT IF:
 *      a button in the sequence after the current position was opened
 *    STATE_SUCCESS IF:
 *      all buttons are open
 *
 * STATE_CLOSING:
 *    This state can be entered from all other states
 *    and serves as the way to close all buttons before opening any again.
 *
 *    The next state will be:
 *    STATE_OPENING IF:
 *      all buttons are closed
 *    STATE_ALERT IF:
 *      a button was opened
 *
 * STATE_ALERT:
 *    This state is used to trigger the alert. It will only be the current state for on iteration in a row.
 *    The next state will be STATE_CLOSING
 *
 * STATE_SUCCESS:
 *    This state is used to indicate that the buttons were opened successfully. It will only be the current state for on iteration in a row.
 *    The next state will be STATE_CLOSING.
 */
//state variables
typedef enum {STATE_OPENING, STATE_CLOSING, STATE_ALERT, STATE_SUCCESS} STATES;
STATES currentState = STATE_CLOSING;
STATES previousState = STATE_CLOSING;
STATES nextState = STATE_CLOSING;

//button related variables
byte positionInSequence = 0;
const byte numberOfButtons = 3;
//uploading and serial transmission do not work when button 1 is connected to ground
//for debugging either disconnect the button or use a different one
const byte buttonPins[numberOfButtons] = {5,1,7};
boolean currentButtonStates[numberOfButtons];
boolean previousButtonStates[numberOfButtons];

//sound variables
//the pin the speaker is connected to
const byte soundPin = 8;

//settings for the alert sound
//the number of tones used
const byte numberOfAlertTones = 4;
//the frequency of the tones in Hertz, length must be equal to numberOfAlertTones
const uint16_t alertTones[] = {400, 300, 200, 100};
//the duration of the tones in milliseconds, length must be equal to numberOfAlertTones
const uint16_t alertTonesDurations[] = {200, 200, 200, 200};

//settings for the success sound
//the number of tones used
const byte numberOfSuccessTones = 4;
//the frequency of the tones in Hertz, length must be equal to numberOfSuccessTones
const uint16_t successTones[] = {600, 700, 800, 900};
//the duration of the tones in milliseconds, length must be equal to numberOfAlertTones
const uint16_t successTonesDurations[] = {100, 100, 100, 100};

void setup() {
  //sets each button pin to INPUT_PULLUP, meaning that digitalRead will return false if it is connected to GND, otherwise true
  for(byte i = 0; i < numberOfButtons; i++){
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  //sets the soundPin to OUTPUT
  pinMode(soundPin, OUTPUT);
}

//main loop
//updates the states of the buttons and calls the function corresponding to the current state,
//which decides the state the system will be in in the next iteration of the loop
//updates the state
void loop() {
  updateButtonStates();
  //the function called by this switch statement determines nextState
  switch(currentState){
    case STATE_OPENING:
      executeStateOpening();
      break;
    case STATE_CLOSING:
      executeStateClosing();
      break;
    case STATE_ALERT:
      executeStateAlert();
      break;
    case STATE_SUCCESS:
      executeStateSuccess();
      break;
  }
  //next state is used for changing the state
  //a function cannot update currentState without updating previousState,
  //so in order to avoid having to do so
  //nextState gets updated,
  //then previousState can be updated with the value of currentState
  //and finally current state gets updated with the value of nextState.
  currentState = nextState;
  previousState = currentState;
  updatePreviousButtonStates();
  delay(50);
}

//polls the states of all buttons and stores them in the currentButtonStates array
void updateButtonStates(){
  for(byte i = 0; i < numberOfButtons; i++){
    currentButtonStates[i] = digitalRead(buttonPins[i]);
  }
}

//fills previousButtonStates with the values in currentButtonStates
void updatePreviousButtonStates(){
  for(byte i = 0; i < numberOfButtons; i++){
    previousButtonStates[i] = currentButtonStates[i];
  }
}

//code supposed to run if currentState is STATE_OPENING
void executeStateOpening(){
  //entry
  if(previousState != currentState){
    //resets the position in sequence
    positionInSequence = 0;
  }
  //do
  //check if open button was closed (except button last opened)
  //underflow prevention
  if(positionInSequence > 1){
    for(byte i = 0; i < positionInSequence - 1; i++){
      if(!currentButtonStates[i]){
        //open button was closed
        nextState = STATE_CLOSING;
        return;
      }
    }
  }
  //check if button last opened was closed
  //underflow prevention
  if(positionInSequence > 0){
    if(!currentButtonStates[positionInSequence - 1]){
      //closing the button last opened results in a valid combination
      //of open and closed buttons,
      //namely the previous one.
      positionInSequence--;
      nextState = currentState;
      return;
    }
  }
  //check if next button in sequence was opened
  if(currentButtonStates[positionInSequence]){
    positionInSequence++;
    if(positionInSequence == numberOfButtons){
      nextState = STATE_SUCCESS;
      return;
    }
  }
  //check if button coming later in sequence was opened
  for(byte i = positionInSequence + 1; i < numberOfButtons; i++){
    if(currentButtonStates[i]){
      nextState = STATE_ALERT;
      return;
    }
  }
  nextState = currentState;
}

void executeStateClosing(){
  //do
  boolean allButtonsClosed = true;
  for(byte i = 0; i < numberOfButtons; i++){
    if(currentButtonStates[i]){
      allButtonsClosed = false;
      if(!previousButtonStates[i]){
        nextState = STATE_ALERT;
        return;
      }
    }
  }
  if(allButtonsClosed){
    nextState = STATE_OPENING;
    return;
  }
  nextState = currentState;
}

void executeStateAlert(){
  //entry
  playSound(numberOfAlertTones, alertTones, alertTonesDurations);
  nextState = STATE_CLOSING;
}

void executeStateSuccess(){
  //entry
  playSound(numberOfSuccessTones, successTones, successTonesDurations);
  nextState = STATE_CLOSING;
}

//used for playing sound
//takes the number of tones,
//followed by an array containing the frequency of each individual tone in Hertz,
//followed by an array containing the duration of each individual tone in milliseconds
void playSound(const byte numberOfTones, const int tones[], const int durations[]){
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
