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


int main (){

StepperControl stepperController;
Camera camera;

if (gpioInitialise() < 0) return 1;
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
	
	cameraPID = fork();                 //new process to execute raspistill
	
	
	

char imageNumber = counter + '0';

char* imageName = (char*)malloc(10*sizeof(char));
if (imageName == NULL) return -1;

imageName[0] = 'i';
imageName[1] = imageNumber;
imageName[2] = '.';
imageName[3] = 'j';
imageName[4] = 'p';
imageName[5] = 'g';



	if (0 == cameraPID){     // the child process
   		functionReturn = camera.takePhotoNewName(imageName);
		if (functionReturn = -1){       			// if the execvp fails
               perror("takePhoto failed");          // print error message
               _exit(1);   						    //make sure the unused process is terminated
        }                      						// if execvp succedes, the proces is auto terminated
	} else if (cameraPID > 0){   					//the parent process
            waitpid(cameraPID, &status, 0); 		//the parent process waits for the child to terminate
	}
	
	cameraPID = fork();
	
	if (0 == cameraPID){     // the child process
       	functionReturn = camera.makeMonoNewName(imageName);
		if (functionReturn = -1){                   // if the execvp fails
               perror("makeMono failed");                      // print error message
               _exit(1);        //make sure the unused process is terminated
        }                      // if execvp succedes, the proces is auto terminated
	} else if (cameraPID > 0){   //the parent process
            waitpid(cameraPID, &status, 0);  //the parent process waits for the child to terminate
			puts("parent done waiting");
	}	
	
	
	
				
	counter++;
	if (counter == 8) break;

}

return 0;
}