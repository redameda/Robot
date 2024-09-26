#include<Servo.h>
#include "IRremote.h"
Servo ServoLeft;
Servo ServoRight;
Servo ServoHand; 
bool powerOn = false;
int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
//vairable uses to store the last decodedRawData
uint32_t last_decodedRawData = 0;
/*-----( Function )-----*/
void translateIR() // takes action based on IR code received
{
  // Check if it is a repeat IR code 
  if (irrecv.decodedIRData.flags)
  
  {
    //set the current decodedRawData to the last decodedRawData 
    irrecv.decodedIRData.decodedRawData = last_decodedRawData;
    Serial.println("REPEAT!");
  } else
  {
    //output the IR code on the serial monitor
    Serial.print("IR code:0x");
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
    
        switch (irrecv.decodedIRData.decodedRawData)
  {
    case  0xEE11BF00: forWard(); break;
    case  0xE619BF00: backWard();    break;
    case  0xEB14BF00: left();    break;
    case  0xE916BF00: right();    break;
    case  0xEA15BF00: pickUp();    break;
      case  0x16E9AEC3: ;forWard(); break;
    case  0x1EE1AEC3: backWard();    break;
    case  0x1CE3AEC3: left();    break;
    case  0x19E6AEC3: right();    break;
    case 0x15EAAEC3: pickUp();    break;
    case 0x1AE5AEC3: Drop();    break;
    case 0xF30CBF00:Drop();break;
    default:
      Serial.println(" other button   ");
  }// End CasE
    
  }
  //map the IR code to the remote key

  //store the last decodedRawData
  last_decodedRawData = irrecv.decodedIRData.decodedRawData;
  delay(500); // Do not get immediate repeat

} //END translateIR

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); // Start the receiver
ServoHand.attach(10,0 ,180);
}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode()) // have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); // receive the next value
  }
}

void startRemote(){
  Serial.println("remote started");


}
void forWard(){
  ServoLeft.writeMicroseconds(1300);
  ServoRight.writeMicroseconds(1300);
  Serial.println("Forward");
  }
  void backWard(){
      ServoLeft.writeMicroseconds(1700);
  ServoRight.writeMicroseconds(1700);
  Serial.println("backward");
    }
  void left(){
      ServoLeft.writeMicroseconds(1300);
  ServoRight.writeMicroseconds(1500);
  Serial.println("Left");
    }  
    void right(){
        ServoLeft.writeMicroseconds(1500);
  ServoRight.writeMicroseconds(1300);
  Serial.println("right");
      }
          void Stop(){
        ServoLeft.writeMicroseconds(1500);
  ServoRight.writeMicroseconds(1500);
  Serial.println("Stop");
      }
      void pickUp(){
        ServoHand.attach(10);
        delay(100);
        ServoHand.write(180);  
        delay(1000);
        ServoHand.detach();
        }
        void Drop(){
           ServoHand.attach(10);
        delay(100);
          ServoHand.write(0); 
          delay(1000);
           ServoHand.detach();
        }
