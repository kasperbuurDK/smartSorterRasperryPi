#!/bin/bash
g++ -o take8Photos take8Photo.cpp StepperControl.cpp Camera.cpp -lpigpio -lrt -lpthread

