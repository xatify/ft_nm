#include "ft_nm.h"

static int run(t_object_file *file) {

	if (file->size <= EI_NIDENT)
		return (-1);

	if (check_header(file->content) != VALID)
	{
		print_error(file->name, "file format not recognized");
		return (1);
	}
	if (get_class(file->content) == ELFCLASS32)
	{
		if (check_32_format(file->content, file->size) == VALID)
			iterate_over_32_symtab((Elf32_Ehdr *)file->content, file);
		else {
			print_error(file->name, "file format not recognized");
			return (1);
		}
	}
	else if (get_class(file->content) == ELFCLASS64)
	{
		if (check_64_format(file->content, file->size) == VALID)
			iterate_over_64_symtab((Elf64_Ehdr *)file->content, file);
		else {
			print_error(file->name, "file format not recognized");
			return (1);
		}
	}

	ft_qsort(
		file->symbols, file->sym_num, sizeof(t_symbol), cmpsym
	);

	for (int i = 0; i < file->sym_num; i++) {
		if (get_class(file->content) == ELFCLASS32)
			print_symbol_32(file->symbols + i);
		else if (get_class(file->content) == ELFCLASS64)
			print_symbol_64(file->symbols + i);
	}

	return 0;
}

int ft_nm(t_object_file *file) {
	if (map(file) == 0 && run(file) == 0) {
		return 0;
	}
	return 1;	
}




