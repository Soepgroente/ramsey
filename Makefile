NAME	= cubing
RM		= rm -rf
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -g -fsanitize=address #-flto 
SRCS	= calculate.c coloring.c main.c math_functions.c utilities.c

OBJDIR	= cubejects

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

all:	$(NAME)

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:	
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test
