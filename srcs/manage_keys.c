/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 22:48:46 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/18 22:29:00 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <term.h>
#include <curses.h>

int	ft_exit(t_select *select)
{
	ft_printf("Exiting ft_select...\n");
	if (tcsetattr(0, TCSANOW, &select->term->old_terms))
		return (error("Cannot restaure old terms !", ERR_TCSETATTR));
	char *ve = tgetstr("ve", NULL);
	tputs(ve, 1, ft_putchar);
	free_list(select->list->head);
	ft_memdel((void *)&select->list);
	ft_memdel((void *)&select->term);
	ft_memdel((void *)&select);
	return (0);
}

void	move_right(t_select *select)
{
	select->list->cursor = (select->list->cursor->next) ?
		select->list->cursor->next : select->list->head;
	print_list(select);
}

/*
** Manage keys codes:
**
** SUM | key[0] | key[1] | key[2] | key
** 183    27       91       65      key up
** 184    27       91       66      key down
** 186    27       91       68      key left
** 185    27       91       67      key right
** 32     32       0        0       key space
** 10     10       0        0       key enter
*/

int manage_keys(t_select *select, char key[3])
{
	size_t sum;
	//ft_printf("buffkey = %d\n", buffkey[0]);
	sum = key[0] + key[1] + key[2];
	if (sum == 183)
	{
		ft_printf("KEY UP\n");
	}
	else if (sum == 184)
	{
		ft_printf("KEY DOWN\n");
	}
	else if (sum == 186)
	{
		select->list->cursor = (select->list->cursor->prev) ?
			select->list->cursor->prev : select->list->last;
		print_list(select);
	}
	else if (sum == 185)
		move_right(select);
	if (sum == 32)
	{
		select->list->cursor->is_select = (!select->list->cursor->is_select) ?
			1 : 0;
		move_right(select);
	}
	if (sum == 10)
		ft_printf("KEY RETURN\n");
	return (0);
}
