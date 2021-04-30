#!/bin/bash

g++ -o test_CPP UsingStepperControl.cpp StepperControl.cpp Camera.cpp -lpigpio -lrt -lpthread