/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:17:00 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 14:29:13 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_qsort.h"

static void	sort_subarrays(void *v, int size, int *indices, t_comparator comp);

static void	define_subarrays(int *indices, int *start_end)
{
	int	tmp;

	tmp = indices[LAST];
	indices[0] = start_end[LEFT];
	indices[1] = tmp - 1;
	indices[2] = tmp + 1;
	indices[3] = start_end[RIGHT];
}

static void	_qsort(void *v, int size, int *start_end, t_comparator comp)
{
	void	*vs[4];
	int		indices[4];

	indices[MID] = (start_end[LEFT] + start_end[RIGHT]) / 2;
	if (start_end[LEFT] >= start_end[RIGHT])
		return ;
	vs[VL] = (char *)(v + (start_end[LEFT] * size));
	vs[VR] = (char *)(v + (indices[MID] * size));
	ft_memswap(vs[VL], vs[VR], size);
	indices[LAST] = start_end[LEFT];
	indices[IDX] = start_end[LEFT];
	while (++indices[IDX] <= start_end[RIGHT])
	{
		vs[VT] = (char *)(v + (indices[IDX] * size));
		if ((*comp)(vs[VL], vs[VT]) > 0)
		{
			indices[LAST] += 1;
			vs[V3] = (char *)(v + ((indices[LAST]) * size));
			ft_memswap(vs[VT], vs[V3], size);
		}
	}
	vs[V3] = (char *)(v + (indices[LAST] * size));
	ft_memswap(vs[VL], vs[V3], size);
	define_subarrays(indices, start_end);
	sort_subarrays(v, size, indices, comp);
}

void	sort_subarrays(void *v, int size, int *indices, t_comparator comp)
{
	_qsort(v, size, indices, comp);
	_qsort(v, size, indices + 2, comp);
}

void	ft_qsort(void *base, int nmemb, int size, t_comparator comp)
{
	int	start_end[2];

	start_end[LEFT] = 0;
	start_end[RIGHT] = nmemb -1;
	_qsort(base, size, start_end, comp);
}
