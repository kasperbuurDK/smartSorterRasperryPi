#!/usr/bin/env bash.

#upgrade and update all
echo '-------- Updating all ----------'
sudo apt-get update && sudo apt-get upgrade && sudo apt-get dist-upgrade 

sudo apt install python-setuptools python3-setuptools
sudo apt install python3-gpiozero
