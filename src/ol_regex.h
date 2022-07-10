#ifndef __OL_REGEX_H__
#define __OL_REGEX_H__

#include <regex.h>

int ol_regex_compile(regex_t *re, const char *pattern, int flag);
char ** ol_regex_match(regex_t* re, const char *text, unsigned int n_match);

#endif
