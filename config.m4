dnl $Id$
dnl config.m4 for extension flvinfo

PHP_ARG_WITH(flvinfo, for flvinfo support,
[  --with-flvinfo@<:@=DIR@:>@    Include flvinfo support (requires ffmpeg)])

if test "$PHP_FLVINFO" != "no"; then

  for i in $PHP_FLVINFO /usr/local /usr; do
    if test -f $i/include/ffmpeg/avformat.h; then
      FFMPEG_DIR=$i
      FFMPEG_INCDIR=$i/include/ffmpeg
    elif test -f $i/include/avformat.h; then
      FFMPEG_DIR=$i
      FFMPEG_INCDIR=$i/include
    fi
  done

  if test -z "$FFMPEG_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the ffmpeg distribution])
  fi

  PHP_CHECK_LIBRARY(avformat, av_find_stream_info,
  [
    PHP_ADD_LIBRARY_WITH_PATH(avformat, $FFMPEG_DIR/lib, FLVINFO_SHARED_LIBADD)
    PHP_ADD_INCLUDE($FFMPEG_INCDIR)
  ],[
    AC_MSG_ERROR([wrong avformat lib version or lib not found])
  ],[
    -L$FFMPEG_DIR/lib -lavformat
  ])

  PHP_SUBST(FLVINFO_SHARED_LIBADD)
  PHP_NEW_EXTENSION(flvinfo, php_flvinfo.c, $ext_shared)
fi
