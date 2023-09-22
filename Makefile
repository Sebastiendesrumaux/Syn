CC=g++
CFLAGS=-I/usr/include/GL -D_GNU_SOURCE -DPTHREADS -fno-strict-aliasing  -pthread -D_REENTRANT -Wno-write-strings -Wno-narrowing 
LFLAGS=-lGL -lGLEW -lGLU -lglut -lGL -lm -lX11 -lXext -lSOIL 

television1: television1.c
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)  -lSDL2_image -lpthread -lpigpio -lrt -lasound -lm -g `sdl2-config --cflags --libs` 
optim: synesthezyx.cpp
	$(CC) -o synesthezyx $^ $(CFLAGS) $(LFLAGS) -O3 -lSDL2_image -lpthread -lpigpio -lrt -lasound -lm `sdl2-config --cflags --libs` 
synesthezyx: synesthezyx.cpp 
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS) -g -O0 -lSDL2_image -lpthread -lpigpio -lrt -lasound -lm `sdl2-config --cflags --libs` 
debug: synesthezyx.cpp
	$(CC) -o synesthezyx -O0 -g $^ $(CFLAGS) $(LFLAGS)  -lSDL2_image -lpthread -lpigpio -lrt -lasound -lm -g `sdl2-config --cflags --libs` 
affimg: affimg.c
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)  -lSDL2_image -lpthread -lpigpio -lrt -lasound -lm -g `sdl2-config --cflags --libs` 
pcm: pcm.c 
	gcc pcm.c -lpthread -lpigpio -lrt -lasound `sdl-config --cflags --libs`  -lm -g -Wall -o pcm
	sudo chmod u+s pcm



is_keyboard: is_keyboard.c
	gcc is_keyboard.c -o is_keyboard
reglage: reglage.c
	gcc reglage.c -o reglage
terminate: terminate.c 
	gcc terminate.c -lpthread -lpigpio -lrt -lasound -g -Wall -o terminate
servo:
	gcc servo_demo.c -lpthread -lpigpio -lrt -lasound -lwiringPi -g -Wall -o servo_demo
minimal:
	gcc minimal_gpio.c -lpthread -lpigpio -lrt -lasound -lwiringPi -g -Wall -o minimal_gpio

testpigpio: testpigpio.c
	gcc testpigpio.c -lpthread -lpigpio -lrt -lasound -g -Wall -o testpigpio

