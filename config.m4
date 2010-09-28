dnl $Id$
dnl config.m4 for extension flvinfo

PHP_ARG_WITH(flvinfo, for flvinfo support,
[  --with-flvinfo@<:@=DIR@:>@    Include flvinfo support (requires ffmpeg)])

if test "$PHP_FLVINFO" != "no"; then

  dnl Default directories to check for ffmpeg headers
  INC_CHECK_DIRS="/usr/local /usr"

  dnl User has specified using --with-flvinfo=[dir] a directory where we should
  dnl look for ffmpeg headers. Prepend this directory to the default dirs so it
  dnl gets checked first.
  if test "$PHP_FLVINFO" != "yes"; then
      INC_CHECK_DIRS="$PHP_FLVINFO $INC_CHECK_DIRS"
  fi

  AC_MSG_CHECKING(for ffmpeg headers)
  for i in $INC_CHECK_DIRS; do
    if test -f $i/include/ffmpeg/avcodec.h; then
      PHP_ADD_INCLUDE($i/include/ffmpeg)
      FFMPEG_INC_FOUND=$i/include/ffmpeg
      break
    elif test -f $i/include/avcodec.h; then
      PHP_ADD_INCLUDE($i/include)
      FFMPEG_INC_FOUND=$i/include
      break
    elif test -f $i/include/libavcodec/avcodec.h; then
      dnl ffmpeg svn revision 12194 and newer put each header in its own dir
      dnl so we have to include them all.
      PHP_ADD_INCLUDE($i/include/libavcodec/)
      PHP_ADD_INCLUDE($i/include/libavformat/)
      PHP_ADD_INCLUDE($i/include/libavutil/)
      PHP_ADD_INCLUDE($i/include/libswscale/)
      PHP_ADD_INCLUDE($i/include/libavfilter/)
      PHP_ADD_INCLUDE($i/include/libavdevice/)
      FFMPEG_INC_FOUND=$i/include/libavcodec
      break
    fi
  done

  if test -z "$FFMPEG_INC_FOUND"; then
     AC_MSG_RESULT()
     AC_MSG_ERROR([ffmpeg headers not found. Make sure ffmpeg is compiled as shared libraries using the --enable-shared option])
  else
     AC_MSG_RESULT(...found in $FFMPEG_INC_FOUND)
  fi

  AC_MSG_CHECKING(for ffmpeg libavformat.so)
  for i in $INC_CHECK_DIRS; do
    if test -f $i/lib/libavformat.so; then
      FFMPEG_LIBDIR=$i/lib
    fi
    dnl x86_64 support
    if test -f $i/lib64/libavformat.so; then
      FFMPEG_LIBDIR=$i/lib64
    fi
    dnl MacOS-X support
    if test -f $i/lib/libavformat.dylib; then
      FFMPEG_LIBDIR=$i/lib
    fi
  done

  PHP_ADD_LIBRARY_WITH_PATH(avformat, $FFMPEG_LIBDIR, FLVINFO_SHARED_LIBADD)

  if test -z "$FFMPEG_LIBDIR"; then
    AC_MSG_RESULT()
    AC_MSG_ERROR(ffmpeg shared libraries not found. Make sure ffmpeg is compiled as shared libraries using the --enable-shared option)
  else
    dnl For debugging
    AC_MSG_RESULT(...found in $FFMPEG_LIBDIR)
  fi

  PHP_SUBST(FLVINFO_SHARED_LIBADD)
  PHP_NEW_EXTENSION(flvinfo, php_flvinfo.c, $ext_shared)
  PHP_ADD_MAKEFILE_FRAGMENT
fi

# vim:ts=2:sw=2:noet
