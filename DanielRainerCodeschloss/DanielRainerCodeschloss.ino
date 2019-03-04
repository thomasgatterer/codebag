//author: Daniel Rainer
//created: 19/02/2019

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
//tracks the state of each button, true if open, false if closed
boolean openButtons[numberOfButtons];
//keeps track of how many buttons were already opened correctly
byte positionInSequence = 0;
//updates when a button is opened or closed, stores the milliseconds passed since runtime started
long timeOfLastAction;
//whe the buttons are partially open the alert will play after so many milliseconds of inactivity
const int timeUntilTimeout = 10000;
//prevents the alert from being triggered for this many milliseconds after a button was closed with others remaining open
const int timeBeforeResetWhenButtonGetsClosed = 7000;
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

void setup() {
  //sets each button pin to INPUT_PULLUP, meaning that digitaRead will return false if it is connected to GND, otherwise true
  for(byte i = 0; i < numberOfButtons; i++){
    pinMode(sequenceOfButtons[i], INPUT_PULLUP);
  }
  //sets the soundPin to OUTPUT
  pinMode(soundPin, OUTPUT);
}

void loop() {
  //updates the array which keeps track for each button if it is open or closed
  updateButtonStates();
  //checks for invalid behavious and triggers the alert upon detection of such
  if(!checkIfButtonStatesValid() || checkForTimeout()){
    alert();
  }
  //the previously called checkIfButtonStatesValid function sets unlocked to true if all buttons were opened correctly
  if(unlocked){
    success();
  }
  //delay in milliseconds to limit resource usage
  delay(100);
}

//updates the array which keeps track for each button if it is open or closed
void updateButtonStates(){
  //each iteration checks the state of one button
  for(byte i = 0; i < numberOfButtons; i++){
    boolean updatedValue = digitalRead(sequenceOfButtons[i]);
    //if change is detected timeOfLastAction is set to the current time
    if(openButtons[i] != updatedValue){
      timeOfLastAction = millis();
    }
    //value in the array gets updated
    openButtons[i] = updatedValue;
  }
}

//returns true if all buttons are in a valid state, otherwise returns false
//additionally it sets unlocked to true if all buttons were opened correctly
boolean checkIfButtonStatesValid(){
  //if a previously opened button was closed before all buttons were opened
  //the sequence resets after the delay in milliseconds defined by timeBeforeResetWhenButtonGetsClosed
  for(byte i = 0; i < positionInSequence; i++){
    if(!openButtons[i]){
      delay(timeBeforeResetWhenButtonGetsClosed);
      reset();
      break;
    }
  }
  //if a button was opened before all of the preceeding ones in the sequence the buttons states are not valid
  for(byte i = positionInSequence + 1; i < numberOfButtons; i++){
    if(openButtons[i]){
      return false;
    }
  }
  //if the next button in the sequence was opened the position in the sequence increments
  if(openButtons[positionInSequence]){
    positionInSequence++;
    //if the following is true all buttons were opened and unlocked can be set to true
    if(positionInSequence == numberOfButtons){
     unlocked = true;
    }
  }
  return true;
}

//prolonged inactivity leads to a reset of the sequence
//returns true if the time limit for opening the next button is exceeded, otherwise returns true
boolean checkForTimeout(){
  if(millis() > timeOfLastAction + timeUntilTimeout && !checkIfAllButtonsClosed()){
    return true;
  }
  return false;
}

//this function is called after an illegal action was committed
//it plays the alert sound and resets the sequence once all buttons are closed
void alert(){
  playSound(numberOfAlertTones, alertTones, alertTonesDurations);
  while(true){
    if(checkIfAllButtonsClosed()){
      reset();
      break;
    }
  }
}

//returns true if all buttons are closed, otherwise returns false
boolean checkIfAllButtonsClosed(){
  for(byte i = 0; i < numberOfButtons; i++){
    //if this button is open not all buttons are closed, hence false is returned
    if(digitalRead(sequenceOfButtons[i])){
      return false;
    }
  }
  return true;
}

//this function is called after all buttons were opened in the correct order
//the function plays the alert sound and resets the sequence once all buttons are closed
void success(){
  playSound(numberOfSuccessTones, successTones, successTonesDurations);
  while(true){
    if(checkIfAllButtonsClosed()){
      reset();
      break;
    }
  }
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

//called for resetting the program
//resets all relevant variables
//loop can continue after this function returned
void reset(){
  positionInSequence = 0;
  unlocked = false;
  //timeOfLastAction = millis();
  for(byte i = 0; i < numberOfButtons; i++){
    openButtons[i] = false;
  }
}
