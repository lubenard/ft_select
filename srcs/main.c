/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:47:35 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/20 10:14:53 by lubenard         ###   ########.fr       */
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
	if (!((*select)->list = malloc(sizeof(t_list))))
	{
		ft_memdel((void **)&(*select)->term);
		ft_memdel((void **)select);
		return (error("error during malloc on t_list struct", ERR_MALLOC));
	}
	return (0);
}

int read_input(t_select *select)
{
	ssize_t	ret_read;
	char	buffkey[3];

	while (1)
	{
		ft_bzero(buffkey, 3);
		ret_read = read(0, buffkey, 3);
		if (buffkey[0] == 27 && !buffkey[1] && !buffkey[2])
			return (ft_exit(select));
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

void print_list(t_select *select)
{
	t_node *tmp;
	size_t nbr_elem;
	size_t i;
	size_t biggest_len;

	char *cl_cap = tgetstr("cl", NULL);
	tputs (cl_cap, 5, ft_putchar);
	tmp = select->list->head;
	biggest_len = compute_biggest_lenght(tmp);
	if (!(nbr_elem = (select->term->col / biggest_len)+ 1))
		return ;
	ft_printf("nbr_elem = %zu\n", nbr_elem);
	i = 0;
	while (tmp)
	{
		ft_printf("%s%s%s%s%s%-*s",tmp->color,
		(tmp->is_select) ? FT_FILLED : "",
		(select->list->cursor == tmp) ? FT_UNDER : "",
		tmp->value,FT_EOC,biggest_len - ft_strlen(tmp->value) + 1, "");
		i++;
		if (i == nbr_elem)
		{
			write(1, "\n", 1);
			i = 0;
		}
		tmp = tmp->next;
	}
	write(1, "\n", 1);
}

int main(int argc, char **argv)
{
	int			ret_code;
	t_select	*select;

	ret_code = 0;
	if (!isatty(0) || !isatty(1))
		return (error("input/output error, are fds open ?", ERR_TTY));
	else if (argc == 1)
		return (error("Usage: ./ft_select args1 args2 args3...", ERR_USAGE));
	if ((ret_code = init_structs(&select)))
		return (ret_code);
	if ((ret_code = init_termcaps(select->term)))
		return (ret_code);
	if ((ret_code = parsing(select->list, argv)))
		return (ret_code);
	print_list(select);
	read_input(select);
	return (0);
}
