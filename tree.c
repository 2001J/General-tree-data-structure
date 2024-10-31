//by Joseph Paul Koyi.
//tree.c
#include "tree.h"

Tree root = { .n = {
    .tag = (TagRoot | TagNode),
    .north = (Node *)&root,
    .west = 0,
    .east = 0,
    .path = "/"
}};

void zero(int8 *str, int16 size) {
    int8 *p;
    int16 n;

    for (n=0, p=str; n < size; p++, n++)
        *p = 0;

    return;
}

Node *create_node(Node *parent, int8 *path) {
    Node *n;
    int16 size;

    errno = NoError;
    assert(parent);
    size = sizeof(struct s_node);
    n = (Node *)malloc((int)size);
    zero((int8 *)n, size);

    parent->west = n;
    n->tag = TagNode;
    n->north = parent;
    strncpy((char *)n->path, (char *)path, 255);

    return n;
}

Leaf *find_last_linear(Node *parent) {
    Leaf *l;

    errno = NoError;
    assert(parent);
    if (!parent->east) 
        reterr(NoError);
    
    for(l = parent->east; l->east; l = l->east);
    assert(l);

    return l;
}

Leaf *create_leaf(Node *parent, int8 *key, int8 *value, int16 count) {
    Leaf *l, *new;
    int16 size;

    assert(parent);
    l = find_last(parent);

    size = sizeof(struct s_leaf);
    new = (Leaf *)malloc(size);
    assert(new);

    if(!l)
        parent->east = new;
    else
        l->east = new;
    
    zero((int8 *)new, size);
    new->tag = TagLeaf;
    new->west = (!l) ? (Tree *)parent : (Tree *)l;

    strncpy((char *)new->key, (char *)key, 127);
    new->value = (int8 *)malloc(count);
    zero(new->value, count);
    assert(new->value);
    strncpy((char *)new->value, (char *)value, count);
    new->size = count;

    return new;
}

Leaf *insert(Node *parent, int8 *key, int8 *value) {
    int16 size = (int16)strlen((char *)value);
    return create_leaf(parent, key, value, size);
}

void delete_leaf(Node *parent, int8 *key) {
    Leaf *current = parent->east;
    Leaf *prev = NULL;

    while (current != NULL && strcmp((char *)current->key, (char *)key) != 0) {
        prev = current;
        current = current->east;
    }

    if (current == NULL) {
        printf("Key not found\n");
        return;
    }

    if (prev == NULL) {
        parent->east = current->east;
    } else {
        prev->east = current->east;
    }

    free(current->value);
    free(current);
}

Leaf *search(Node *parent, int8 *key) {
    Leaf *current = parent->east;

    while (current != NULL) {
        if (strcmp((char *)current->key, (char *)key) == 0) {
            return current;
        }
        current = current->east;
    }

    return NULL;
}

void in_order_traversal(Node *node) {
    if (node == NULL) return;

    in_order_traversal(node->west);
    printf("Node Path: %s\n", node->path);
    in_order_traversal((Node *)node->east);
}

void pre_order_traversal(Node *node) {
    if (node == NULL) return;

    printf("Node Path: %s\n", node->path);
    pre_order_traversal(node->west);
    pre_order_traversal((Node *)node->east);
}

void post_order_traversal(Node *node) {
    if (node == NULL) return;

    post_order_traversal(node->west);
    post_order_traversal((Node *)node->east);
    printf("Node Path: %s\n", node->path);
}

void debug_tree(Node *node) {
    if (node == NULL) return;

    printf("Node Path: %s, Tag: %d\n", node->path, node->tag);
    debug_tree(node->west);
    debug_tree((Node *)node->east);
}

void free_leaves(Leaf *leaf) {
    while (leaf != NULL) {
        Leaf *next = leaf->east;
        free(leaf->value);
        free(leaf);
        leaf = next;
    }
}

void free_nodes(Node *node) {
    if (node == NULL) return;

    free_nodes(node->west);
    free_leaves(node->east);
    free(node);
}

int main() {
    Node *n, *n2;
    Leaf *l1, *l2;
    int8 *key, *value;
    int16 size;

    n = create_node((Node *)&root, (int8 *)"/Users");
    assert(n);
    n2 = create_node(n, (int8 *)"/Users/login");
    assert(n2);

    key = (int8 *)"joe";
    value = (int8 *)"abc123";
    size = (int16)strlen((char *)value);
    l1 = create_leaf(n2, key, value, size);
    assert(l1);

    printf("%s\n", l1->value);

    key = (int8 *)"jane";
    value = (int8 *)"xyz789";
    size = (int16)strlen((char *)value);
    l2 = create_leaf(n2, key, value, size);
    assert(l2);

    printf("%s\n", l2->key);

    printf("%p %p\n", n, n2);

    // Test insert, delete, and search
    insert(n2, (int8 *)"alice", (int8 *)"password123");
    Leaf *found = search(n2, (int8 *)"alice");
    if (found) {
        printf("Found key 'alice' with value: %s\n", found->value);
    }

    delete_leaf(n2, (int8 *)"alice");
    found = search(n2, (int8 *)"alice");
    if (!found) {
        printf("Key 'alice' not found after deletion\n");
    }

    // Test traversals
    printf("In-Order Traversal:\n");
    in_order_traversal((Node *)&root);

    printf("Pre-Order Traversal:\n");
    pre_order_traversal((Node *)&root);

    printf("Post-Order Traversal:\n");
    post_order_traversal((Node *)&root);

    // Debug tree
    printf("Debug Tree:\n");
    debug_tree((Node *)&root);

    // Free all dynamically allocated memory
    free_nodes(root.n.west);

    return 0;
}