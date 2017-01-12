ROOTDIR=/home/enseign/ASE

CC	= gcc
CFLAGS	= -Wall -m32 -W 
CFLAGS  += -g
INCS    = -I$(ROOTDIR)/include
LIBS    = -L$(ROOTDIR)/lib -lhardware

all: display_stack try_mul ping_pong ping_pong_bis prodcons philosophe
display_stack: display_stack.o
	${CC} ${CFLAGS} -o $@ $^
try_mul: try_mul.o try.o
	${CC} ${CFLAGS} -o $@ $^
sem: sem.o contexte.o
ping_pong: ping_pong.o contexte.o
philosophe: philosophe.o contexte.o
	${CC} ${CFLAGS} -o $@ $^ ${LIBS}
prodcons: prodcons.o contexte.o
	${CC} ${CFLAGS} -o $@ $^ ${LIBS}
ping_pong_bis: ping_pong_bis.o contexte.o 
	${CC} ${CFLAGS} -o $@ $^ ${LIBS}
%.o: %.c %.h 
	${CC} ${CFLAGS} ${INCS} -c $<
%.o: %.c  
	${CC} ${CFLAGS} ${INCS} -c $<

clean:
	rm *.o 
	rm display_stack 
	rm try_mul
	rm ping_pong
	rm ping_pong_bis
	rm prodcons
	rm philosophe
.PHONY: all clean
