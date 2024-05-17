#!/bin/bash

# shopt -s globstar

# echo "====================================="
# echo "======Testing 32 elf objects ========" 
# TEMPDIR=$(pwd)/tests/objdir
# ODIR32=$TEMPDIR"/32"
# mkdir -p $ODIR32

# ls -d -1 "$PWD/"**/* | grep -E '\.c' > cfiles
# while read p; do
#     name=$(basename -- $p)
#     name="${name%.*}"
#     gcc -c -m32 $p -o $ODIR32"/"$name".o"
#     # echo $name
# done <cfiles
# rm -r cfiles

TEMPDIR=$(pwd)/tests/o

generate_elfs() {
    ARCH=$1
    ODIR=""
    C32=""
    case $ARCH in
        32)
            ODIR="$TEMPDIR/32"
            C32="-m32";;
        64)
            ODIR="$TEMPDIR/64";;
    esac


    rm -rf $ODIR
    mkdir -p $ODIR

    ls -d -1 "$PWD/"**/* | grep -E '\c' > .cfiles
    while read p; do
        name=$(basename -- $p)
        name="${name%.*}"
        gcc -c $C32 $p -o $ODIR/$name.o
    done <.cfiles

}

generate_elfs "32"
