/*
 *  config.h - header for conf_parse.c
 *  Copyright (C) 2022-2023 H. Thevindu J. Wijesekera
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

#ifndef _CONF_PARSE_
#define _CONF_PARSE_

#include "utils/list_utils.h"

typedef struct _config
{
    unsigned short app_port;
    unsigned short app_port_secure;
    char insecure_mode_enabled;
    char secure_mode_enabled;
#ifndef NO_WEB
    unsigned short web_port;
    char web_mode_enabled;
#endif
    char *priv_key;
    char *server_cert;
    char *ca_cert;
    list2 *allowed_clients;
} config;

extern config parse_conf(const char *);

#endif