/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2005 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.0 of the PHP license,       |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_0.txt.                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ffmpeg/config.h>
#include <avformat.h>
#include <avcodec.h>
#include <allformats.h>

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_flvinfo.h"

/* If you declare any globals in php_flvinfo.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(flvinfo)
*/

/* True global resources - no need for thread safety here */
static int le_flvinfo;

/* {{{ arginfo */
/* {{{ get_flv_dimensions */
static
ZEND_BEGIN_ARG_INFO(arginfo_get_flv_dimensions, 0)
    ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()
/* }}} */
/* }}} */


/* {{{ flvinfo_functions[]
 *
 * Every user visible function must have an entry in flvinfo_functions[].
 */
function_entry flvinfo_functions[] = {
    PHP_FE(get_flv_dimensions,	arginfo_get_flv_dimensions)
	{NULL, NULL, NULL}	/* Must be the last line in flvinfo_functions[] */
};
/* }}} */

/* {{{ flvinfo_module_entry
 */
zend_module_entry flvinfo_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"flvinfo",
    flvinfo_functions,		/* function list */
	PHP_MINIT(flvinfo),
	PHP_MSHUTDOWN(flvinfo),
	PHP_RINIT(flvinfo),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(flvinfo),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(flvinfo),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_FLVINFO
ZEND_GET_MODULE(flvinfo)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("flvinfo.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_flvinfo_globals, flvinfo_globals)
    STD_PHP_INI_ENTRY("flvinfo.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_flvinfo_globals, flvinfo_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_flvinfo_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_flvinfo_init_globals(zend_flvinfo_globals *flvinfo_globals)
{
	flvinfo_globals->global_value = 0;
	flvinfo_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(flvinfo)
{
	/* If you have INI entries, uncomment these lines 
	ZEND_INIT_MODULE_GLOBALS(flvinfo, php_flvinfo_init_globals, NULL);
	REGISTER_INI_ENTRIES();
	*/

#define	REGISTER_ONLY_FLV 1

#ifdef REGISTER_ONLY_FLV
    avcodec_init();

    // Register flv decoder
	// from libavcodec/allcodecs.c
#define REGISTER_ENCODER(X,x) \
	if (ENABLE_##X##_ENCODER)  register_avcodec(&x##_encoder)
#define REGISTER_DECODER(X,x) \
	if (ENABLE_##X##_DECODER)  register_avcodec(&x##_decoder)
#define REGISTER_ENCDEC(X,x)  REGISTER_ENCODER(X,x); REGISTER_DECODER(X,x)

	REGISTER_ENCDEC(FLV, flv);
	REGISTER_DECODER(VP3, vp3);
	REGISTER_DECODER(VP5, vp5);
	REGISTER_DECODER(VP6, vp6);
	REGISTER_DECODER(VP6F, vp6f);

	// from libavformat/allformats.c
#define REGISTER_MUXER(X,x) \
	if (ENABLE_##X##_MUXER)   av_register_output_format(&x##_muxer)
#define REGISTER_DEMUXER(X,x) \
	if (ENABLE_##X##_DEMUXER) av_register_input_format(&x##_demuxer)
#define REGISTER_MUXDEMUX(X,x)  REGISTER_MUXER(X,x); REGISTER_DEMUXER(X,x)
	REGISTER_MUXDEMUX(FLV, flv);

    /* file protocols */
    register_protocol(&file_protocol);
#else
    // Register all formats and codecs
    av_register_all();
#endif

#if CONFIG_VP3_DECODER
	REGISTER_LONG_CONSTANT("FLV_CODEC_VP3", 1, CONST_CS | CONST_PERSISTENT);
#endif
#if CONFIG_VP5_DECODER
	REGISTER_LONG_CONSTANT("FLV_CODEC_VP5", 1, CONST_CS | CONST_PERSISTENT);
#endif
#if CONFIG_VP6_DECODER
	REGISTER_LONG_CONSTANT("FLV_CODEC_VP6", 1, CONST_CS | CONST_PERSISTENT);
#endif
#if CONFIG_VP6F_DECODER
	REGISTER_LONG_CONSTANT("FLV_CODEC_VP6F", 1, CONST_CS | CONST_PERSISTENT);
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(flvinfo)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(flvinfo)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(flvinfo)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(flvinfo)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "flvinfo support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto array get_flv_dimensions(string filename)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(get_flv_dimensions)
{
	char *arg;
	int arg_len;
	int width = 0;
	int height = 0;
	AVFormatContext *pFormatCtx;
	AVCodecContext *enc;
	int i;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

    // Open video file
    if (av_open_input_file(&pFormatCtx, arg, NULL, 0, NULL) != 0) {
		zend_error(E_NOTICE, "av_open_input_file: Couldn't open file %s", arg);
        return;
	}

    // Retrieve stream information
    if (av_find_stream_info(pFormatCtx) < 0) {
		zend_error(E_NOTICE, "av_find_stream_info: Couldn't find stream information");
        return;
	}

    // Dump information about file onto standard error
    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        AVStream *st = pFormatCtx->streams[i];
		enc = st->codec;

		// skip non flv files
		switch (enc->codec_id) {
		case CODEC_ID_FLV1:
#if CONFIG_VP3_DECODER
		case CODEC_ID_VP3:
#endif
#if CONFIG_VP5_DECODER
		case CODEC_ID_VP5:
#endif
#if CONFIG_VP6_DECODER
		case CODEC_ID_VP6:
#endif
#if CONFIG_VP6F_DECODER
		case CODEC_ID_VP6F:
#endif
			break;
		default:
#if DEBUG
			AVCodec *p = avcodec_find_decoder(enc->codec_id);
			if (p) {
				zend_error(E_NOTICE, "flvinfo: skip non-flv codec: #%d: ", enc->codec_id, p->name);
			} else {
				zend_error(E_NOTICE, "flvinfo: skip unknown codec: #%d", enc->codec_id);
			}
#endif
			continue;
		}

		// we're not interested of audio stream
		if (enc->codec_type == CODEC_TYPE_VIDEO) {
			if (enc->width) {
				width = enc->width;
			}
			if (enc->height) {
				height = enc->height;
			}
		}
    }

    // Close the video file
    av_close_input_file(pFormatCtx);

	if (!width && !height) {
		zend_error(E_NOTICE, "flvinfo: flv was not detected");
		RETURN_FALSE;
	}

	if (array_init(return_value) == FAILURE) {
		RETURN_FALSE;
	}

	add_next_index_long(return_value, width);
	add_next_index_long(return_value, height);
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
