NAME        = philo

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -pthread
RM          = rm -f

SRCS := main.c \
utils.c \
init_parse_input.c \
libft.c \
init_philo.c \
init_philo_thr.c \
philo_actions.c

OBJS_MAIN := $(SRCS:.c=.o)

all: $(NAME)

/%.o: /%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_MAIN)
	$(CC) $(OBJS_MAIN) -o $(NAME) -lpthread
	echo "${BOLD}Creating  -> ${RED}$(NAME)${NO_COLOR}"
	${MAKE} spiderman

clean:
	$(RM) $(OBJS_MAIN)
	echo "\n✅ ${RED}SUCCESS:${NO_COLOR} ${BOLD}Objs files have been deleted"

fclean: clean
	$(RM) $(NAME)
	echo "\n✅ ${RED}SUCCESS:${NO_COLOR} ${BOLD}Objs file $(NAME) has been deleted\n"

re: fclean all

.PHONY: clean fclean re all
.SILENT:

RED         := ${shell tput setaf 1}
BLUE        := ${shell tput setaf 4}
NO_COLOR    := ${shell tput sgr0}
BOLD        := ${shell tput bold}

spiderman:
	@echo '⠀⠀⠀⢀⣤⠶⢞⠉⢉⡽⠁⠈⡗⠶⢤⣀⠀⠀⠀⠀'
	@echo '⠀⢀⡴⢻⠁⠀⢼⠉⠀⢰⠀⠀⡷⢄⠀⠹⠷⡄⠀⠀'
	@echo '⠀⡎⡀⠼⠉⠀⢨⠤⠐⢸⠀⠠⣧⠀⠈⡟⠄⣘⡄⠀'
	@echo '⠸⣿⡀⠀⠧⠊⠀⠆⠀⣸⡀⢀⠀⠀⠲⠀⠀⣼⣱⠀'
	@echo '⣶⣿⣿⣎⡀⢡⠄⠚⠁⢸⠀⠙⠂⣴⠁⣠⣾⣿⣿⡄'
	@echo '⣿⣿⠈⠛⢿⣥⡐⡤⢓⢹⢁⠣⡔⣠⣿⠟⠋⢸⣿⡇'
	@echo '⡏⣿⠀⠀⠀⠙⢿⣦⣾⣽⣽⣮⣾⠟⠁⠀⠀⢸⡿⡇'
	@echo '⢹⠿⣧⠀⠀⠀⠀⣹⣿⣿⣿⣿⡁⠀⠀⠀⢠⣿⢿⠃'
	@echo '⢸⣇⠻⣷⣤⣤⣾⡿⢻⢽⠼⠻⣿⣦⣤⣴⡿⠇⣿⠀'
	@echo '⠈⡏⢢⡨⠛⢉⡔⠉⠆⢠⠄⢓⠉⢢⡝⠛⢤⠊⡎⠀'
	@echo '⠀⠘⣼⠁⢠⠊⠈⡾⠠⢠⡠⠔⠏⠀⢱⡄⢉⡾⠀⠀'
	@echo '⠀⠀⠈⢲⣾⠀⢰⠅⠀⢈⢀⡀⠼⠎⢁⣷⡝⠁⠀⠀'
	@echo '⠀⠀⠀⠀⠙⢌⢺⠄⢀⠈⢁⣀⠤⣟⡵⠋⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠈⠂⠤⠬⠭⠤⠚⠁⠀⠀⠀⠀⠀⠀'
