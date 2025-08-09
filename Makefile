# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/02 19:06:30 by emgenc            #+#    #+#              #
#    Updated: 2025/08/09 22:32:54 by emgenc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Text formatting codes ###
BOLD				:= \033[1m
BOLD_OFF			:= \033[22m
ITALIC				:= \033[3m
ITALIC_OFF			:= \033[23m
UNDERLINE			:= \033[4m
UNDERLINE_OFF		:= \033[24m
STRIKETHROUGH		:= \033[9m
STRIKETHROUGH_OFF	:= \033[29m

### Foreground color codes ###
FG_BLACK			:= \033[30m
FG_RED				:= \033[31m
FG_GREEN			:= \033[32m
FG_YELLOW			:= \033[33m
FG_BLUE				:= \033[34m
FG_MAGENTA			:= \033[35m
FG_CYAN				:= \033[36m
FG_WHITE			:= \033[37m
FG_DEFAULT			:= \033[39m

### Background color codes ###
BG_BLACK			:= \033[40m
BG_RED				:= \033[41m
BG_GREEN			:= \033[42m
BG_YELLOW			:= \033[43m
BG_BLUE				:= \033[44m
BG_MAGENTA			:= \033[45m
BG_CYAN				:= \033[46m
BG_WHITE			:= \033[47m
BG_DEFAULT			:= \033[49m

RESET				:= \033[0m

####### Commons #######
SUCCESS				:= ${FG_GREEN}${BOLD}
WARNING				:= ${FG_YELLOW}${BOLD}
REDWARNING			:= ${FG_RED}${BOLD}
INFO				:= ${FG_CYAN}${BOLD}
INFOMAGENTA			:= ${FG_MAGENTA}${BOLD}

NAME				:= miniRT
NAME_BONUS			:= miniRT_bonus
PRJ_ROOT			:= $(CURDIR)

# UTIL_SOURCES		= 
UTIL_OBJECTS		= ${UTIL_SOURCES:.c=.o}

# MANDATORY_SOURCES	= 
MANDATORY_OBJECTS	= ${UTIL_OBJECTS} ${MANDATORY_SOURCES:.c=.o}

# BONUS_SOURCES		= 
BONUS_OBJECTS		= ${UTIL_OBJECTS} ${BONUS_SOURCES:.c=.o}

CC					= cc
CFLAGS				= -Wall -Wextra -Werror
VGRIND_FLAGS		= --leak-check=full --errors-for-leak-kinds=all --track-origins=yes --show-leak-kinds=all

.SILENT:

all:	${NAME}

${NAME}:	${MANDATORY_OBJECTS}
	clear
	echo "${INFO}miniRT: compiling mandatory..."
	$(CC) ${MANDATORY_OBJECTS} -o ./miniRT/${NAME}
	echo "${SUCCESS}Compilation successful!${RESET}"

bonus:	${BONUS_OBJECTS}
	clear
	echo "${INFO}miniRT: compiling bonus..."
	$(CC) ${BONUS_OBJECTS} -o ./miniRT_bonus/${NAME_BONUS}
	echo "${SUCCESS}Compilation successful!${RESET}"

clean:
	clear
	echo -n "${WARNING}${UNDERLINE}Cleaning${UNDERLINE_OFF} objects...\t"
	rm -rf ${MANDATORY_OBJECTS} ${BONUS_OBJECTS}
	echo "${SUCCESS}Objects cleaned.${RESET}"

fclean:	clean
	clear
	echo -n "${REDWARNING}${UNDERLINE}Removing${UNDERLINE_OFF} executables...\t"
	rm -rf ./miniRT/${NAME} ./miniRT_bonus/${NAME_BONUS}
	echo "${SUCCESS}Executables removed.${RESET}"

re:	fclean all

exec: fclean all clean
	clear
	echo "${INFO}miniRT: compiling mandatory..."
	echo "${SUCCESS}Compilation finished. Ready!\n\n${RESET}${WARNING}WARNING: Executing mandatory ${UNDERLINE}without valgrind.\n${RESET}${INFOMAGENTA}For leak controls, use ${RESET}${REDWARNING}make vgrind.${RESET}"
	./miniRT/${NAME} 5 800 200 200

execbonus: fclean all clean
	clear
	echo "${INFO}miniRT: compiling bonus..."
	echo "${SUCCESS}Compilation finished. Ready!\n\n${RESET}${WARNING}WARNING: Executing bonus ${UNDERLINE}without valgrind.\n${RESET}${INFOMAGENTA}For leak controls, use ${RESET}${REDWARNING}make vgrind.${RESET}"
	./miniRT_bonus/${NAME_BONUS} 5 800 200 200

vgrind: fclean all clean
	clear
	echo "${INFO}miniRT: compiling and executing ${RESET}${REDWARNING}${UNDERLINE}with vgrind...${RESET}"
	echo "${SUCCESS}Compilation finished. Ready!\n\n${RESET}"
	valgrind ${VGRIND_FLAGS} ./miniRT/${NAME} 5 800 200 200

vgrindbonus: fclean all clean
	clear
	echo "${INFO}miniRT: compiling and executing ${RESET}${REDWARNING}${UNDERLINE}with vgrind...${RESET}"
	echo "${SUCCESS}Compilation finished. Ready!\n\n${RESET}"
	valgrind ${VGRIND_FLAGS} ./miniRT_bonus/${NAME_BONUS} 5 800 200 200

clear: fclean
	clear

.PHONY:	all bonus clean fclean re exec vgrind execbonus vgrindbonus clear
