/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:06:02 by lubenard          #+#    #+#             */
/*   Updated: 2020/04/13 22:13:26 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		return_choice(t_select *select)
{
	t_node	*tmp;

	tmp = select->list->head;
	while (tmp)
	{
		if (tmp->is_select)
		{
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, " ", 1);
		}
		tmp = tmp->next;
	}
	ft_exit(select);
	return (0);
}

void	free_list(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->alloc)
			ft_strdel(&tmp->value);
		ft_memdel((void *)&tmp);
	}
}

size_t	compute_biggest_lenght(t_node *head)
{
	size_t len;

	len = 0;
	while (head)
	{
		if (head->len > len)
			len = head->len;
		head = head->next;
	}
	return (len);
}

int		ft_putchar_input(int c)
{
	write(0, &c, 1);
	return (0);
}

int		error(char *err_mess, short err_code)
{
	ft_dprintf(2, "Error: %s\n", err_mess);
	return (err_code);
}
