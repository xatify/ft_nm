/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:59:34 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 22:42:52 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	run_single(t_object_file *file, char *arg)
{
	int	ret;

	if (!arg)
		ret = open_file(file, "a.out");
	else
		ret = open_file(file, arg);
	if (ret == -1)
		exit(1);
	return (ft_nm(file));
}

int	main(int argc, char *argv[])
{
	t_object_file	file;
	int				error;
	int				i;

	init_file(&file);
	error = 0;
	if (argc <= 2)
		return (run_single(&file, argv[1]));
	i = 0;
	while (++i < argc)
	{
		reset_file(&file);
		if (open_file(&file, argv[i]) == -1)
		{
			error = 1;
			continue ;
		}
		print_file_name(argv[i]);
		if (ft_nm(&file))
			error = 1;
	}
	reset_file(&file);
	return (error);
}
