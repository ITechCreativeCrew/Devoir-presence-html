
#define MAX_NAME 256
#define MAX_FNAME 256
#define NB_MAX 76

//--------------------------------------------
enum User
{
    YES=0,NO=1,PERSO=2,ABSENT=3
};

enum caseBasics
{
    NORMAL_MODE=1,SEARCHING=2,EVALUATION=3,QUIT=4,ABOUT_US=5
};
enum caseSearcing
{
    BYNUMERO=1,BYNAME=2,CANCEL=3,QUIT1=4
};
enum caseEvalution
{
    ABSENT1=1,PERSO1=2,YES1=3,NO1=4,CANCEL1=5,FIC=6
};

struct Student
{
    char name[MAX_NAME];
    char fname[MAX_FNAME];
    enum User OK;
    int number;
    int check;  // pour verifier si c est deja cheque
};
typedef enum User User;
typedef struct Student Student;

FILE*  openr(char *str);
FILE*  openw(char *str);

//--------------------------------------------
void sep(FILE *file);
int Entre(FILE *f);
void fchoix();
void fchoix1();
void cp( );
void creatFile();

//--------------------------------------------
void interface(Student *std);
void menu(); //
int getnb(); // get nb between 1 and 5 correspond in  casebasics
int  quit();
void menuEvaluation(Student *std);
void menuSearching(Student *std);
void menuUs(Student *std);
//--------------------------------------------

int getNumero(); // to  get student number between 1 and NB_MAX
int  ByNumero(Student *std);
void ByName(Student t1[]);
void normal(Student *std);

//--------------------------------------------
// to display all  stusdent who have the same std.ok like allPerso
void allAbsent(Student *std);
void allPerso(Student *std); 
void allYes(Student *std);
void allNo(Student *std);

//--------------------------------------------
// like above but in one specific file
void fallAbsent(Student *std);  
void fallPerso(Student *std);
void fallYes(Student *std);
void fallNo(Student *std);
 void evaluation(Student *std);
//--------------------------------------------
int getnbOK();                  //  to get std.ok
void getname(Student *std);     //  to affect std.name  from the file ficname
void getfname(Student *std);    // to affect std.fname  from the file ficfname
void stdOK(int std,char *str );

void animation(char *mess);

#include "file.c" 