/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 22:48:46 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/26 16:06:06 by lubenard         ###   ########.fr       */
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

	ft_dprintf(0, "\nExiting ft_select...\n");
	if (tcsetattr(0, TCSANOW, &select->term->old_terms))
		exit(error("Cannot restaure old terms !", ERR_TCSETATTR));
	ve = tgetstr("ve", NULL);
	tputs(ve, 1, ft_putchar_input);
	free_list(select->list->head);
	ft_memdel((void *)&select->list);
	ft_memdel((void *)&select->term);
	ft_memdel((void *)&select);
	exit(0);
}

void delete_entry(t_select *select)
{
	t_node *tmp;

	tmp = select->list->cursor;
	if (!tmp->next && !tmp->prev)
		ft_exit(select);
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
	select->list->size--;
}

void move_key(t_select *select, int move)
{
	if (move == UP)
		move_up(select);
	else if (move == DOWN)
		move_down(select);
	else if (move == LEFT)
		move_left(select);
	else if (move == RIGHT)
		move_right(select);
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

void manage_keys(t_select *select, char key[3])
{
	size_t sum;

	sum = key[0] + key[1] + key[2];
	//ft_printf("%d %d %d, sum = %zu\n", key[0], key[1], key[2], sum);
	if (sum >= 183 && sum <= 186)
		move_key(select, sum);
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
}
