/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 17:32:49 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/29 17:26:35 by lubenard         ###   ########.fr       */
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
	char *research_tmp;

	research_tmp = ft_strdup(select->research);
	ft_strdel(&select->research);
	select->research = ft_stradd(research_tmp, buffkey);
	ft_strdel(&research_tmp);
	set_cursor_on_first(select);
	print_list(select);
	return (0);
}
