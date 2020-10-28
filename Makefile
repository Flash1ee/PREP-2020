TARGET = main.out
TEST = test.out
HDRS_DIR = project/include
SRCPATH:=./project/src/
TESTPATH = ./project/tests/
UNIT = $(TESTPATH)check_correct.c $(TESTPATH)unit_tests.c $(SRCPATH)write.c
SRCS = $(filter-out $(UNIT),$(wildcard $(SRCPATH)*.c)) $(SRCPATH)write.c
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
