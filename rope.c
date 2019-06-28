#include "rope.h"

#define loop while(1)

void Rope_create(Rope **node, Rope *par, char *s, size_t l, size_t r, size_t leaf_len)
{
    
    Rope *tmp = malloc(sizeof(Rope));
    tmp->left = tmp->right = NULL;
    tmp->parent = par;

    if (par == NULL) {

        tmp->str = NULL;
        tmp->l_count = r;
        *node = tmp;
        Rope_create(&(tmp->left), tmp, s, l, r, leaf_len);

    } else if ((r - l) > leaf_len) {

        tmp->str = NULL;
        tmp->l_count = (r - l) / 2;
        *node = tmp;
        size_t m = (l + r) / 2;
        Rope_create(&(tmp->left), tmp, s, l, m, leaf_len);
        Rope_create(&(tmp->right), tmp, s, m, r, leaf_len);

    } else {
        *node = tmp;
        tmp->l_count = (r - l);
        size_t j = 0;
        tmp->str = malloc(leaf_len);
        for (size_t i = l; i < r; i++)
            tmp->str[j++] = s[i];
    }
}

Rope *Rope_new(char *s, size_t leaf_len)
{
    size_t len = strlen(s);
    if (len == 0)
        return NULL;
    Rope *root = NULL;
    Rope_create(&root, NULL, s, 0, len, leaf_len);
    return root;
}

Rope *Rope_subnew(char *s, size_t strt, size_t end, size_t leaf_len)
{
    if ((end > strlen(s) - 1) || (strt > end))
        return NULL;
    Rope *root = NULL;
    Rope_create(&root, NULL, s, strt, end, leaf_len);
    return root;
}

void Rope_delete(Rope *root)
{
    Rope *prev, *node = root;

    while(node != NULL) {
        
        if ((node->right == NULL) && (node->left == NULL)) {
            prev = node->parent;
            if (node->str != NULL)
                free(node->str);
            free(node);
            node = prev;
            continue;
        }
        
        if (node->right == NULL) {
            prev = node;
            node = node->left;
            prev->left = NULL;

        } else {
            prev = node;
            node = node->right;
            prev->right = NULL;
        }
        
    }
}

Rope *Rope_concat(Rope *root1, Rope *root2)
{
    Rope *tmp = malloc(sizeof(Rope));
    tmp->parent = tmp->right = NULL; 
    tmp->str = NULL;
    tmp->l_count = ROPE_LEN(root1) + ROPE_LEN(root2);
    tmp->left = root1;
    root1->parent = tmp;
    root1->right = root2;
    root2->parent = root1;
    return tmp;
}

char *Rope_get_char(Rope *root, size_t i)
{
    size_t len = ROPE_LEN(root);

    if ((i > len - 1) || (len == 0))
        return NULL;

    i += 1;

    Rope *node = root->left;
    size_t pos = node->l_count;

    loop {
        if (pos >= i) {
            if (node->left == NULL) {
                size_t tmp = pos - (node->l_count - 1);
                i -= tmp;
                return &(node->str[i]);
            }
            Rope *par = node;
            node = node->left;
            pos -= (par->l_count - node->l_count);
        } else {
            node = node->right;
            pos += node->l_count;
        }
    }

}

bool Rope_set_char(Rope *root, size_t i, char c)
{
    size_t len = ROPE_LEN(root);

    if ((i > len - 1) || (len == 0))
        return false;

    i += 1;

    Rope *node = root->left;
    size_t pos = node->l_count;

    loop {
        if (pos >= i)
        {
            if (node->left == NULL)
            {
                size_t tmp = pos - (node->l_count - 1);
                i -= tmp;
                node->str[i] = c;
                return true;
            }
            Rope *par = node;
            node = node->left;
            pos -= (par->l_count - node->l_count);
        }
        else
        {
            node = node->right;
            pos += node->l_count;
        }
    }
}

char *Rope_to_str(Rope *root)
{
    size_t len = ROPE_LEN(root);
    char *s = malloc(len + 1);
    s[len] = '\0';
    char *pos = s;
    size_t i = 0;
    while(i < len)
        *pos++ = *(Rope_get_char(root, i++));
    return s; 
}

char *Rope_to_substr(Rope *root, size_t st, size_t e)
{
    size_t len = e - st + 1;
    char *s = malloc(len + 1);
    s[len] = '\0';
    char *pos = s;
    size_t i = st;
    size_t end = e + 1;
    while (i < end)
        *pos++ = *(Rope_get_char(root, i++));
    return s;
}

static void Rope_print_int(Rope *r)
{
    if (r == NULL)
        return;
    if ((r->left == NULL) && (r->right == NULL))
    {
        for (int i = 0; i < r->l_count; i++)
            putchar(r->str[i]);
    }
    Rope_print_int(r->left);
    Rope_print_int(r->right);
}

void Rope_print(Rope *r)
{
    Rope_print_int(r);
    putchar('\n');
}

#undef loop
