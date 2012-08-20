CC=gcc
CFLAGS=-O2
LDFLAGS=-L/opt/local/lib -lgmp -lm

# list of c files in every subdirectory
SRC=$(wildcard */*.c)
# every c files gets a single executable
TARGETS=$(SRC:.c=)

all: $(TARGETS)

% : %.c
	@echo "Building solution $(@D)"
	@$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^

clean:
	@rm -rf $(TARGETS) 

.PHONY: clean
