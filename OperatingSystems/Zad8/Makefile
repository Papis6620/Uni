#
# make: all, clean, tar  
#
#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
#------------------------
NAME1 = serwer
NAME2 = klient
NAME4 = kolejka
#----------------------
EXEC1 = $(NAME1)
EXEX1 = $(NAME1).x
OBJS1 = $(NAME1).o

EXEC2 = $(NAME2)
EXEX2 = $(NAME2).x
OBJS2 = $(NAME2).o

LIB1 = $(NAME4).c
#----------------------
#############################
COFLAGS = -Wall -std=c99 -pedantic
LDFLAGS = -Wall -std=c99 -pedantic 
CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
%.x: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEX1) $(EXEX2)
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^ $(LIB1) -lrt
#############################
$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(LDFLAGS) $^ $(LIB1) -lrt
#############################
$(EXEX1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^ $(LIB1) -lrt
#############################
$(EXEX2): $(OBJS2)
	 $(LD) -o $@ $(LDFLAGS) $^ $(LIB1) -lrt
#############################
.PHONY: run
run: $(EXEX2) $(EXEX3)
	xterm -hold -title $(NAME1) -bg red -fg black -e ./$(EXEX1) &
	xterm -hold -title $(NAME2) -bg blue -fg black -e ./$(EXEX2) &
	xterm -hold -title $(NAME2)2 -bg blue -fg black -e ./$(EXEX2) &

#############################
.PHONY: clean tar
# Porzadki
EXECS := $(EXEC1) $(EXEC2) $(EXEX1) $(EXEX2)
clean:                                                     
	rm -f *.o  *~ $(EXECS)
#==========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#==========================================================================
