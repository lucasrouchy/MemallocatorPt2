#include "myalloc.h"
struct block *head = NULL;

void split_space(struct block* curr, int requested_size){
  int available = curr->size;
  int requested_padded_size = PADDED_SIZE(requested_size);
  int padded_struct_block_size = PADDED_SIZE(sizeof(struct block));
  int min_size = requested_padded_size + padded_struct_block_size;
  if (available < min_size + 16) return;

  struct block *split_node = PTR_OFFSET(curr, min_size);
  split_node->size = available - min_size;
  curr->size = requested_padded_size;
  curr->next = split_node;

}

void *myalloc(int num){
    if (head == NULL) {
      head = sbrk(1024);
      head->next = NULL;
      head->size = 1024 - PADDED_SIZE(sizeof(struct block));
      head->in_use = 0;
    }
    struct block *current = head;

    int padded_num = PADDED_SIZE(num);

    while (current != NULL){
      if (current->in_use == 0 && current->size >= padded_num){
        split_space(current, num);
        current->in_use = 1;
        int padded_struct_block_size = PADDED_SIZE(sizeof(struct block));
        return PTR_OFFSET(current, padded_struct_block_size);

      }
      current = current->next;
    }
    return NULL;

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


void myfree(void *p){


}
int main(void){
    void *p;

    print_data();
    p = myalloc(512);
    print_data();

}
