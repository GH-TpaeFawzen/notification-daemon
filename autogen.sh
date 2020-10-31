#!/bin/sh
#
# Run this to generate all the initial makefiles, etc.

srcdir=$(dirname "$0")
case "$srcdir" in ('') srcdir=.; esac

if [ ! -f $srcdir/configure.ac ]; then
  echo "**Error**: Directory "\'$srcdir\'" does not look like the top-level" \
       "project directory."
  exit 1
fi

PKG_NAME=$(autoconf --trace 'AC_INIT:$1' "$srcdir/configure.ac")

case "$# ${#NOCONFIGURE}" in (0 0)
  echo "**Warning**: I am going to run 'configure' with no arguments." >&2
  echo "If you wish to pass any to it, please specify them on the '$0'" \
       "command line." >&2
esac

set -x
aclocal --install || exit 1
autoreconf --verbose --force --install -Wno-portability || exit 1
{ set +x; } 2>/dev/null

case "$NOCONFIGURE" in ('')
  set -x
  $srcdir/configure "$@" || exit 1
  { set +x; } 2>/dev/null

  case "$1" in (--help)
    exit 0
  ;;(*)
    echo "Now type 'make' to compile $PKG_NAME." || exit 1
  ;;esac
;;(*)
  echo "Skipping configure process."
;;esac
