CSRC=$(wildcard *.c)
SSRC=$(wildcard *.S)

_OBJS = $(CSRC:%.c=%.o) $(SSRC:%.S=%.o)
OBJS = $(addprefix $(BUILD_DIR)/, $(_OBJS))

CFLAGS=-Og -std=c99 -Wall -Iinclude
SFLAGS=-Og -Wall -Iinclude

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	$(CC) $(SFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

.PHONY: all
all: $(BUILD_DIR) $(OBJS)
	$(SIZE) -t $(OBJS)

.PHONY: clean
clean: 
	rm -f $(OBJS)
