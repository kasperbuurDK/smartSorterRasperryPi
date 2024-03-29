#include <iostream>
#include <pigpio.h>
#include "./StepperControl.hpp"
#include "./Camera.hpp"

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define Pin1 6
#define Pin2 13
#define Pin3 19
#define Pin4 26

#define cameraRedLED 4
#define cameraGreenLED 17


#define NO_NEED_TO_BREAK 1

int handle;
char result = '0';

int main (){

StepperControl stepperController;
Camera camera;

if (gpioInitialise() < 0) return 1;
    handle = serOpen("/dev/ttyS0", 9600, 0);
    gpioSetMode(Pin1, PI_OUTPUT);
    gpioSetMode(Pin2, PI_OUTPUT);
    gpioSetMode(Pin3, PI_OUTPUT);
    gpioSetMode(Pin4, PI_OUTPUT);
	gpioSetMode(cameraGreenLED, PI_OUTPUT);
    gpioSetMode(cameraRedLED, PI_OUTPUT);
	
	gpioWrite(cameraGreenLED, 0);
	gpioWrite(cameraRedLED,0);
	
	
	int functionReturn = 889977;       // variable used for return value of function calls, initialized to unlikely value
	int status = 887766;    //initialized to an unlikely return value, variable used by waitpid later, but not otherwise used here  	
	int counter = 0;
	pid_t cameraPID;
		
while(NO_NEED_TO_BREAK){
 	stepperController.stepForward();
	gpioDelay(WAIT_BETWEEN_MOVES);
	
	serWriteByte(handle, result);
	serWriteByte(handle, '\r');
	serWriteByte(handle, '\n');
	
	cameraPID = fork();                 //new process to execute raspistill

	if (0 == cameraPID){     // the child process
   		functionReturn = camera.takePhoto();
		if (functionReturn = -1){                   // if the execvp fails
               perror("takePhoto failed");                      // print error message
               _exit(1);        //make sure the unused process is terminated
        }                      // if execvp succedes, the proces is auto terminated
	} else if (cameraPID > 0){   //the parent process
            waitpid(cameraPID, &status, 0);  //the parent process waits for the child to terminate
	}
	
cameraPID = fork();
	
if (0 == cameraPID){     // the child process
       	functionReturn = camera.makeMono();
		if (functionReturn = -1){                   // if the execvp fails
               perror("makeMono failed");                      // print error message
               _exit(1);        //make sure the unused process is terminated
        }                      // if execvp succedes, the proces is auto terminated
	} else if (cameraPID > 0){   //the parent process
            waitpid(cameraPID, &status, 0);  //the parent process waits for the child to terminate
			puts("parent done waiting");
	}	
	
	camera.blackPixelCount();
	int cameraApproved;
	camera.readResult(&cameraApproved);
	std::cout << "cameraApproved = " << cameraApproved <<std::endl;
	
	int howManyEmpty;
	
	if(cameraApproved == 0) {
	gpioWrite(cameraGreenLED, 1);
	gpioWrite(cameraRedLED,0);
	result = '0';
	howManyEmpty = 0;
    }
    else if (cameraApproved == 1 )
	{
		gpioWrite(cameraRedLED, 1); 
		gpioWrite(cameraGreenLED,0);
		result = '1';
		howManyEmpty = 0;
	
	} else if (cameraApproved == 9) {
		gpioWrite(cameraRedLED, 1); 
		gpioWrite(cameraGreenLED,1);
		howManyEmpty++;	
		result = '9';
	}
	
	if (howManyEmpty == 3) {
		std::cout << "3 empty in a row, shutting down" << std::endl;
		break;
	}
				
	counter++;
	
}

return 0;
}





