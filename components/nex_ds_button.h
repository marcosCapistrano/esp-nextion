#ifndef NEX_DS_BUTTON_H
#define NEX_DS_BUTTON_H

typedef struct s_nex_ds_button_t *s_nex_ds_button;
typedef struct s_nex_ds_button_t {
	uint8_t pid;
	uint8_t cid;
	const char *name;

	uint32_t value;

} s_nex_ds_button_t;

#endif