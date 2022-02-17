#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>
#include <locale.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define  BLACK   0
#define  DARK_BLUE   1
#define  DARK_GREEN   2
#define  DARK_CYAN   3
#define  DARK_RED   4
#define  DARK_MAGENTA   5
#define  DARK_YELLOW   6
#define  DARK_WHITE   7
#define  GRAY   8
#define  BLUE   9
#define  GREEN   10
#define  CYAN   11
#define  RED   12
#define  MAGENTA   13
#define  YELLOW   14
#define  WHITE   15

int hConsole;
int length;
int bend_no;
int len;
char key;
void record();
void load();
int life;
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();

struct coordinate{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    
    char key;

    Print();

    system("cls");

    load();

    length=5;

    head.x=25;

    head.y=20;

    head.direction=RIGHT;

    Boarder();

    Food(); //to generate food coordinates initially

    life=3; //number of extra lives

    bend[0]=head;

    Move();   //initialing initial bend coordinate

    return 0;

}

void Move()
{
    int a,i;

    do{

        Food();
        fflush(stdin);

        len=0;

        for(i=0;i<30;i++)

        {

            body[i].x=0;

            body[i].y=0;

            if(i==length)

            break;

        }

        Delay(length);

        Boarder();

        if(head.direction==RIGHT)

            Right();

        else if(head.direction==LEFT)

            Left();

        else if(head.direction==DOWN)

            Down();

        else if(head.direction==UP)

            Up();

        ExitGame();

    }while(!kbhit());

    a=getch();

    if(a==27)

    {

        system("cls");

        exit(0);

    }
    key=getch();

    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))

    {

        bend_no++;

        bend[bend_no]=head;

        head.direction=key;

        if(key==UP)

            head.y--;

        if(key==DOWN)

            head.y++;

        if(key==RIGHT)

            head.x++;

        if(key==LEFT)

            head.x--;

        Move();

    }

    else if(key==27)

    {

        system("cls");

        exit(0);

    }

    else

    {

        printf("\a");

        Move();

    }
}

void gotoxy(int x, int y)
{

 COORD coord;

 coord.X = x;

 coord.Y = y;

 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
 }
void load(){
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("Espere...");
    gotoxy(30,15);
    for(r=1;r<=20;r++){
    for(q=0;q<=100000000;q++);//to display the character slowly
    printf("%c",1028);}
    getch();
}
void Down()
{
    int i;
    for(i=0;i<=(head.y-bend[bend_no].y)&&len<length;i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}
void Delay(long double k)
{
    Score();
    long double i;
    for(i=0;i<=(10000000);i++);
}
void ExitGame()
{
    int i,check=0;
    for(i=4;i<length;i++)   //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            printf("\t\t\t   ACABOU TODAS AS VIDAS!\n\n\t\t\tBOA SORTE NA PR�XIMA VEZ!!!\n\n\t\Pressione qualquer tecla para sair...\n\n");
            record();
            exit(0);
        }
    }
}
void Food()
{
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)

            food.y+=11;
    }
    else if(food.x==0)/*to create food for the first time coz global variable are initialized with 0*/
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}
void Left()
{
    int i;
    for(i=0;i<=(bend[bend_no].x-head.x)&&len<length;i++)
    {
        GotoXY((head.x+i),head.y);
       {
                if(len==0)
                    printf("<");
                else
                    printf("*");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;

}
void Right()
{
    int i;
    for(i=0;i<=(head.x-bend[bend_no].x)&&len<length;i++)
    {
        //GotoXY((head.x-i),head.y);
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }
        /*body[len].x=head.x-i;
        body[len].y=head.y;*/
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}
void Bend()
{
    int i,j,diff;
    for(i=bend_no;i>=0&&len<length;i--)
    {
            if(bend[i].x==bend[i-1].x)
            {
                diff=bend[i].y-bend[i-1].y;
                if(diff<0)
                    for(j=1;j<=(-diff);j++)
                    {
                        body[len].x=bend[i].x;
                        body[len].y=bend[i].y+j;
                        GotoXY(body[len].x,body[len].y);
                        printf("*");
                        len++;
                        if(len==length)
                            break;
                    }
                else if(diff>0)
                    for(j=1;j<=diff;j++)
                    {
                        /*GotoXY(bend[i].x,(bend[i].y-j));
                        printf("*");*/
                        body[len].x=bend[i].x;
                        body[len].y=bend[i].y-j;
                        GotoXY(body[len].x,body[len].y);
                        printf("*");
                        len++;
                        if(len==length)
                            break;
                    }
            }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1;j<=(-diff)&&len<length;j++)
                {
                    /*GotoXY((bend[i].x+j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                        printf("*");
                   len++;
                   if(len==length)
                           break;
               }
           else if(diff>0)
               for(j=1;j<=diff&&len<length;j++)
               {
                   /*GotoXY((bend[i].x-j),bend[i].y);
                   printf("*");*/
                   body[len].x=bend[i].x-j;
                   body[len].y=bend[i].y;
                   GotoXY(body[len].x,body[len].y);
                       printf("*");
                   len++;
                   if(len==length)
                       break;
               }
       }
   }
}
void Boarder()
{	
   system("cls");
   int i;
   GotoXY(food.x,food.y);   /*displaying food*/
       printf("O");
   for(i=10;i<71;i++)
   {
       GotoXY(i,10);
           printf("=");
       GotoXY(i,30);
           printf("=");
   }
   for(i=9;i<31;i++)
   {
       GotoXY(10,i);
           printf("�");
       GotoXY(70,i);
       printf("�");
   }
}
void Print()
{
   //GotoXY(10,12);
   
system("color 2");   

printf("\n\n                                                                            \n"
       "  MMMMMMMMMMMMMM                                                                \n"
	   " IMMMMMMMMMMMMMM                                           HHH H                \n"
	   " IMMMM                                                     H  HH                \n"
	   " IMMM                 MMMMMM     MMMMMMMMM   IMMMMMMM     MMMMMMM       MMMMMM  \n"
	   " IMMM               MMMMMMMMM   MM       MM  IMMM   MMM  MMM   MMM    MMMMMMMMM \n"  
	   " IMMM              MMMM   MMMM  MM        M  IMM     MM  MM     MM   MMMM   MMMM\n"
	   " IMMM             MMMM     MMM  MM       MM  IMM    MM   MM     MM  MMMM     MMM\n"
	   " IMMM             MMM      MMM  MMMMMMMMM    IMMMMMM     MMMMMMMMM  MMM      MMM\n"
	   " IMMM             MMM      MMM  MM       MM  IMM   MM    MM     MM  MMM      MMM\n"
	   " IMMMM            MMMM    MMMM  MM        M  IMM    MM   MM     MM  MMMM    MMMM\n"  
	   " IMMMMMMMMMMMMMM   MMMMMMMMMM   MM       MM  IMM     MM  MM     MM   MMMMMMMMMM \n"  
	   "  MMMMMMMMMMMMMM    MMMMMMMM    MMMMMMMMMM   IMM     MM  MM     MM    MMMMMMMM  \n"
	   "________________________________________________________________________________\n");
printf("\nNNMD                                                                          \n"         
	   " NND$?M7          :ZO?N?N?=+?+M7                  I7+M++M?+M??N?MZ7I            \n"          
	   "   D$?M7?M??M+?M?$ZZO?N?N?=+?+M7I7?            .:???O+M??NMM+L__|Z7II\       __ \n"         
	   "     ?M7?M??M+?M?$ZZO?N?N?=+?+M.M7I7M++M+??++M+??M++M?+M??NMM++M?+MM?NM   ||    \n"       
	   "        ?M??M+?M?$Z:           :M7I?$???I?I???I?IM++M?+M??NM++M?+M??N7=====     \n"     
	   "                                        :?I???I?II7+M++M?+M??N?MZ7II7     ||__  \n"     
	   "                                                                                \n"     
	   "                                                                                \n"       
	   "");
    
    
    printf("\n                 {<Corre��es e Arte feita por Paulo Archanjo>} \n \t\t _____________________________________________\n\n\t\t  I Pressione qualquer tecla para continuar I\n");
    
  getch();
   system("cls");
   system("color 0F");
   printf("\t\t\t\t <<Instru��es>>\n________________________________________________________________________________\n");
   printf("\n-> Use as setas para mover a cobra.\n\n-> Voc� receber� alimentos nas v�rias coordenadas da tela que voc� deve comer.\nToda vez que voc� come um alimento, o comprimento da cobra aumenta em 1 elemento\ne, portanto, a pontua��o.\n\n-> Aqui voc� receber� tr�s vidas. Sua vida diminuir� quando voce bater na parede\nou no corpo da cobra.\n\n-> Voc� pode pausar o jogo no meio pressionando qualquer tecla. Para continuar o\njogo pausado, pressione qualquer outra tecla mais uma vez. \n\n-> Se voc� quiser sair, pressione ESC.\n\n-> Quando o Loading terminar, Pressione ENTER\n");
   printf("\n\nPressione qualquer tecla para jogar ...");
   if(getch()==27)
   exit(0);
}
void record(){
   char plname[20],nplname[20],cha,c;
   int i,j,px;
   FILE *info;
   info=fopen("record.txt","a+");
   getch();
   system("cls");
   printf("Insira seu Nome: ");
   scanf("%[^\n]",plname);
   //************************
   for(j=0;plname[j]!='\0';j++){ //to convert the first letter after space to capital
   nplname[0]=toupper(plname[0]);
   if(plname[j-1]==' '){
   nplname[j]=toupper(plname[j]);
   nplname[j-1]=plname[j-1];}
   else nplname[j]=plname[j];
   }
   nplname[j]='\0';
   //*****************************
   //sdfprintf(info,"\t\t\tPlayers List\n");
   fprintf(info,"Nome do Jogador: %s\n",nplname);
    //for date and time

   time_t mytime;
  mytime = time(NULL);
  fprintf(info,"Data de Jogatina: %s",ctime(&mytime));
     //**************************
     fprintf(info,"Pontua��o:%d\n",px=Scoreonly());//call score to display score
     //fprintf(info,"\nLevel:%d\n",10);//call level to display level
   for(i=0;i<=50;i++)
   fprintf(info,"%c",'_');
   fprintf(info,"\n");
   fclose(info);
   printf("Se desejar ver recordes passados, pressione 'y'\n");
   cha=getch();
   system("cls");
   if(cha=='y'){
   info=fopen("record.txt","r");
   do{
       putchar(c=getc(info));
       }while(c!=EOF);}
     fclose(info);
}
int Score()
{
   int score;
   GotoXY(20,8);
   score=length-5;
   printf("PONTUA��O : %d",(length-5));
   score=length-5;
   GotoXY(50,8);
   printf("VIDAS : %d",life);
   return score;
}
int Scoreonly()
{
int score=Score();
system("cls");
return score;
}
void Up()
{
   int i;
   for(i=0;i<=(bend[bend_no].y-head.y)&&len<length;i++)
   {
       GotoXY(head.x,head.y+i);
       {
           if(len==0)
               printf("^");
           else
               printf("*");
       }
       body[len].x=head.x;
       body[len].y=head.y+i;
       len++;
   }
   Bend();
   if(!kbhit())
       head.y--;
}
