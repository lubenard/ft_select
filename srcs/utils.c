/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:06:02 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/23 14:35:46 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int return_choice(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->is_select)
		{
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, " ", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void free_list(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		ft_memdel((void *)&tmp);
	}
}

int error(char *err_mess, int err_code)
{
	ft_dprintf(2, "Error: %s\n", err_mess);
	return (err_code);
}
