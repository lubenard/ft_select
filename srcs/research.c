/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 17:32:49 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/27 15:22:50 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void set_cursor_on_first(t_select *select)
{
	t_node	*tmp;

	tmp = select->list->head;
	while (tmp)
	{
		if (!ft_strncmp(select->research, tmp->value,
		ft_strlen(select->research)))
		{
			select->list->cursor = tmp;
			break ;
		}
		tmp = tmp->next;
	}
}

int research(t_select *select, char buffkey)
{
	select->research = ft_stradd(select->research, buffkey);
	set_cursor_on_first(select);
	print_list(select);
	return (0);
}
