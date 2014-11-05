/*
 * config.h
 *
 *  Created on: Oct 24, 2014
 *      Author: jcobb
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>
#include <stdbool.h>


typedef struct
{
	bool		var_bool;
	int32_t 	var_int32_t;
	int16_t 	var_int16_t;
	int8_t		var_int8_t;
	uint32_t 	var_uint32_t;
	uint16_t 	var_uint16_t;
	uint8_t 	var_uint8_t;

} config_t;

extern config_t config;

void config_init();
void load_config();
void write_config();

#endif /* CONFIG_H_ */
