/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:29:41 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 19:11:04 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x86.h"

void	*get_section_by_name(Elf32_Ehdr *hdr, const char *name)
{
	Elf32_Shdr	*sheader;

	sheader = get_sheader_by_name(hdr, name);
	if (sheader)
	{
		return ((char *)hdr + sheader->sh_offset);
	}
	return (NULL);
}
