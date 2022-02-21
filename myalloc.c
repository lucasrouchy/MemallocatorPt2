#include "myalloc.h"
struct block *head = NULL;


void *myalloc(int num){
    if (head == NULL) {
      head = sbrk(1024);
      head->next = NULL;
      head->size = 1024 - PADDED_SIZE(sizeof(struct block));
      head->in_use = 0;
    }
    struct block *current;

    int padded_struct_block_size = PADDED_SIZE(sizeof(struct block));

    return PTR_OFFSET(current, padded_struct_block_size);
}

void print_data(void)
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}


int main(void){
    void *p;

    print_data();
    p = myalloc(64);
    print_data();
}
