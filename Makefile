CC	:= x86_64-w64-mingw32-gcc
CFLAGS	:= -Wall -Iallegro/include -O2
LDLIBS	:= -lallegro.dll -lallegro_main.dll -lallegro_image.dll -lallegro_font.dll -lallegro_audio.dll -lallegro_acodec.dll
LDFLAGS	:= -Lallegro/lib

DLLS	:= allegro/bin/allegro-5.2.dll allegro/bin/allegro_image-5.2.dll allegro/bin/allegro_font-5.2.dll allegro/bin/allegro_audio-5.2.dll allegro/bin/allegro_acodec-5.2.dll

.PHONY: all clean

all: build/icytower.exe
	cp -r gfx sfx build/
	cp $(DLLS) build/

build/icytower.exe: icytower.o gfx.o sfx.o menu.o options.o characters.o floor_types.o fullscreen.o game.o physics.o
	mkdir -p build
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

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
	rm -rf *.o build
