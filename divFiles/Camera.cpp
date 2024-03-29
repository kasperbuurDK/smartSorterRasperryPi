#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "./Camera.hpp"

#define SHELLSCRIPT "convert picture.jpg -format \"%[fx:(1-mean)*w*h]\" info: > result.txt"

#define LOWER_BOUNDARY 	50000
#define	UPPER_BOUNDARY 	140000
#define EMPTY 			190000

int status = 0;



Camera::Camera(){
	
}

int Camera::takePhoto(){
	
	int execvReturn;
    fflush(stdout);
        char **cmd;
        cmd = (char**)malloc((12) * sizeof(char **));
        cmd[0] = "raspistill"; // executable name
        cmd[1] = "-t";
        cmd[2] = "500";
        cmd[3] = "-e";
        cmd[4] = "jpg";
        cmd[5] = "-w";
        cmd[6] = "640";
        cmd[7] = "-h";
        cmd[8] = "480";
        cmd[9] = "-o";
        cmd[10] = "picture.jpg";
        cmd[11] = (char *)0; // terminator
        execvReturn = execv("/usr/bin/raspistill", cmd);
   
	return execvReturn;
}

int Camera::takePhotoNewName(char* imageName){
	int execvReturn;
    fflush(stdout);
        char **cmd;
        cmd = (char**)malloc((12) * sizeof(char **));
        cmd[0] = "raspistill"; // executable name
        cmd[1] = "-t";
        cmd[2] = "500";
        cmd[3] = "-e";
        cmd[4] = "jpg";
        cmd[5] = "-w";
        cmd[6] = "640";
        cmd[7] = "-h";
        cmd[8] = "480";
        cmd[9] = "-o";
        cmd[10] = imageName;
        cmd[11] = (char *)0; // terminator
        execvReturn = execv("/usr/bin/raspistill", cmd);
   
	return execvReturn;
	
}


int Camera::makeMonoNewName(char* imageName){
	int execvReturn;
	
    char **cmd;
    cmd = (char**)malloc((5) * sizeof(char **));
    cmd[0] = "convert"; // executable name
    cmd[1] = imageName;
    cmd[2] = "-monochrome";
    cmd[3] = imageName;
    cmd[4] = (char *)0; // terminator
    execvReturn = execvp("convert",cmd);
    
	return execvReturn;	
}

int Camera::makeMono(){
	int execvReturn;
	
    char **cmd;
    cmd = (char**)malloc((5) * sizeof(char **));
    cmd[0] = "convert"; // executable name
    cmd[1] = "picture.jpg";
    cmd[2] = "-monochrome";
    cmd[3] = "picture.jpg";
    cmd[4] = (char *)0; // terminator
    execvReturn = execvp("convert",cmd);
    
	return execvReturn;	
}

void Camera::blackPixelCount(){
    printf("Counting number of black pixels\n");
    fflush(stdout);
    system(SHELLSCRIPT);
    printf("conversion done\n");
    fflush(stdout);
}

void Camera::readResult(int* result){
    FILE *fp;
    fp = fopen("result.txt", "r");
	int numberOfBlackPixels;
    fscanf(fp, "%d", &numberOfBlackPixels);
    printf("Number of black pixels is: %d\n", numberOfBlackPixels);
	if (numberOfBlackPixels > LOWER_BOUNDARY && numberOfBlackPixels < UPPER_BOUNDARY){
	*result = 0;
	}
	else if (numberOfBlackPixels > EMPTY )*result = 9;
	else *result = 1;
	
    //fflush(stdout);
}
