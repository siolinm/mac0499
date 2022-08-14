#include"menu.h"
#include"currentTime.h"
#include"util.h"
#include"heapsort.h"
#include"cert.h"
#include"debug.h"
#include<stdio.h>
#include"time.h"

void loadFile(){
    FILE * file;
    int i = 0;
    char filename[80];
    printf("Enter the file name: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    fscanf(file, "%d\n", &n);
    init(n);
    for(i = 1; i <= n; i++){
        fscanf(file, "%lf %lf", &(speed[i]), &(x0[i]));
        sorted[i] = i;
        naive[i] = i;
        indS[i] = i;
    }
    
    fclose(file);
    
    heapsort();
    db(printS());
    initCert();
    db(printC());
    initPQ();
    db(printPQ());
}

int menu(){
    char opt = 'x';
    int * aux;
    int correct, i;
    double start, end, t;
    start = end = 0;
    while(opt != 's'){
        printf("--------------- MENU ---------------\n");
        printf("(a)dvance\n");
        printf("(c)hange trajectory\n");
        printf("(l)oad file\n");
        printf("(n)ow\n");
        printf("(q)uery\n");
        printf("(s)top\n");
        printf("---------------      ---------------\n");
        printf(">>> ");
        scanf(" %c", &opt);
        start = clock();
        if(opt == 's')
            destroy();
        else if(opt == 'q')
            query();
        else if(opt == 'a'){
            printf("Enter the new time value: ");
            scanf(" %lf", &t);
            advance(t);
        }
        else if(opt == 'c'){
            printf("Enter the element's id and the new speed: ");
            scanf("%d %lf", &i, &t);
            change(i, t);
        }
        else if(opt == 't')
            queryNaive();
        else if(opt == 'n')
            printf("now: %g\n", getTime());
        else if(opt == 'l')
            loadFile();
        else if(opt == 'f'){
            aux = sorted;
            sorted = naive;
            heapsort();
            sorted = aux;
            correct = 1;
            for(i = 1; i <= n && correct; i++)                
                correct = (value(sorted[i]) == value(naive[i]));
            if(!correct)
                printf("Isn't ");
            printf("correct\n");
        }
        end = clock();
        printf("The operation took %g seconds\n", (double)(end - start)/CLOCKS_PER_SEC);        
        if(opt != 's'){
            db(printPQ());
            db(printIQ());
            db(printC());
            db(printS());
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
    int i;

    i = indS[j];
    x0[j] += (speed[j] - v)*getTime();
    speed[j] = v;
    update(i);
    update(i - 1);

    printf("Element %d now has a speed of %g\n", j, v);    
}

void query_kth(int i){
    if(i >= 1 && i < n)
        printf("The %dº element predecessor is %d\n", sorted[i], sorted[i + 1]);
    else
        printf("This position does not have a predecessor\n");
}

void query(){
    int i;
    printf("Enter the position: ");
    scanf("%d", &i);
    query_kth(i);
}

void queryNaive(){
    int * aux = sorted;
    sorted = naive;
    heapsort();
    query();
    sorted = aux;
}