#include <iostream>
#include <pigpio.h>

#define HOLES 7
#define STEP_DELAY 2000

#define Pin1 6
#define Pin2 13
#define Pin3 19
#define Pin4 26

class StepperControl {

public:
    StepperControl();
    int stepForward();
    int getPostionReal();

private:
    int positionCounter;
    int positionReal;
	int step;
    int updatePosition(int value);
	int loop();
};


int main (){

StepperControl stepperController;

if (gpioInitialise() < 0) return 1;

    gpioSetMode(Pin1, PI_OUTPUT);
    gpioSetMode(Pin2, PI_OUTPUT);
    gpioSetMode(Pin3, PI_OUTPUT);
    gpioSetMode(Pin4, PI_OUTPUT);

for (int i = 0; i < 8; i++){
	stepperController.stepForward();
	gpioDelay(600000);
	printf("position = %d\n", stepperController.getPostionReal());
	// TODO getPostionReal returns 0 everry time

}

}



StepperControl::StepperControl() {  //Constructur
    positionCounter = 0;
    positionReal = positionCounter % HOLES;
}

int StepperControl::stepForward() { //TODO make it move steppermotor
    
	for (int i = 0; i <= (512); i++)
      {
         loop();
         step++;
         if (step > 3) step = 0;
         gpioDelay(STEP_DELAY);
      }
	  return 0;
	
	updatePosition(1);

}

int StepperControl::loop() {
	switch (step)
    {
    case 0:
        gpioWrite(Pin1, PI_HIGH);
        gpioWrite(Pin2, PI_LOW);
        gpioWrite(Pin3, PI_LOW);
        gpioWrite(Pin4, PI_LOW);
        break;
    case 1:
        gpioWrite(Pin1, PI_LOW);
        gpioWrite(Pin2, PI_HIGH);
        gpioWrite(Pin3, PI_LOW);
        gpioWrite(Pin4, PI_LOW);
        break;
    case 2:
        gpioWrite(Pin1, PI_LOW);
        gpioWrite(Pin2, PI_LOW);
        gpioWrite(Pin3, PI_HIGH);
        gpioWrite(Pin4, PI_LOW);
        break;
    case 3:
        gpioWrite(Pin1, PI_LOW);
        gpioWrite(Pin2, PI_LOW);
        gpioWrite(Pin3, PI_LOW);
        gpioWrite(Pin4, PI_HIGH);
        break;

    default:
        gpioWrite(Pin1, PI_LOW);
        gpioWrite(Pin2, PI_LOW);
        gpioWrite(Pin3, PI_LOW);
        gpioWrite(Pin4, PI_LOW);
        break;
    }

return 0;
}


int StepperControl::updatePosition(int value) {
    positionCounter +=value;
    positionReal = positionCounter % HOLES;

    return 0;
}

int StepperControl::getPostionReal() {
    return positionReal;
}



