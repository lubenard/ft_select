/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:06:02 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/14 11:06:06 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int free_structs(t_list_hand *linked_list)
{
	t_node	*tmp;

	while (linked_list->head)
	{
		tmp = linked_list->head;
		linked_list->head = linked_list->head->next;
		free(tmp);
	}
	free(linked_list);
	return (0);
}


int error(char *err_mess, int err_code)
{
	ft_dprintf(2, "Error: %s\n", err_mess);
	return (err_code);
}
