#include <IRremote.h>
#include <Servo.h>

const byte IR_RECEIVE_PIN = 6;

const byte MEOW_BUTTON = 2;
const byte DOOR_CLOSED_BUTTON = 3;

#define LITTLE_SERVO_PIN 9
#define BIG_SERVO_PIN 10


#define BUTTON_UP 70
#define BUTTON_LEFT 68
#define BUTTON_RIGHT 67
#define BUTTON_DOWN 21
#define BUTTON_ONE 22
#define BUTTON_TWO 25
#define BUTTON_THREE 13
#define BUTTON_FOUR 12
#define BUTTON_FIVE 24
#define BUTTON_SIX 94
#define BUTTON_SEVEN 8
#define BUTTON_EIGHT 28
#define BUTTON_NINE 90
#define BUTTON_ASTERISK 66
#define BUTTON_ZERO 82
#define BUTTON_HASHTAG 74


Servo littleServo;
Servo bigServo;

int pawlOpenDegrees=30;
int pawlHomeDegrees=0;
int armOneNotchDegrees=-60;
int armHomeDegrees =50;
int armFreeDegrees = 20;

int movementDelay = 500;

bool doorIsClosing = false;
int catWaitTimeMs = 5000;

void setup()
{
  Serial.begin(115200);

  pinMode(MEOW_BUTTON, INPUT);
  pinMode(DOOR_CLOSED_BUTTON, INPUT);



  //IrReceiver.begin(IR_RECEIVE_PIN);
    littleServo.attach(LITTLE_SERVO_PIN, 500, 2500);
   littleServo.write(0);
   
    bigServo.attach(BIG_SERVO_PIN, 500, 2500);
   bigServo.write(armHomeDegrees);
   
}

  void PawlGoHome(){
    littleServo.write(pawlHomeDegrees);
    delay(movementDelay);
  }

  void PawlGoOpen(){
    littleServo.write(pawlHomeDegrees+pawlOpenDegrees);
    delay(movementDelay);
  }

  void ArmGoHome(){
    bigServo.write(armHomeDegrees);
    delay(movementDelay);
  }

  void ArmGoForward(){
    bigServo.write(armOneNotchDegrees+armHomeDegrees);
    delay(movementDelay);
  }

  void ArmGoFree(){
    bigServo.write(armHomeDegrees+armFreeDegrees);
    delay(movementDelay);
  }

   bool GetDidCatMeowFromRemoteControl(){
     // Put in the code to read the IR sensor
     return false;
   }

  bool GetDidCatMeowFromEncoder(){
     int meowSwitchState = digitalRead(MEOW_BUTTON); // Read the state of the switch
      if (meowSwitchState == LOW)
        return true;
      else
        return false;
  }

  bool GetDidDoorCloseFromEncoder(){
     int doorSwitchState = digitalRead(DOOR_CLOSED_BUTTON); // Read the state of the switch
     return (doorSwitchState == LOW)
  }

void loop()
{
  int myDelay = 500;
  bool catMeowed = GetDidCatMeowFromEncoder();
  if (catMeowed) {
    Serial.println("Cat Meowed"); // Print a message if the switch is pressed
    PawlGoOpen();
    delay(catWaitTimeMs);
    Serial.println("Hope the cat is gone! Time to close the door!");
    PawlGoHome();
    doorIsClosing = true;
  } 

  bool doorClosed = GetDidDoorCloseFromEncoder();
  if (doorClosed) {
    Serial.println("Door Has Closed"); // Print a message if the switch is pressed
    doorIsClosing=false;
    ArmGoFree();
  } 

if (doorIsClosing == true){
  ArmGoForward();
  ArmGoHome();
}
  
  /*
  if (IrReceiver.decode())
  {
      if (IrReceiver.decodedIRData.command != 0)
      {
        Serial.print("Code: ");
        Serial.println(IrReceiver.decodedIRData.command);

        // if (IrReceiver.decodedIRData.command == BUTTON_LEFT) // LEFT
        //     littleServo.write(20);
        // if (IrReceiver.decodedIRData.command == BUTTON_RIGHT) // RIGHT
        //     littleServo.write(0);

        // if (IrReceiver.decodedIRData.command == BUTTON_UP) // UP
        //     bigServo.write(20);
        // if (IrReceiver.decodedIRData.command ==BUTTON_DOWN) // DOWN
        //     bigServo.write(0);    

        //needed to block repeat codes
        IrReceiver.decodedIRData.command = 0;
      }
      // Any code here will be repeated so long as the button is held down
     //Serial.println("Button Held...");
    IrReceiver.resume();     
  }
*/


} //END of   loop()