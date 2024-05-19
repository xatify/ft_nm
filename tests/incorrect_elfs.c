/*
    this file is used to generate incomplete object files
    for testing the behavior of nm command.
*/

#include <stdio.h>
#include <unistd.h>
#include <elf.h>
#include <string.h>

/**
 * @brief hold the name and the generator of the object
 * file
 * 
 */
typedef struct s_object_file {
    const char *name;
    int (*generator)(const char *);

} t_objectf;


/**
 * @brief create a file with name name
 * and erase the content
 * 
 * @param name name of the file
 * 
 * @return FILE pointer
 */
static FILE *create_file(const char *name) {
    FILE *fp;

    fp = fopen(name, "wb");
    return fp;
}

/**
 * @brief generate empty object file
 * 
 * @param name name of the file
 */
static int gen_empty(const char *name) {
    FILE *fp;

    fp = create_file(name);
    if (!fp)
        return 0;
    // no data
    fclose(fp);
    return 1;
}


/**
 * @brief filling elf ident array with good data
 * 
 * @param ident 
 */
static void elf_ident(unsigned char *ident) {
    memset(ident, 0, EI_NIDENT);
    
    ident[EI_MAG0] = 0x7f;
    ident[EI_MAG1] = 'E';
    ident[EI_MAG2] = 'L';
    ident[EI_MAG3] = 'F';

    ident[EI_CLASS] = ELFCLASS32;
    ident[EI_DATA] = ELFDATA2LSB;
    ident[EI_VERSION] = EV_CURRENT;
}



/**
 * @brief generate object file with wrong ident
 * 
 * @param name name of the file
 * @return int 
 */
static int gen_wrong_ident(const char *name) {
    FILE *fp = NULL;
    Elf32_Ehdr hdr;
    ssize_t s;

    fp = create_file(name);
    if (!fp)
        return 0;

    elf_ident(&(hdr.e_ident[0]));
    // corupted byte
    hdr.e_ident[EI_MAG2] = 'J';
    s = fwrite(&hdr, sizeof(Elf32_Ehdr), 1, fp);
    if (s != 1) {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;
}


/**
 * @brief generating object file
 * with only correct e_ident in header
 * 
 */
static int gen_no_symbols(const char *name) {
    FILE *fp = NULL;
    Elf32_Ehdr hdr;
    ssize_t s;

    fp = create_file(name);
    if (!fp) {
        return 0;
    }

    elf_ident(&(hdr.e_ident[0]));
    s = fwrite(&hdr, sizeof(Elf32_Ehdr), 1, fp);
    if (s != 1) {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;
}


/**
 * @brief array of genrating incomplete 
 * object file type
 * 
 */
static const t_objectf files[] = {
    {
        // empty file
        .name = "./incorrect/empty_file.o",
        .generator = gen_empty,
    },
    {
        // object with wrong identification
        .name = "./incorrect/wrong_ident.o",
        .generator = gen_wrong_ident,
    },
    {
        .name = "./incorrect/no_symbols.o",
        .generator = gen_no_symbols
    },

};




int main(int argc, char *argv[]) {
    int ret;

    int (*gen)(const char *);

    for (int i = 0; i < sizeof(files)/ sizeof(t_objectf); i++) {
        gen = *(files[i].generator);
        int ret = gen(files[i].name);
        if (!ret) {
            printf("unable to generate ofile: %s", files[i].name);
            return 1;
        }
    }
    return 0;
}