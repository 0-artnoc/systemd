/*-*- Mode: C; c-basic-offset: 8; indent-tabs-mode: nil -*-*/

/***
  This file is part of systemd.

  Copyright 2012 Zbigniew Jędrzejewski-Szmek

  systemd is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  systemd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with systemd; If not, see <http://www.gnu.org/licenses/>.
***/

#pragma once

#include <stdarg.h>
#include <microhttpd.h>

#include "macro.h"

void microhttpd_logger(void *arg, const char *fmt, va_list ap) _printf_(2, 0);

int respond_oom_internal(struct MHD_Connection *connection);

/* respond_oom() must be usable with return, hence this form. */
#define respond_oom(connection) log_oom(), respond_oom_internal(connection)

int respond_error(struct MHD_Connection *connection,
                  unsigned code,
                  const char *format, ...);

int check_permissions(struct MHD_Connection *connection, int *code);

#ifdef HAVE_GNUTLS
void log_func_gnutls(int level, const char *message);

/* This is additionally filtered by our internal log level, so it
 * should be set fairly high to capture all potentially interesting
 * events without overwhelming detail.
 */
#define GNUTLS_LOG_LEVEL 6
#endif
