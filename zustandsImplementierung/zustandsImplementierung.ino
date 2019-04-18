// Quelle: https://www.youtube.com/watch?v=32FkQvnlMcc&t=2696s
// zustandsdiagramm in www.draw.io

typedef enum {STATE_ON, STATE_COUNT, STATE_OFF} STATES;

STATES currentState = STATE_OFF, lastState = STATE_COUNT;

//the pin the speaker is connected to
const byte soundPin = 8;
const byte LED_OUT = 13;

const byte WECHSLER_IN = 12;
const byte ONOFF_IN = 12;


void setup() {
  pinMode(LED_OUT, INPUT_PULLUP);
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
