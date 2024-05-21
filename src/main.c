/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:59:34 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 14:56:19 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#include "../libs/ft/libft.h"
#include "ft_nm.h"

int open_file(t_object_file* file, char *name) {
    int fd;
    fd = open(name, O_RDONLY);
    if (fd < 0) {
        print_error(name, "No such file");
        return -1;
    }
    file->fd = fd;
    file->name = name;
    return 0;
}



int ft_nm(t_object_file *file) {
    int ret = map(file);

    // printf("maping %d\n", ret);
    if (ret == 0) {
        ret = load_elf_header(file);
        if (ret)
            return 1;

    }
    else {
        return 1;
    }
    return 0;
}

void init_file(t_object_file *file) {
    file->fd = -1;
    file->name = NULL;
    file->size = -1;
    file->content = NULL;
    file->sym_num = 0;
    file->symbols = NULL;
}

void reset_file(t_object_file *file) {
    close(file->fd);
    if (file->content) {
        munmap(file->content, file->size);
    }
    if (file->symbols) {
        free(file->symbols);
    }
    init_file(file);
}

int main(int argc, char *argv[]) {
    t_object_file file;
    int ret;
    int error;
    int i;

    
    init_file(&file);

    error = 0;

    if (argc <= 2) {
        if (!argv[1])
            ret = open_file(&file, "a.out");
        else
            ret = open_file(&file, argv[1]);
        if (ret == -1) {
            exit (1);
        }
        ret = ft_nm(&file);
        if (ret) {
            error = 1;
        }
        
    }
    else {
        i = 1;
        while (i < argc) {
            reset_file(&file);
            ret = open_file(&file, argv[i]);
            if (ret == -1) {
                exit(1);
            }
            output("\n");
            output(argv[i]);
            output(":");
            output("\n");
            ret = ft_nm(&file);
            if (ret) {
                error = 1;
            }
            i++;
        }
    }
    reset_file(&file);
    if (error) {
        return 1;
    }
    return (0);
}


