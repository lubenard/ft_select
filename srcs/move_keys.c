/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:19:03 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/30 13:58:40 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	move_right(t_select *select)
{
	t_node *tmp;

	if (!ft_strcmp(select->research, ""))
		select->list->cursor = (select->list->cursor->next) ?
		select->list->cursor->next : select->list->head;
	else
	{
		tmp = (select->list->cursor->next) ?
		select->list->cursor->next : select->list->head;
		set_cursor_on(select, tmp, NEXT);
	}
	print_list(select);
}

void	move_left(t_select *select)
{
	t_node *tmp;

	if (!ft_strcmp(select->research, ""))
		select->list->cursor = (select->list->cursor->prev) ?
		select->list->cursor->prev : select->list->last;
	else
	{
		tmp = (select->list->cursor->prev) ?
		select->list->cursor->prev : select->list->last;
		set_cursor_on(select, tmp, PREV);
	}
	print_list(select);
}

void	move_up(t_select *select)
{
	size_t i;

	i = 0;
	while (i != select->list->nbr_elem)
	{
		select->list->cursor = (select->list->cursor->prev) ?
		select->list->cursor->prev : select->list->last;
		i++;
	}
	print_list(select);
}

void	move_down(t_select *select)
{
	size_t i;

	i = 0;
	while (i != select->list->nbr_elem)
	{
		select->list->cursor = (select->list->cursor->next) ?
		select->list->cursor->next : select->list->head;
		i++;
	}
	print_list(select);
}
