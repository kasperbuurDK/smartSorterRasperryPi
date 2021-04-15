#!/usr/bin/env bash.

#upgrade and update all
echo '-------- Updating all ----------'

sudo apt-get update && sudo apt-get upgrade && sudo apt-get dist-upgrade 
sudo apt-get install cmake
sudo apt-get install git


# install python and pigpio
sudo apt install python-setuptools python3-setuptools

wget https://github.com/joan2937/pigpio/archive/master.zip
unzip master.zip
cd pigpio-master
make
sudo make install





