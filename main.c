//LainHE

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

void returnFunc(void); // For back to main menu
void insertMaterial(void); // For add materials to stored file
void removeMaterial(void); // For delete materials in stored file
void updateMaterial(void); // For change materials' elements in stored file
void searchMaterial(void); // For find materials by given ID or Name
void listMaterial(void); // For display all materials
int  checkID(int); // For detect it is exist or not by given ID
int  replace(char*, char*); // For replace all context's space to underline (For store and read data)
int  replaceBack(char*, char*); // For replace all context's underline to space (For display data)

//File pointers
FILE *fp,*ft;
//Globe variables
char findMaterial, cont, cont2;

struct beforeChanges{
    char Name[200];
    char Author[200];
    char Publisher[200];
    char Type[100];
    char DateofPublish[100];
};
struct beforeChanges b;

struct Materials{
    int id;
    char Name[200];
    char Author[200];
    char Publisher[200];
    char Type[100];
    char DateofPublish[100];
};
struct Materials m;


int main(){
    system("cls");
    int s;

    printf("                                                             "
           "                                      Made by LainHE");
    puts("\n=================================================== MAIN MENU "
         "===================================================");
    puts("\n 1. Insert Material");
    puts("\n 2. Remove Material");
    puts("\n 3. Update Material");
    puts("\n 4. Search Material");
    puts("\n 5. List   Material");
    puts("\n 6. Close  Application");
    puts("\n============================================================"
         "=====================================================");
    printf("\nEnter your choice: ");

    scanf(" %d", &s);
    switch(s){
        case 1:
            insertMaterial();break;
        case 2:
            removeMaterial();break;
        case 3:
            updateMaterial();break;
        case 4:
            searchMaterial();break;
        case 5:
            listMaterial();break;
        case 6:
            exit(0);
        default:
            system("cls");
            printf("\n\aWrong entry! Please enter number 1 - 6\n");rewind(stdin);
            returnFunc();break;
    }
}


void insertMaterial(void){
    char ch;while((ch = getchar()) != '\n' && ch != EOF);
    system("cls");
    int t;

    printf("=================================================== Insert Materials "
           "===================================================\n");
    fp = fopen("db.txt", "a+");
    printf("Enter material ID         : ");
    scanf(" %d",&t);rewind(stdin);
    //Detect inputted ID is number rather than letter
    if(t>=1){} //Do nothing
    else{ //Reminder user have to input number and back to main menu
        printf("\n\aPlease only enter numbers");
        returnFunc();
    }

    if(checkID(t) == 0){
        printf("\n\aID already exists! Please enter different number");
        returnFunc();
    }
    m.id=t;

    printf("\nEnter material name       : ");
    scanf(" %[^\n]s", b.Name);replace(b.Name,m.Name);rewind(stdin);
    printf("\nEnter author name         : ");
    scanf(" %[^\n]s", b.Author);replace(b.Author,m.Author);rewind(stdin);
    printf("\nEnter publisher name      : ");
    scanf(" %[^\n]s", b.Publisher);replace(b.Publisher,m.Publisher);rewind(stdin);
    printf("\nPlease input date as DD/MM/YYYY as possible\nEnter date of publish     : ");
    scanf(" %[^\n]s", b.DateofPublish);replace(b.DateofPublish,m.DateofPublish);rewind(stdin);
    printf("\nPlease input type with Book\\Magazine\\Newspaper\\CD/DVD as possible"
           "\nEnter material type       : ");
    scanf(" %[^\n]s", b.Type);replace(b.Type,m.Type);rewind(stdin);


    fprintf(fp, "%d\t%s\t%s\t%s\t%s\t%s\n",\
    m.id, m.Name, m.Author, m.Publisher, m.DateofPublish, m.Type);
    printf("\nData saved");
    fclose(fp);
    a: //Loop
    printf("\nInsert one more material? (Y/N): ");
    scanf(" %s",&cont);
    switch(cont){
        case 'y':
            insertMaterial();break;
        case 'n':
            main();break;
        default: //reminder users have to input y or n and detect again
            system("cls");
            printf("\n\aPlease enter only Y or N");
            goto a;
    }
}


void removeMaterial(void){
    system("cls");
    int d;

    puts("================================================ Remove Materials "
         "===============================================");
    printf("Enter material ID to remove: ");
    scanf(" %d",&d);rewind(stdin);
    fp=fopen("db.txt","r+");
    while(fscanf(fp, "%d\t%s\t%s\t%s\t%s\t%s\n",\
    &m.id, b.Name, b.Author, b.Publisher, b.DateofPublish, b.Type) != EOF){
        if(m.id==d){
            printf("\n ====================================================="
                   "==========================================================");
            printf("\n ID               : %d",m.id);
            replaceBack(b.Name,m.Name);
            printf("\n Name             : %s",m.Name);
            replaceBack(b.Author,m.Author);
            printf("\n Author           : %s",m.Author);
            replaceBack(b.Publisher,m.Publisher);
            printf("\n Publisher        : %s",m.Publisher);
            replaceBack(b.DateofPublish,m.DateofPublish);
            printf("\n Date of Publish  : %s",m.DateofPublish);
            replaceBack(b.Type,m.Type);
            printf("\n Type             : %s",m.Type);
            puts("\n ========================================================"
                 "=======================================================");
            findMaterial = 't';
        }
    }
    if(findMaterial!='t'){
        printf("\n\aNo material found");
        returnFunc();
    }
    if(findMaterial=='t'){
        a: //Loop a
        printf("\nRemove material shown above? (Y/N): ");
        scanf(" %s",&cont);rewind(stdin);
        switch(cont){
            case 'y':
                ft=fopen("bu.txt","w+");  //Temporary file for remove
                rewind(fp);
                while(fscanf(fp, "%d\t%s\t%s\t%s\t%s\t%s\n",\
                &m.id, m.Name, m.Author, m.Publisher, m.DateofPublish, m.Type) != EOF){
                    if(m.id!=d){
                        fseek(ft,0,SEEK_CUR);
                        fprintf(ft, "%d\t%s\t%s\t%s\t%s\t%s\n",\
                        m.id, m.Name, m.Author, m.Publisher, m.DateofPublish, m.Type);
                    } //Write all data to bu(backup) except specified ID that user inputted
                }
                fclose(ft);fclose(fp);
                remove("db.txt");
                rename("bu.txt","db.txt"); //Replace the files
                printf("\n\nmaterial removed");
            b: //loop b under loop a
                printf("\nRemove another material? (Y/N): ");
                scanf(" %s",&cont2);
                switch(cont2){
                    case 'y':
                        system("cls");removeMaterial();break;
                    case 'n':
                        main();break;
                    default:
                        system("cls");printf("\n\aPlease enter only Y or N");
                        goto b;
                }
            case 'n':
                main();break;
            default:
                puts("\n\aPlease enter only Y or N");
                goto a;
        }
    }
}


void updateMaterial(void){
    char ch;while((ch = getchar()) != '\n' && ch != EOF);
    system("cls");
    int d, cp;

    puts("=================================================== Update Materials "
         "=================================================");
    fp=fopen("db.txt","r+");
    printf("\nEnter material ID to be edited: ");
    scanf(" %d",&d);rewind(stdin);
    if(checkID(d)==0){
//        cp = (ftell(fp));//Was use for check where is the begin of line that we want to update
        ft=fopen("bu.txt","w+");
        rewind(fp);
        while(fscanf(fp, "%d\t%s\t%s\t%s\t%s\t%s\n",\
        &m.id, b.Name, b.Author, b.Publisher, b.DateofPublish, b.Type) != EOF){
            if(m.id!=d){
                fseek(ft,0,SEEK_CUR);
                fprintf(ft, "%d\t%s\t%s\t%s\t%s\t%s\n",\
                m.id, b.Name, b.Author, b.Publisher, b.DateofPublish, b.Type);
            }else if (m.id==d) {
                fprintf(ft, "");
                printf("\n\n--------------------------");
                printf("\nThe material ID            : %d",m.id);
                replaceBack(b.Name,m.Name);

                printf("\n--------------------------");
                printf("\nOriginal Name is           : %s", m.Name);
                printf("\nEnter new Name             : ");scanf(" %[^\n]s",b.Name);
                replace(b.Name,m.Name);rewind(stdin);replaceBack(b.Author,m.Author);

                printf("\n--------------------------");
                printf("\nOriginal Author is         : %s", m.Author);
                printf("\nEnter new Author           : ");scanf(" %[^\n]s",b.Author);
                replace(b.Author,m.Author);rewind(stdin);replaceBack(b.Publisher,m.Publisher);

                printf("\n--------------------------");
                printf("\nOriginal Publisher is      : %s", m.Publisher);
                printf("\nEnter new Publisher        : ");scanf(" %[^\n]s",b.Publisher);
                replace(b.Publisher,m.Publisher);rewind(stdin);replaceBack(b.DateofPublish,m.DateofPublish);

                printf("\n--------------------------");
                printf("\nOriginal Date of Publish is: %s", m.DateofPublish);
                printf("\nPlease input date as DD/MM/YYYY as possible"
                       "\nEnter new Date of Publish  : ");scanf(" %[^\n]s",b.DateofPublish);
                replace(b.DateofPublish,m.DateofPublish);rewind(stdin);replaceBack(b.Type,m.Type);

                printf("\n--------------------------");
                printf("\nOriginal Type is           : %s", m.Type);
                printf("\nPlease input type with Book\\Magazine\\Newspaper\\CD/DVD as possible"
                       "\nEnter new Type             : ");scanf(" %[^\n]s",b.Type);
                replace(b.Type,m.Type);rewind(stdin);

                fprintf(ft, "%d\t%s\t%s\t%s\t%s\t%s\n",\
                d, m.Name, m.Author, m.Publisher, m.DateofPublish, m.Type);
            }
        }
        fclose(ft);fclose(fp);
//        printf("|%ld|\n",(ftell(fp)));//<- Use for check where fp is
//        fwrite(&m,sizeof(m),1,fp);

        remove("db.txt");
        rename("bu.txt","db.txt");
        puts("\nMaterial is updated");
        a:
        printf("\nUpdate one more material?(Y/N)");
        scanf(" %s",&cont);
        switch(cont){
            case 'y':
                updateMaterial();break;
            case 'n':
                main();break;
            default:
                system("cls");
                printf("\n\aPlease enter only Y or N");
                goto a;
        }
    }else{
        printf("\n\aNo material found");
        returnFunc();
    }
}


void searchMaterial(void){
    char ch;while((ch = getchar()) != '\n' && ch != EOF);
    system("cls");
    int d,c;

    puts("================================================ Search Materials "
         "===============================================");
    puts("\n 1. Search By ID");
    puts("\n 2. Search By Name");
    printf("\n\nEnter Your Choice: ");
    fp=fopen("db.txt","r+");
    rewind(fp); //Make sure file pointer is at beginning of file
    scanf(" %d", &c);rewind(stdin);
    switch(c){
        case 1:{
            system("cls");

            puts("================================================== Search by ID "
                 "=================================================");
            printf("\nEnter the material ID:");
            scanf(" %d",&d);rewind(stdin);
            if(d>=1){}
            else {
                printf("\n\aPlease only enter numbers");
                returnFunc();
            }

            while(fscanf(fp, "%d\t%s\t%s\t%s\t%s\t%s\n",\
            &m.id, b.Name, b.Author, b.Publisher, b.DateofPublish, b.Type) != EOF){
                if(m.id==d){
                    printf("\n =================================================="
                           "=============================================================");
                    printf("\n ID               : %d",m.id);
                    replaceBack(b.Name,m.Name);
                    printf("\n Name             : %s",m.Name);
                    replaceBack(b.Author,m.Author);
                    printf("\n Author           : %s",m.Author);
                    replaceBack(b.Publisher,m.Publisher);
                    printf("\n Publisher        : %s",m.Publisher);
                    replaceBack(b.DateofPublish,m.DateofPublish);
                    printf("\n Date of Publish  : %s",m.DateofPublish);
                    replaceBack(b.Type,m.Type);
                    printf("\n Type             : %s",m.Type);
                    puts("\n ===================================================="
                         "===========================================================");
                    findMaterial='t';
                }
            }
            if(findMaterial!='t'){
                puts("\n\n\aNo material Found");
                goto a;
            }
            a:
            printf("\nTry another search? (Y/N)");
            scanf(" %s",&cont);
            switch(cont){
                case 'y':
                    searchMaterial();break;
                case 'n':
                    main();break;
                default:
                    system("cls");
                    printf("\n\aPlease enter only Y or N");
                    goto a;
            }
        }
        case 2:{
            system("cls");
            char s[20];

            puts("================================================= Search by Name "
                 "================================================");
            printf("\nEnter material Name: ");
            scanf(" %[^\n]s",s);rewind(stdin);
            int e=0;
            while(fscanf(fp, "%d\t%s\t%s\t%s\t%s\t%s\n",\
            &m.id, b.Name, b.Author, b.Publisher, b.DateofPublish, b.Type) != EOF){
                replaceBack(b.Name,m.Name);
                if(strstr(m.Name,s)!=NULL){
                    printf("\n ==================================================="
                           "============================================================");
                    printf("\n ID               : %d",m.id);
                    printf("\n Name             : %s",m.Name);
                    replaceBack(b.Author,m.Author);
                    printf("\n Author           : %s",m.Author);
                    replaceBack(b.Publisher,m.Publisher);
                    printf("\n Publisher        : %s",m.Publisher);
                    replaceBack(b.DateofPublish,m.DateofPublish);
                    printf("\n Date of Publish  : %s",m.DateofPublish);
                    replaceBack(b.Type,m.Type);
                    printf("\n Type             : %s",m.Type);
                    puts("\n ====================================================="
                         "==========================================================");
                    e++;
                }
            }
            if(e==0){
                puts("\n\n\aNo material found");
                goto b;
            }
            b:
            printf("\nTry another search? (Y/N)");
            scanf(" %s",&cont2);
            switch(cont2){
                case 'y':
                    fclose(fp);
                    searchMaterial();break;
                case 'n':
                    fclose(fp);
                    main();break;
                default:
                    system("cls");
                    printf("\n\aPlease enter only Y or N");
                    goto b;
            }
        }
        default :
            printf("\n\aWrong entry! Please enter number 1 or 2\n");
            returnFunc();break;
    }
}


void listMaterial(void){
    char ch;while((ch = getchar()) != '\n' && ch != EOF);
    system("cls");
    int i=0;

    puts("================================================= Material List "
         "=================================================");
    puts(" \n\t\t\t\t\t\tORDER OF DISPLAY\n\t\t\t"
         "ID -> Material Name -> Author -> Publisher -> Date of Publish -> Type");
    puts("\n -----------------------------------------------------"
         "----------------------------------------------------------");
    fp=fopen("db.txt","r");
    rewind(fp);
    while(fscanf(fp, "%d\t%s\t%s\t%s\t%s\t%s\n",\
    &m.id, b.Name, b.Author, b.Publisher, b.DateofPublish, b.Type) != EOF){
//        fgetc(fp);
        printf("\n\t[%d]",m.id);
        replaceBack(b.Name,m.Name);
        printf("\t\"%s\"",m.Name);
        replaceBack(b.Author,m.Author);
        printf("\t\"%s\"",m.Author);
        replaceBack(b.Publisher,m.Publisher);
        printf("\t\"%s\"",m.Publisher);
        replaceBack(b.DateofPublish,m.DateofPublish);
        printf("\t%s",m.DateofPublish);
        replaceBack(b.Type,m.Type);
        printf("\t%s",m.Type);
        printf("\n\n");
        i++;
//        i=i+(sizeof(m.id)/4);
    }
    printf("Total materials = %d\n",i);
    fclose(fp);
    returnFunc();
}


int replace(char *char1,char *char2){
    while (*char1){
        if (*char1 != ' '){
            *char2 = *char1;
            char2++;
        }else{
            strcpy(char2, "_");
            char2++;
        }
        char1++;
    }
    *char2 = '\0';
    return 0;
}


int replaceBack(char *char1,char *char2){
    while (*char1){
        if (*char1 != '_'){
            *char2 = *char1;
            char2++;
        }else{
            strcpy(char2, " ");
            char2++;
        }
        char1++;
    }
    *char2 = '\0';
    return 0;
}


void returnFunc(void){
    printf("\nPress ENTER to return main menu");
    b:
    if(getch()==13) //Allow only use enter
        main();
    else
        goto b;
}


int checkID(int t){
    rewind(fp);
    while(fscanf(fp, "%d\t%s\t%s\t%s\t%s\t%s\n",\
    &m.id, b.Name, b.Author, b.Publisher, b.DateofPublish, b.Type) != EOF)
        if (m.id==t)
            return 0;  //Return 0 if material exists
    return 1; //Return 1 if it not
}