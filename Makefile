# OS
# ----------------------------------------------------------------------------
# Makefile
# ----------------------------------------------------------------------------
# Program: minishell
# Author: Ramsay

CC = gcc
CFLAGS = -static -Wall -Wextra

PROGRAM = minishell

SRC_DIR = src
INC_DIR = include
LIB_DIR = lib
OBJ_DIR = obj
BIN_DIR = bin

_DEPS = parser.h minishell.h ramsayboy.h
DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))

_OBJS = main.o minishell.o ramsayboy.o
OBJS = $(patsubst %,$(SRC_DIR)/%,$(_OBJS))

_LIBS = libparser.a
LIBS = $(patsubst %,$(LIB_DIR)/%,$(_LIBS))

%.o: %.c $(DEPS)
	@echo "[INFO] Generating $@ from $<..."
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "[DONE] $@ created"
	@echo "----------------------------------"

$(BIN_DIR)/$(PROGRAM): $(OBJS) $(LIBS)
	@echo "[INFO] Compiling project..."
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "[DONE] Project compiled"
# find out another way to do this
	@mv $(OBJS) $(OBJ_DIR)/

#minishell: $(OBJS) libparser.a
#	$(CC) $(CFLAGS) $< -o $@ -L. -lparser

.PHONY: clean create_dirs

create_dirs:
	@mkdir -p obj/
	@mkdir -p bin/
	@echo "[DONE] Directories needed created"

#ifneq ($(wildcard /obj/.),)
#	@echo "Creating obj/...";
#	@mkdir obj/
#else
#	@echo "obj/ already exists"
#endif
#
#ifneq ($(wildcard /bin/.),)
#	@echo "Creating bin/...";
#	@mkdir bin/
#else
#	@echo "bin/ already exists"
#endif

clean:
	@echo "[INFO] Cleaning..."
	@rm -rfv $(OBJ_DIR)/*.o
	@rm -rfv $(BIN_DIR)/$(PROGRAM)
	@echo "[DONE] Successful cleaning"