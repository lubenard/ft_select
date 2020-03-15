/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:47:35 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/14 11:10:26 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_select.h"

int main(int argc, char **argv)
{
	int ret_code;

	ret_code = 0;
	if (!isatty(0) || !isatty(1))
		return (error("input/output error, are fds open ?", ERR_TTY));
	else if (argc == 1)
		return (error("Usage: ./ft_select args1 args2 args3...", ERR_USAGE));
	if ((ret_code = init_termcaps()))
		return (ret_code);
	if ((ret_code = parsing(argv)))
		return (ret_code);
	return (0);
}
