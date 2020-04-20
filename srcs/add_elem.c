/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 21:54:30 by lubenard          #+#    #+#             */
/*   Updated: 2020/04/20 18:15:24 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** When adding element is on, this validate the entry and add it
** to the end of the linked list
*/

int		confirm_new_elem(t_select *select)
{
	t_node *node;

	if (!ft_strisascii(select->add_elem))
		return (error("argument is not ascii", ERR_ARG_NOT_ASCII));
	if (!(node = new_node(select->list->last, select->add_elem,
	select->list->last->index + 1, 1)))
		return (error("error during malloc on node", ERR_MALLOC));
	if (!select->list->last)
		select->list->head = node;
	select->list->last = node;
	select->list->size++;
	select->flag_add_elem = 0;
	handle_resize(0);
	ft_bzero(select->add_elem, ft_strlen(select->add_elem));
	return (0);
}

/*
** Activate or desactivate adding mode
*/

void	add_elem(t_select *select)
{
	select->flag_add_elem = (select->flag_add_elem) ? 0 : 1;
	print_list(select);
}
