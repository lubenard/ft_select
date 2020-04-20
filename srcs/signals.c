/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 18:34:21 by lubenard          #+#    #+#             */
/*   Updated: 2020/04/14 19:13:38 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_select.h"
#include <term.h>
#include <sys/ioctl.h>

extern t_select *g_select;

/*
** Handle CTRL-Z (jobcontrol)
**
** What is it doing ?
** Restauring old termcaps + make the cursor visible again
*/

static void	handle_sigtstp(int sig)
{
	(void)sig;
	tputs(g_select->term->civis, 1, ft_putchar_input);
	if (tcsetattr(0, TCSANOW, &g_select->term->old_terms))
		return ;
	tputs(g_select->term->civis, 1, ft_putchar_input);
	ioctl(STDIN_FILENO, TIOCSTI, "\x1A");
	signal(SIGTSTP, SIG_DFL);
}

/*
** Handle fg (background tack bring to foreground)
**
** What is it doing ?
** Remodify termcaps + make the cursor invisible again
*/

static void	handle_sigcont(int signal)
{
	(void)signal;
	init_termcaps(g_select->term);
	print_list(g_select);
}

/*
** Handle CTRL-C
*/

static void	handle_sigint(int signal)
{
	(void)signal;
	ft_exit(g_select);
}

/*
** Handle Terminal resize
*/

void		handle_resize(int signal)
{
	struct winsize w;

	(void)signal;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	g_select->term->col = w.ws_col;
	g_select->term->line = w.ws_row;
	if (g_select->list->biggest_len <= 0)
		return ;
	if (!(g_select->list->nbr_elem = (g_select->term->col /
	g_select->list->biggest_len)) || (int)(g_select->list->size /
	g_select->list->nbr_elem) >= g_select->term->line)
	{
		tputs(g_select->term->clear, 1, ft_putchar_input);
		error("term size too small", ERR_TERM_SIZE);
		return ;
	}
	print_list(g_select);
}

/*
** Define all signals and attributewhat to do
*/

void		handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGCONT, handle_sigcont);
	signal(SIGTSTP, handle_sigtstp);
	signal(SIGSEGV, handle_sigint);
	signal(SIGPIPE, handle_sigint);
	signal(SIGTERM, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	signal(SIGABRT, handle_sigint);
	signal(SIGWINCH, handle_resize);
}
