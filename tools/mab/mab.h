#ifndef _MAB_H
#define _MAB_H
/*
 * mab.h: tool to Make A Blob of ACPI tables
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the main directory of this
 * archive for more details.
 *
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 *
 * NB: all values are assumed to be little-endian in the blob.
 *
 */

/* VERSION a.b.c = <public release>.<functionality changes>.<bug fixes> */
const char VERSION[] = { "0.28.1" };
const char PROGNAME[] = { "mab" };

#endif
