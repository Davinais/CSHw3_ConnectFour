C = clang
CFLAGS = -g -std=c11 -Wall -Wextra

BIN_DIR = bin
BUILD_DIR = obj
SRC_DIR = src

SOURCES := $(wildcard $(SRC_DIR)/*.c)
INCLUDES := ./$(SRC_DIR)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJECTS:%.o=%.d)
TARGET := hw3

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(C) -o $@ $(OBJECTS)

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(C) -MM $< > $(BUILD_DIR)/$*.d
	$(C) -I$(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(DEPS) $(BIN_DIR)/$(TARGET)
