#include <string.h>
#include <stdlib.h>
#include <regex.h>

#include "ol_string.h"

char * ol_str_clone(const char *str) {
	int len = strlen(str);
	char* new_str = malloc(sizeof(char)*len + 1);

	if (new_str == NULL)
		return NULL;

	strcpy(new_str, str);
	return new_str;
}

char * ol_str_replace(char *orig, char *rep, char *replacement)
{
	char *result; // the return string
	char *ins;    // the next insert point
	char *tmp;    // varies
	int len_rep;  // length of rep (the string to remove)
	int len_replacement; // length of replacement (the string to replace rep replacement)
	int len_front; // distance between rep and end of last rep
	int count;    // number of replacements

	// sanity checks and initialization
	if (!orig || !rep)
		return NULL;
	len_rep = strlen(rep);
	if (len_rep == 0)
		return NULL; // empty rep causes infinite loop during count
	if (!replacement)
		replacement = "";
	len_replacement = strlen(replacement);

	// count the number of replacements needed
	ins = orig;
	for (count = 0; (tmp = strstr(ins, rep)); ++count)
		ins = tmp + len_rep;

	tmp = result = malloc(strlen(orig) + (len_replacement - len_rep) * count + 1);

	if (!result)
		return NULL;

	// first time through the loop, all the variable are set correctly
	// from here on,
	//    tmp points to the end of the result string
	//    ins points to the next occurrence of rep in orig
	//    orig points to the remainder of orig after "end of rep"
	while (count--) {
		ins = strstr(orig, rep);
		len_front = ins - orig;
		tmp = strncpy(tmp, orig, len_front) + len_front;
		tmp = strcpy(tmp, replacement) + len_replacement;
		orig += len_front + len_rep; // move to next "end of rep"
	}

	strcpy(tmp, orig);
	return result;
}

char * ol_str_replace_regex(char *origin, regex_t *replace, char *replacement)
{
	regmatch_t rm[2];
	if (regexec(replace, origin, 1, rm, 0) == 0) {
		int size = rm[0].rm_eo - rm[0].rm_so;
		char result[size];
		strncpy(result, origin + rm[0].rm_eo, size);
		return ol_str_replace(origin, result, replacement);
	}
	return NULL;
}
