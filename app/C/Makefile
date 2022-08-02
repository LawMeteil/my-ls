CC = gcc
NAME = my_ls
SRC = my_ls.c 
RM = rm -f
OBJ = $(SRC:%.c=%.o)
CFLAGS = -Wall -Werror -Wextra -std=c11
LDFLAGS = -L. -lmy
$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
all:	$(NAME)
clean:
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(OBJ)
re: fclean all