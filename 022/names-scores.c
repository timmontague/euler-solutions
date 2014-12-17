#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <ctype.h>

/*
 * Using names.txt, a 46K text file containing over five-thousand first names,
 * begin by sorting it into alphabetical order. Then working out the
 * alphabetical value for each name, multiply this value by its alphabetical
 * position in the list to obtain a name score.
 *
 * For example, when the list is sorted into alphabetical order, COLIN, which is
 * worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN
 * would obtain a score of 938 × 53 = 49714.
 *
 * What is the total of all the name scores in the file?
 */

typedef struct _name_t {
    char *name;
    int score;
} name_t;

name_t *get_name(FILE *fd) {
    char c = fgetc(fd);
    char *s = NULL;
    size_t s_len = 0;
    size_t s_maxlen = 0;
    int score = 0;
    name_t *n;
    if (c == EOF) {
	return NULL;
    }
    if (c == ',') {
	c = fgetc(fd);
    }
    if (c != '"') {
	printf("expected quote\n");
	exit(1);
    }
    n = malloc(sizeof(name_t));
    if (!n) {
	perror("get_name");
	exit(1);
    }
    c = fgetc(fd);
    while (c != '"') {
	s_len++;
	if (s_len > s_maxlen) {
	    s_maxlen += 10;
	    s = realloc(s, s_maxlen*sizeof(char));
	    if (!s) {
		perror("get_name");
		exit(1);
	    }
	}
	s[s_len-1] = c;
	score += tolower(c)-'a'+1;
	c = fgetc(fd);
    }
    s[s_len] = '\0';
    n->name = s;
    n->score = score;
    return n;
}

static int cmp(const void *a, const void *b) {
    char *s1, *s2;
    s1 = (*(name_t**)a)->name;
    s2 = (*(name_t**)b)->name;
    return strcmp(s1,s2);
}

int main(void) {
    name_t **list = NULL;
    name_t *n = NULL;
    size_t list_len = 0;
    size_t list_maxlen = 0;
    size_t i;
    unsigned long long sum = 0;
    FILE *fd = fopen("names.txt", "r");
    if (!fd) {
	perror("main");
	return 1;
    }
    n = get_name(fd);
    while(n) {
	list_len++;
	if (list_len > list_maxlen) {
	    list_maxlen += 100;
	    list = realloc(list, list_maxlen*sizeof(name_t*));
	    if (!list) {
		perror("main");
		return 1;
	    }
	}
	list[list_len-1] = n;
	n = get_name(fd);
    }
    qsort(list, list_len, sizeof(name_t*), cmp);
    for (i = 0; i < 10; i ++) {
    }
    for (i = 0; i < list_len; i++) {
	sum += (list[i]->score * (i+1));
    }
    printf("%lld\n", sum);
    return 0;
}
