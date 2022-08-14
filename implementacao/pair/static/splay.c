#include"splay.h"

#define minimum(a, b) (getXCoordinate(a) > getXCoordinate(b) ? b : a)

Node * createNode(Item * key){
    Node * new = malloc(sizeof(*new));
    new->left = new->right = NULL;
    new->parent = NULL;
    new->key = key;
    return new;
}

void rotateLeft(Node * x){
    Node * aux, *parent;
    
    parent = x->parent;
    aux = x->right;
    if(!aux)
        return;

    x->right = aux->left;
    if(aux->left)
        aux->left->parent = x;
    
    aux->left = x;
    x->parent = aux;
    aux->parent = parent;

    if(parent){
        if(parent->left == x)
            parent->left = aux;
        else
            parent->right = aux;
    }
    else
        root = aux;

}

void rotateRight(Node * x){
    Node * aux, *parent;
    
    parent = x->parent;
    aux = x->left;
    if(!aux)
        return;

    x->left = aux->right;
    if(aux->right)
        aux->right->parent = x;
    
    aux->right = x;
    x->parent = aux;
    aux->parent = parent;

    if(parent){
        if(parent->left == x)
            parent->left = aux;
        else
            parent->right = aux;
    }
    else
        root = aux;
}

Node * queryLow(Item * p, Node * start){
    Node *x = start, *low;
    low = NULL;
    while(x){
        /* I go down while the points are above or in the line */
        while(x && checkLine(p, x->key, -0.5*PI_3) >= 0)
            x = x->left;

        /* x should now be the first point that i found below the line */
        while(x && x->right && checkLine(p, x->right->key, -0.5*PI_3) == -1)
            x = x->right;
        
        if(x){
            low = x;
            x = x->right;
            if(!(x && checkLine(p, x->key, -0.5*PI_3) >= 0))
                x = NULL;
        }
    }
    
    return low;
}

Node * queryUp(Item * p, Node * start){    
    Node *x = start, *up;
    up = NULL;
    
    while(x){
        /* I go up while the points are below the line */
        while(x && checkLine(p, x->key, 0.5*PI_3) == -1)
            x = x->right;
        

        /* x should now be the first point that i found above or in the line */
        /* I go down while the points are above or in the line*/
        while(x && x->left && checkLine(p, x->left->key, 0.5*PI_3) >= 0)
            x = x->left;

        if(x){
            up = x;
            x = x->left;
            if(!(x && checkLine(p, x->key, 0.5*PI_3) == -1))
                x = NULL;            
        }
    }

    return up;
}

Node * cands(Item * p){
    Node * x, *lowNode, *lcandsRoot;
    int low = 0;
    if(!root)
        return NULL;
    x = queryLow(p, root);

    if(x){
        low = 1;
        splay(x);
        lowNode = x;
    }

    if(!low){
        x = queryUp(p, root);
    }
    else{
        x = queryUp(p, root->right);
        if(root->right)
            root->right->parent = NULL;
    }

    if(x){
        splay(x);        
        lcandsRoot = x->left;
        x->left = NULL;
        if(low){
            root = lowNode;
            root->right = x;
            x->parent = root;
        }
    }
    else{
        if(low){
            lcandsRoot = root->right;
            root->right = NULL;
        }
        else{
            lcandsRoot = root;
            root = NULL;
        }
    }

    return lcandsRoot;
}

Item * lcand(Node * lcandsRoot, Item * min){
    Item * aux;
    if(!lcandsRoot)
        return min;
    
    if(!min)
        min = lcandsRoot->key;
    else
        min = minimum(lcandsRoot->key, min);

    if(lcandsRoot->left){
        aux = lcand(lcandsRoot->left, min);
        min = minimum(aux, min);
    }

    if(lcandsRoot->right){
        aux = lcand(lcandsRoot->right, min);
        min = minimum(aux, min);
    }

    free(lcandsRoot);
    
    return min;
}


void insert(Item * key){
    Node * new = createNode(key);
    Node * parent = root, *x;
    
    if(root == NULL){
        root = new;
        return;
    }

    if(compare(parent->key, new->key))
        x = parent->left;
    else
        x = parent->right;

    while(x != NULL){
        parent = x;
        if(compare(x->key, new->key))
            x = x->left;
        else
            x = x->right;
    }

    if(compare(parent->key, new->key))
        parent->left = new;
    else
        parent->right = new;
    
    new->parent = parent;
    splay(new);
}

void splay(Node * x){
    while(x && x->parent){
        /*
            l or r case
        */
        if(!x->parent->parent){
            if(x->parent->left == x)
                rotateRight(x->parent);
            else
                rotateLeft(x->parent);
        }
        else{
            if(x->parent->left == x){
                /* rr case*/
                if(x->parent->parent->left == x->parent){
                    rotateRight(x->parent->parent);
                    rotateRight(x->parent);
                }
                else{
                    /* rl case */
                    rotateRight(x->parent);
                    rotateLeft(x->parent);
                }
            }
            else{
                /* lr case */
                if(x->parent->parent->left == x->parent){
                    rotateLeft(x->parent);
                    rotateRight(x->parent);
                }
                else{
                    /* ll case */
                    rotateLeft(x->parent->parent);
                    rotateLeft(x->parent);
                }
            }
        }
    }
}

int compare(Item * a, Item * b){
    if(getYCoordinate(a) > getYCoordinate(b))
        return 1;
    return 0;
}

void freeAll(Node * r){
    if(r != NULL){
        freeAll(r->left);
        freeAll(r->right);        
        free(r);
    }
    root = NULL;
}

void print(char * prefix, int size, Node * r, int b){
	int i;
    char * new;
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
        printf("(%g, %g)", r->key->x, r->key->y);
        if(r->parent){
            printf("'s parent: (%g, %g)", r->parent->key->x, r->parent->key->y);
        }
		printf("\n");
        new = malloc((size + 4)*sizeof(*new));
        for(i = 0; i < size; i++)
            new[i] = prefix[i];
        if(b)
            new[size - 1] = '|';
        else
            new[size - 1] = ' ';
        for(i = size; i < size + 4; i++)
            new[i] = ' ';        
        new[size + 3] = '\0';
		print(new, size + 4, r->left, 1);
        print(new, size + 4, r->right, 0);
        
    }
    if(!b)
        free(prefix);
}