#!/bin/bash
set -e

[ -n "$TRAVIS_BUILD_DIR" ] || { echo "Script must be run within Travis CI environment" 1>&2; exit 1; }

# Test installation prefix
[ -n "$prefix" ] || prefix="/tmp/local"

# BASIS configuration
[ -n "$utilities" ] || utilities=yes
[ -n "$tools"     ] || tools=yes
[ -n "$example"   ] || example=no
[ -n "$doc"       ] || doc=no
[ -n "$manual"    ] || manual=no
[ -n "$tests"     ] || tests=no

# Update package managers
[[ $TRAVIS_OS_NAME != linux ]] || sudo apt-get update -qq
[[ $TRAVIS_OS_NAME != osx   ]] || brew update
[ -z "$(which pip)" ] || sudo -H pip install --upgrade pip

# Install Python 3
if [[ $python == 3 ]]; then
  if [[ $TRAVIS_OS_NAME == linux ]]; then
    sudo apt-get install -qq python3
  elif [[ $TRAVIS_OS_NAME == osx ]]; then
    brew install python3
  fi
fi

# Use dependencies built and installed from sources
export PATH="$prefix/bin:$PATH"
[[ $TRAVIS_OS_NAME != linux ]] || export   LD_LIBRARY_PATH="$prefix/lib:$LD_LIBRARY_PATH"
[[ $TRAVIS_OS_NAME != osx   ]] || export DYLD_LIBRARY_PATH="$prefix/lib:$DYLD_LIBRARY_PATH"

if [[ $doc == yes ]] || [[ $manual == yes ]]; then
  $TRAVIS_BUILD_DIR/test/travis/doxygen.sh "$doxygen" "$prefix"
  $TRAVIS_BUILD_DIR/test/travis/sphinx.sh  "$sphinx"  "$prefix" $manual
fi