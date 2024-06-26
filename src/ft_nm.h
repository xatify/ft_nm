/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:15:20 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 22:15:51 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "../libs/ft/libft.h"
# include "x64/x64.h"
# include "x86/x86.h"
# include "object_file.h"
# include "output.h"
# include "checks.h"

typedef void(*	t_printer) (t_symbol *);
typedef void(*	t_iterator) (t_object_file *);
typedef int(*	t_checker) (const void *, int);

int	ft_nm(t_object_file *file);

#endif