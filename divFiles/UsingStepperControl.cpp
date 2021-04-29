#include <iostream>
#include <pigpio.h>
#include "./StepperControl.hpp"

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>
#include <vector>

#define NO_NEED_TO_BREAK 1


extern char **environ;

int main (){

StepperControl stepperController;

if (gpioInitialise() < 0) return 1;

    gpioSetMode(Pin1, PI_OUTPUT);
    gpioSetMode(Pin2, PI_OUTPUT);
    gpioSetMode(Pin3, PI_OUTPUT);
    gpioSetMode(Pin4, PI_OUTPUT);

	pid_t cameraPID;
    //pid_t pid2;                    //pid to register if its a child process or parent
	int exeRet = 889977;       // variable used for return value of execvp, initialized to unlikely value
	int status = 887766;    //initialized to an unlikely return value, variable used by waitpid later, but not otherwise used here  
    char* takePhoto ="raspistill";
	char* arguments[5];
	arguments[0] = "raspistill";
	arguments[1] = "-o";
	arguments[2] = "nameX.jpg";	
		
int counter = 0;     	
		
while(NO_NEED_TO_BREAK){
 	stepperController.stepForward();
	gpioDelay(600000);
	
	
//	std::cout << arguments[i] << std::endl;
char imageNumber = counter + '0';
printf("imageNumber = %c\n", imageNumber);

char* imageName = (char*)malloc(10*sizeof(char));
if (imageName == NULL) return -1;

imageName[0] = 'i';
imageName[1] = imageNumber;
imageName[2] = '.';
imageName[3] = 'j';
imageName[4] = 'p';
imageName[5] = 'g';

arguments[2]  = imageName; 


			
	cameraPID = fork();                 //new process to execute raspistill
	if (0 == cameraPID){     // the child process
            
		exeRet = execvp(takePhoto, arguments); //make the systemcall
		if (exeRet = -1){                   // if the execvp fails
               perror("Sys call failed");                      // print error message
               _exit(1);        //make sure the unused process is terminated
        }                                      // if execvp succedes, the proces is auto terminated
		
    }
	else if (cameraPID > 0){   //the parent process
            waitpid(cameraPID, &status, 0);  //the parent process waits for the child to terminate
			puts("parent done waiting");
	}
	
	printf("imageName = %s\n", arguments[2]);
	counter++;
	if (counter == 8) break;
	free(imageName);

}

return 0;
}





