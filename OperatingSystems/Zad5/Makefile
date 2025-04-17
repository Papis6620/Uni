# make: all, clean, tar  
#
#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = zad5
NAME2 = input
NAME3 = output
#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
#----------------------
EXEC3 = $(NAME3)
OBJS3 = $(NAME3).o
#############################
COFLAGS = -Wall -O
LDFLAGS = -Wall -O
CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) 
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
# uruchamianie plików 
.PHONY: run
ARGS ?= 
run: $(EXEC1)
	./$(EXEC1) $(ARGS)
	wait
	diff -s $(ARGS)
.PHONY: clean tar
# Porzadki
EXECS = $(EXEC1) $(EXEC2) $(EXEC3)
clean:                                                     
	rm -f *.o  *~ $(EXECS)
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================
