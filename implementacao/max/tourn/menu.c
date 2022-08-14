#include"menu.h"
#include"debug.h"

void loadFile(){
    FILE * file;
    int i = 0, j;
    char filename[80];
    printf("Enter the file name: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    fscanf(file, "%d\n", &n);
    init(n);
    for(i = 1, j = 2*n - 1; i <= n; i++, j--){
        fscanf(file, "%lf %lf", &(speed[i]), &(x0[i]));
        tourn[j] = i;
    }
    
    fclose(file);
    /* sorts sorted */
    initTourn();
    db(printT());
    db(printIT());
    initCert();
    db(printC());
    initPQ();
    db(printPQ());
    db(printIQ());
}

int menu(){
    double t;
    int j;
    char opt = 'x';
    while(opt != 's'){
        printf("--------------- MENU ---------------\n");
        printf("(a)dvance\n");
        printf("(c)hange trajectory\n");
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
        else if(opt == 'n') 
            printf("now: %g\n", getTime());
        else if(opt == 'l')
            loadFile();
        if(opt != 's'){
            db(printPQ());
            db(printIQ());
            db(printC());
            db(printT());
            db(printIT());
            db(
                printf("Next event: %g\n", nextEvent());
            );
        }
    }

    return 0;
}

double nextEvent(){
    return cert[minPQ()];
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
    int i, k;    
        
    i = indT[j];
    x0[j] += (speed[j] - v)*getTime();
    speed[j] = v;
        
    update(i);
    while(i <= 2*n - 1){
        i = 2*i;
        if(i + 1 <= 2*n - 1){
            if(tourn[i] != tourn[i/2]) 
                i++;
            k = 2*(i/2) + !(i % 2);            
            update(k);
        }
    }

    printf("Element %d now has a speed of %g\n", j, v);    
}

void query(){    
    printf("Max element: %d, max value: %g\n", tourn[1], value(1));
}