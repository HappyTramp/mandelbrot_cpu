RM = rm -f

NAME = mandel

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

CC = gcc
OFLAG = -Ofast -funroll-loops -ffast-math
CCFLAGS = -I$(INC_DIR) -Wall -Wextra $(OFLAG)
LDFLAGS = -lm -lpthread \
		  $(shell pkg-config --libs --cflags sdl2 SDL2_ttf)

INC = $(shell find $(INC_DIR) -type f -name '*.h')
SRC = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: prebuild $(NAME)

prebuild:
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	$(CC) $(CCFLAGS) -c -o $@ $<

debug: OFLAG = -g
debug: all

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
