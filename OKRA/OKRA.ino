//Code for the OKRA oven-fire prevention device.
//Written by Cooper Clem 2022

bool isPreheating = false;
int blinkingState = 0;
long lastBoopTime = 0;
long lastBeepTime = 0;

final int buzzerPin = 11;
final int blinkerPin = 12

void setup() {
  pinMode(blinkerPin, OUTPUT); 
  pinMode(buzzerPin,OUTPUT);
}

void loop() {
  //if it isn't already blinking and the preheat button is pressed
  if(!isPreheating && analogRead(A0) > 600){
    isPreheating = true;
    blinkingState = 0;
  }

  //if its supposed to be blinking, blink
  if(isPreheating){
    handleNotificaiton();
  }

  //wait for the door to open
  if(isPreheating && analogRead(A1) < 60){
      isPreheating = false; //since door is open, it isn't supposed to blink anymore
      //vv reset the blinking state variablesvv
      blinkingState = 0;  
      noTone(buzzerPin);
      digitalWrite(blinkerPin, LOW);
    }
}

//open loop state-machine for handling the blinking; you could just use delays I'm just being extra
void handleNotification(){
  switch(blinkingState){
      case 0:
        lastBoopTime = millis();
        
        tone(buzzerPin, 1500);
        digitalWrite(blinkerPin, HIGH);
        
        blinkingState++;
        break;
      case 1:
        if(millis() - lastBoopTime > 200){
          noTone(buzzerPin);
          digitalWrite(blinkerPin, LOW);
          lastBeepTime = millis();
          blinkingState++;
        }
        break;
      case 2:
        if(millis() - lastBeepTime > 200){
          blinkingState = 0;
        }
        break;
    }
}
