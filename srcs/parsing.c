/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:07:14 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/14 12:09:35 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int new_node(char *arg)
{
	t_node *node;

	if (!ft_isascii(arg))
		return (error("argument is not ascii", ERR_ARG_NOT_ASCII));
	if (!(node = malloc(sizeof(t_node))))
		return (error("error during malloc on linked list node", ERR_MALLOC));
	return (0);
}

int parsing(int argc char **argv)
{
	int		i;

	if (!(ft_2dstrnew(argc)))
		return (error("malloc failed, exiting...", ERR_MALLOC);
	i = 0;
	while (i < argc)
	{
		new_node(argv);
		i++;
	}
	return (0);
}
