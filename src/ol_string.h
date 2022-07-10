#ifndef __OL_STRING_H__
#define __OL_STRING_H__

#include <regex.h>

char * ol_str_clone(const char *string);
char * ol_str_replace(char *origin, char *replace, char *replacement);
char * ol_str_replace_regex(char *origin, regex_t *replace, char *replacement);

#endif
