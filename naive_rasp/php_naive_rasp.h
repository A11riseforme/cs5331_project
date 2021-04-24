/* naive_rasp extension for PHP */

#ifndef PHP_NAIVE_RASP_H
# define PHP_NAIVE_RASP_H

extern zend_module_entry naive_rasp_module_entry;
# define phpext_naive_rasp_ptr &naive_rasp_module_entry

# define PHP_NAIVE_RASP_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_NAIVE_RASP)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

static int php_do_icall_handler(zend_execute_data* ZEND_OPCODE_HANDLER_ARGS);

#endif	/* PHP_NAIVE_RASP_H */
