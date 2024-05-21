/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:53:29 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 23:38:11 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symbol.h"
#include "../libs/ft/libft.h"

#include <stdlib.h>

void	init_symbol_array(t_object_file *file, size_t size)
{
	file->symbols = (t_symbol *)malloc(size * sizeof(t_symbol));
	file->sym_num = 0;
}

int	cmpsym(const void *sym1, const void *sym2)
{
	int	diff;

	diff = ft_stralnumcmp(((t_symbol *)sym1)->name, ((t_symbol *)sym2)->name);
	if (!diff)
		return (ft_strcmp(((t_symbol *)sym1)->name, ((t_symbol *)sym2)->name));
	return (diff);
}

t_symbol	*get_next_empty_symbol(t_object_file *file)
{
	return (file->symbols + file->sym_num);
}
