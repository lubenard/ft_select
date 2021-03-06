/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:47:35 by lubenard          #+#    #+#             */
/*   Updated: 2020/04/14 18:13:48 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_select.h"

t_select *g_select;

/*
** init structs for launch
*/

static int	init_structs(void)
{
	if (!(g_select = malloc(sizeof(t_select))))
		return (error("error during malloc on main structure", ERR_MALLOC));
	ft_bzero(g_select, sizeof(t_select));
	if (!(g_select->term = malloc(sizeof(t_term))))
	{
		free_structs(g_select);
		return (error("error during malloc on term structure", ERR_MALLOC));
	}
	if (!(g_select->list = malloc(sizeof(t_list_hand))))
	{
		free_structs(g_select);
		return (error("error during malloc on t_list struct", ERR_MALLOC));
	}
	if (!(g_select->research = ft_strdup("")))
	{
		free_structs(g_select);
		return (error("error during malloc on research", ERR_MALLOC));
	}
	if (!(g_select->add_elem = ft_strdup("")))
	{
		free_structs(g_select);
		return (error("error during malloc on add_elem", ERR_MALLOC));
	}
	g_select->flag_add_elem = 0;
	return (0);
}

static void	read_input(t_select *select)
{
	short	ret_read;
	char	buffkey[3];

	while (1)
	{
		ft_bzero(buffkey, 3);
		ret_read = read(0, buffkey, 3);
		if (ft_isprint(buffkey[0]) && buffkey[0] != 32
		&& buffkey[0] != 126)
			research(select, buffkey[0]);
		else if (buffkey[0] == 27 && !buffkey[1] && !buffkey[2])
			ft_exit(select);
		else
			manage_keys(select, buffkey);
	}
}

int			main(int argc, char **argv)
{
	int			ret_code;

	ret_code = 0;
	if (!isatty(0))
		return (error("input/output error, are fds open ?", ERR_TTY));
	else if (argc == 1)
		return (error("Usage: ./ft_g_select args1 args2 args3...", ERR_USAGE));
	if ((ret_code = init_structs()))
		return (ret_code);
	if ((ret_code = parsing(g_select->list, argv)))
		return (ret_code);
	if ((ret_code = init_termcaps(g_select->term)))
		return (ret_code);
	g_select->list->biggest_len =
	compute_biggest_lenght(g_select->list->head);
	handle_resize(0);
	handle_signals();
	read_input(g_select);
	return (0);
}
