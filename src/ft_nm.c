/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:00:17 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 22:15:05 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_printer	get_printer(int class)
{
	static t_printer	printers[] = {
		NULL,
		print_symbol_32,
		print_symbol_64,
	};

	return (printers[class]);
}

static t_iterator	get_iterator(int class)
{
	static t_iterator	iterators[] = {
		NULL,
		iterator_32,
		iterator_64,
	};

	return (iterators[class]);
}

static t_checker	get_checker(int class)
{
	static t_checker	checkers[] = {
		NULL,
		check_32_format,
		check_64_format,
	};

	return (checkers[class]);
}

static int	run(t_object_file *file)
{
	int	class;
	int	i;

	if (file->size <= EI_NIDENT)
		return (-1);
	if (check_header(file->content) == VALID)
	{
		class = get_class(file->content);
		if ((*get_checker(class))(file->content, file->size) == VALID)
		{
			(*get_iterator(class))(file);
			ft_qsort(file->symbols, file->sym_num, sizeof(t_symbol), cmpsym);
			i = 0;
			while (i < file->sym_num)
			{
				(*get_printer(class))(file->symbols + i);
				i++;
			}
			return (0);
		}
	}
	print_error(file->name, "file format not recognized");
	return (1);
}

int	ft_nm(t_object_file *file)
{
	if (map(file) == 0 && run(file) == 0)
		return (0);
	return (1);
}
