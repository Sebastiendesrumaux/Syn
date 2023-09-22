# -*- coding: utf-8 -*-

#fifo.py
import os
import sys
import time
from neopixel import *

# LED strip configuration:
LED_COUNT      = 84      # Number of LED pixels.
LED_PIN        = 18      # (en BCM - (correspond à 12 en physique)) GPIO pin connected to the pixels (18 uses PWM!).
#LED_PIN        = 10      # GPIO pin connected to the pixels (10 uses SPI /dev/spidev0.0).
LED_FREQ_HZ    = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 10      # DMA channel to use for generating signal (try 10)
LED_BRIGHTNESS = 255     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False   # True to invert the signal (when using NPN transistor level shift)
LED_CHANNEL    = 0       # set to '1' for GPIOs 13, 19, 41, 45 or 53

bufferSize = 100;
PATHC2P = "/tmp/fifoc2p";
PATHP2C = "/tmp/fifop2c";
try:
    os.mkfifo(PATHC2P)
except Exception as e:
    print "mkfifoc2p:", e.__doc__
    print e.message
    print "mkfifoc2p:", sys.exc_info()[0]
try:
    os.mkfifo(PATHP2C)
except Exception as e:
    print "mkfifop2c:", e.__doc__
    print e.message
    print "mkfifop2c:", sys.exc_info()[0]
    
print "reader.py"
pipec2p = open(PATHC2P, "r");
print "reader.py: open fifo en mode lecture c2p done"

pipep2c = open(PATHP2C, "w");
print "reader.py: open fifo p2c done"




strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)
# Intialize the library (must be called once before other functions).

def colorWipe(strip, color, wait_ms=50):
    """Wipe color across display a pixel at a time."""
    for i in range(strip.numPixels()):
        strip.setPixelColor(i, color)
        strip.show()
        time.sleep(wait_ms/1000.0)

strip.begin()
#strip.setPixelColor(2, Color(255,255,0))
#colorWipe(strip,Color(128,255,0))
#colorWipe(strip,Color(0,0,0))
strip.show()


while True:
    #print "boucle de lecture python"
    input = pipec2p.readline();
    if input != "":
        input = input.replace("\n","");
        cmd, sep, apres = input.partition(" ");
        if cmd == "setPixelColor":

            pix,r,v,b = apres.split(" ");
            strip.setPixelColor(int(pix),Color(int(r),int(v),int(b)))
            strip.show()
        if cmd == "getNbPixels":
            pipep2c.write(str(LED_COUNT)+"\n");
        
        pipep2c.write("ok\n");
        pipep2c.flush();

pipep2c.close();
pipec2p.close();
