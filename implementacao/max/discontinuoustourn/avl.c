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

    setHeight(no);
    setHeight(rightChild);

    return rightChild;
}

/* OK */
int getBalance(Node *no)
{
    return (no ? (height(no->left) - height(no->right)) : 0);
}

int compareObject(Object * a, Object * b){
    return (a->id < b->id);
}

/* OK */
Node *insertObject(Node *r, Object *key)
{
    int a;
    if (!r)
        return newNode(key);

    if (compareObject(key, r->key)){
        r->left = insertObject(r->left, key);
    }
    else{        
        r->right = insertObject(r->right, key);
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
Node *deleteObject(Node *r, Object *key)
{
    Node *aux;
    int a;
    
    if (r == NULL)
        return r;

    if (key == r->key)
    {
        if (r->left && r->right)
        {
            aux = leftmost(r->right);
            r->key = aux->key;        
            r->right = deleteObject(r->right, r->key);
        }
        else
        {
            aux = r;
            r = (r->left ? r->left : r->right);
            free(aux);
        }
    }
    else if (compareObject(key, r->key))
    {
        r->left = deleteObject(r->left, key);
    }
    else
    {
        r->right = deleteObject(r->right, key);
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

Object * getObject(Node * r, int id){
    if(!r)
        return NULL;

    if(id < r->key->id)
        return getObject(r->left, id);
    else if(id > r->key->id)
        return getObject(r->right, id);
    
    return r->key;
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
        printf("%d: %g*t + %g = ...\n", r->key->id, r->key->speed, r->key->x0);        
		
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

void removeAll(Node * r){
    if(!r)
        return;
    removeAll(r->left);
    removeAll(r->right);
    destroyObject(r->key);
    free(r);
}