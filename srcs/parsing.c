/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:07:14 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/23 17:01:27 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Create new node to connect to linked list
*/

t_node *new_node(t_node *last, char *arg)
{
	t_node *node;

	if (!(node = malloc(sizeof(t_node))))
		return (0);
	node->value = arg;
	node->len = ft_strlen(arg);
	check_file_exist(node);
	node->is_select = 0;
	node->next = NULL;
	if (last)
	{
		node->prev = last;
		last->next = node;
	}
	else
		node->prev = NULL;
	return (node);
}

int parsing(t_list_hand *list, char **argv)
{
	int			i;
	t_node		*node;

	i = 1;
	list->last = NULL;
	while (argv[i])
	{
		if (!ft_strisascii(argv[i]))
			return (error("argument is not ascii", ERR_ARG_NOT_ASCII));
		if (!(node = new_node(list->last, argv[i++])))
			return (error("error during malloc on node", ERR_MALLOC)); 
		if (i - 1 == 1)
			list->head = node;
		list->last = node;
	}
	list->cursor = list->head;
	list->size = i;
	return (0);
}
