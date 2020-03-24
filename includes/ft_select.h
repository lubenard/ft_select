/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:47:14 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/24 19:07:01 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <termios.h>

/*
** Error codes handling
*/

enum {ERR_USAGE, ERR_TTY, ERR_TERM, ERR_MALLOC, ERR_ARG_NOT_ASCII,
	ERR_TCGETATTR, ERR_TCSETATTR};

/*
** Color Macro
*/

# define FT_BLACK		"\033[30m"
# define FT_RED			"\033[31m"
# define FT_GREEN		"\033[32m"
# define FT_YELLOW		"\033[33m"
# define FT_BLUE		"\033[34m"
# define FT_PURPLE		"\033[35m"
# define FT_CYAN		"\033[36m"
# define FT_WHITE		"\033[37m"
# define FT_EOC			"\033[0m"
# define FT_BOLD		"\033[1m"
# define FT_ITALIC		"\033[3m"
# define FT_UNDER		"\033[4m"
# define FT_FILLED		"\033[7m"

# define UP				183
# define DOWN			184
# define LEFT			186
# define RIGHT			185

/*
** Termcaps structure
*/

typedef struct	s_term
{
	int		col;
	int		line;
	char	*clear;
	struct termios terms;
	struct termios old_terms;
}				t_term;

/*
** linked list elements
*/

typedef struct	s_node
{
	char			*value;
	int				is_select;
	size_t			len;
	size_t			index;
	char			color[7];
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct	s_list_hand
{
	t_node	*head;
	t_node	*last;
	t_node	*cursor;
	size_t	size;
	size_t	biggest_len;
	size_t	nbr_elem;
}				t_list_hand;

/*
** Main structure
*/

typedef struct	s_select
{
	t_list_hand	*list;
	t_term		*term;
}				t_select;

/*
** Prototypes
*/

/*
** Move keys functions
*/
void move_right(t_select *select);
void move_left(t_select *select);
void move_up(t_select *select);
void move_down(t_select *select);

/*
** Handle signal
*/

int handle_signals(void);

int init_termcaps(t_term *term);
int error(char *err_mess, int err_code);
int parsing(t_list_hand* list, char **argv);
void free_list(t_node *head);
int ft_exit(t_select *select);
int manage_keys(t_select *select, char buffkey[3]);
void print_list(t_select *select);
void check_file_exist(t_node *node);
int return_choice(t_node *head);

int ft_putchar_input(int c);
#endif
