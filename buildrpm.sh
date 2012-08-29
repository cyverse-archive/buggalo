#!/bin/bash

# Determine the name of the tarball.
SPEC=$1
BASE=$(grep Name $SPEC | cut -d ' ' -f 2)
VERSION=$(grep Version $SPEC | cut -d ' ' -f 2)
RELEASE=$(grep Release $SPEC | cut -d ' ' -f 2)
ARCH=$(grep BuildArchitectures $SPEC | cut -d ' ' -f 2)
ARCH=${ARCH:-$(rpm --eval %_target_cpu)}
NAME=$BASE-$VERSION
BUILD=build/$NAME
TARBALL=$NAME.tar.gz
RPM=$NAME-$RELEASE.$ARCH.rpm

# Build the tarball.
mkdir -p $BUILD
cp -pr $(ls | grep -v build | grep -v '\.tar\.gz') $BUILD
tar czpvf $TARBALL -C build $NAME

# Build the RPM.
RPMBASE=/usr/src/redhat
cp -p $SPEC $RPMBASE/SPECS/
cp -p $TARBALL $RPMBASE/SOURCES/
rpmbuild -ba $RPMBASE/SPECS/$SPEC

# Copy the RPM back to the current working directory.
cp $RPMBASE/RPMS/$ARCH/$RPM .
rm $RPMBASE/RPMS/$ARCH/$RPM

# Add the RPM to our YUM repository.
/home/tomcat/push.sh $(pwd)/$RPM
