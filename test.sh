#!/bin/sh
echo ".$1." >>/home/pi/prg/colormusic/test.log
cd /home/pi/prg/colormusic
sudo ./run
#if [ "$1" = "midi1" ]; then
#	/usr/bin/sudo /usr/bin/killall -9 lightorgan
#	/home/pi/prg/colormusic/lightorgan& >>/home/pi/prg/colormusic/test.log
#	echo "ouais"
#	echo "lala" $1 $2  >>/home/pi/prg/colormusic/test.log
#fi
