#!/usr/bin/env bash.
echo ----- updating python, making sure everything is ok
sudo apt install python-setuptools python3-setuptools
echo -------- python updated
echo ------- cloning pigpio
git clone https://github.com/joan2937/pigpio
echo ------- cloned
echo --------- cd pigpio-master 
cd pigpio-master
echo --------- make
make
echo --------- make install
sudo make install
