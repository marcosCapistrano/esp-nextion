#ifndef NEX_NUMBER_H
#define NEX_NUMBER_H

typedef struct s_nex_number_t *s_nex_number;
typedef struct s_nex_number_t {
	uint8_t pid;
	uint8_t cid;
	const char *name;

	uint32_t value;
} s_nex_number_t;

#endif