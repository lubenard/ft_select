/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 18:34:21 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/24 19:08:35 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_select.h"

//extern t_select *select;

void handle_sigint(int signal)
{
	(void)signal;
	//ft_exit((t_select*)data);
}

int handle_signals(void)
{
	(void)select;
	signal(SIGINT, handle_sigint);
	return (0);
}
