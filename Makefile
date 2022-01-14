CFLAGS = -Wall -Wextra -Werror

HDRS = pipex.h get_next_line.h

HDRS_BONUS = pipex_bonus.h get_next_line_bonus.h

HEADERS = $(addprefix includes/, ${HDRS})

HEADERS_BONUS = $(addprefix includes_bonus/, ${HDRS_BONUS})

CC = cc

RM = rm -f

NAME = pipex

BONUS = .bonus

SRC = pipex.c validation.c parents.c error_managment.c fork.c\
		get_next_line.c get_next_line_utils.c

SRC_BONUS = pipex_bonus.c validation_bonus.c parents_bonus.c error_managment_bonus.c fork_bonus.c\
		get_next_line_bonus.c get_next_line_utils_bonus.c

LIBFT_NAME = libft.a

LIBFTDIR = ./libft/

LIBFT = $(addprefix ${LIBFTDIR}, ${LIBFT_NAME})

SOURCES = $(addprefix src/, ${SRC})

SOURCES_BONUS = $(addprefix src_bonus/, ${SRC_BONUS})

.PHONY:	clean all bonus fclean re

all:	${NAME}

${LIBFT}:
	${MAKE} -C ${LIBFTDIR}

${NAME}:	${LIBFT} ${SOURCES} ${HEADERS}
	cc -Wall -Wextra -Werror -L ${LIBFTDIR} -lft ${SOURCES} -o $@

bonus:	${BONUS}

${BONUS}:	${LIBFT} ${SOURCES_BONUS} ${HEADERS_BONUS}
	cc -Wall -Wextra -Werror -L ${LIBFTDIR} -lft ${SOURCES_BONUS} -o pipex
	@touch $@

clean:
	${MAKE} clean -C ${LIBFTDIR}
	@${RM} ${BONUS}

fclean:		clean
	${RM} ${NAME}
	${MAKE} fclean -C ${LIBFTDIR}

re:	fclean all
