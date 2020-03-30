/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:07:14 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/30 13:47:16 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	switch_elem(t_node *first, t_node *next)
{
	if (next->prev)
		next->prev->next = next->next;
	if (next->next)
		next->next->prev = next->prev;
	if (first->prev)
		first->prev->next = next;
	next->next = first;
	next->prev = first->prev;
	first->prev = next;
}

void		sort_ascii(t_list_hand *list)
{
	t_node	*first;
	t_node	*tmp;
	t_node	*next;

	first = list->head;
	tmp = list->head;
	while (tmp->next)
	{
		next = tmp->next;
		if (ft_strcmp(tmp->value, next->value) > 0)
		{
			while (first->next && ft_strcmp(first->value, next->value) < 0)
				first = first->next;
			switch_elem(first, next);
			tmp = tmp->prev;
			first = list->head;
		}
		tmp = tmp->next;
	}
	list->last = tmp;
	while (tmp->prev)
		tmp = tmp->prev;
	list->head = tmp;
}

/*
** Create new node to connect to linked list
*/

t_node		*new_node(t_node *last, char *arg, size_t index)
{
	t_node *node;

	if (!(node = malloc(sizeof(t_node))))
		return (0);
	node->value = arg;
	node->index = index;
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

int			parsing(t_list_hand *list, char **argv)
{
	int			i;
	t_node		*node;
	size_t		sort;

	i = 1;
	sort = 0;
	list->last = NULL;
	while (argv[i])
	{
		if (!ft_strisascii(argv[i]))
			return (error("argument is not ascii", ERR_ARG_NOT_ASCII));
		if (!ft_strcmp(argv[i], "--sort"))
		{
			sort++;
			i++;
		}
		if (!(node = new_node(list->last, argv[i], i)))
			return (error("error during malloc on node", ERR_MALLOC));
		if (!list->last)
			list->head = node;
		list->last = node;
		i++;
	}
	(sort) ? sort_ascii(list) : 0;
	list->cursor = list->head;
	list->size = (sort) ? i - 1 : i;
	return (0);
}
