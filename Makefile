CC = g++
PWD := $(shell pwd)
CFLAGS = -fPIC
LDFLAGS = -shared

RM = rm -f


SRCS := $(wildcard *.h)
OBJS := $(patsubst %.h,%.o,$(SRCS))


all: main


%.so:%.o
	$(CC) $(INC) $(CFLAGS) -o $@ $^

main: Main.cpp $(OBJS)
	$(CC) -o $@ $^

clean:
	$(RM) $(PWD)/*.so $(PWD)/*.o main