#include"menu.h"
#include"debug.h"

void loadFile(){
    FILE * file;
    Object * obj;
    int i = 0, j;
    char filename[80];
    printf("Enter the file name: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    fscanf(file, "%d\n", &n);
    init(n);
    for(i = 1, j = 2*n - 1; i <= n; i++, j--){
        obj = malloc(sizeof(*obj));
        fscanf(file, "%lf %lf", &(obj->speed), &(obj->x0));
        obj->id = lastID++;
        Q[i] = obj;
        obj->pqpos = i;
        tourn[j] = obj;
        root = insertObject(root, obj);
    }
    
    fclose(file);
    
    initTourn();    
    initCert();    
    initPQ();    
}

int menu(){
    double t, x;
    int j;
    char opt = 'x';
    while(opt != 's'){
        printf("--------------- MENU ---------------\n");
        printf("(a)dvance\n");
        printf("(c)hange trajectory\n");
        printf("(d)elete\n");
        printf("(i)nsert point\n");
        printf("(l)oad file\n");
        printf("(n)ow\n");
        printf("(q)uery\n");
        printf("(s)top\n");
        printf("---------------      ---------------\n");
        printf(">>> ");
        scanf(" %c", &opt);
        if(opt == 's')
            destroy();
        else if(opt == 'q')
            query();
        else if(opt == 'a') {
            printf("Enter the new time value: ");
            scanf(" %lf", &t);
            advance(t);
        }
        else if(opt == 'c') {
            printf("Enter the element's id and the new speed: ");
            scanf("%d %lf", &j, &t);
            change(j, t);
        }
        else if(opt == 'i') {
            printf("Enter the speed and the element's value: ");
            scanf("%lf %lf", &t, &x);
            insert(x, t);
        }
        else if(opt == 'd'){
            printf("Enter the object ID: ");
            scanf("%d", &j);
            delete(j);
        }
        else if(opt == 'n') 
            printf("now: %g\n", getTime());
        else if(opt == 'l')
            loadFile();
        if(opt != 's'){
            db(printT(NULL, 1, 1, 0));
            db(
                printf("Next event: %g\n", nextEvent());
            );
        }
    }

    return 0;
}

double nextEvent(){
    return minPQ()->certificate;
}

void advance(double t){        
    if(t < getTime())
        printf("Time earlier than current time\n");
    
    while(t >= nextEvent()){
        setTime(nextEvent());
        event();
    }
    setTime(t);
}

void change(int j, double v){
    Object * obj;
    int i, k;
    obj = getObject(root, j);
    i = obj->lastMatch;
    obj->x0 += (obj->speed - v)*getTime();
    obj->speed = v;

    update(obj);
    while(i <= 2*n - 1){
        i = 2*i;
        if(i + 1 <= 2*n - 1){
            if(tourn[i] != tourn[i/2])
                i++;
            k = 2*(i/2) + !(i % 2);
            update(tourn[k]);
        }
    }

    printf("Element %d now has a speed of %g\n", j, v);    
}

void insert(double xt, double v){
    Object * obj;
    
    obj = malloc(sizeof(*obj));
    obj->speed = v;
    obj->x0 = xt - v*getTime();
    obj->id = lastID++;
    root = insertObject(root, obj);
    insertTourn(obj);
    newCert(obj);
    insertPQ(obj);
    printf("The element has been created with an id: %d\n", obj->id);
}

void delete(int i){
    Object * obj;
    
    obj = getObject(root, i);
    root = deleteObject(root, obj);
    deletePQ(obj);
    deleteTourn(obj);
    destroyObject(obj);
}

void query(){    
    printf("Max element: %d, max value: %g\n", tourn[1]->id, value(1));
}