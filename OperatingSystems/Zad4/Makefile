#
# make: all, clean, tar  
#
#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = zad4
#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------
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
all: $(EXEC1)
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
.PHONY: run
ARGS ?=
run: $(EXEC1)
	./$(EXEC1) $(ARGS)
	wait
	diff -s $(ARGS)
#############################
.PHONY: clean tar
# Porzadki
EXECS = $(EXEC1)
clean:                                                     
	rm -f *.o  *~ $(EXECS)
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================

