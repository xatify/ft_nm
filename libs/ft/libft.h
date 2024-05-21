/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:41:22 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 15:05:43 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

typedef int(*	t_comparator)(const void	*v1, const void	*v2);

size_t	ft_strlen(const char *str);
char	ft_strdup(const char *str);
void	fd_write(const char	*str, int fd);
void	fd_swrite(const char *str, int fd, size_t size);
void	output(const char *str);
void	error(const char *str);
void	soutput(const char *str, size_t size);
void	*ft_memcpy(void *lhs, const void *rhs, size_t size);
void	*ft_memset(void *v, int c, size_t n);
void	*ft_bzero(void *s, size_t size);
int		ft_memcmp(const void *lhs, const void *rhs, size_t size);
void	ft_qsort(void *base, int nmemb, int size, t_comparator comp);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strequal(const char *s1, const char *s2);
int		ft_stralnumcmp(const char *s1, const char *s2);
void	ft_memswap(void *v1, void *v2, int size);

#endif
