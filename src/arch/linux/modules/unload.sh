#!/bin/sh
device="ktblmgr"

sudo rmmod schedule_hook
cd intercept
./unload.sh
cd ..
sudo rm -f /dev/${device}
sudo rmmod cross_state_manager

echo "Done"
