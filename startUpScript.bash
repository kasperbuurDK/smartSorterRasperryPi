#!/usr/bin/env bash.

#upgrade and update all
sudo apt-get update && sudo apt-get upgrade && sudo apt-get dist-upgrade 
sudo apt-get install cmake
sudo apt-get install git
sudo apt-get install wiringpi

# some setup and test forpigpio library
sudo apt install python-setuptools python3-setuptools

cd ~
mkdir downloadDir && cd downloadDir
wget https://github.com/joan2937/pigpio/archive/master.zip
unzip master.zip
cd pigpio-master
make
sudo make install

#preparing for steppermotor library for c++
cd ~
mkdir stepperMotorDir && cd stepperMotorDir
# Download the code
git clone https://crish4cks@bitbucket.org/crish4cks/steppermotor.git

# Build it!
cd steppermotor/ 
mkdir build && cd build
cmake .. 
make



