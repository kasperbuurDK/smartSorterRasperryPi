

#include <stdio.h>

#include <pigpio.h>

#define STEP_DELAY 2000

/*
2000  7 RPM
1500  9 RPM
1000 13 RPM
 900 15 RPM
*/

#define Pin1 6
#define Pin2 13
#define Pin3 19
#define Pin4 26

int step = 0;

void loop()
{
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
}


int main()
{

	printf("pin1 = %d, pin2 = %d, pin3 = %d, pin4 = %d\n", Pin1, Pin2, Pin3, Pin4);
    int i,j;
    int step_delay = STEP_DELAY;

    if (gpioInitialise() < 0) return 1;

    gpioSetMode(Pin1, PI_OUTPUT);
    gpioSetMode(Pin2, PI_OUTPUT);
    gpioSetMode(Pin3, PI_OUTPUT);
    gpioSetMode(Pin4, PI_OUTPUT);

    for(j = 0; j < 4; j++){
      for (i = 0; i <= 512; i++)
      {
         loop();
         step++;
         if (step > 3) step = 0;
         gpioDelay(step_delay);
      }
     printf("%d\n", j*i);
     gpioDelay(600000);
    }
    gpioTerminate();
}



