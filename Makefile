PKG_CONFIG := raylib

CFLAGS := \
		-Wall -Wextra \
		-I./thirdparty/ \
		$$(pkg-config --cflags $(PKG_CONFIG))

LDFLAGS := $$(pkg-config --libs $(PKG_CONFIG))

SOURCES_DIR := ./src
BUILD_DIR = ./build

SOURCES := $(shell find $(SOURCES_DIR) -name '*.c')
OBJECTS := $(SOURCES:%=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/saltytaire: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
