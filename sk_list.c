/*
 * desc: yet another simple ANSI-C skip list implement
 * 
 * author: c4pt0r <huangdongxu@gmail.com>
 * date:   2012-10-1
 *
 * */
#include <stdio.h>
#include <memory.h>

#include <stdlib.h>
#include "sk_list.h"
#include <assert.h>
#define _DEBUG_LOG printf

/*
 * init skip list
 * */
struct sk_list *
sk_new_list() 
{
    struct sk_list * lst;
    int i = 0;

    lst = (struct sk_list *) malloc (sizeof(struct sk_list));
    lst->level = 0;

    lst->header = NewNodeOfLevel(SK_MAX_LEVEL_SIZE);
    for (i = 0; i< SK_MAX_LEVEL_SIZE; i++)
    {
        lst->header->forward[i] = NIL(lst);
    }
    return lst;
}

/*
 * debug tool, dump skip list
 * */
void
sk_dump_list(struct sk_list * lst)
{
    int i =0;
    struct sk_list_node * p;
    printf("total level: %d\n", lst->level);
    for (i =0 ;i < lst->level; i++)
    {
        printf("level %d\n", i);
        p = lst->header->forward[i];
        while(p != NIL(lst)){
            printf("%lld ", p->_val);
            printf("%s ", p->objects->value);
            p = p->forward[i];
        }
        printf("\n");
    }
}

/*
 * insert node
 * */
struct sk_list_node *
sk_insert_node(struct sk_list* lst, sk_node_val val, char * key)
{
    int key_length, i, new_level;
    struct sk_list_node * update[SK_MAX_LEVEL_SIZE];
    struct sk_list_object * obj;
    struct sk_list_node * node;

    node = lst->header;
    assert(node != NULL);
    for (i = lst->level; i>=0; i--)
    {
        assert(node->forward[i] != NULL);
        while (node->forward[i] != NIL(lst) && node->forward[i]->_val < val)
        {
            node = node->forward[i];
        } 
        update[i] = node;
    }
    
    if (node->forward[0] != NIL(lst) && node->forward[0]->_val == val)
    {
        node = node->forward[0];
        key_length = strlen(key);
        obj = (struct sk_list_object *) malloc (sizeof(struct sk_list_object) + (key_length + 1) * sizeof(char));    
        obj->next = node->objects;
        strncpy(obj->value, key, key_length);
        node->objects = obj;
        return node;
    }

    /* check level if need update */
    for (new_level = 0; rand() < RAND_MAX / 2 && new_level < SK_MAX_LEVEL_SIZE - 1; new_level++);
    if (new_level > lst->level)
    {
        for (i = lst->level + 1; i <= new_level; i++)
            update[i] = NIL(lst);
        lst->level = new_level;
    } 

    /* create new node */
    node = NewNodeOfLevel(new_level);
    memset(node,0, sizeof(struct sk_list_node ) + new_level * sizeof(struct sk_list_node*));
    node->_val = val;
    /* create new node object */
    key_length = strlen(key);
    obj = (struct sk_list_object *) malloc (sizeof(struct sk_list_object) + (key_length + 1) * sizeof(char));    
    obj->next = NULL;
    strncpy(obj->value, key, key_length);
    node->objects = obj;

    /* update levels*/
    for(i =0 ; i<= new_level; i++)
    {
        node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = node;
    }
    return node;
}

/*
 * find node
 * */
struct sk_list_node*
sk_find_node(struct sk_list * lst,sk_node_val val)
{
    int i;
    struct sk_list_node * node;

    node = lst->header;

    for (i = lst->level; i >= 0; i--)
    {
        while (node->forward[i] != NIL(lst) && node->forward[i]->_val < val) {
            node = node->forward[i];
        }
    }

    node = node->forward[0];
    if (node != NIL(lst) && node->_val == val)
        return node;
    return NULL;
}

int
sk_delete_node(struct sk_list *lst,  struct sk_list_node * node)
{
    return 0;
} 
