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

int error(char *err_mess, int err_code)
{
	ft_dprintf(2, "Error: %s\n", err_mess);
	return (err_code);
}
