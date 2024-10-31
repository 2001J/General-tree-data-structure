// By Joseph Paul Koyi
//tree.h
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <assert.h>
#include <errno.h>


#define TagRoot     1 // 00 01
#define TagNode     2 // 00 10
#define TagLeaf     4 // 01 00

#define NoError     0

typedef void* Nullptr;
Nullptr null_ptr = 0;

#define find_last(x)         find_last_linear(x)
#define reterr(x) \
    errno = (x); \
    return null_ptr


typedef unsigned int int32;
typedef unsigned short int16;
typedef unsigned char int8;
typedef unsigned char Tag;

struct s_node {
    Tag tag;
    struct s_node *north;
    struct s_node *west;
    struct s_leaf *east;
    int8 path[256];
};
typedef struct s_node Node;

struct s_leaf {
    Tag tag;
    union u_tree *west;
    struct s_leaf *east;
    int8 key[128];
    int8 *value;
    int16 size;
};
typedef struct s_leaf Leaf;

union u_tree {
    Node n;
    Leaf l;
};
typedef union u_tree Tree;

// Function prototypes
void zero(int8 *str, int16 size);
Node *create_node(Node *parent, int8 *path);
Leaf *find_last_linear(Node *parent);
Leaf *create_leaf(Node *parent, int8 *key, int8 *value, int16 count);
Leaf *insert(Node *parent, int8 *key, int8 *value);
void delete_leaf(Node *parent, int8 *key);
Leaf *search(Node *parent, int8 *key);
void in_order_traversal(Node *node);
void pre_order_traversal(Node *node);
void post_order_traversal(Node *node);
void debug_tree(Node *node);
void free_leaves(Leaf *leaf);
void free_nodes(Node *node);
