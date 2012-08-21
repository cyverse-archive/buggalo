#!/bin/sh

# Determine the name of the tarball.
SPEC=$1
BASE=$(grep Name $SPEC | cut -d ' ' -f 2)
VERSION=$(grep Version $SPEC | cut -d ' ' -f 2)
NAME=$BASE-$VERSION
BUILD=build/$NAME

# Put all of the source files in the build directory.
mkdir -p $BUILD
cp -pr $(ls | grep -v build | grep -v '\.tar\.gz') $BUILD
tar czpvf $NAME.tar.gz -C build $NAME
