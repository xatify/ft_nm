/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:09:48 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 18:37:34 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x64.h"

void	*get_64section_by_name(const Elf64_Ehdr *hdr, const char *name)
{
	Elf64_Shdr	*sheader;

	sheader = get64_sheader_by_name(hdr, name);
	if (sheader)
	{
		return ((char *)hdr + sheader->sh_offset);
	}
	return (NULL);
}
