/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:59:56 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 15:08:54 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(const char *str);

void	fd_write(const char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	fd_swrite(const char *str, int fd, size_t len)
{
	write(fd, str, len);
}

void	output(const char *str)
{
	fd_write(str, STDOUT_FILENO);
}

void	error(const char *str)
{
	fd_write(str, STDERR_FILENO);
}

void	soutput(const char *str, size_t size)
{
	fd_swrite(str, STDOUT_FILENO, size);
}
