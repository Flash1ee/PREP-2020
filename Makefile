TARGET_FRST  = stage1.out
TARGET_SEC  = stage2.out

# XXX: Don't forget backslash at the end of any line except the last one
HDRS_FRST = \
	   project/stage1/include/

HDRS_SEC = \
	   project/stage2/include/

SRCS_FRST = \
       project/stage1/src/main.cpp \
       project/stage1/src/entities.cpp  \
       project/stage1/src/enemy.cpp \
       project/stage1/src/player.cpp 
SRCS_SEC = \
       project/stage2/src/main.cpp \
       project/stage2/src/map.cpp  \
       project/stage2/src/enemy.cpp \
       project/stage2/src/player.cpp 


.PHONY: build clean run


build: $(SRCS_FRST) $(SRCS_SEC)
	$(CXX) -std=gnu++17 -Wall -Wextra -Werror $(addprefix -I,$(HDRS_FRST)) -o $(TARGET_FRST) $(CFLAGS) $(SRCS_FRST)
	$(CXX) -std=gnu++17 -Wall -Wextra -Werror $(addprefix -I,$(HDRS_SEC)) -o $(TARGET_SEC) $(CFLAGS) $(SRCS_SEC)
	
clean:
	rm -rf $(TARGET)

run: all
	./main.out