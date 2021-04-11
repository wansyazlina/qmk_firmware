/*
Copyright 2020 imchipwood

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
// #define VENDOR_ID       0xFEED
// #define PRODUCT_ID      0x0913
// #define MANUFACTURER    imchipwood
 #define PRODUCT         dumbpad

/* Column/Row IO definitions */
// #define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
 #define DEBOUNCE 5

/* Reduce tapdance required taps from 5 to 2 */
#define TAPPING_TOGGLE 2

/* LED layer indicators */

// Using external LED for layers indicator
 #define LAYER_INDICATOR_LED_0 B6 // Red
 #define LAYER_INDICATOR_LED_1 B1 // Blue or Green

 // On-board LED for debugging

 #define LAYER_INDICATOR_LED_2 B0
#define LAYER_INDICATOR_LED_3 D5

#define RGB_DI_PIN B3
#ifdef RGB_DI_PIN
#define RGBLED_NUM 4
#endif
