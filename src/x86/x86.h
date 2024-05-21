/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x86.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:16:38 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 15:44:21 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef X86_H
# define X86_H

#include ""

void iterate_over_32_symtab(Elf32_Ehdr *hdr, t_object_file *file);

void *get_section_by_name(Elf32_Ehdr *hdr, const char *name);



#endif