char *satz(char *old)
{
        char *new=NULL;
        if (old!=NULL)
        {
            new=(char*)malloc((strlen(old)+1)*sizeof(char));
            if (new!=NULL)
            {
                strcpy(new,old);
            }
        }  
    return new;
    }
//---------------------------------------------------------------------
    void animation(char *mess)
{
	int i;
	for(i = 0; i < strlen(mess); i++)
	{
		printf("%c",mess[i]);
		fflush(stdout);
		usleep(50000);                             // Pause de 50 millisecondes entre chaque caractère
	}
}
//----------------------------------------------------------------
char *string(int nbr)
{
	char *tab=NULL;
	tab=(char*)malloc(nbr*sizeof(char));
	if(tab == NULL)
	{
		printf("Erreur d'allocation");
		exit(1);
	}
	return (tab);
}
//----------------------------------------------------------------
//----------------------------------------------------------------
void helpMe()
{
    printf("Your choice should be in 1 or 2 or 3 or 4  or 5\n");
    printf("You can't combine these options\n into different state like \n");
    printf("like 12 (or 21) for 1 and 2... ");
    printf("Please enter the number in menu \n");

}
//----------------------------------------------------------------
int  quit()
{
        
    printf("Thank you!!!\n");
    printf("See you soon ...\n");
    system("sleep 4");
    system("clear");

    return 0;
}
//----------------------------------------------------------------
    int getnb()
    {
        int n;
        int lim=0;
        char* input;
        input=string(50);
        while( lim<3)
        {
            printf("Your choice :\n");
            printf("=>");
            fgets(input,sizeof(input),stdin);
            char *endptr;
            n=strtol(input,&endptr,10);  
            if (endptr != input && *endptr =='\n' && n>0 && n<=6)
            {
                lim=2;
                return n;
            }
            else
            {
                helpMe();
                lim++;
            }
        } 
        free(input);
    }
//----------------------------------------------------------------
void creatFile()
{
    system("cut -d' ' -f2,3,4,5,6 listeL1.csv >ficfname ");
    system("cut -d' ' -f1 listeL1.csv >ficname ");
}
//----------------------------------------------------------------

void getname(Student *std)
{
    int i=1;
    FILE *fnom;
    fnom=openr("ficname");
    char *ligne;
    ligne=(char*)malloc(256*sizeof(char));
    while(fgets(ligne,255,fnom)!=NULL)
    {
       ligne[strcspn(ligne, " \n")] = '\0';
       strcpy(std[i].name,ligne);
       i++;
    }
    fclose(fnom);
    remove ("ficname");

}

void getfname(Student *std)
{
    int i=1;
    FILE *fnom;
    fnom=openr("ficfname");
    char *ligne;
    ligne=(char*)malloc(256*sizeof(char));
    while(fgets(ligne,256,fnom)!=NULL)
    {
       ligne[strcspn(ligne, "\n")] = '\0';
       strcpy(std[i].fname,ligne);
       std[i].number=i;
       std[i].OK=ABSENT;
       std[i].check=NO;
       i++;
    }
    fclose(fnom);
    remove ("ficfname");

}
//----------------------------------------------------------------
    int getNumero()
    {
        int n;
        int lim=0;
        char *input;
        input=string(50);
        while( lim<3)
        {
            printf("Your Number :\n");
            printf("=>");
            fgets(input,sizeof(input),stdin);
            char *endptr;
            n=strtol(input,&endptr,10);
            if(n<=0)  
            printf("Please enter a Positif number\n");
            if (endptr != input && *endptr =='\n' && n>0 && n<NB_MAX)
            {
                lim=2;
                return n;
            }
            else
            {
                //helpMe();
                lim++;
                if (lim==2)
                    printf("to much error \n Thr application quit with ERROR!!!!\n");

            }
        }  
        free(input); 
    }

    
//----------------------------------------------------------------
void stdOK(int std,char *str )
{
        if(std==YES)
            strcpy(str,"YES");
        else if(std==NO)
            strcpy(str,"NO");
        else if(std==PERSO)
            strcpy(str,"PERSO");
        else if(std==ABSENT)
            strcpy(str,"ABSENT");
        
}
//----------------------------------------------------------------
//----------------------------------------------------------------
void fchoix()
{
    printf("If you want to use a panasonic machine enter %d\n",YES);
    printf("If you won't use  machine enter %d\n",NO);
    printf("If you want to use your personal machine enter %d\n",PERSO);
    printf("to cancel %d\n",ABSENT );
   animation("    ******************   \n\n");

}
//----------------------------------------------------------------
void fchoix1()
{
    printf("Use panasonic machine  : %d \nDont use machine:%d  \nUse personal machine  :%d \n",YES,NO,PERSO);
    printf("to cancel %d\n",ABSENT );
    animation("  ++++++++++++++++++++++++++++++  \n\n");
}

//----------------------------------------------------------------
 int  ByNumero(Student *std)
{  
   
    FILE *file_liste;
    file_liste=openw("presence");
   
      
    int n=getNumero();
    fprintf(file_liste, "<HTML>\n  <TITLE>\n </TITLE>\n <BODY>\n <TABLE border = 4>\n ");
    if(std[n].check==YES)
    {
        printf("Sorry,It's Already Checked !!\n");
        interface(std);
    }
    else
    {
    printf("%d] %s %s",std[n].number,std[n].name,std[n].fname);
    std[n].OK=getnbOK();
    std[n].check=YES;
      char str[50];
      stdOK(std[n].OK,str);
      
        fprintf(file_liste," <TR> <TD>%d]</TD> <TD>%s</TD>  <TD>%s</TD>                         <TD> %s  </TD>[ <TD>%s </TD>]  </TR>  \n",std[n].number,std[n].name,std[n].fname,str,__TIME__);
  }
  fprintf(file_liste, "</TABLE></BODY>\n </HTML>\n");
  interface(std);
}
//----------------------------------------------------------------------------------
/* void  ByName(Student t1[])
{
    FILE *fr;
	fr=openw("presence");
	int j=1;
	int choice;
	char Sname[MAX_NAME];

		printf("Please entry your name (or firstname):");
		scanf("%s",Sname);
		for (int i=0;i<strlen(Sname);i++)
		{
			Sname[i]=toupper(Sname[i]); //on change sname en majuscule pour etre comparable
		}
		int ok=0;
		for(j=1;j<NB_MAX;j++)
		{
			for (int i=0;i<strlen(t1[j].fname);i++)
			{
				t1[j].fname[i]=toupper(t1[j].fname[i]); //on change  en majuscule le prenom pour etre comparable
			}
			if(strcmp(Sname,t1[j].fname)==0 || strcmp(Sname,t1[j].name)==0) //on les compare
			{
				ok=1;
				for (int i=1;i<strlen(t1[j].fname);i++)
					t1[j].fname[i]=tolower(t1[j].fname[i]);
                

        
		 */

//-----------------------------------------------------------
void ByName(Student *std)
{
        
        FILE *file_liste;
		file_liste=openw("presence.html");
        char *ligne;
        int i;
        int ok=0;
        ligne=(char*)malloc(256*sizeof(char));

        printf("name (or firstname):");
        fgets(ligne,256,stdin);
        
       ligne[strcspn(ligne, "\n")] = '\0';
       fprintf(file_liste, "<HTML>\n  <TITLE>\n </TITLE>\n <BODY>\n <TABLE border = 4>\n ");
for (int i=0;i<strlen(ligne);i++)
	{
		ligne[i]=toupper(ligne[i]); //on change sname en majuscule pour etre comparable
	}

        for(i=1;i<NB_MAX;i++)
        {
          //  printf ("%s%s%s",ligne,std[i].name,std[i].fname);
          for (int j=0;j<strlen(std[i].fname);j++)
			{
				std[i].fname[j]=toupper(std[i].fname[j]); //on change  en majuscule le prenom pour etre comparable
			}
          

            if( strcmp(ligne,std[i].name)==0 || 
                strcmp(ligne,std[i].fname)==0||
                strcasecmp(ligne,std[i].name)==0||
                strcasecmp(ligne,std[i].fname)==0||
                strstr(std[i].name,ligne)!=NULL|| 
                strstr(std[i].fname,ligne)!=NULL
           /* strcasestr(std[i].name,ligne)!=NULL||
                strcasestr(std[i].fname,ligne)!=NULL*/)  
             {   
                for (int j=1;j<strlen(std[i].fname);j++)
					std[i].fname[j]=tolower(std[i].fname[j]);
            ok=1;
            break;
             }

        }
    free(ligne);
    if (ok==1)
     {  
		 if(std[i].check != YES)
		  {  
		
				fchoix1();
                printf("%d]%s %s\n",std[i].number,std[i].name,std[i].fname);
                std[i].OK=getnbOK();
                char str[50];
                std[i].check=YES;
                stdOK(std[i].OK,str);
                fprintf(file_liste,"<TR> <TD>%d]<TD> <TD>%s<TD>  <TD>%s<TD>                          <TD> %s <TD>[<TD>%s <TD>] </TR> \n",std[i].number,std[i].name,std[i].fname,str,__TIME__);
           } 
           else
           {
			   printf("Sorry,It's Already Checked §§\n");
				interface(std);
            }
       } 
    else
    {
        printf("%s is not found\n",ligne);
      }
      fprintf(file_liste, "</TABLE></BODY>\n </HTML>\n");
    fclose(file_liste);
    interface(std);
} 

//----------------------------------------------------------
void normal(Student *std)
{
    int i,begin=1,end=NB_MAX;
    FILE *file_liste;
    file_liste=openw("presence.html");
    printf("Start by the number :\n");
    begin=getNumero();
    printf("and End with the number :\n");
    end=getNumero(); 
    char *str;
    str=string(50);
    fprintf(file_liste,"%s\n",__DATE__);
     fprintf(file_liste, "<HTML>\n  <TITLE>\n </TITLE>\n <BODY>\n <TABLE border = 4>\n ");
    for (i=begin;i<=end;i++)
    {
    
        if(std[i].check==YES)
        {
            char mess[100];
            strcpy(mess,"\n!!! Sorry,It's Already Checked !!!\n");
            animation(mess);
            interface(std);
        }
    else
    {
        printf("%d] %s %s \n",std[i].number,std[i].name,std[i].fname);
        std[i].OK=getnbOK();
        std[i].check=YES;
        stdOK(std[i].OK,str);
        fprintf(file_liste,"<TR><TD>%d]</TD> <TD> %s</TD>  <TD>%s</TD>                           <TD>%s</TD>[<TD>%s</TD>] </TR> \n",std[i].number,std[i].name,std[i].fname,str,__TIME__);
    }   
  
   // fprintf(file_liste,"-----------------------------------------------------------------------------------------------\n");
    
    }
      fprintf(file_liste, "</TABLE></BODY>\n </HTML>\n");
    fclose(file_liste);
    free(str);
    interface(std);
}
//----------------------------------------------------------------
//----------------------------------------------------------------

void menu()
{
        
    printf("______________________________________\n");
    animation("    *** WELCOME TO THIS APP ***       \n");
    system("sleep 2");
    printf("______________________________________\n") ;
    animation(" +++ DEVELOPED BY Die TechPro +++     \n");
    printf("______________________________________\n");
    system("sleep 3");
    system("clear");
}
//----------------------------------------------------------------
void menuUs(Student *std)
{
    printf("    ++++++++++++++++++++++++++++++++++\n");
    printf("|\tCheckPC v1.1                    \t|\n");
    printf("|\tBy Die TechPro'group            \t|\n");
    printf("|\tOur team members:               \t|\n");
    printf("|\t=>Nancia ,Karen,Mario,Nax,Isaia \t|\n");
    animation("|\temail us in:DieTechPro@gmail.com\t|\n");
    printf("|\t[4]:quit                         \t|\n");
    printf("|\t[5]:cancel                      \t|\n");
    printf("    ++++++++++++++++++++++++++++++++++\n");
    int n=getnb();
    int i=0;
    if(n==5)
        interface(std);
    else if(n==4)
        quit();
    else
    {
        animation("enter 4 (to Quit) or 5 (to cancel)\n");
        menuUs(std);
        i++;
        if (i==2)
            quit();
    }
}

//----------------------------------------------------------------
void allAbsent(Student *std)              
{
    animation("all ABSENT are:\n");
    printf("N°]  Nom            Prenom\n\n");
    int i;
    for (i=0;i<NB_MAX;i++)
    {
        if (std[i].OK==ABSENT)
        printf("%d] %s %s\n",std[i].number,std[i].name,std[i].fname);
    } 
    interface(std);
}       
 void allPerso(Student *std)              
{

    animation("all PERSO are:\n");
    printf("N°]  Nom            Prenom\n\n");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==PERSO)
        printf("%d] %s %s\n",std[i].number,std[i].name,std[i].fname);
    }
    interface(std);

}      
void allYes(Student *std)
{
    animation("all YES are:\n");
    printf("N°]  Nom            Prenom\n\n");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==YES)
        printf("%d] %s %s\n",std[i].number,std[i].name,std[i].fname);
    }
    interface(std);


}     
void allNo(Student *std)
{
    animation("all NO are:\n");
    printf("N°]  Nom            Prenom\n\n");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==NO)
        printf("%d] %s %s\n",std[i].number,std[i].name,std[i].fname);
    }   
    interface(std);
}
//----------------------------------------------------------------


void menuEvaluation(Student *std)
{
    printf("    -------------------------\n");
animation("To display :\n");
    printf("|\t[1]:All Absent    \t|\n"); 
    printf("|\t[2]:All Perso     \t|\n");
    printf("|\t[3]:All Yes       \t|\n");
    printf("|\t[4]:All No        \t|\n");
    printf("|\t[5]:cancel        \t|\n");
animation( "|\t[6]:On a file:    \t|\n");
    printf("    -------------------------\n");
    int n=getnb();
        switch(n)
        {
            case ABSENT1:
                allAbsent(std);
                break;

            case PERSO1:   
                allPerso(std);
                break;

            case YES1:
                allYes(std);
                break;

             case NO1:
                allNo(std);
                break;

             case FIC:

                    printf("    -------------------------\n");
                    animation("To write :\n");
                        printf("|\t[1]:All Absent    \t|\n"); 
                        printf("|\t[2]:All Perso     \t|\n");
                        printf("|\t[3]:All Yes       \t|\n");
                        printf("|\t[4]:All No        \t|\n");
                        printf("|\t[5]:cancel        \t|\n");
                        printf("    -------------------------\n");
                        int m=getnb();
                            switch(m)
                            {
                                case ABSENT1:
                                    fallAbsent(std);
                                    break;

                                case PERSO1:
                                    fallPerso(std);
                                    break;

                                case YES1:
                                    fallYes(std);
                                    break;

                                case NO1:
                                    fallNo(std);
                                    break;
                                case CANCEL1: 
                                    menuEvaluation(std);
                                    break;  
                            }


            case CANCEL1: 
                interface(std);
                break;        
        } 
}

//----------------------------------------------------------------

void interface(Student *std)
{
        creatFile();
        getname(std);
        getfname(std);
    printf("    -------------------------\n");
    printf("|\t[1]: Normal Mode \t|\n"); 
    printf("|\t[2]: Searching   \t|\n");
    printf("|\t[3]: Evaluation  \t|\n");
    printf("|\t[4]: Quit        \t|\n");
    printf("|\t[5]: About Us..  \t|\n");
    printf("    -------------------------\n");
    int n=getnb();
        switch(n)
        {
            case NORMAL_MODE:
                fchoix();
                normal(std);
                break;
            case SEARCHING:
                menuSearching(std);
                break;

            case EVALUATION:
                menuEvaluation(std);
                break;
            case QUIT:
                quit();
                break;
            case ABOUT_US: 
                menuUs(std);
                break;
            
        }
        
}
//---------------------------------------------------------------

//---------------------------------------------------------------
void fallAbsent(Student *std)              
{
    char *output_filename;
        output_filename=string(256);
        printf("please entry the file name: ");
        fgets(output_filename,256,stdin);
    FILE *file = openw(output_filename);

    fprintf(file,"%s %s\n",__DATE__,__TIME__);
    fprintf(file,"all ABSENT are:\n");
    fprintf(file,"N°]  Nom            Prenom\n\n");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==ABSENT)
        fprintf(file,"%d] %s %s\n",std[i].number,std[i].name,std[i].fname);
    }
    fprintf(file,"\t\n----------------------------------\n");
    printf("A new evaluation file ALL ABSENT created <<%s>>\n", output_filename);
    free(output_filename);
    fclose(file);
    
}       
 void fallPerso(Student *std)              
{
    char *output_filename;
        output_filename=string(256);
        printf("please entry the file name: ");
        fgets(output_filename,256,stdin);
    FILE *file = openw(output_filename);

    fprintf(file,"%s %s\n",__DATE__,__TIME__);
    fprintf(file,"all PERSO are:\n");
    fprintf(file,"N°]  Nom            Prenom\n\n");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==PERSO)
        fprintf(file,"%d] %s %s\n",std[i].number,std[i].name,std[i].fname);
    }
    fprintf(file,"\t\n----------------------------------\n");
    printf("A new evaluation file ALL PERSO created <<%s>>\n", output_filename);
    free(output_filename);
    fclose(file);
    
   
}      
void fallYes(Student *std)
{
    char *output_filename;
        output_filename=string(256);
        printf("please entry the file name: ");
        fgets(output_filename,256,stdin);
    FILE *file = openw(output_filename);

    fprintf(file,"%s %s\n",__DATE__,__TIME__);
    fprintf(file,"all YES are:\n");
    fprintf(file,"N°]  Nom            Prenom\n\n");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==YES)
        fprintf(file,"%d] %s %s",std[i].number,std[i].name,std[i].fname);
    }
    fprintf(file,"\t\n----------------------------------\n");
    printf("A new evaluation file ALL YES created <<%s>>\n", output_filename);
    free(output_filename);
    fclose(file);
   
}     
void fallNo(Student *std)
{ 
        char *output_filename;
        output_filename=string(256);
        printf("please entry the file name: ");
        fgets(output_filename,256,stdin);
        FILE *file = openw(output_filename);

    fprintf(file,"%s %s\n",__DATE__,__TIME__);
    fprintf(file,"all NO are:\n");
    fprintf(file,"N°]  Nom            Prenom\n\n");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==NO)
        fprintf(file,"%d] %s %s\n",std[i].number,std[i].name,std[i].fname);
    }   
    fprintf(file,"\t\n----------------------------------\n");
    printf("A new evaluation file ALL NO created <<%s>>\n", output_filename);
    free(output_filename);
    fclose(file);
    
    
}
   
//-------------------------------------------------------------------------------------
void menuSearching(Student *std)
{
    fchoix();
    printf(" \n   ----------------------------------\n");
    
    animation("Searching \n");
    printf("|\t[1]:By numero                  \t|\n"); 
    printf("|\t[2]:By name  (or firstname)    \t|\n");
    printf("|\t[3]:cancel                     \t|\n");
    printf("|\t[4]:Quit                       \t|\n");
    printf("    ---------------------------------\n");
    int n=getnb();
        switch(n)
        {
             case BYNUMERO:
                ByNumero(std);
                break;

            case BYNAME:
                ByName(std);
                break;
 
            case QUIT1:
                quit();
                break;

            case CANCEL: 
                interface(std);
                break;        
        }
        

}

//----------------------------------------------------------------
FILE*  openr(char *str)
{
    FILE *f;
    f=fopen(str,"r");
    if(f==NULL)
    {
        printf("opening file ERROR \n");
        exit(1);
    }
    else
        return f;
}
//---------------------------------------------------------------------------------

FILE*  openw(char *str)
{
    FILE *f;
    f=fopen(str,"a");
    if(f==NULL)
    {
        printf("opening file ERROR \n");
        exit(1);
    }
    else
        return f;
}


//----------------------------------------------------------------
int getnbOK()
    {
        int n;
        Student *std;
        int lim=0;
        char *input;
        input=(char*)malloc(50*sizeof(char));
        while( lim<3 )
        {
            printf("Your choice :\n");
            printf("=>");
            fgets(input,sizeof(input),stdin);
           
            char *endptr;
            n=strtol(input,&endptr,10);
           
            if (endptr != input && *endptr =='\n' && n>=0 && n<4)
            {
                lim=2;
                if(n==3)
                    interface(std); 
                else
                    return n;
            }
            else
            {
                fchoix1();
                lim++;
                if(lim==2)
                    interface(std);
            }
        }  
        free(input);
    }

//----------------------------------------------------------------



