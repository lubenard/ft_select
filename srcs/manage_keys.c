/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 22:48:46 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/17 23:26:00 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	ft_exit(t_select *select)
{
	ft_printf("Exiting ft_select...\n");
	if (tcsetattr(0, TCSANOW, &select->term->old_terms))
		return (error("Cannot restaure old terms !", ERR_TCSETATTR));
	free_list(select->list->head);
	ft_memdel((void *)&select->list);
	ft_memdel((void *)&select->term);
	ft_memdel((void *)&select);
	return (0);
}

int manage_keys(t_select *select, char buffkey[3])
{
	(void)select;
	ft_printf("buffkey = %d\n", buffkey[0]);
	return (0);
}
