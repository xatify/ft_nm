/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ascii.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:18:16 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 13:51:00 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	to_lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 0x20);
	return (c);
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
