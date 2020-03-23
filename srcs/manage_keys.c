/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 22:48:46 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/23 16:08:28 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <term.h>
#include <curses.h>

/*
** Exit when key esc is pressed
**
** First, restaure old termcaps
** Then, restaure cursor (ve variable)
** Finally, clear memory
*/

int	ft_exit(t_select *select)
{
	char *ve;

	ft_dprintf(0, "Exiting ft_select...\n");
	if (tcsetattr(0, TCSANOW, &select->term->old_terms))
		return (error("Cannot restaure old terms !", ERR_TCSETATTR));
	ve = tgetstr("ve", NULL);
	tputs(ve, 1, ft_putchar_input);
	free_list(select->list->head);
	ft_memdel((void *)&select->list);
	ft_memdel((void *)&select->term);
	ft_memdel((void *)&select);
	exit (0);
}

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

void delete_entry(t_select *select)
{
	t_node *tmp;

	tmp = select->list->cursor;
	if (!tmp->next && !tmp->prev)
	{
		ft_exit(select);
		exit(0);
	}
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next && !tmp->next->prev)
		select->list->head = select->list->cursor->next;
	if (tmp->prev && !tmp->prev->next)
		select->list->last = tmp->prev;
	move_right(select);
	free(tmp);
	//select->list->size--;
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
** 127    127      0        0       key del
** 126    126      0        0       key suppr
*/

int manage_keys(t_select *select, char key[3])
{
	size_t sum;
	//ft_printf("%d %d %d\n", key[0], key[1], key[2]);
	sum = key[0] + key[1] + key[2];
	//ft_printf("key = %zu\n", sum);
	if (sum == 183)
		ft_printf("KEY UP\n");
	else if (sum == 184)
		ft_printf("KEY DOWN\n");
	else if (sum == 186)
		move_left(select);
	else if (sum == 185)
		move_right(select);
	else if (sum == 32)
	{
		select->list->cursor->is_select = (!select->list->cursor->is_select) ?
			1 : 0;
		move_right(select);
	}
	else if (sum == 10)
	{
		return_choice(select->list->head);
		ft_exit(select);
	}
	else if (sum == 127 || sum == 126)
		delete_entry(select);
	return (0);
}
