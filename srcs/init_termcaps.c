/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:46:36 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/13 16:25:29 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include "ft_select.h"

int init_termcaps(t_term *term)
{
	char	*term_type;
	int		ret;

	if ((term_type = getenv("TERM")))
		ret = tgetent(NULL, term_type);
	else
		ret = tgetent(NULL, "xterm-256color");
	if (ret == -1)
		return (error("Please check that TERM=xterm-256color", ERR_TERM));
	tcgetattr(0, &term->terms);
	term->terms.c_lflag &= ~(ICANON);
	if (tcsetattr(0, TCSANOW, &term->terms))
		return (0);
	term->col = tgetnum("co");
	term->line = tgetnum("li");
	return (0);
}
