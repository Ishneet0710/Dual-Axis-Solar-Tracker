#include <Servo.h> // include Servo library



Servo horizontal; // creates horizontal servo
int servoh = 180;// set initial angle for horizontal servo
int servohLimitHigh = 180;//limits for servo horizontal angle
int servohLimitLow = 65;



Servo vertical; // creates vertical servo
int servov = 45;//set initial angle for vertical servo
int servovLimitHigh = 80;//limits for servo vertical angle
int servovLimitLow = 15;
int analogTopLeft = 0; // These will be used in analogRead
int analogTopRight = 1;
int analogBottomLeft = 2;
int analogBottomRight = 3;


void setup() {
	Serial.begin(9600);
	horizontal.attach(9); // attach horizontal motor to pin 9
	vertical.attach(10); // attach vertical motor to pin 10
	horizontal.write(180);
	vertical.write(45);
	delay(2000);
}


void loop() {
	int topLeft = analogRead(analogTopLeft); // reads analog A0
	int topRight = analogRead(analogTopRight); // reads analog A1
	int bottomLeft = analogRead(analogBottomLeft); // reads analog A2
	int bottomRight = analogRead(analogBottomRight); // reads analog A3
	int delayTime = 10;// time delay between each set of servo movement
	int tolerance = 30;
	int averageTop = (topLeft + topRight) / 2; // top average value
	int averageBottom = (bottomLeft + bottomRight) / 2; // bottom average value
	int averageleft = (topLeft + bottomLeft) / 2; // left average value
	int averageRight = (topRight + topBottom) / 2; // right average value
	int differenceVertical = averageTop - averageBottom; // check the difference of up and down
	int differenceHorizontal = averageleft - averageRight; // check the difference of left and right
	Serial.print(averageTop);
	Serial.print(" ");
	Serial.print(averageBottom);
	Serial.print(" ");
	Serial.print(averageleft);
	Serial.print(" ");
	Serial.print(averageRight);
	Serial.print(" ");
	Serial.print(delayTime);
	Serial.print(" ");
	Serial.print(tolerance);
	Serial.println(" ");
	if (-1*tolerance > differenceVertical || differenceVertical > tolerance){ // check if the difference is in the tolerance range else change vertical angle
	    if (averageTop > averageBottom) {
			servov = ++servov;//increase vertical angle
			if (servov > servovLimitHigh) {
				servov = servovLimitHigh;//ensure vertical angle does not cross limit
            }
        }
        else if (averageTop < averageBottom) {
			servov= --servov;
			if (servov < servovLimitLow) {
				servov = servovLimitLow;
            }
        }
		vertical.write(servov);//tells vertical servo to move accordingly
    }
//same code for the horizontal motor
    if (-1*tolerance > differenceHorizontal || differenceHorizontal > tolerance) {
		if (averageleft > averageRight){
			servoh = --servoh;
			if (servoh < servohLimitLow) {
				servoh = servohLimitLow;
            }
        }
		else if (averageleft < averageRight) {
			servoh = ++servoh;
			if (servoh > servohLimitHigh) {
				servoh = servohLimitHigh;
            }
        }
		else if (averageleft = averageRight) {
			// nothing
        }
		horizontal.write(servoh);
    }
   delay(dtime);//delay time between each set of combined movement by both horizontal and vertical servo
}