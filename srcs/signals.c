/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 18:34:21 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/26 14:48:34 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_select.h"
#include <term.h>
#include <sys/ioctl.h>

extern t_select *ft_select;

/*
** Handle CTRL-Z (jobcontrol)
**
** What is it doing ?
** Restauring old termcaps + make the cursor visible again
*/

void handle_sigtstp(int sig)
{
	char *ve;

	(void)sig;
	if (tcsetattr(0, TCSANOW, &ft_select->term->old_terms))
		return ;
	ve = tgetstr("ve", NULL);
	tputs(ve, 1, ft_putchar_input);
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
	signal(SIGTSTP, SIG_DFL);
}

/*
** Handle fg (background tack bring to foreground)
**
** What is it doing ?
** Remodify termcaps + make the cursor invisible again
*/

void handle_sigcont(int signal)
{
	(void)signal;
	init_termcaps(ft_select->term);
	print_list(ft_select);
}

/*
** Handle CTRL-C
*/

void handle_sigint(int signal)
{
	(void)signal;
	ft_exit(ft_select);
}

/*
** Define all signals and attributewhat to do
*/

void handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGCONT, handle_sigcont);
	signal(SIGTSTP, handle_sigtstp);
	signal(SIGKILL, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	signal(SIGABRT, handle_sigint);
}