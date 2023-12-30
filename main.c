#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct Employee{
    int id;
    char name[10];
    int age;
    float salary;
    float commission;
    float deduction;
};
#define Left 75
#define Right 77
#define Esc 27
#define Enter 13
#define End 79
#define Home 71
#define Del 83
#define Backspace 8
#define Tab 9
#define Ins 82
#define Up 72
#define Down 80
#define Esc 27
#define Enter 13
#define End 79
#define Home 71

void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}
void textattr(int i)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

void printchars(char *arr, int size){
    int i=0;
    for(int i=0; i<size; i++){
        if(arr[i]!='\0'){
            printf("%c", arr[i]);
        }else{
            break;
        }
    }
}
char* LineEditor(int size,int col,int row,int startKey,int endKey)
{
    char *arr;
    arr=malloc(size * sizeof(char));
    int f=0;
    int l=0;
    int c = 0;
    char *Fp = arr;
    char *Lp = arr;
    char *C = arr;
    int flag = 1;
    char ch;
    do{
        gotoxy(col+c,row);
        ch=getch();
        if(ch==-32){
            ch=getche();
            switch(ch){
                case Left:
                    if(c > 0){
                     c--;
                     C--;
                    }
                break;
                case Right:
                    if(c < l){
                     c++;
                     C++;
                    }
                break;
                case Home:
                    c = 0;
                break;
                case End:
                    c = l-1;
                break;
                case Del:
                    if(c < l) {
                        for(int i=0; i<l; i++) {
                            arr[c+i]=arr[c+1+i];
                        }
                        arr[l-1]='\0';
                        l--;
                        Lp--;
                        gotoxy(col, row);
                        printf("%s",arr);
                        arr[l-1]='\0';
                    }
                break;
                case Ins:
                    if(l!=size){
                        ch=getch();
                        Lp++;
                        l++;
                        for(int i=l; i>c; i--) {
                            arr[i]=arr[i-1];
                        }
                        arr[c]=ch;
                        arr[l]='\0';
                        gotoxy(col, row);
                        printf("%s",arr);
                    }
                break;
            }
        }else{
            switch(ch){
                case Enter:
                    flag=0;
                break;
                case Backspace:
                        Lp--;
                        l--;
                        C--;
                    if(c>0) {
                        for(int i=0; i<l; i++) {
                            arr[c-1+i]=arr[c+i];
                        }
                        c--;
                        //arr[l]='\0';
                        gotoxy(col, row);
                        printchars(arr,size);
                    }
                break;
                default:
                   if(c<size && isprint(ch)!=0 &&ch>=startKey&&ch<=endKey){
                    if(c==l){
                     Lp++;
                     l++;
                    }
                     arr[c]=ch;
                     arr[l]='\0';
                     //printf("%c", ch);

            gotoxy(col,row);
            printf("                 ");
            gotoxy(col,row);
            printf("%s",arr);
                     c++;
                    }
                break;
            }
            }


    }while(flag==1);
    return arr;
}
void getData(int i, struct Employee* empArr){
     printf("Employee %i\n",i+1);
     printf("id: %i\t\t",empArr[i].id);
     printf("Name: ");
     puts(empArr[i].name);
     printf("Age: %i\t\t",empArr[i].age);
     printf("Salary: %.1f\n",empArr[i].salary);
     printf("Commission: %.1f\t\t ",empArr[i].commission);
     printf("Deduction: %.1f \n",empArr[i].deduction);
     printf("net salary: %f \n\n", (empArr[i].salary+empArr[i].commission-empArr[i].deduction));
}
int main()
{

    struct Employee* empArr;
    int size=10;

    empArr= malloc(size * sizeof(struct Employee));
    char menus[8][30]={"New", "Display all" ,"Display by id" ,"Display by name" ,"Delete All" ,"delete by id" ,"Delete by name", "Exit"};
    int cursor = 0;
    int flag = 0;
    int myId;
    char data[6][20]={"id", "name", "age", "salary", "commission", "deduction"};
    char cont;
    char name[20];
    int index;
    do{
        system("cls");
        for(int i=0; i<8; i++){
            if(i==cursor){
                textattr(9);
            }else{
                textattr(7);
            }
            gotoxy(10,10+i);
            printf("%s", menus[i]);
        }
        char ch =getch();
        switch(ch){
            case -32:
                ch=getch();
                switch(ch){
                    case Up:
                        cursor--;
                        if(cursor<0){cursor=7;}
                    break;
                    case Down:
                        cursor++;
                        if(cursor>7){cursor=0;}
                    break;
                    case End:
                        cursor=7;
                    break;
                    case Home:
                        cursor=0;
                    break;
                }
            break;
            case Enter:
                switch(cursor){
                    case 0:
                        do{
                            system("cls");
                            printf("choose index between 0 and 9\n");
                            scanf("%i", &index);
                            _flushall();
                            system("cls");
                            for(int i=0; i<6; i++){
                                if(i%2==0){
                                    gotoxy(10,10+i+3);
                                }else{
                                    gotoxy(70,10+i+3);
                                }
                                printf("%s:",data[i]);
                            }

                             empArr[index].id=atoi(LineEditor(10,15,13,48,57));

                            _flushall();
                            strcpy(empArr[index].name,LineEditor(10,75,14,97,122));

                            _flushall();

                            empArr[index].age=atoi(LineEditor(3,15,15,48,57));

                            empArr[index].age=atof(LineEditor(10,78,16,48,57));

                            empArr[index].commission=atof(LineEditor(10,22,17,48,57));

                            empArr[index].commission=atof(LineEditor(10,81,18,48,57));

                            getch();
                            printf("Do you want to continue y or no? ");
                            cont=getch();
                        }while(cont=='y');
                    break;
                    case 1:
                        system("cls");
                        for(int i=0; i<10; i++){
                            if(empArr[i].salary){
                                getData(i, empArr);
                                printf("======================================\n");
                            }
                        }
                        getch();
                    break;
                    case 2:
                        system("cls");
                        do{
                            printf("Enter your id\n");
                            scanf("%i", &myId);
                        }while(myId==0);
                        for(int i=0;i<10;i++){
                            if(myId==empArr[i].id){
                                    getData(i,empArr);
                            }
                        }
                        getch();
                    break;
                    case 3:
                        system("cls");
                        printf("Enter your name\n");
                        _flushall();

                        gets(name);
                        for(int i=0;i<10;i++){
                            if(strcmp(name,empArr[i].name)==0){
                                    getData(i,empArr);
                            }
                        }
                        getch();
                    break;
                    case 4:
                        system("cls");
                        for(int i=0;i<10;i++){
                            empArr[i].id=0;
                            empArr[i].name[0]='\0';
                            empArr[i].age=0;
                            empArr[i].salary=0;
                            empArr[i].commission=0;
                            empArr[i].deduction=0;
                        }
                    break;
                    case 5:
                        system("cls");
                         do{
                            printf("Enter your id\n");
                            scanf("%i", &myId);
                        }while(myId==0);
                        for(int i=0;i<10;i++){
                            if(myId==empArr[i].id){
                                empArr[i].id=0;
                                empArr[i].name[0]='\0';
                                empArr[i].age=0;
                                empArr[i].salary=0;
                                empArr[i].commission=0;
                                empArr[i].deduction=0;
                            }
                        }
                    break;
                    case 6:
                        system("cls");
                        printf("Enter your name\n");
                        _flushall();
                        gets(name);
                        _flushall();
                        for(int i=0;i<10;i++){
                            if(strcmp(name,empArr[i].name)==0){
                                empArr[i].id=0;
                                empArr[i].name[0]='\0';
                                empArr[i].age=0;
                                empArr[i].salary=0;
                                empArr[i].commission=0;
                                empArr[i].deduction=0;
                            }
                        }
                    break;
                    case 7:
                        flag=1;
                    break;
                }
            break;
            case Esc:
                flag=1;
            break;
        }
    }while(flag==0);
    return 0;
}
