#ifndef NEX_PAGE_H
#define NEX_PAGE_H

typedef struct s_nex_page_t *s_nex_page;
typedef struct s_nex_page_t {
	uint8_t pid;
	uint8_t cid;
	const char *name;
} s_nex_page_t;

#endif