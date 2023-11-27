NAME=minitalk
BINARY1=client
BINARY2=server
CODEDIRS=src
INCDIR=./include/
BIN_DIR=./bin/

CC=gcc
OPT=-O
# https://stackoverflow.com/questions/8025766/makefile-auto-dependency-generation
#DEPFLAGS=-MP -MD
CFLAGS=-Wall -Wextra -Werror -I$(INCDIR) $(OPT)

CFILES=$(shell find $(CODEDIRS) -name '*.c')
OBJECTS = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(BINARY1) $(BINARY2)

# https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean
$(BINARY1): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ lib/libft.a

$(BINARY2): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ lib/libft.a

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(BINARY1)
	rm -f $(BINARY2)

re: fclean all

diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git --no-pager diff --stat

struct:
	$(info Create folder and basic file structure.)
	mkdir src lib include docs tests
	git clone https://github.com/viodid/libft.git lib/
	cd lib; make; make clean; rm -rf .git


.PHONY: minitalk all clean fclean re diff struct