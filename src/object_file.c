/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:33:01 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/22 13:59:58 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../libs/ft/libft.h"
#include "object_file.h"
#include "output.h"

int	open_file(t_object_file *file, char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		print_error(name, "No such file");
		return (-1);
	}
	file->fd = fd;
	file->name = name;
	return (0);
}

void	init_file(t_object_file *file)
{
	file->fd = -1;
	file->name = NULL;
	file->size = -1;
	file->content = NULL;
	file->sym_num = 0;
	file->symbols = NULL;
}

void	reset_file(t_object_file *file)
{
	close(file->fd);
	if (file->content)
		munmap(file->content, file->size);
	if (file->symbols)
		free(file->symbols);
	init_file(file);
}

int	map(t_object_file *file)
{
	struct stat	filestat;

	if (fstat(file->fd, &filestat) == -1)
		return (-1);
	if (S_ISDIR(filestat.st_mode))
	{
		print_error(file->name, "is a directory");
		return (-1);
	}
	file->size = filestat.st_size;
	file->content = mmap(NULL, file->size, PROT_READ, MAP_PRIVATE, file->fd, 0);
	if (file->content == MAP_FAILED)
		return (-1);
	return (0);
}
