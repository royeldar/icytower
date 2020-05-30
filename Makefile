CC	:= gcc
CFLAGS	:= -Wall
LDLIBS	:= -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_audio -lallegro_acodec

.PHONY: all clean

all: icytower

icytower: icytower.o gfx.o sfx.o menu.o options.o characters.o floor_types.o fullscreen.o game.o physics.o

icytower.o: icytower.c icytower.h gfx.h sfx.h menu.h options.h characters.h floor_types.h game.h
gfx.o: gfx.c gfx.h
sfx.o: sfx.c sfx.h
menu.o: menu.c menu.h icytower.h gfx.h sfx.h options.h characters.h floor_types.h fullscreen.h
options.o: options.c options.h
characters.o: characters.c characters.h gfx.h sfx.h
floor_types.o: floor_types.c floor_types.h gfx.h
fullscreen.o: fullscreen.c fullscreen.h
game.o: game.c game.h icytower.h gfx.h sfx.h options.h characters.h floor_types.h physics.h
physics.o: physics.c physics.h

clean:
	rm -f icytower *.o
