# options
CXX = g++

INC = include
CPPFLAGS = -I$(INC)
CXXFLAGS = -m32
LDFLAGS = -m32

TARGET = big_integer
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj

SRC = $(notdir $(wildcard $(SRC_DIR)/*.cpp))
_OBJ = $(SRC:.cpp=.o)
OBJ = $(patsubst %.o,$(OBJ_DIR)/%.o,$(_OBJ))

all: $(BIN_DIR)/$(TARGET)

OUTPUT_OPTION = -o $@

# compile
COMPILE.cpp = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(OBJ_DIR):
	mkdir -p $@

# link
LINK.o = $(CXX) $(LDFLAGS)

$(BIN_DIR)/$(TARGET): $(OBJ) | $(BIN_DIR)
	$(LINK.o) $^ $(OUTPUT_OPTION)

$(BIN_DIR):
	mkdir -p $@

# clean
clean:
	rm -f $(OBJ) $(BIN_DIR)/$(TARGET)

.PHONY: all clean