#include <string.h>
#include <stdlib.h>
#include <regex.h>

int ol_regex_compile(regex_t *re, const char *pattern, int flags)
{
	return regcomp(re, pattern, flags||REG_EXTENDED) != 0 ? 1 : 0;
}

char ** ol_regex_match(regex_t* re, const char *text, unsigned int n_match)
{
	regmatch_t *rm = calloc(n_match, sizeof(regmatch_t));
	char *result;
	char **matched = calloc(n_match, sizeof(char *));
	int size;

	if (regexec(re, text, n_match, rm, 0) == 0)
	{
		for (unsigned int i = 0; i < n_match; i++)
		{
			size = rm[i].rm_eo - rm[i].rm_so;
			result = malloc(sizeof(char) * size);
			strncpy(result, &text[rm[i].rm_so], size);
			matched[i] = result;
		}

		free(rm);
		return matched;
	}

	return NULL;
}
