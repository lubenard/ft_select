/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:46:36 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/27 15:32:06 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include "ft_select.h"

static void	get_data_termcaps(t_term *term)
{
	char *civis;

	term->col = tgetnum("co");
	term->line = tgetnum("li");
	term->clear = tgetstr("cl", NULL);
	ft_putstr_fd(tgetstr("ti", NULL), STDIN_FILENO);
	civis = tgetstr("vi", NULL);
	tputs(civis, 1, ft_putchar_input);
}

/*
** Init termcaps and get size of terminal
*/

int			init_termcaps(t_term *term)
{
	char	*term_type;
	int		ret;

	if ((term_type = getenv("TERM")))
		ret = tgetent(NULL, term_type);
	else
		ret = tgetent(NULL, "xterm-256color");
	if (ret == -1)
		return (error("Please check that TERM=xterm-256color", ERR_TERM));
	if (tcgetattr(0, &term->terms))
		return (error("cannot get attr !", ERR_TCGETATTR));
	term->old_terms = term->terms;
	term->terms.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(0, TCSANOW, &term->terms))
		return (error("cannot apply settings to terminal !", ERR_TCSETATTR));
	get_data_termcaps(term);
	return (0);
}
