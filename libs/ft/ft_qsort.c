/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:17:00 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 01:30:47 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_qsort.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>




static void	_swap(void *vl, void *vr, int size)
{
	char	*pl;
	char	*pr;
	char	c;

	pl = (char *)vl;
	pr = (char *)vr;
	while (size--)
	{
		c = *pl;
		*pl = *pr;
		*pr = c;
		pl++;
		pr++;
	}
}

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
	_swap(vs[VL], vs[VR], size);
	indices[LAST] = start_end[LEFT];
	indices[IDX] = start_end[LEFT] + 1;
	while (indices[IDX] <= start_end[RIGHT])
	{
		vs[VT] = (char *)(v + (indices[IDX] * size));
		if ((*comp)(vs[VL], vs[VT]) > 0)
		{
			indices[LAST] += 1;
			vs[V3] = (char *)(v + ((indices[LAST]) * size));
			_swap(vs[VT], vs[V3], size);
		}
		indices[IDX] += 1;
	}
	vs[V3] = (char *)(v + (indices[LAST] * size));
	_swap(vs[VL], vs[V3], size);
	define_subarrays(indices, start_end);
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


int cmp(const void *s1, const void *s2) {

	return (strcmp(*(char **)s1, *(char **)s2));	
}


int cmp_int(const void *n1, const void *n2) {
	return *((int *)n1) - *((int *)n2);
}


int main(int argc, char *argv[]) {

	int p[] = {
		// "hello",
		// "abcd",
		// "echo",
		// "hello1",
		// "there",
		// "is",
		// "nothing"
		545,66666666,354,335,31,353,1387
	};

	ft_qsort(p, sizeof(p)/sizeof(p[0]), sizeof(p[0]), cmp_int);

	for (int i =0; i < sizeof(p) / sizeof(p[0]); i++) {
		printf("%d\n",p[i]);
	}

	return 0;
}

