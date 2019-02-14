/*
 * This program monitors buttons connected to the ATMega328p chip it is running on.
 * If a connection is interrupted it activates an alert in the form of a certain melody specified in alertTones,
 * except the connection is the one specified in the openingSequence.
 * If all buttons were opened in the right sequence feedback is given in the form of a certain melody specified in unlockedTones.
 * Upon closing the buttons again the program will reset.
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

const int numOfButtons = 3; //the number of buttons used in the sequence
const int buttonPins[numOfButtons] = {1,5,7}; //the Arduino pins the buttons are connected to. For pin positions on the ATMega328p refer to http://www.hobbytronics.co.uk/image/data/tutorial/arduino-hardcore/atmega328-arduino-pinout.jpg or some other source.
const int openingSequence[numOfButtons] = {5,1,7}; //use the pin numbers of buttonPins in any order
int positionInSequence = 0; //tracks up to which position in the openingSequence buttons may be open
const int soundPin = 8; //sound signal output on this pin

//settings for the sound to be played upon successfully unlocking all buttons in the right order
const int numOfUnlockedTones = 3; //length of the following array (unlockedTones)
const int unlockedTones[numOfUnlockedTones] = {523, 659, 784}; //a sequence of tones of equal length, tones defined in Hertz.
const int unlockedSoundRepetitions = 5; //Defines how often the above sequence (unlockedTones) should be played.
const int unlockedTonesLengthMS = 300; //Defines the amount of time in milliseconds each tone of the sequence should be played.

//settings for the sound to be played when a mistake is made in opening the buttons
const int numOfAlertTones = 3; //length of the following array (alertTones)
const int alertTones[numOfAlertTones] = {247, 196, 165}; //a sequence of tones of equal length, tones defined in Hertz.
const int alertSoundRepetitions = 3; //Defines how often the above sequence (alertTones) should be played.
const int alertTonesLengthMS = 700; //Defines the amount of time in milliseconds each tone of the sequence should be played.

//Sets the correct pinModes. Resets the program when called later.
void setup() {
  for(int i = 0; i < numOfButtons; i++){
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(soundPin, OUTPUT);
}

//main loop of the program. function restarts when it finished
//causes the buttons states to be checked repeatedly
void loop() {
 checkButtonStates();
 delay(100);
}

//checks the state of each button
void checkButtonStates(){
  //loops through all buttons
  for(int i = 0; i < numOfButtons; i++){
    if(buttonOpen(buttonPins[i])){
      //this button is open
      if(!mayBeOpen(buttonPins[i])){
        //wrong button opened
        alert();
      }else if (positionInSequence == numOfButtons){
        //all buttons opened
        unlocked();
      }
    }
  }
}

//tell if a button is open (connection interrupted)
boolean buttonOpen(int pinNum){
  boolean isOpen = digitalRead(pinNum); //true if open (no connection to GND, otherwise false
  return isOpen;
}

//checks if a certain button may currently be open
boolean mayBeOpen(int pinNum){
  //positionInSequence keeps track where in the sequence the program is, meaning which buttons have been opened and which one may be opened next.
  for(int i = 0; i <= positionInSequence; i++){
    if (pinNum == openingSequence[i]){
      //This button may be open.
      if(i == positionInSequence){
        //This button may be open and is the next button of the sequence, therefor positionInSequence gets incremented.
        positionInSequence++;
      }
      //The button may be open, therefore true is retuned.
      return true;
    }
  }
  //This is only reached when the button may not be open. (It comes later in the sequence.)
  return false;
}

//a wrong button was opened
void alert(){
  //plays a melody defined in the alert sound settings
  alertSound();
  //When all buttons are closed again the program gets reset.
  while(true){
    //Loop gets interrupted when all buttons are closed again (connected to the right pins and GND), causing a reset of the program.
    if(allButtonsClosed()){
      break;
    }
    delay(100);
  }
  reset();
}

//Causes the melody defined in the alert sound settings to be played.
void alertSound(){
  //Plays the melody alertSoundRepetitions times.
  for(int i = 0; i < alertSoundRepetitions; i++){
    //Loops through all the tones of the alertTones array.
    for(int j = 0; j < numOfAlertTones; j++){
      //Starts playing a sound on the pin given to the function as the first parameter by switching the pin on and off again n times per second, n being the second parameter and the frequency in Hertz of the tone.
      //Tone keeps playing until another tone is played or noTone() is called.
      tone(soundPin, alertTones[j]);
      //Defines how long the tone is to be played.
      delay(alertTonesLengthMS);
    }
  }
  //Stops the tone currently played.
  noTone(soundPin);
}

//Returns true if all button pins are connected to GND, otherwise false.
boolean allButtonsClosed(){
  for(int i = 0; i < numOfButtons; i++){
    if(digitalRead(buttonPins[i]) == HIGH){
      return false;
    }
  }
  return true;
}

//All buttons were opened in correct order.
//When the melody finished playing and all buttons are closed (buttons pins connected to GND) again the program gets reset.
void unlocked(){
  //Plays the melody defined in the unlocked sound settings
  unlockedSound();
  while(true){
    //Loop gets interrupted when all buttons are closed again (connected to the right pins and GND), causing a reset of the program.
    if(allButtonsClosed()){
      break;
    }
    delay(100);
  }
  reset();
}

//Plays the melody defined in the unlocked sound settings.
void unlockedSound(){
  //Plays the melody unlockedSoundRepetitions times.
  for(int i = 0; i < unlockedSoundRepetitions; i++){
    //Loops through all the tones of the unlockedTones array.
    for(int j = 0; j < numOfUnlockedTones; j++){
      //Starts playing a sound on the pin given to the function as the first parameter by switching the pin on and off again n times per second, n being the second parameter and the frequency in Hertz of the tone.
      //Tone keeps playing until another tone is played or noTone() is called.
      tone(soundPin, unlockedTones[j]);
      //Defines how long the tone is to be played.
      delay(unlockedTonesLengthMS);
    }
  }
  //Stops the tone currently played.
  noTone(soundPin);
}

//Resets the program.
void reset(){
  positionInSequence = 0;
  setup();
}
