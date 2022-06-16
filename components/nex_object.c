#include "nex_object.h"

nex_object_t nex_object_create(void *instance, s_nex_object_i *interface, uint8_t pid, uint8_t cid, const char *name) {
	nex_object_t nex_object = (nex_object_t) malloc(s_nex_object_t);

	nex_object->instance = instance;
	nex_object->interface = interface;

	nex_object->pid = pid;
	nex_object->cid = cid;
	nex_object->name = name;

	return nex_object;
}

