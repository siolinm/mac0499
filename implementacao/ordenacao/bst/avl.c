#include "avl.h"
/*
    https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
    https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
    https://www.youtube.com/watch?v=YkF76cOgtMQ&list=PLxI8Can9yAHf8k8LrUePyj0y3lLpigGcl&index=21
    https://www.youtube.com/watch?v=FzS0n_Z8lrk
*/

/* OK */
int height(Node *a)
{
    return (a ? a->height : -1);
}

/* OK */
void setHeight(Node *a)
{
    a->height = max(height(a->left), height(a->right)) + 1;
}

/* OK */
Node *newNode(Object *key)
{
    Node *new = (Node *)malloc(sizeof(Node));

    new->left = NULL;
    new->right = NULL;
    new->key = key;
    new->height = 1;
    new->children = 0;
    key->node = new;

    return new;
}

/* OK */
Node *rotateRight(Node *no)
{
    Node *leftChild, *aux;

    leftChild = no->left;
    if (!leftChild)
        return no;
    aux = leftChild->right;

    leftChild->right = no;
    no->left = aux;

    leftChild->children += no->children + 1;

    setHeight(no);
    setHeight(leftChild);

    return leftChild;
}

/* OK */
Node *rotateLeft(Node *no)
{
    Node *rightChild, *aux;

    rightChild = no->right;
    if (!rightChild)
        return no;
    aux = rightChild->left;

    rightChild->left = no;
    no->right = aux;

    no->children -= rightChild->children + 1;

    setHeight(no);
    setHeight(rightChild);

    return rightChild;
}

/* OK */
int getBalance(Node *no)
{
    return (no ? (height(no->left) - height(no->right)) : 0);
}

int compare(Object * a, Object * b){
    return (value(a) < value(b) || (value(a) == value(b) && a->speed < b->speed));
}

/* OK */
Node *insertNode(Node *r, Object *key)
{
    int a;
    if (!r)
        return newNode(key);

    if (compare(key, r->key)){
        r->left = insertNode(r->left, key);
    }
    else{
        r->children += 1;
        r->right = insertNode(r->right, key);
    }

    if(key->prev == NULL && !compare(key, r->key)){
        key->prev = r->key;
        key->next = r->key->next;
        if(key->next)
            key->next->prev = key;
        r->key->next = key; 
    }
    else if(key->next == NULL && compare(key, r->key)){
        key->next = r->key;
        key->prev = r->key->prev;
        if(key->prev)
            key->prev->next = key;
        r->key->prev = key;
    }
    
    setHeight(r);

    a = getBalance(r);

    if (a > 1 && key < r->left->key)
        return rotateRight(r);

    if (a > 1 && key > r->left->key)
    {
        r->left = rotateLeft(r->left);
        return rotateRight(r);
    }

    
    if (a < -1 && key > r->right->key)
        return rotateLeft(r);

    if (a < -1 && key < r->right->key)
    {
        r->right = rotateRight(r->right);
        return rotateLeft(r);
    }

    return r;
}

/* OK */
Node *leftmost(Node *r)
{
    while (r->left)
        r = r->left;

    return r;
}

/* OK */
Node *deleteNode(Node *r, Object *key)
{
    Node *aux;
    int a;
    
    if (r == NULL)
        return r;

    if (key == r->key)
    {
        if(key->prev)
            key->prev->next = key->next;
        if(key->next)
            key->next->prev = key->prev;
        if (r->left && r->right)
        {
            aux = leftmost(r->right);
            r->key = aux->key;
            r->key->node = r;        
            r->right = deleteNode(r->right, r->key);
            r->children -= 1;
        }
        else
        {
            aux = r;
            r = (r->left ? r->left : r->right);
            free(aux);
        }
    }
    else if (compare(key, r->key))
    {
        r->left = deleteNode(r->left, key);
    }
    else
    {
        r->right = deleteNode(r->right, key);
        r->children -= 1;
    }

    if(r == NULL)
        return r;

    a = getBalance(r);
    
    if (a > 1 && getBalance(r->left) >= 0){
        return rotateRight(r);    
    }
    else if (a > 1)
    {
        r->left = rotateLeft(r->left);
        return rotateRight(r);
    }
    else if (a < -1 && getBalance(r->right) <= 0){
        return rotateLeft(r);
    }
    else if(a < -1)
    {
        r->right = rotateRight(r->right);
        return rotateLeft(r);
    }

    return r;

}

Object * query_kth(Node *r, int i){
    if(r->children == i - 1)
        return r->key;

    if(r->children < i)
        return query_kth(r->left, i - r->children - 1);    

    return query_kth(r->right, i);
}

void print(char * prefix, int size, Node * r, int b){
	int i;
    char * newprefix;
    if(prefix == NULL){
        prefix = malloc(sizeof(*prefix));
        prefix[0] = '\0';
    }
    if(r != NULL)
    {
        for(i = 0; prefix[i] != '\0'; i++)
            printf("%c", prefix[i]);

        if(b) 
            printf("├──"); 
        else 
            printf("└──" );
        printf("%d: %g*t + %g = %g\n", r->key->id, r->key->speed, r->key->initv, value(r->key));        
		
        newprefix = malloc((size + 4)*sizeof(*newprefix));
        for(i = 0; i < size; i++)
            newprefix[i] = prefix[i];
        if(b)
            newprefix[size - 1] = '|';
        else
            newprefix[size - 1] = ' ';
        for(i = size; i < size + 4; i++)
            newprefix[i] = ' ';        
        newprefix[size + 3] = '\0';
		print(newprefix, size + 4, r->left, 1);
        print(newprefix, size + 4, r->right, 0);
        
    }
    if(!b)
        free(prefix);
}

void printL(){
    Node * aux;
    Object * obj, * lobj;
    aux = leftmost(r);
    obj = aux->key;
    while(obj != NULL){
        /*printf("%d: %g*t + %g = %g", obj->id, obj->speed, obj->initv, value(obj));*/
        /*printf("%d: %g", obj->id, value(obj));*/
        /*printf("%d", obj->id);*/
        if(obj->next)
            /*printf(" --> ")*/;
        else{
            lobj = obj;
            printf("\n");
        }     
        obj = obj->next;
    }
    obj = lobj;
    while(obj != NULL){
        printf("%d", obj->id);
        if(obj->prev)
            printf(" (%gs)--> ", obj->certificate);
        else{
            lobj = obj;
            printf("\n");
        }        
        obj = obj->prev;
    }
}

void removeAll(Node * r){
    if(!r)
        return;
    removeAll(r->left);
    removeAll(r->right);
    destroyObject(r->key);
    free(r);
}