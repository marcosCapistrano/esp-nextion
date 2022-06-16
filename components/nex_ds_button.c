#include "nex_ds_button.h"

uint32_t nex_ds_button_get_value(nex_ds_button_t ds_button) {
	return ds_button->value;
}

_Bool nex_ds_button_set_value(nex_ds_button_t ds_button, uint32_t value) {
	//Send command
	//If OK, update value
}