#include "ft_nm.h"



















/**
 * @brief iterate over symbol table of 32 bit object file
 *  and populate the symbols array in file struct
 * 
 * @param hdr elf header
 * @param file 
 */
void iterate_over_32_symtab(Elf32_Ehdr *hdr, t_object_file *file) {
    Elf32_Shdr *sheader;
    Elf32_Sym *section;
    size_t idx;
    t_symbol *symbols;

    int i;

    
    section = NULL;
    sheader = get_sheader_by_name(hdr, ".symtab");
    section = (Elf32_Sym *)get_section_by_name(hdr, ".symtab");

    unsigned int size = (sheader->sh_size) / (sheader->sh_entsize);
    
    symbols = (t_symbol *)malloc(size * sizeof(t_symbol));
    i = 0;

    if (sheader && section) {
        idx = 0;
        while (idx < size) {
            if (idx != STN_UNDEF) {
                if (get_symbol(hdr, section, symbols) == 0) {
                    i++;
                    symbols++;
                }
            }
            idx++;
            section++;
        }
    }
    file->symbols = symbols - i;
    file->sym_num = i;
}
