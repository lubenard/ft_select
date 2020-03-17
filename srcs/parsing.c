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

t_node *new_node(t_node *last, char *arg)
{
	t_node *node;

	if (!(node = malloc(sizeof(t_node))))
		return (0);
	node->value = arg;
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
	if (!(list = malloc(sizeof(t_list))))
		return (error("error during malloc on t_list struct", ERR_MALLOC));
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
	list->size = i;
	ft_printf("------DEBUG MODE-------\n");
	ft_printf("Linked list data:\n");
	ft_printf("	Head: %p\n", list->head);
	ft_printf("	Head data: %s\n", list->head->value);
	ft_printf("	list size: %zu\n", list->size);
	while (list->head)
	{
		ft_printf("	node data: %p value %s is_selected %d next %p prev %p\n", list->head, list->head->value, list->head->is_select, list->head->next, list->head->prev);
		list->head = list->head->next;
	}
	//free_structs(list); not free due to debug
	return (0);
}
