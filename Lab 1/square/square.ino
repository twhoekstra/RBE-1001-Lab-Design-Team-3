
// Written bt Joseph St. Germain on 6/5/15
// This is a Tank Drive output example of the DFRobots Wireless controller. This library was written to interface through the Serial #1 port on the mega.
// The defualt design has an Xbee wireless module on either side for communication.
// The library could be altered for any serial port and may be updated to handle the other serial ports but only supports Serial1 currently.
// The DFW tank drive example needs to have 2 servo motors connected to pins 4 and 5 for driving.It also requires having a battery plugged in and turned on.

#include <DFW.h> // DFW include
#include <Servo.h> // servo library

class DFWRobot:public AbstractDFWRobot{\
	Servo rightmotor; // Servo object
	Servo leftmotor; // Servo object

int d = 24;
int f = 60;

void turn90(){
        rightmotor.write(135);    
        leftmotor.write(135);
        delay(245);
        rightmotor.write(90);    
        leftmotor.write(90);
        delay(1000);    
       }

int straight(int d, int f){
        rightmotor.write(150);    
        leftmotor.write(30);
        delay(f*d);
        rightmotor.write(90);    
        leftmotor.write(90);
        delay(1000);    
       }
public:
	DFW * dfwPointer;
	void robotStartup(){
	  leftmotor.attach(11, 1000, 2000); // left drive motor pin#, pulse time for 0,pulse time for 180
	  rightmotor.attach(10, 1000, 2000); // right drive motor pin#, pulse time for 0,pulse time for 180
	}
	 void autonomous( long time){};
	 void teleop(long time){
     rightmotor.write(90);    
     leftmotor.write(90);
     delay(1000);
     straight(d, f);
     exit(0);
     
       

	};
	 void robotShutdown(void){};
	int getDebugLEDPin(void){
		return 13;
	};
};

DFWRobot robot;
DFW dfw(& robot );  // Instantiates the DFW object and setting the debug pin. The debug pin will be set high if no communication is seen after 2 seconds


void setup() {
  Serial.begin(9600); // Serial output begin. Only needed for debug
  dfw.begin(); // Serial1 output begin for DFW library. Buad and port #."Serial1 only"
  robot.robotStartup();// force a robot startup for testing
  robot.dfwPointer=&dfw;// pass a controller to the robot
}

void loop() {
  dfw.run();// Called to update the controllers output. Do not call faster than every 15ms.
  robot.teleop(0);// run the teleop function manually
}

