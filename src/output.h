/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:24:07 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 23:36:01 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "symbol.h"

# define SYMVAL32WIDTH 8
# define SYMVAL64WIDTH 16

void	print_error(const char *str, const char *reason);
void	print_symbol_64(t_symbol *sym);
void	print_symbol_32(t_symbol *sym);
int		to_print_value(t_symbol *sym);
void	hexa_rep(size_t n, int size, char c, char *buf);
void	print_file_name(const char *fname);

#endif