##
## EPITECH PROJECT, 2022
## examples/sandbox/Makefile
## File example:
## Makefile for the sanbdox example
##

NAME = sandbox
SOURCES = *.cpp
CXX_FLAGS = -g -MD
INCLUDE_FLAGS = -I../../src
LINKER_FLAGS = -L../../ -lhoppy

ifeq ($(OS), Windows_NT)
	LINKER_FLAGS = -L../../ -lhoppy -luser32
	OUTPUT = $(NAME).exe
else
	LINKER_FLAGS = -L../../ -L/usr/X11R6/lib -lX11 -lX11-xcb -lxcb -lhoppy
	OUTPUT = $(NAME)
endif

all: $(NAME)

$(NAME):
	clang $(SOURCES) $(CXX_FLAGS) -o $(OUTPUT) $(INCLUDE_FLAGS) $(LINKER_FLAGS)

clean:
	rm -f $(NAME).d
	rm -f $(NAME).ilk
	rm -f $(NAME).pdb
	
fclean: clean
	rm -f $(OUTPUT)

re: fclean all

.PHONY: all, $(NAME), clean, fclean, re
