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

  dnl Check for FLV codecs availability
	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS -I$FFMPEG_INCDIR"
	for codec in VP3 VP5 VP6 VP6F; do
	    AC_MSG_CHECKING(for CODEC_ID_$codec availability)
			AC_TRY_COMPILE([
				#include <avcodec.h>
			], [
				int main(void) {
					enum CodecID codec = CODEC_ID_$codec;
					return 0;
				}
			], [
				dnl i'd use here:
				dnl AC_DEFINE_UNQUOTED(HAVE_CODEC_$codec, 1, [Whether the ffmpeg has CODEC_ID_$codec])
				dnl but autoheader won't catch those defines. sigh
				case "$codec" in
				VP3)
					AC_DEFINE(HAVE_CODEC_VP3, 1, [Whether the ffmpeg has CODEC_ID_VP3])
					;;
				VP5)
					AC_DEFINE(HAVE_CODEC_VP5, 1, [Whether the ffmpeg has CODEC_ID_VP5])
					;;
				VP6)
					AC_DEFINE(HAVE_CODEC_VP6, 1, [Whether the ffmpeg has CODEC_ID_VP6])
					;;
				VP6F)
					AC_DEFINE(HAVE_CODEC_VP6F, 1, [Whether the ffmpeg has CODEC_ID_VP6F])
					;;
				esac
				AC_MSG_RESULT([yes])
			], [
				AC_MSG_RESULT([no])
			])
	done
  CPPFLAGS=$old_CPPFLAGS

  PHP_SUBST(FLVINFO_SHARED_LIBADD)
  PHP_NEW_EXTENSION(flvinfo, php_flvinfo.c, $ext_shared)
  PHP_ADD_MAKEFILE_FRAGMENT
fi

# vim:ts=2:sw=2:noet
