#ifndef SCOPE_H
#define SCOPE_H

#include "hash_table.h"
#include "symbol.h"
#include "decl.h"

void scope_enter();
void scope_exit();
void scope_bind(const char *name, struct symbol *s);
struct symbol * scope_lookup(const char *name);

int scope_level();
void scope_remove_local(const char *name);
struct symbol *scope_lookup_local(const char *key);

#endif
