/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 17:32:49 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/30 13:53:32 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Delete the current research
*/

int		delete_research(t_select *select)
{
	if (select->flag_add_elem)
		ft_bzero(select->add_elem, ft_strlen(select->add_elem));
	else
		ft_bzero(select->research, ft_strlen(select->research));
	print_list(select);
	return (0);
}

/*
** Delete the last character of the research field
*/

void	delete_char_research(t_select *select)
{
	if (select->flag_add_elem)
		select->add_elem[ft_strlen(select->add_elem) - 1] = '\0';
	else
		select->research[ft_strlen(select->research) - 1] = '\0';
	print_list(select);
}

void	set_cursor_on_next(t_select *select, t_node *tmp)
{
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

int		research(t_select *select, char buffkey)
{
	char *research_tmp;

	if (select->flag_add_elem)
	{
		research_tmp = ft_strdup(select->add_elem);
		ft_strdel(&select->add_elem);
		select->add_elem = ft_stradd(research_tmp, buffkey);
		ft_strdel(&research_tmp);
		print_list(select);
	}
	else
	{
		research_tmp = ft_strdup(select->research);
		ft_strdel(&select->research);
		select->research = ft_stradd(research_tmp, buffkey);
		ft_strdel(&research_tmp);
		set_cursor_on_next(select, select->list->head);
	}
	print_list(select);
	return (0);
}
