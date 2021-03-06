/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 12:27:40 by lubenard          #+#    #+#             */
/*   Updated: 2020/04/14 18:12:34 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <sys/stat.h>
#include <sys/types.h>

/*
** Determine color following type of file
*/

static char	*determine_color(char *value)
{
	struct stat stat_struct;

	stat(value, &stat_struct);
	if (S_ISDIR(stat_struct.st_mode))
		return (FT_BLUE);
	else if (stat_struct.st_mode & S_IXUSR)
		return (FT_GREEN);
	else if (S_ISCHR(stat_struct.st_mode))
		return (FT_YELLOW);
	else if (S_ISLNK(stat_struct.st_mode))
		return (FT_PURPLE);
	else if (S_ISBLK(stat_struct.st_mode))
		return (FT_CYAN);
	else if (S_ISFIFO(stat_struct.st_mode))
		return (FT_RED);
	else
		return (FT_WHITE);
}

/*
** Determine if file exist, and if it is, choose color
*/

void		check_file_exist(t_node *node)
{
	if (!access(node->value, F_OK))
		ft_strcpy(node->color, determine_color(node->value));
	else if (!ft_strcmp(node->value, "blue_pill"))
		ft_strcpy(node->color, FT_BLUE);
	else if (!ft_strcmp(node->value, "red_pill"))
		ft_strcpy(node->color, FT_RED);
	else
		ft_strcpy(node->color, FT_CYAN);
}
