#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "file.h"
//#include "file.c" 
int main(int argc ,char * argv[] )
{
        Student *std;
        std=(Student *)malloc(NB_MAX*sizeof(Student));
       
        menu();
        interface(std);

        free(std);
        return 0;
}




