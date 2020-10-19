TARGET = main.out
TEST = test.out
HDRS_DIR = project/include
SRCPATH:=./project/src/
TESTPATH = ./project/tests/
UNIT = $(TESTPATH)main_module.c $(TESTPATH)write_to_file.c $(TESTPATH)read_from_file.c $(TESTPATH)read_write_test.c
SRCS = $(filter-out $(UNIT),$(wildcard $(SRCPATH)*.c))
INCPATH = ./project/include/
CFLAGS = -I $(INCPATH) -Wall -Wextra -Werror
.PHONY: all clean test

all: $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(CFLAGS) $(SRCS)
test: $(UNIT)
	$(CC) $(CFLAGS) -o $(TEST) $(UNIT) $(SRCPATH)io.c


clean:
	rm -rf $(TARGET)
	rm -rf $(TEST)
