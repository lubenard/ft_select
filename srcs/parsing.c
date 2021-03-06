/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:07:14 by lubenard          #+#    #+#             */
/*   Updated: 2020/04/14 18:14:49 by lubenard         ###   ########.fr       */
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

/*
** Perform ascii sort on options if --sort option is specified
*/

void		sort_ascii(t_list_hand *list)
{
	t_node	*first;
	t_node	*tmp;
	t_node	*next;

	first = list->head;
	tmp = list->head;
	if (!first)
		return ;
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

t_node		*new_node(t_node *last, char *arg, size_t index, short alloc)
{
	t_node *node;

	if (!(node = malloc(sizeof(t_node))))
		return (0);
	if (!alloc)
		node->value = arg;
	else
		node->value = ft_strdup(arg);
	node->alloc = alloc;
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

void		detect_sort_opt(char **argv, int *i, short *sort)
{
	if (!ft_strcmp(argv[*i], "--sort"))
	{
		(*sort)++;
		(*i)++;
	}
}

int			parsing(t_list_hand *list, char **argv)
{
	int			i;
	t_node		*node;
	short		sort;

	i = 1;
	sort = 0;
	list->last = NULL;
	while (argv[i])
	{
		if (!ft_strisascii(argv[i]))
			return (error("argument is not ascii", ERR_ARG_NOT_ASCII));
		detect_sort_opt(argv, &i, &sort);
		if (!argv[i])
			break ;
		if (!(node = new_node(list->last, argv[i], i, 0)))
			return (error("error during malloc on node", ERR_MALLOC));
		if (!list->last)
			list->head = node;
		list->last = node;
		i++;
	}
	(sort) ? sort_ascii(list) : 0;
	list->cursor = list->head;
	list->size = (sort) ? i - 1 : i;
	return ((!list->head) ? error("No argument given", ERR_TTY) : 0);
}
