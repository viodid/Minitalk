NAME=minitalk
BINARY1=client
BINARY2=server
CODEDIRS=src
INCDIR=./include/
INCLIB=./lib/libft.a ./lib/ft_printf/printf.a
BIN_DIR=./bin/

CC=gcc
OPT=-g3
# https://stackoverflow.com/questions/8025766/makefile-auto-dependency-generation
#DEPFLAGS=-MP -MD
CFLAGS=-Wall -Wextra -Werror -I$(INCDIR) $(OPT)

CFILES1=$(shell find $(CODEDIRS)/client -name '*client.c')
CFILES2=$(shell find $(CODEDIRS)/server -name '*server.c')
OBJECTS1 = $(CFILES1:.c=.o)
OBJECTS2 = $(CFILES2:.c=.o)

BONUS_CFILES1 = $(shell find $(CODEDIRS)/client -name '*bonus.c') $(CODEDIRS)/client/utils_client.c
BONUS_CFILES2 = $(shell find $(CODEDIRS)/server -name '*bonus.c')
BONUS_OBJ1 = $(BONUS_CFILES1:.c=.o)
BONUS_OBJ2 = $(BONUS_CFILES2:.c=.o)

all: $(NAME)

$(NAME): $(BINARY1) $(BINARY2)

# https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean
$(BINARY1): $(OBJECTS1)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLIB)

$(BINARY2): $(OBJECTS2)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLIB)

clean:
	rm -f $(OBJECTS1) $(OBJECTS2) $(BONUS_OBJ1) $(BONUS_OBJ2)

fclean: clean
	rm -f $(BINARY1) $(BINARY2) client_bonus server_bonus

re: fclean all

bonus: client_bonus server_bonus

client_bonus: $(BONUS_OBJ1)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLIB)

server_bonus: $(BONUS_OBJ2)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLIB)


diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git --no-pager diff --stat

struct:
	$(info Create folder and basic file structure.)
	mkdir -p src lib/ft_printf include docs tests
	git clone https://github.com/viodid/libft.git lib/
	git clone https://github.com/viodid/ft_printf.git lib/ft_printf/
	cd lib; make; make clean; rm -rf .git
	cd lib/ft_pintf; make; make clean; rm -rf .git


.PHONY: minitalk all clean fclean re diff struct