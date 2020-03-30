/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 17:32:49 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/30 11:56:59 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Delete the current research
*/

int delete_research(t_select *select)
{
	ft_strdel(&select->research);
	if (!(select->research = ft_strdup("")))
		return (error("error during malloc on research", ERR_MALLOC));
	print_list(select);
	return (0);
}

/*
** Delete the last character of the research field
*/

void delete_char_research(t_select *select)
{
	select->research[ft_strlen(select->research) - 1] = '\0';
	print_list(select);
}

void set_cursor_on(t_select *select, t_node *tmp, size_t sens)
{
	while (tmp)
	{
		if (!ft_strncmp(select->research, tmp->value,
		ft_strlen(select->research)))
		{
			select->list->cursor = tmp;
			break ;
		}
		if (sens == NEXT)
			tmp = tmp->next;
		else if (sens == PREV)
			tmp = tmp->prev;
	}
}

int research(t_select *select, char buffkey)
{
	char *research_tmp;

	research_tmp = ft_strdup(select->research);
	ft_strdel(&select->research);
	select->research = ft_stradd(research_tmp, buffkey);
	ft_strdel(&research_tmp);
	set_cursor_on(select, select->list->head, NEXT);
	print_list(select);
	return (0);
}
