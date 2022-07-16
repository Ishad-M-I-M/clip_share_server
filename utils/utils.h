/*
 *  utils/utils.h - header for utils
 *  Copyright (C) 2022 H. Thevindu J. Wijesekera
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _UTILS_
#define _UTILS_

#include <stdio.h>
#include "list_utils.h"

extern void error(const char *);

extern int get_clipboard_text(char **, size_t *);
extern int put_clipboard_text(char *, size_t);
extern int get_image(char **, size_t *);
extern list2 *get_copied_files(void);
extern long get_file_size(FILE *);
extern int file_exists(const char *);

#endif