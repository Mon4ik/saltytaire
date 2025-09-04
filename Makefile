PKG_CONFIG := raylib

CFLAGS := \
		-Wall -Wextra \
		$$(pkg-config --libs --cflags $(PKG_CONFIG))

saltytare: *.c
	$(CC) $(CFLAGS) -o $@ $^
