# This Makefile is used for code-brush coding practise
# Author: Yun Wang <yunw@email.arizona.edu> 
# Date: 03/28/2016

CC = g++ 
CFLAGS = -g -Wall -std=c++0x
INCS = -I.
LIBS = -L. 
OBJS = main.o 

brush:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)
.cpp.o: 
	$(CC) -c $<  $(INC) $(CFLAGS)

clean:
	rm -f  run $(OBJS) 

#EOF
