# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trubat-d <trubat-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/27 02:15:22 by trubat-d          #+#    #+#              #
#    Updated: 2022/10/27 18:07:05 by trubat-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ECHO = @echo
PRINT = @printf
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
INVERT = \033[7m
RESETTXT = \033[0m
BOLD = \033[1m

SRC_PATH = src/
SRC = ft_calloc.c pipex.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strjoin.c ft_strlen.c \
		ft_strncmp.c ft_substr.c heredoc.c fork_processing.c close_handler.c init_handler.c
SRCS = $(addprefix $(SRC_PATH),$(SRC))

OBJ_PATH = obj/
OBJ = $(SRC:%.c=%.o)
OBJS = $(addprefix $(OBJ_PATH),$(OBJ))

NAME = pipex
AR = ar rcs
CC		= gcc
RM		= rm -f

INCLUDES = -I includes/

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		$(ECHO) "$(YELLOW)\nCompilation de pipex$(RESETTXT)"
		@ gcc $(CFLAGS) $(INCLUDES) $(OBJS) -o $@
		$(ECHO) "$(GREEN)$(BOLD)Compilation Terminée !!!$(RESETTXT)"

%.o:$(SRC_PATH)%.c
		$(PRINT) "$(YELLOW).$(RESETTXT)"
		@mkdir -p $(OBJ_PATH)
		@$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $(OBJ_PATH)$@

bonus: $(NAME)

clean:
		$(ECHO) "$(RED)Suppression des objets...$(RESETTXT)"
		@$(RM) $(OBJS)
		$(ECHO) "$(RED)$(BOLD)Suppression des objets terminé !$(RESETTXT)"

fclean:	clean
		$(ECHO) "$(RED)Suppression de pipex...$(RESETTXT)"
		@$(RM) $(NAME)
		$(ECHO) "$(RED)$(BOLD)Suppression de pipex terminé !$(RESETTXT)"

re:		fclean all

.PHONY: all clean fclean re