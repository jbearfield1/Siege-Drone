CXX := g++

SRC_DIR := ./src
OBJ_DIR := ./obj
BIN_DIR := ./bin

TARGET := $(BIN_DIR)/run
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

CPPFLAGS := -I./include -MMD -MP
CXXFLAGS := 
LDFLAGS := -Llib
LDLIBS := -lm

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -v $(BIN_DIR)/* $(OBJ_DIR)/*

-include $(OBJ:.o=.d)