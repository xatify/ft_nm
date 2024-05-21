/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:50:13 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 23:10:01 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMBOL_H
# define SYMBOL_H

# include "object_file.h"
# include <stddef.h>

typedef struct s_object_file	t_object_file;
typedef struct s_symbol
{
	size_t	value;
	char	type;
	char	*name;
}	t_symbol;

int			cmpsym(const void *sym1, const void *sym2);
t_symbol	*get_next_empty_symbol(t_object_file *file);
void		init_symbol_array(t_object_file *file, size_t size);

#endif