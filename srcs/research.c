/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 17:32:49 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/26 18:30:48 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <term.h>

int research(t_select *select, char buffkey)
{
	t_node	*tmp;
	size_t	hit;

	hit = 0;
	tputs (select->term->clear, 1, ft_putchar_input);
	tmp = select->list->head;
	select->research = ft_stradd(select->research, buffkey);
	while (tmp)
	{
		if (!ft_strncmp(select->research, tmp->value, ft_strlen(select->research)))
		{
			ft_dprintf(0,"%s%s%s%s%s%-*s",tmp->color,
				(tmp->is_select) ? FT_FILLED : "",
				(select->list->cursor == tmp) ? FT_UNDER : "",
				tmp->value,FT_EOC,select->list->biggest_len -
				ft_strlen(tmp->value) + 1, "");
			hit++;
		}
		tmp = tmp->next;
	}
	//if (!hit)
	//	print_list(select);
	return (0);
}
