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

#ifndef PHP_FLVINFO_H
#define PHP_FLVINFO_H

extern zend_module_entry flvinfo_module_entry;
#define phpext_flvinfo_ptr &flvinfo_module_entry

#ifdef PHP_WIN32
#define PHP_FLVINFO_API __declspec(dllexport)
#else
#define PHP_FLVINFO_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(flvinfo);
PHP_MSHUTDOWN_FUNCTION(flvinfo);
PHP_RINIT_FUNCTION(flvinfo);
PHP_RSHUTDOWN_FUNCTION(flvinfo);
PHP_MINFO_FUNCTION(flvinfo);

PHP_FUNCTION(confirm_flvinfo_compiled);	/* For testing, remove later. */
PHP_FUNCTION(flvinfo_file);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(flvinfo)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(flvinfo)
*/

/* In every utility function you add that needs to use variables 
   in php_flvinfo_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as FLVINFO_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define FLVINFO_G(v) TSRMG(flvinfo_globals_id, zend_flvinfo_globals *, v)
#else
#define FLVINFO_G(v) (flvinfo_globals.v)
#endif

#endif	/* PHP_FLVINFO_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
