/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:19:03 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/24 18:21:21 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void move_right(t_select *select)
{
	select->list->cursor = (select->list->cursor->next) ?
		select->list->cursor->next : select->list->head;
	print_list(select);
}

void move_left(t_select *select)
{
	select->list->cursor = (select->list->cursor->prev) ?
		select->list->cursor->prev : select->list->last;
	print_list(select);
}

void move_up(t_select *select)
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

void move_down(t_select *select)
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