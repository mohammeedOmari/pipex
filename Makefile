CFLALGS = -Wall -Wextra -Werror
NAME = pipex
CC = cc
SRC = pipex.c pipex_utils.c src/ft_putstr_fd.c src/ft_split.c src/ft_strchr.c src/ft_strjoin.c src/ft_strlen.c src/ft_strncmp.c src/ft_substr.c src/ft_strdup.c src/ft_memcpy.c
BSRC = 	bonus/pipex_bonus.c bonus/pipex_utils_bonus.c bonus/get_1_bonus.c bonus/get_2_bonus.c bonus/src/ft_putstr_fd_bonus.c bonus/src/ft_split_bonus.c \
		bonus/src/ft_strchr_bonus.c bonus/src/ft_strjoin_bonus.c bonus/src/ft_strlen_bonus.c bonus/src/ft_strncmp_bonus.c bonus/src/ft_substr_bonus.c bonus/src/ft_strdup_bonus.c \
		bonus/src/ft_memcpy_bonus.c 

OBJS = $(SRC:.c=.o)
BOBJS = $(BSRC:.c=.o)
NAME_BONUS = pipex_bonus
HEADER = ./bonus/pipex_bonus.h

all: $(NAME)

bonus : $(NAME_BONUS)

$(NAME_BONUS): $(BOBJS)
	$(CC) $(CFLALGS) $^ -o $(NAME_BONUS)

%_bonus.o: %_bonus.c $(HEADER)
	$(CC) $(CFLALGS) -c $< -o $@

%.o: %.c pipex.h
	$(CC) $(CFLALGS) -c $< -o $@

$(NAME): $(OBJS) 
	$(CC) $(CFLALGS) $^ -o $(NAME)

clean:
	rm -rf $(OBJS) $(BOBJS)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS) 

re: fclean all