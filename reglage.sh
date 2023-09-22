echo $1
cd /home/pi/prg/colormusic
#/usr/bin/sudo /bin/echo "launch reglage" >> reglage.log
sudo killall -INT reglage
make reglage
/home/pi/prg/colormusic/reglage $1
