#!/bin/bash

g++ -o smartSort UsingStepperControl.cpp StepperControl.cpp Camera.cpp -lpigpio -lrt -lpthread
