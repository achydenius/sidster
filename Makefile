CC = g++
CFLAGS = -Wall -pedantic
OBJS = sidster.o
INCLUDES = -I/usr/local/include/resid
LIBS = -lresid

all: sidster

sidster: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDES)

clean:
	rm -f *.o
