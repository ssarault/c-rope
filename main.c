#include "rope.h"

#define MYPRINT(v, l) \
do { \
    for (int i = 0; i < (l); i++) \
        putchar((v)->str[i]); \
} while(0)

int main(void)
{
    Rope *r = Rope_new("My name is Sean", 2);
    printf("%ld \n", r->l_count);
    Rope *l = r->left;
    printf("%ld \n", l->l_count);
    l = l->left;
    printf("%ld \n", l->l_count);
    l = l->right;
    printf("%ld \n", l->l_count);
    printf("%d\n", l->str == NULL);
    Rope_print(r);
    printf("%ld %ld\n", sizeof("me"), strlen("me"));
    Rope_delete(r);
    Rope *a = Rope_new("Hello world!", 2);
    Rope *b = Rope_new("How are you?", 2);
    Rope *c = Rope_concat(a, b);
    Rope_print(c);
    Rope_delete(c);
    return 0;
}