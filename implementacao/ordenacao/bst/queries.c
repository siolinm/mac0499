#include"queries.h"
#include"avl.h"

Node *newNodeQ(Object *key)
{
    Node *new = (Node *)malloc(sizeof(Node));

    new->left = NULL;
    new->right = NULL;
    new->key = key;
    new->height = 1;
    new->children = 0;    

    return new;
}

/* OK */
Node *insertNodeQ(Node *r, Object *key)
{
    int a;
    if (!r)
        return newNodeQ(key);    
    
    if (key->id < r->key->id)
        r->left = insertNodeQ(r->left, key);
    else
        r->right = insertNodeQ(r->right, key);
      
    
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
Node *deleteNodeQ(Node *r, Object *key)
{
    Node *aux;
    int a;

    if (r == NULL)
        return r;

    if (key->id == r->key->id)
    {                
        if (r->left && r->right)
        {
            aux = leftmost(r->right);
            r->key = aux->key;
            r->right = deleteNodeQ(r->right, r->key);
        }
        else
        {
            aux = r;
            r = (r->left ? r->left : r->right);
            free(aux);
        }        
    }
    else if (key->id < r->key->id)
    {
        r->left = deleteNodeQ(r->left, key);
    }
    else
    {
        r->right = deleteNodeQ(r->right, key);
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

Object * queryQ(Node * r, int id){
    if(!r)
        return NULL;

    if(id < r->key->id)
        return queryQ(r->left, id);
    else if(id > r->key->id)
        return queryQ(r->right, id);
    
    return r->key;
}

void printQ(char * prefix, int size, Node * r, int b){
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
		printQ(newprefix, size + 4, r->left, 1);
        printQ(newprefix, size + 4, r->right, 0);        
    }
    if(!b)
        free(prefix);
}

void removeAllQ(Node * r){
    if(!r)
        return;
    removeAllQ(r->left);
    removeAllQ(r->right);    
    free(r);
}