#include"menu.h"
#include"debug.h"
#include"kds.h"
#include"draw.h"

void loadFile(){
    FILE * file;
    Object * obj;
    int i = 0, j;
    char filename[80];
    printf("Enter the file name: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    fscanf(file, "%d\n", &n);

    drawInit();
    initKDS();

    for(i = 1, j = 2*n - 1; i <= n; i++, j--){
        obj = malloc(sizeof(*obj));
        fscanf(file, "%lf %lf %lf %lf %c", &(obj->x0.x), &(obj->x0.y), &(obj->speed.x), &(obj->speed.y), &(obj->name));
        sendPoint(obj);
    }

    buildKDS();

    fclose(file);
}

int main(){
    Coordinate p;
    Vector v;
    double t;
    int j;
    char opt = 'x';
    while(opt != 's'){
        printf("--------------- MENU ---------------\n");
        printf("(a)dvance\n");
        printf("(c)hange trajectory\n");
        printf("(d)elete\n");
        db(printf("dra(w)\n"));
        printf("(i)nsert point\n");
        printf("(l)oad file\n");
        printf("(n)ow\n");
        db(printf("next (e)vent\n"));
        printf("(q)uery\n");
        db(printf("show in(f)o\n"));
        printf("(s)top\n");
        printf("(t)est\n");
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
            printf("Enter the element id and the new speed: ");
            scanf("%d %lf %lf", &j, &v.x, &v.y);
            change(j, v);
        }
        else if(opt == 'i') {
            printf("Enter the position and the element speed: ");
            scanf("%lf %lf %lf %lf", &p.x, &p.y, &v.x, &v.y);
            insert(p, v);
        }
        else if(opt == 'd'){
            printf("Enter the object ID: ");
            scanf("%d", &j);
            delete(j);
        }
        else if(opt == 'n')
            printf("now: %g\n", now);
        else if(opt == 'l')
            loadFile();
        db(
        else if(opt == 'w')
            draw();
        else if(opt == 'f')
            showInfo();
        else if(opt == 'e')
            advance(nextEvent());
        else if(opt == 't')
            test();
        );
        if(opt != 's'){
            db(
                printf("Next event: %g\n", nextEvent());
                j = minPQ()->certType;
                if(j < TOURN_CERT)
                    printf("Swap in order: ");
                else{
                    // printTourn();
                    printf("Tourn event: ");
                }

                if(getDirection(j) == HORIZONTAL){
                    printf("HORIZONTAL");
                }
                else if(getDirection(j) == UP){
                    printf("UP");
                }
                else if(getDirection(j) == DOWN){
                    printf("DOWN");
                }
                printf("\n");
            );
        }
    }

    return 0;
}