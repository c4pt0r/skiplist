/*
 * desc: yet another simple ANSI-C skip list implement
 * 
 * author: c4pt0r <huangdongxu@gmail.com>
 * date:   2012-10-1
 *
 * */
#ifndef SK_LIST_H
#define SK_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define SK_MAX_LEVEL_SIZE 16
#define sk_node_val unsigned long long
#define NewNodeOfLevel(l) (struct sk_list_node *)malloc(sizeof(struct sk_list_node) + (l)*sizeof(struct sk_list_node*))
#define NIL(lst)  (lst)->header

struct sk_list_object {
    struct sk_list_object * next; 
    size_t length;
    char  value[1];    
};

struct sk_list_node {
    sk_node_val _val; /* node value */
    struct sk_list_object * objects;  /* node object link list */
    struct sk_list_node* forward[1];
};

struct sk_list {
    int level;
    struct sk_list_node * header;
};

struct sk_list * sk_new_list();
void sk_dump_list();
struct sk_list_node *  sk_insert_node(struct sk_list* lst, sk_node_val val, char * key);
struct sk_list_node *  sk_find_node(struct sk_list * lst, sk_node_val val);

#endif
