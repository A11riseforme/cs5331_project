/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2021 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: e0175540@u.nus.edu                                           |
  +----------------------------------------------------------------------+
*/

/* naive_rasp extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_naive_rasp.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()  \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ void naive_rasp_test1()
 */
PHP_FUNCTION(naive_rasp_test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "naive_rasp");
}
/* }}} */

/* {{{ string naive_rasp_test2( [ string $var ] )
 */
PHP_FUNCTION(naive_rasp_test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
	Z_PARAM_OPTIONAL
	Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(naive_rasp)
{
	/* If you have INI entries, uncomment these lines
        REGISTER_INI_ENTRIES();
        */
	zend_set_user_opcode_handler(ZEND_DO_ICALL, php_do_icall_handler);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(naive_rasp)
{
#if defined(ZTS) && defined(COMPILE_DL_NAIVE_RASP)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(naive_rasp)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "naive_rasp support", "enabled");
	php_info_print_table_row(2, "Version", PHP_NAIVE_RASP_VERSION);
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_naive_rasp_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_naive_rasp_test2, 0)
ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ naive_rasp_functions[]
 */
static const zend_function_entry naive_rasp_functions[] = {
	PHP_FE(naive_rasp_test1, arginfo_naive_rasp_test1)
		PHP_FE(naive_rasp_test2, arginfo_naive_rasp_test2)
			PHP_FE_END};
/* }}} */

/* {{{ naive_rasp_module_entry
 */
zend_module_entry naive_rasp_module_entry = {
	STANDARD_MODULE_HEADER,
	"naive_rasp",			/* Extension name */
	naive_rasp_functions,	/* zend_function_entry */
	PHP_MINIT(naive_rasp),	/* PHP_MINIT - Module initialization */
	NULL,					/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(naive_rasp),	/* PHP_RINIT - Request initialization */
	NULL,					/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(naive_rasp),	/* PHP_MINFO - Module info */
	PHP_NAIVE_RASP_VERSION, /* Version */
	STANDARD_MODULE_PROPERTIES};
/* }}} */

#ifdef COMPILE_DL_NAIVE_RASP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(naive_rasp)
#endif

static int php_do_icall_handler(zend_execute_data *execute_data)
{
	const zend_op *opline = execute_data->opline;
	zend_execute_data *call = execute_data->call;
	zend_function *fbc = call->func;

	zend_string *fname = fbc->common.function_name;
	char *funcname = ZSTR_VAL(fname);
	//php_printf("you are icalling %s!\n", funcname);

	// if not fopen being called
	if (!zend_string_equals_literal(fname, "fopen"))
	{
		return ZEND_USER_OPCODE_DISPATCH;
	}

	zend_string_release(fname);

	//php_printf("gotcha!\n");

	// retrieve the first argument, which is the filename
	zval *arg = ZEND_CALL_ARG(call, 1);
	char *filename = ZSTR_VAL(Z_STR_P(arg));

	// check if filename contains `../`
	if (strstr(filename, "../"))
	{
		php_printf("You are doing something funny huh?\n");
		// don't continue execution!
		return ZEND_USER_OPCODE_RETURN;
	}

	// continue execution
	return ZEND_USER_OPCODE_DISPATCH;
}