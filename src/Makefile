# the compiler: gcc for C program, define as g++ for C++
CC = gcc
CXX = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall 

# Libraries
LDFLAGS = -lm `pkg-config --libs sdl SDL_ttf SDL_image`

TARGET = centron

OBJS = main.o core.o graphics.o resources.o drawable.o log.o starfield.o timer.o util.o

all: $(TARGET)

debug: CFLAGS += -DDEBUG -g
debug: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CFLAGS) -c $^

core.o: core.cpp core.h
	$(CXX) $(CFLAGS) -c $^

graphics.o: graphics.cpp graphics.h
	$(CXX) $(CFLAGS) -c $^

drawable.o: drawable.cpp drawable.h
	$(CXX) $(CFLAGS) -c $^

resources.o: resources.cpp resources.h
	$(CXX) $(CFLAGS) -c $^

log.o: log.cpp log.h
	$(CXX) $(CFLAGS) -c $^

starfield.o: starfield.cpp starfield.h
	$(CXX) $(CFLAGS) -c $^

timer.o: timer.cpp timer.h
	$(CXX) $(CFLAGS) -c $^

util.o: util.cpp util.h
	$(CXX) $(CFLAGS) -c $^

clean:
	$(RM) $(TARGET) *.o *.gch
