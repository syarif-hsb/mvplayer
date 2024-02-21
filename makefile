CC			= gcc
SRC			= mvplayer.c ui.c
OBJ     = ${SRC:.c=.o}
CFLAGS	= -Wall -g
LDFLAGS	= `pkg-config --libs sdl2`

all: mvplayer

mvplayer: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

%.o: %.c makefile
	${CC} -c ${CFLAGS} $<

clean:
	rm -f mvplayer ${OBJ}

.PHONY:
	all clean
