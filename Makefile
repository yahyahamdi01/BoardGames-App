#Compiler
CC := g++
#Compiler flags
CFLAGS := -Wall -std=c++17 -MMD -MP
#SFML flags
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
#Directories
SRC_DIR := src
GAME_DIR := game
EXCEPT_DIR := exception
BUTIN_DIR := $(GAME_DIR)/butin
CHECKERS_DIR := $(GAME_DIR)/checkers
BULLTRICKER_DIR := $(GAME_DIR)/bulltricker
#Source files
SRC := $(wildcard $(SRC_DIR)/*.cpp) \
	   $(wildcard $(SRC_DIR)/$(EXCEPT_DIR)/*.cpp) \
	   $(wildcard $(SRC_DIR)/$(GAME_DIR)/*.cpp) \
	   $(wildcard $(SRC_DIR)/$(BUTIN_DIR)/*.cpp) \
	   $(wildcard $(SRC_DIR)/$(CHECKERS_DIR)/*.cpp) \
	   $(wildcard $(SRC_DIR)/$(BULLTRICKER_DIR)/*.cpp)
#Object directory
OBJ_DIR := obj
#Object files
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
#Dependency files
DEP := $(OBJ:.o=.d)
#Executable name
EXE := boardgame

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(SFMLFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf $(OBJ_DIR) $(EXE)

-include $(DEP)

.PHONY: all clean