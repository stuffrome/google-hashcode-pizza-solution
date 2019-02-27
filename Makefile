SRC_DIR := ./source
TST_DIR := ./test
INC_DIR := ./include
OBJ_DIR := ./objects
CC := g++
CFLAGS := -std=c++17 -g
TARGET := pizza
INC := -I include/ -I$(HOME)/.local/include

SRCS := $(wildcard $(SRC_DIR)/*.cpp main.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)
clean:
	rm -rf $(TARGET) $(OBJ_DIR)/*.o
	
.PHONY: all clean