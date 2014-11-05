/*
 * config.c
 *
 *  Created on: Oct 24, 2014
 *      Author: jcobb
 */


#include "config.h"


config_t config;

void config_init()
{
	config.var_bool = false;
	config.var_int8_t = 0;
	config.var_int16_t = 0;
	config.var_int32_t = 0;
	config.var_uint8_t = 0;
	config.var_uint16_t = 0;
	config.var_uint32_t = 0;

}


void load_config()
{
}

void write_config()
{

}
