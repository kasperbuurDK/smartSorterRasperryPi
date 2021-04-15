#!/usr/bin/env bash.

#upgrade and update all
sudo apt-get update && sudo apt-get upgrade && sudo apt-get dist-upgrade 

# some setup and test forpigpio library
sudo apt install python-setuptools python3-setuptools

cd ~
mkdir downloadDir && cd downloadDir
wget https://github.com/joan2937/pigpio/archive/master.zip
unzip master.zip
cd pigpio-master
make
sudo make install

sudo ./x_pigpio # check C I/F

sudo pigpiod    # start daemon

./x_pigpiod_if2 # check C      I/F to daemon
./x_pigpio.py   # check Python I/F to daemon
./x_pigs        # check pigs   I/F to daemon
./x_pipe        # check pipe   I/F to daemon

sudo killall pigpiod  #end pigpiod 



#preparing for steppermotor library for c++

cd ~
mkdir stepperMotorDir && cd stepperMotorDir
sudo apt-get install cmake
sudo apt-get install git-core

# Download the code
git clone https://crish4cks@bitbucket.org/crish4cks/steppermotor.git

# Build it!
cd steppermotor/ 
mkdir build && cd build
cmake .. 
make



