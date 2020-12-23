#include <stdbool.h>
#include "Adapter.h"
#include "AdapterNode.h"

struct AdapterNodeInt;
typedef struct AdapterNodeInt *AdapterNode;

void init_node(AdapterNode *vp, int value);
void setNext(AdapterNode v, AdapterNode n);
void *getData(AdapterNode v);
AdapterNode getNext(AdapterNode v);