/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:35:21 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 14:31:11 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_QSORT_H
# define FT_QSORT_H

# include <stddef.h>

typedef int(*	t_comparator)(const void *, const void *);

void	ft_memswap(void *vl, void *vr, int size);

enum e_VS
{
	VT,
	V3,
	VL,
	VR,
};

enum e_INDICES
{
	IDX,
	LAST,
	MID,
};

enum e_START_END
{
	LEFT,
	RIGHT,
};

#endif
