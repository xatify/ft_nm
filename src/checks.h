/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:01:35 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 20:13:05 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKS_H
# define CHECKS_H

typedef enum s_check
{
	VALID = 0,
	NOIDENT = 1 << 0x0,
	NOCLASS = 1 << 0x1,
	NOENCOD = 1 << 0x2,
	NOVERS = 1 << 0x3,
	NOVALID = 1 << 0x4,
}	t_check;

int	check_header(const void *content);
int	get_class(const void *content);
int	check_32_format(const void *content, int size);
int	check_64_format(const void *content, int size);

#endif