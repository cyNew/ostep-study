#include <stdio.h>
#include <stdlib.h>

typedef struct header_t {
    int size;
    int magic;
} header_t;

typedef struct node_t {
    int size;
    node_t *next;
} node_t;

int main() {
    node_t header;
    header.size = 4096 - sizeof(header);
    header.next = NULL;
    return 0;
}