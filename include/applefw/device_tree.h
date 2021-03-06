/* Copyright (c) 2019-2021 Siguza
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses", as
 * defined by the Mozilla Public License, v. 2.0.
**/

#ifndef DT_H
#define DT_H

#include <stddef.h>             // size_t
#include <stdint.h>


int file2mem(const char *path, int (*func)(void*, size_t, void*), void *arg);

// ========== DT ==========

#define DT_KEY_LEN 0x20

typedef struct
{
    uint32_t nprop;
    uint32_t nchld;
    char prop[];
} dt_node_t;

typedef struct
{
    char key[DT_KEY_LEN];
    uint32_t len;
    char val[];
} dt_prop_t;

int dt_check(void *mem, size_t size, size_t *offp);
int dt_parse(dt_node_t *node, int depth, size_t *offp, int (*cb_node)(void*, dt_node_t*), void *cbn_arg, int (*cb_prop)(void*, dt_node_t*, int, const char*, void*, size_t), void *cbp_arg);
dt_node_t* dt_find(dt_node_t *node, const char *name);
void* dt_prop(dt_node_t *node, const char *key, size_t *lenp);

#endif
