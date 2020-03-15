# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubenard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/12 18:13:02 by lubenard          #+#    #+#              #
#    Updated: 2020/03/14 11:06:56 by lubenard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g3

NAME		= ft_select
LIBFT		= libft
SRCSDIR		= srcs
INCDIR		= includes
OBJSDIR		= objs

FILES		= main.c \
			  init_termcaps.c \
			  utils.c

SRCS		= $(addprefix $(SRCSDIR)/, $(FILES))
OBJS		= $(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)
OBJSD		= $(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.d)

MAKEFLAGS += --silent

##### Colors #####

_END		= \x1b[0m
_BOLD		= \x1b[1m
_UNDER		= \x1b[4m
_REV		= \x1b[7m
_GREY		= \x1b[30m
_RED		= \x1b[31m
_GREEN		= \x1b[32m
_YELLOW		= \x1b[33m
_BLUE		= \x1b[34m
_PURPLE		= \x1b[35m
_CYAN		= \x1b[36m
_WHITE		= \x1b[37m

##### Debug #####

FSANITIZE	= false

##### Customized rule to compile for specific version #####

all: $(NAME)

ifeq ($(FSANITIZE), true)
 CFLAGS += -fsanitize=address
endif

$(NAME): $(OBJS)
	@$(MAKE) -q -C $(LIBFT) || $(MAKE) -j4 -C $(LIBFT)
	@echo -e -n "\n${_BLUE}${_BOLD}[Create Executable] $(NAME)${_END}"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(LIBFT) -lft -ltermcap
	@echo -e "\n${_GREEN}${_BOLD}$(NAME) done.${_END}"

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c Makefile
	@mkdir -p $(@D)
	@echo -n -e "\r\033[K${_PURPLE}${BOLD}[${NAME}] Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFT)/$(INCDIR) -MMD -o $@ -c $<

libft:
	@$(MAKE) -q -C $(LIBFT) || $(MAKE) -j4 -C $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./$(LIBFT)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@echo -e "${_RED}${_BOLD}Cleaning obj files from ${NAME}...${_END}"
	@rm -f $(OBJS)
	@rm -f $(OBJSD)
	@rm -Rf $(OBJDIR)

fclean: clean
	@echo -e "${_RED}${_BOLD}Cleaning project...${_END}"
	@rm -f $(NAME)
	@rm -f $(LIBFT)/libft.a
	@rm -rf $(OBJDIR)
	@rm -rf $(NAME).dSYM

re: fclean all

norm:
	@norminette $(INCDIR) $(SRCSDIR)
	@echo "Norm $(_GREEN)done!$(_END)"

check_error:
	@grep -rn "printf" **/*.[ch] | grep -v "ft_"
	@grep -rn "stdio.h" srcs/*.c

.PHONY: all clean fclean re norm $(LIBFT)

.SILENT:

-include $(OBJSD)
