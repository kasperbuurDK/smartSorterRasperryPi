#!/bin/bash
echo ----- updating python, making sure everything is ok
sudo apt install python-setuptools python3-setuptools
echo -------- python updated
echo ------- cloning pigpio
git clone https://github.com/joan2937/pigpio
echo ------- cloned pigpio
echo -------  cdToPigpio 
cd pigpio/
echo ---------- doingMake
make
echo ----------- doingMakeInstall
make install
