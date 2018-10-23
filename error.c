/* 
 * Implementation for error reporting.
 *
 * Copyright (C) 2018 by Xiaoliang Fang (fangxlmr@foxmail.com).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "error.h"

void error(int status, int errnum, const char *format, ...)
{
    va_list ap;

    if (status != 0) {
        exit(status);

    } else if (errnum != 0) {
        fprintf(stderr, "%d: %s", errnum, strerror(errnum));
        va_start(ap, format);
        vfprintf(stderr, format, ap);
        va_end(ap);
    }
}
