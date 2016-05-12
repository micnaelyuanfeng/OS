/*
Copyright (C) <2016>  William Taylor Jones <freemicronix@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef _X86_RTC_H
#define _X86_RTC_H

#include <x86/isa/interrupt.h>
#include <stdint.h>
#include <x86/io.h>
#include <stdbool.h>

#define CURRENT_YEAR				2016

typedef struct rtc_time
{
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint32_t year;
} rtc_time_t;

void RTC_Update(void);
rtc_time_t* RTC_Get_Current_Time(void);
void RTC_Handler(interrupt_context_t *int_ctx);
void Initialize_RTC(void);
uint32_t Get_RTC_Ticks(void);

#endif