#!/bin/bash

# ARCH SHOULD HAVE THE VALUES "32" or "64"
ARCH=64

URL_LIBS_TO_TEST=http://projects.caixamagica.pt/projects/cartaocidadao/repository/middleware-offline/builds/2012-05-09/caixamagica-16-32/pteid-pkg-web.tar.gz


URL_TEST_SUITE=http://projects.caixamagica.pt/projects/cartaocidadao/repository/middleware-offline/tools/test-suite/sdk-NewVersion/java/src
WORK_DIR=~/test_web_libs_pteid

mkdir -p $WORK_DIR
echo  $WORK_DIR
rm -rf $WORK_DIR/*
cd $WORK_DIR

## Export and extract Libs to be tested:
svn export $URL_LIBS_TO_TEST pkg_to_test.tar.gz
tar xzvf pkg_to_test.tar.gz

## Export native libs
svn export http://projects.caixamagica.pt/projects/cartaocidadao/repository/middleware-offline/builds/1_native-libs/linux-$ARCH
mv linux-$ARCH/* pteid-pkg/lib

## Export suite-tests to run tests on SDK:
svn export $URL_TEST_SUITE java-test
cd java-test

echo "Now to test your libs:"
echo "cd $WORK_DIR/java-test"
echo "make"


