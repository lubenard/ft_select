/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:47:14 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/14 12:06:51 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"

/*
** Error codes handling
*/

enum {ERR_USAGE, ERR_TTY, ERR_TERM, ERR_MALLOC, ERR_ARG_NOT_ASCII};

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
# define FT_STRIKE		"\033[9m"

/*
** Termcaps structure
*/


/*
** linked list elements
*/
typedef struct	s_node
{
	char			*value;
	int				is_select;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct	s_list
{
	t_node	*head;
	size_t	size;
}				t_list;

/*
** Prototypes
*/

int init_termcaps(void);
int error(char *err_mess, int err_code);

#endif
