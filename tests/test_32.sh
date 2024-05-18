#!/bin/bash

shopt -s globstar

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

    ls -d -1 "$PWD/"**/* | grep -E '\.c' > .cfiles
    while read p; do
        name=$(basename -- $p)
        name="${name%.*}"
        gcc -c $C32 $p -o $ODIR/$name.o
    done <.cfiles

    rm -rf .cfiles
}


test() {

    if [ ! -f $NMPATH ]; then
        >&2 echo "command not found";
        return 1
    fi
    
    generate_elfs $1

    for o in "$ODIR"/*; do
        echo "============== Testing $o ============="
        if [ -f "$o" ]; then
            diff <(./$NMPATH $o) <(nm $o)
        fi
    done
}


NMPATH="./src/nm"

test $1

