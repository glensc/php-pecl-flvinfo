dnl $Id$
dnl config.m4 for extension avformat

PHP_ARG_WITH(avformat, for avformat support,
[  --with-avformat@<:@=DIR@:>@   Include avformat support (requires ffmpeg)])

if test "$PHP_AVFORMAT" != "no"; then

  for i in $PHP_AVFORMAT /usr/local /usr; do
    if test -f $i/include/ffmpeg/avformat.h; then
      AVFORMAT_DIR=$i
      AVFORMAT_INCDIR=$i/include/ffmpeg
    elif test -f $i/include/avformat.h; then
      AVFORMAT_DIR=$i
      AVFORMAT_INCDIR=$i/include
    fi
  done

  if test -z "$AVFORMAT_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the ffmpeg distribution])
  fi

  PHP_CHECK_LIBRARY(avformat, av_find_stream_info,
  [
    PHP_ADD_LIBRARY_WITH_PATH(avformat, $AVFORMAT_DIR/lib, AVFORMAT_SHARED_LIBADD)
    PHP_ADD_INCLUDE($AVFORMAT_INCDIR)
    AC_DEFINE(HAVE_AVFORMATLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong avformat lib version or lib not found])
  ],[
    -L$AVFORMAT_DIR/lib -lavformat
  ])

  PHP_SUBST(AVFORMAT_SHARED_LIBADD)
  PHP_NEW_EXTENSION(avformat, avformat.c, $ext_shared)
fi
