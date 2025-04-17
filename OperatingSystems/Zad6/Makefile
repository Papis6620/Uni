DIR = `basename $(CURDIR)`

NAME1 = zad6
NAME2 = licznik
LIB1 = semafory
PROC = 3
SK = 2
SEM = /semafor

EXEC1  = $(NAME1).x
EXEC2  = $(NAME2).x

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o

LIBS1  = $(LIB1).c

CFLAGS = -pthread -Wall -std=c99 -pedantic -O
LFLAGS = -pthread -Wall -std=c99 -pedantic -O

CO = gcc
LD = $(CO)

AR = ar

ARFLAGS = rsv

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run

run: $(EXEC1) $(EXEC2)
	clear
	./$(EXEC1) $(EXEC2) $(PROC) $(SK) $(SEM)

.PHONY: clean tar

clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )