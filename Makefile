EXE	=	sDAQ

CC	=	gcc

COPTS	=	-fPIC -DLINUX -Wall

FLAGS	=	-Wall -s

DEPLIBS	=       -l CAENVME -l ncurses -lc -lm

LIBS	=

INCLUDEDIR =	-I.

OBJS	=	./src/sDAQ_Main.o

INCLUDES =	./header/CAENVMElib.h ./header/CAENVMEtypes.h ./header/CAENVMEoslib.h
#########################################################################

all	:	$(EXE)

clean	:
		/bin/rm -f $(OBJS) $(EXE)

$(EXE)	:	$(OBJS)
		/bin/rm -f $(EXE)
		$(CC) $(FLAGS) -o $(EXE) $(OBJS) $(DEPLIBS)

$(OBJS)	:	$(INCLUDES) Makefile

%.o	:	%.c
		$(CC) $(COPTS) $(INCLUDEDIR) -c -o $@ $<

