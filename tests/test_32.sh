#!/bin/bash

shopt -s globstar

TEMPDIR=$(pwd)/tests/o


ARCH=""
ODIR=""
C32=""
set_env() {
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
}

generate_elfs() {

    rm -rf $ODIR
    mkdir -p $ODIR

    ls -d -1 "$PWD/"**/* | grep -E '\.c' > .cfiles
    while read p; do
        name=$(basename -- $p)
        name="${name%.*}"
        gcc -c $C32 $p -o $ODIR/$name.o
    done <.cfiles

    rm -rf .cfiles
}


test_single_arg() {
    echo ============== Single Arg Test ==============
    for o in "$ODIR"/*; do
        echo "============== Testing $o ============="
        if [ -f "$o" ]; then
            diff <(./$NMPATH $o) <(nm $o)
        fi
    done
}

test_multiple_args() {
    echo "=============== Multiple ARGs test=========="
    diff <(./$NMPATH $ODIR/*) <(nm $ODIR/*)
}

test_no_args() {

    echo "=============== No ARGS test ==============="
    # rm -f "$ODIR/a.out"
    rm -f a.out
    diff <(./$NMPATH) <(nm)
    echo '
#include <stdio.h>
const char *p = "testing";
int main (int argc, char **argv) {
    printf("%s\n", p);
    return 0;
}
    ' > .tmp.c

    gcc $C32 .tmp.c -o a.out

    diff <(./$NMPATH) <(nm)
    rm -f a.out .tmp.c
}

# test_incorrect_object

test_incorrect_elfs() {
    
    echo "========= Testing incorrect elfs ============"
    # compile the gen_incorrect_elfs.c

    cd ./tests
    mkdir incorrect
    gcc incorrect_elfs.c
    ./a.out

    for o in incorrect/*; do
        ../$NMPATH $o 2> err1
        ret1=$?
        nm $o 2> err2
        ret2=$?

        diff err1 err2
        if [ "$ret1" != "$ret2" ]; then
            echo error on $o file
        fi
    done

    rm -rf incorrect
    rm -rf a.out
    rm -rf err*
    cd - > /dev/null
}

NMPATH="./src/ft_nm"

if [ ! -f $NMPATH ]; then
    >&2 echo "command not found";
    return 1
fi



set_env $1
generate_elfs $1
test_single_arg
test_multiple_args 

test_no_args

test_incorrect_elfs



