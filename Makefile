TARGET = main.out
HDRS_DIR = project/include
SRCPATH:=./project/src/
SRCS = $(wildcard $(SRCPATH)*.c)
INCPATH = ./project/include/
CFLAGS = -I $(INCPATH) -Wall -Wextra -Werror
.PHONY: all clean

all: $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -rf $(TARGET)
