/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:35:21 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/20 23:41:08 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_QSORT_H
# define FT_QSORT_H

typedef int(*	t_comparator)(const void *, const void *);

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
