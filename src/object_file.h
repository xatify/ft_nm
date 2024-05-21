/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:39:03 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 23:08:37 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_FILE_H
# define OBJECT_FILE_H

# include <stddef.h>

typedef struct s_symbol	t_symbol;
typedef struct s_object_file
{
	int			fd;
	char		*name;
	int			size;
	void		*content;
	int			sym_num;
	t_symbol	*symbols;
}	t_object_file;

int		map(t_object_file *file);
int		open_file(t_object_file *file, char *name);
void	init_file(t_object_file *file);
void	reset_file(t_object_file *file);

#endif