CXX = clang
CXXFLAGS = -g -std=c11 -Wall -Wextra

BIN_DIR = bin
BUILD_DIR = obj
SRC_DIR = src

SOURCES := $(wildcard $(SRC_DIR)/*.c)
INCLUDES := ./$(SRC_DIR)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJECTS:%.o=%.d)
TARGET := hw3

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CXX) -MM $< > $(BUILD_DIR)/$*.d
	$(CXX) -I$(INCLUDES) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(DEPS) $(BIN_DIR)/$(TARGET)
