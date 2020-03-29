/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 14:29:43 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/29 17:23:15 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <term.h>

static void print_elem(t_select *select, t_node *tmp, size_t *i)
{
	ft_dprintf(0,"%s%s%s%s%s%-*s",tmp->color,
	(tmp->is_select) ? FT_FILLED : "",
	(select->list->cursor == tmp) ? FT_UNDER : "",
	tmp->value,FT_EOC,select->list->biggest_len -
	ft_strlen(tmp->value) + 1, "");
	(*i)++;
	if (*i == select->list->nbr_elem)
	{
		write(0, "\n\n", 2);
		*i = 0;
	}
}

static int print_search(t_select *select)
{
	t_node	*tmp;
	size_t	i;

	tputs(select->term->clear, 1, ft_putchar_input);
	tmp = select->list->head;
	i = 0;
	while (tmp)
	{
		if (!ft_strncmp(select->research, tmp->value,
		ft_strlen(select->research)))
			print_elem(select, tmp, &i);
		tmp = tmp->next;
	}
	return (0);
}

void print_list(t_select *select)
{
	t_node *tmp;
	size_t i;

	tputs (select->term->clear, 1, ft_putchar_input);
	tmp = select->list->head;
	i = 0;
	if (select->research && !ft_strcmp(select->research, ""))
	{
		while (tmp)
		{
			print_elem(select, tmp, &i);
			tmp = tmp->next;
		}
	}
	else if (select->research)
		print_search(select);
}