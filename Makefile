# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 22:23:11 by abelosev          #+#    #+#              #
#    Updated: 2025/11/13 15:02:22 by dinza-cr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SE_FILES 	= src/exec/exec.c \
				src/exec/builtin.c \
				src/exec/builtin2.c \
				src/exec/heredoc.c \
				src/exec/execve.c \
				src/exec/redir.c \
				src/exec/free_exec.c 

SP_FILES	= src/pars/cmd_check_outils.c \
				src/pars/cmd_check.c \
				src/pars/envp_get_list.c \
				src/pars/envp_get_tab.c \
				src/pars/expand_tokenizer.c \
				src/pars/expand.c \
				src/pars/ft_split1.c \
				src/pars/get_files_outils.c \
				src/pars/get_files.c \
				src/pars/group_list.c \
				src/pars/group_outils.c \
				src/pars/outils_envp.c \
				src/pars/outils_expand.c \
				src/pars/outils_free.c \
				src/pars/outils_free_struct.c \
				src/pars/outils_print.c \
				src/pars/outils_print_group.c \
				src/pars/parser_outils.c \
				src/pars/parser.c \
				src/pars/quotes_expand.c \
				src/pars/quotes_ok.c \
				src/pars/quotes_outils.c \
				src/pars/quotes_remove.c \
				src/pars/quotes_spaces.c \
				src/pars/syntax_pb.c \
				src/pars/token_list.c

SB_FILES = src/builtins/ft_cd.c \
			src/builtins/ft_echo.c \
			src/builtins/ft_env.c \
			src/builtins/ft_exit.c \
			src/builtins/ft_export.c \
			src/builtins/ft_pwd.c \
			src/builtins/ft_unset.c \

SU_FILES = src/utils/main_outils.c \
			src/utils/main.c \
			src/utils/signals.c \
			src/utils/exec_outils.c \
			src/utils/signals_hd.c

SRC		= $(SE_FILES) $(SP_FILES) $(SB_FILES) $(SU_FILES)
	
O_DIR	= obj
OBJ		= $(SRC:%.c=$(O_DIR)/%.o)
DEP		= $(OBJ:.o=.d)

LIBFT		= libft/libft.a
LIBFT_DIR	= ./libft

# Compilation & cleaning
CC		= cc
CF		= -Wall -Wextra -Werror -g3 -I/opt/homebrew/opt/readline/include -MMD -MP
INC		= -Iinc -I$(LIBFT_DIR)
LDFLAGS	= -L $(LIBFT_DIR) -lft -lreadline -L/opt/homebrew/opt/readline/lib
RM		= rm -rf

all:	$(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(O_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(RM) $(O_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	@$(RM) $(NAME)

re: fclean all

-include $(DEP)

valgrind: all
	@valgrind --suppressions=$(PWD)/ignore_readline --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
		./minishell

.PHONY: all clean fclean re
