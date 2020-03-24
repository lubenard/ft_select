/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:47:35 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/24 19:14:45 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_select.h"

#include <curses.h>
#include <term.h>

int init_structs(t_select **select)
{
	if (!(*select = malloc(sizeof(t_select))))
		return (error("error during malloc", ERR_MALLOC));
	if (!((*select)->term = malloc(sizeof(t_term))))
	{
		ft_memdel((void **)select);
		return (error("error during malloc", ERR_MALLOC));
	}
	if (!((*select)->list = malloc(sizeof(t_list_hand))))
	{
		ft_memdel((void **)&(*select)->term);
		ft_memdel((void **)select);
		return (error("error during malloc on t_list struct", ERR_MALLOC));
	}
	return (0);
}

void read_input(t_select *select)
{
	ssize_t	ret_read;
	char	buffkey[3];

	while (1)
	{
		ft_bzero(buffkey, 3);
		ret_read = read(0, buffkey, 3);
		if (buffkey[0] == 27 && !buffkey[1] && !buffkey[2])
			ft_exit(select);
		else
			manage_keys(select, buffkey);
	}
}

size_t compute_biggest_lenght(t_node *head)
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

int ft_putchar_input(int c)
{
	write(0, &c, 1);
	return (0);
}

void print_list(t_select *select)
{
	t_node *tmp;
	size_t i;

	tputs (select->term->clear, 1, ft_putchar_input);
	tmp = select->list->head;
	i = 0;
	while (tmp)
	{
		ft_dprintf(0,"%s%s%s%s%s%-*s",tmp->color,
		(tmp->is_select) ? FT_FILLED : "",
		(select->list->cursor == tmp) ? FT_UNDER : "",
		tmp->value,FT_EOC,select->list->biggest_len -
		ft_strlen(tmp->value) + 1, "");
		i++;
		if (i == select->list->nbr_elem)
		{
			write(0, "\n\n", 2);
			i = 0;
		}
		tmp = tmp->next;
	}
	write(0, "\n", 1);
}

int main(int argc, char **argv)
{
	int			ret_code;
	t_select	*select;

	ret_code = 0;
	if (!isatty(0))
		return (error("input/output error, are fds open ?", ERR_TTY));
	else if (argc == 1)
		return (error("Usage: ./ft_select args1 args2 args3...", ERR_USAGE));
	if ((ret_code = init_structs(&select)))
		return (ret_code);
	if ((ret_code = init_termcaps(select->term)))
		return (ret_code);
	if ((ret_code = parsing(select->list, argv)))
		return (ret_code);
	select->list->biggest_len = compute_biggest_lenght(select->list->head);
	if (!(select->list->nbr_elem = (select->term->col /
	select->list->biggest_len)))
		return (1);
	//handle_signals();
	print_list(select);
	read_input(select);
	return (0);
}
