#include "sk_list.h"
#include <assert.h>

int main()
{
    int i;
    struct sk_list * lst = NULL;
    srand(time(NULL));
    lst = sk_new_list();
    assert(lst->header != NULL);
    assert(lst != NULL);
    assert(lst->level ==  0);
    for (i = 0; i < SK_MAX_LEVEL_SIZE; i++)
        assert(lst->header->forward[i] == NIL(lst));

    for (i =0 ;i < 100; i++)    
        sk_insert_node(lst, rand() % 1000 , "key");

    sk_dump_list(lst);
}
