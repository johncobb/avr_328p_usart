/*
 * defines.h
 *
 *  Created on: Oct 20, 2014
 *      Author: jcobb
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
//#include "config.h"


typedef bool boolean;
typedef uint8_t byte;

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))


#endif /* DEFINES_H_ */
