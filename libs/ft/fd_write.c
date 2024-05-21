/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:59:56 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/20 22:01:53 by abbouzid         ###   ########.fr       */
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
