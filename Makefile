CC = g++
PWD := $(shell pwd)
CFLAGS = -fPIC
LDFLAGS = -shared

RM = rm -f


SRCS := $(wildcard *.h)
OBJS := $(patsubst %.h,%.o,$(SRCS))

# if you want to print console uncomment this code below
all: main run_console_output


# if you want to print txt file uncomment this code below
# all: main run_redirect_ouput_to_file


%.so:%.o
	$(CC) $(INC) $(CFLAGS) -o $@ $^

main: Main.cpp $(OBJS)
	$(CC) -o $@ $^

run_redirect_ouput_to_file:
	sudo ./main > manual_data.txt

run_console_output:
	sudo ./main

clean:
	$(RM) $(PWD)/*.so $(PWD)/*.o main