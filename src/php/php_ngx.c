/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#include "php_ngx.h"

#include "../ngx_http_php_module.h"
#include "../ngx_http_php_request.h"

#include "php_ngx_location.h"
#include "php_ngx_log.h"
#include "php_ngx_socket_tcp.h"

// If you declare any globals in php_php_ngx.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(php_ngx)


/* True global resources - no need for thread safety here */
//static int le_php_ngx;

/* {{{ php_ngx_functions[]
 *
 * Every user visible function must have an entry in php_ngx_functions[].
 */
const zend_function_entry php_ngx_functions[] = {
	PHP_FE(confirm_php_ngx_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in php_ngx_functions[] */
};
/* }}} */

/* {{{ php_ngx_module_entry
 */
zend_module_entry php_ngx_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"php_ngx",
	php_ngx_functions,
	PHP_MINIT(php_ngx),
	PHP_MSHUTDOWN(php_ngx),
	PHP_RINIT(php_ngx),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(php_ngx),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(php_ngx),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHP_NGX
ZEND_GET_MODULE(php_ngx)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("php_ngx.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_php_ngx_globals, php_ngx_globals)
    STD_PHP_INI_ENTRY("php_ngx.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_php_ngx_globals, php_ngx_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_php_ngx_init_globals
 */
// Uncomment this function if you have INI entries
static void php_php_ngx_init_globals(zend_php_ngx_globals *php_ngx_globals)
{
	//php_ngx_globals->global_value = 0;
	//php_ngx_globals->global_string = NULL;
}

/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(php_ngx)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	ZEND_INIT_MODULE_GLOBALS(php_ngx, php_php_ngx_init_globals,NULL);

	//ngx_location_init(module_number TSRMLS_CC);
	//php_ngx_log_init(module_number TSRMLS_CC);
	//ngx_socket_tcp_init(module_number TSRMLS_CC);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(php_ngx)
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
PHP_RINIT_FUNCTION(php_ngx)
{
	//ngx_location_init(0 TSRMLS_CC);
	PHP_NGX_G(global_r) = NULL;

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(php_ngx)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(php_ngx)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "php_ngx support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_php_ngx_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_php_ngx_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "php_ngx", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


static int php_ngx_startup(sapi_module_struct *sapi_module)
{
	if (php_module_startup(sapi_module, NULL, 0) == FAILURE){
		return FAILURE;
	}
	return SUCCESS;
}

static int php_ngx_deactivate(TSRMLS_D)
{
	return SUCCESS;
}

static int php_ngx_ub_write(const char *str, uint str_length TSRMLS_DC)
{
	return str_length;
}

static void php_ngx_flush(void *server_context)
{
}

static int php_ngx_header_handler(sapi_header_struct *sapi_header, sapi_header_op_enum op, sapi_headers_struct *sapi_headers TSRMLS_DC)
{
	return 0;
}

static int php_ngx_read_post(char *buffer, uint count_bytes TSRMLS_DC)
{
	return 0;
}

static char* php_ngx_read_cookies(TSRMLS_D)
{
	return NULL;
}

static void php_ngx_register_variables(zval *track_vars_array TSRMLS_DC)
{
	php_import_environment_variables(track_vars_array TSRMLS_CC);

	/*if (SG(request_info).request_method) {
		php_register_variable("REQUEST_METHOD", (char *)SG(request_info).request_method, track_vars_array TSRMLS_CC);
	}
	if (SG(request_info).request_uri){
		php_register_variable("DOCUMENT_URI", (char *)SG(request_info).request_uri, track_vars_array TSRMLS_CC);

	}
	if (SG(request_info).query_string){
		php_register_variable("QUERY_STRING", (char *)SG(request_info).query_string, track_vars_array TSRMLS_CC);
	}*/
}

/*static void php_ngx_log_message(char *message)
{
}*/

/* {{{ sapi_module_struct php_ngx_module
*/
sapi_module_struct php_ngx_module = {
	"php-ngx",						/* name */
	"Embed php nginx module",					/* pretty name */

	php_ngx_startup,				/* startup */
	php_module_shutdown_wrapper,	/* shutdown */

	NULL,//php_ngx_activate,				/* activate */
	php_ngx_deactivate,				/* deactivate */

	php_ngx_ub_write,				/* unbuffered write */
	php_ngx_flush,					/* flush */
	NULL,							/* get uid */
	NULL,							/* getenv */

	php_error,						/* error handler */

	php_ngx_header_handler,			/* header handler */
	NULL,							/* send headers handler */
	NULL,							/* send header handler */

	php_ngx_read_post,				/* read POST data */
	php_ngx_read_cookies,			/* read Cookies */

	php_ngx_register_variables,		/* register server variables */
	NULL,//php_ngx_log_message,			/* Log message */
	NULL,							/* Get request time */
	NULL,							/* Child terminate */

	"",								/* php_ini_path_override */

	NULL,
	NULL,

	NULL,
	NULL,
	NULL,

	0,
#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION > 3)
	0,
#endif

	NULL,

	NULL,

	NULL,
	NULL,

	NULL,

	NULL,
	0,

	NULL,
	NULL,
	NULL
	//STANDARD_SAPI_MODULE_PROPERTIES
};

/* {{{ arginfo ext/standard/dl.c */
ZEND_BEGIN_ARG_INFO(arginfo_dl, 0)
	ZEND_ARG_INFO(0, extension_filename)
ZEND_END_ARG_INFO()
/* }}} */

static const zend_function_entry additional_functions[] = {
	ZEND_FE(dl, arginfo_dl)
	{NULL, NULL, NULL, 0, 0}
};

int php_ngx_module_init()
{
	zend_llist global_vars;
#ifdef ZTS
	__attribute__((__unused__)) void ***tsrm_ls = NULL;
#endif

#ifdef HAVE_SIGNAL_H
#if defined(SIGPIPE) && defined(SIG_IGN)
	signal(SIGPIPE, SIG_IGN); /* ignore SIGPIPE in standalone mode so
								 that sockets created via fsockopen()
								 don't kill PHP if the remote site
								 closes it.  in apache|apxs mode apache
								 does that for us!  thies@thieso.net
								 20000419 */
#endif
#endif

#ifdef ZTS
  tsrm_startup(1, 1, 0, NULL);
  tsrm_ls = ts_resource(0);
  //*ptsrm_ls = tsrm_ls;
#endif

  sapi_startup(&php_ngx_module);

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION > 3)
  php_ngx_module.php_ini_ignore_cwd = 1;
#endif

#ifdef PHP_WIN32
  _fmode = _O_BINARY;			/*sets default for file streams to binary */
  setmode(_fileno(stdin), O_BINARY);		/* make the stdio mode be binary */
  setmode(_fileno(stdout), O_BINARY);		/* make the stdio mode be binary */
  setmode(_fileno(stderr), O_BINARY);		/* make the stdio mode be binary */
#endif

  php_ngx_module.additional_functions = additional_functions;

  php_ngx_module.executable_location = NULL;

  if (php_ngx_module.startup(&php_ngx_module) == FAILURE){
  	return FAILURE;
  }

  zend_llist_init(&global_vars, sizeof(char *), NULL, 0); 

  return SUCCESS;
}

int php_ngx_request_init(TSRMLS_D)
{
	if (php_request_startup(TSRMLS_C)==FAILURE) {
		return FAILURE;
  	}

  	SG(headers_sent) = 0;
  	SG(request_info).no_headers = 1;
  	php_register_variable("PHP_SELF", "-", NULL TSRMLS_CC);

  	return SUCCESS;
}

void php_ngx_request_shutdown(TSRMLS_D)
{
	SG(headers_sent) = 1;
	php_request_shutdown((void *)0);
}

void php_ngx_module_shutdown(TSRMLS_D)
{
	php_module_shutdown(TSRMLS_C);
	sapi_shutdown();
#ifdef ZTS
	tsrm_shutdown();
#endif
	if (php_ngx_module.ini_entries){
		free(php_ngx_module.ini_entries);
		php_ngx_module.ini_entries = NULL;
	}
}




/* }}} */