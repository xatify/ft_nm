/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:30:31 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 23:35:05 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_nm.h"

int	to_print_value(t_symbol *sym)
{
	if (sym->type == 'U' || sym->type == 'u' || sym->type == 'w')
		return (0);
	return (1);
}

void	print_symbol_32(t_symbol *sym)
{
	char	buf[SYMVAL32WIDTH + 1];
	char	c;

	if (to_print_value(sym))
		c = '0';
	else
		c = ' ';
	hexa_rep(sym->value, 8, c, buf);
	output(buf);
	output(" ");
	soutput(&(sym->type), 1);
	output(" ");
	output(sym->name);
	output("\n");
}

void	print_symbol_64(t_symbol *sym)
{
	char	buf[SYMVAL64WIDTH + 1];
	char	c;

	if (to_print_value(sym))
		c = '0';
	else
		c = ' ';
	hexa_rep(sym->value, 16, c, buf);
	output(buf);
	output(" ");
	soutput(&(sym->type), 1);
	output(" ");
	output(sym->name);
	output("\n");
}

void	print_error(const char *str, const char *reason)
{
	error("nm: ");
	error(str);
	error(": ");
	error(reason);
	error("\n");
}

void	print_file_name(const char *fname)
{
	output("\n");
	output(fname);
	output(":\n");
}
