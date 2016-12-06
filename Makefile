CC = g++
CFLAGS = -Wall -pedantic
OBJS = renderer.o loader.o sidster.o
INCLUDES = -I/usr/local/include/resid
LIBS = -lresid -lyaml-cpp

all: sidster

sidster: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDES)

clean:
	rm -f *.o
