/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:24:07 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 17:30:25 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

void print_error(const char *str, const char *reason);
void print_symbol_64(t_symbol *sym);
void print_symbol_32(t_symbol *sym);
int to_print_value(t_symbol *sym);
void hexa_rep(size_t n, int size, char c, char *buf);


#endif