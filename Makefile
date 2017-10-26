# Makefile for the Percolate project

SRC_DIR=src

SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))
EXE_FILE=Percolate

## all       : Compile code and create executible 
.PHONY : all
all : $(EXE_FILE)

$(EXE_FILE) : $(OBJ_FILES)
	g++ $^ -o $@

## objs      : create object files
.PHONY : objs
objs : $(OBJ_FILES)

%.o : $(SRC_DIR)/%.cpp
	g++ -c -std=c++11 $<



## clean     : remove auto generated files
.PHONY : clean
clean :
	rm -f $(OBJ_FILES)
	rm -f $(EXE_FILE)

## variables : Print variables
.PHONY :variables
variables:
	@echo SRC_DIR:   $(SRC_DIR)
	@echo SRC_FILES: $(SRC_FILES)
	@echo OBJ_FILES: $(OBJ_FILES)
	


## help      : Print help
.PHONY : help
help : Makefile
	@sed -n 's/^##//p' $<