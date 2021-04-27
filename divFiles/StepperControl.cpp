//
// Created by kaspe on 16-04-2021.
//

#include "./StepperControl.hpp"
#include <pigpio.h>

StepperControl::StepperControl() {
    positionCounter = 0;
    positionReal = positionCounter % HOLES;
}

int StepperControl::stepForward() { //TODO make it move steppermotor
    
	for (int i = 0; i <= (512/2); i++)
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
    return positionReal ;
}
