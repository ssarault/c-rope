#ifndef ROPE_H
#define ROPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct Rope
{
    struct Rope *left, *right, *parent;
    char *str;
    size_t l_count;
} Rope;

#define ROPE_LEN(r) ((r)->l_count)

void Rope_create(Rope **node, Rope *par, char *s, size_t l, size_t r, size_t leaf_len);
Rope *Rope_new(char *s, size_t leaf_len);
Rope *Rope_subnew(char *s, size_t strt, size_t end, size_t leaf_len);
void Rope_delete(Rope *root);
Rope *Rope_concat(Rope *root1, Rope *root2);
char *Rope_get_char(Rope *root, size_t i);
bool Rope_set_char(Rope *root, size_t i, char c);
char *Rope_to_str(Rope *root);
char *Rope_to_substr(Rope *root, size_t s, size_t e);
void Rope_print(Rope *r);

#endif