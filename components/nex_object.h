#ifndef NEX_OBJECT_H
#define NEX_OBJECT_H

typedef struct s_nex_object_i {

};

typedef struct s_nex_object_t *nex_object_t;
typedef struct s_nex_object_t {
	void *instance;
	const s_nex_object_i *interface;

	uint8_t pid;
	uint8_t cid;
	const char* name;
} s_nex_object_t;

#endif