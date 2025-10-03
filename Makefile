# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/02 19:06:30 by emgenc            #+#    #+#              #
#    Updated: 2025/09/07 11:50:35 by emgenc           ###   ########.fr        #
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

########## Commons ##########
SUCCESS				:= ${FG_GREEN}${BOLD}
WARNING				:= ${FG_YELLOW}${BOLD}
REDWARNING			:= ${FG_RED}${BOLD}
INFO				:= ${FG_CYAN}${BOLD}
INFOMAGENTA			:= ${FG_MAGENTA}${BOLD}

NAME				:= miniRT
NAME_BONUS			:= miniRT_bonus
PRJ_ROOT			:= $(CURDIR)

LIBFT				= e-libft/libft.a
MLX					= minilibx/libmlx_Linux.a
MLXFLAGS			= -Lminilibx -lmlx_Linux -lXext -lX11 -lm

UTIL_SOURCES		= draw_scene.c draw_scene_utils.c color.c color_utils.c vector.c transformation.c objects_constructors.c objects_intersection.c objects_intersection2.c vector2.c point.c parser.c parser_funcs.c parser_utils.c get_next_line.c
UTIL_OBJECTS		= ${UTIL_SOURCES:.c=.o}

MANDATORY_SOURCES	= rt.c 
MANDATORY_OBJECTS	= ${UTIL_OBJECTS} ${MANDATORY_SOURCES:.c=.o}

# BONUS_SOURCES		= 
BONUS_OBJECTS		= ${UTIL_OBJECTS} ${BONUS_SOURCES:.c=.o}

CC					= cc
CFLAGS				= -Wall -Wextra -Werror -g3
VGRIND_FLAGS		= --leak-check=full --errors-for-leak-kinds=all --track-origins=yes --show-leak-kinds=all

.SILENT:

all:	${NAME}

$(LIBFT):
	make -C e-libft

$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git minilibx
	make -C minilibx

${NAME}:	${MLX} ${LIBFT} ${MANDATORY_OBJECTS}
	clear
	echo "${INFO}miniRT: compiling mandatory...${RESET}"
	$(CC) ${MANDATORY_OBJECTS} ${LIBFT} ${MLX} ${MLXFLAGS} -o ${NAME}
	echo "${SUCCESS}Compilation successful!${RESET}"

bonus:	${MLX} ${LIBFT} ${BONUS_OBJECTS}
	clear
	echo "${INFO}miniRT: compiling bonus...${RESET}"
	$(CC) ${BONUS_OBJECTS} ${LIBFT} ${MLX} ${MLXFLAGS} -o ${NAME_BONUS}
	echo "${SUCCESS}Compilation successful!${RESET}"

clean:
	clear
	echo -n "${WARNING}${UNDERLINE}Cleaning${UNDERLINE_OFF} objects...\n${RESET}"
	rm -rf ${MANDATORY_OBJECTS} ${BONUS_OBJECTS} ${UTIL_OBJECTS}
	make clean -C e-libft
	echo "${SUCCESS}Objects cleaned.${RESET}"

fclean:	clean
	clear
	echo -n "${REDWARNING}${UNDERLINE}Removing${UNDERLINE_OFF} executables...\n${RESET}"
	rm -rf ${NAME} ${NAME_BONUS}
	make fclean -C e-libft
	rm -rf minilibx
	echo "${SUCCESS}Executables removed.${RESET}"

re:	fclean all

exec: clean all
	clear
	echo "${INFO}miniRT: compiling mandatory...${RESET}"
	echo "${SUCCESS}Compilation finished. Ready!\n\n${RESET}${WARNING}WARNING: Executing mandatory ${UNDERLINE}without valgrind.\n${RESET}${INFOMAGENTA}For leak controls, use ${RESET}${REDWARNING}make vgrind.${RESET}"
	make -C ${PRJ_ROOT} clean
	./${NAME}

execbonus: fclean all
	clear
	echo "${INFO}miniRT: compiling bonus...${RESET}"
	echo "${SUCCESS}Compilation finished. Ready!\n\n${RESET}${WARNING}WARNING: Executing bonus ${UNDERLINE}without valgrind.\n${RESET}${INFOMAGENTA}For leak controls, use ${RESET}${REDWARNING}make vgrind.${RESET}"
	make -C ${PRJ_ROOT} clean
	./${NAME_BONUS}

vgrind: fclean all
	clear
	echo "${INFO}miniRT: compiling and executing ${RESET}${REDWARNING}${UNDERLINE}with vgrind...${RESET}"
	echo "${SUCCESS}Compilation finished. Ready!\n\n${RESET}"
	make -C ${PRJ_ROOT} clean
	valgrind ${VGRIND_FLAGS} ./${NAME}

vgrindbonus: fclean all
	clear
	echo "${INFO}miniRT: compiling and executing ${RESET}${REDWARNING}${UNDERLINE}with vgrind...${RESET}"
	echo "${SUCCESS}Compilation finished. Ready!\n\n${RESET}"
	make -C ${PRJ_ROOT} clean
	valgrind ${VGRIND_FLAGS} ./${NAME_BONUS}

clear: fclean
	clear

.PHONY:	all bonus clean fclean re exec vgrind execbonus vgrindbonus clear
