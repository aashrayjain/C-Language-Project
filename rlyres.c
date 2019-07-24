#include <stdio.h>
#include "conio2.h"
#include "rlyres.h"
#include "conio.h"
#include <string.h>
#include <ctype.h>
#include <malloc.h>
int enterchoice()
{
    clrscr();
    int choice,i;
    textcolor(YELLOW);
    gotoxy(20,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=0;i<=60;i++)
        printf("-");
    printf("Select an option");
    printf("\n1-View Trains\n2-Book Ticket\n3-View Ticket\n4-Search Ticket No\n5-View all bookings\n6-View Train Bookings\n7-Cancel Ticket\n8-Cancel Train\n9-Quit\n");
    printf("\nEnter choice:");
    scanf("%d",&choice);
    return choice;
}

void  add_trains()
{
    FILE *fp;
    fp=fopen("h:\\railway reservation system\\alltrains.dat","rb");
    if(fp==NULL)
    {
    Train alltrains[4]={
    {"123","BPL","GWA",2100,1500},
    {"546","BPL","DEL",3500,2240},
    {"345","HBJ","AGR",1560,3360},
    {"896","HBJ","MUM",4500,3360}
    };
    fp=fopen("h:\\railway reservation system\\alltrains.dat","wb");
    fwrite(alltrains,4*sizeof(Train),1,fp);
    printf("file saved successfully\n");
    getch();
    fclose(fp);
    }
    else
    {
        printf("file already saved\n");
        getch();
        fclose(fp);
    }
}

void view_trains()
{
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FAIR\tSECOMD AC FAIR\n");
    for(i=0;i<=60;i++)
        printf("-");
    FILE *fp=fopen("h:\\railway reservation system\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp))
          printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    printf("\n\n\n\n");
    fclose(fp);
}

int check_train_no(char *trainno)
{
    FILE *fp;
    fp=fopen("h:\\railway reservation system\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        if(strcmp(trainno,tr.train_no)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

Passenger * get_passenger_details()
{
    clrscr();
    gotoxy(47,1);
    textcolor(GREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter Passenger name:");
    static Passenger psn;
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char *pos;
    pos=strchr(psn.p_name,'\n');
    *pos='\0';
    if(strcmp(psn.p_name,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,18);
        printf("RESERVATION CANCELLED!");
        getch();
        textcolor(YELLOW);
        return NULL;
    }


    int valid;
    printf("Enter gender(M/F):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,18);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,18);
            printf("RESERVATION CANCELLED!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(psn.gender!='M' && psn.gender!='F')
        {
           textcolor(LIGHTRED);
           gotoxy(1,18);
           printf("error! Gender should be M or F(in uppercase)");
           valid=0;
           getch();
           textcolor(YELLOW);
           gotoxy(19,2);
           printf(" \b");
           textcolor(YELLOW);
    }
    }while(valid==0);
    gotoxy(1,18);
    printf("\t\t\t\t\t\t\t");


    gotoxy(1,3);
    printf("Enter train Number:");
    do
        {
        fflush(stdin);
        scanf("%s",psn.train_no);
        if(strcmp(psn.train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,18);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,18);
            printf("Reservation Cancelled ");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_train_no(psn.train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,18);
            printf("Error!Invalid Train Number");
            getch();
            gotoxy(20,3);
            printf("\t\t\t\t\t\t");
            gotoxy(20,3);
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,18);
    printf("\t\t\t\t\t\t\t");



    gotoxy(1,4);
    printf("enter travelling class(First AC-F,Second AC-S):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
            gotoxy(1,18);
            textcolor(LIGHTRED);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,18);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(psn.p_class!='F' && psn.p_class!='S')
        {
           gotoxy(1,18);
           textcolor(LIGHTRED);
           printf("Error!Travelling class should be F or S(in uppercase)");
           valid=0;
           getch();
           gotoxy(48,4);
           printf("\t\t\t\t\t\t\t\t\t\t");
           gotoxy(48,4);
           textcolor(YELLOW);
    }
    }while(valid==0);
    gotoxy(1,18);
    printf("\t\t\t\t\t\t\t");


    gotoxy(1,5);
    printf("Enter address:");
    fflush(stdin);
    fgets(psn.address,30,stdin);
    pos=strchr(psn.address,'\n');
    *pos='\0';
    if(strcmp(psn.address,"0")==0)
    {
        gotoxy(1,18);
        textcolor(LIGHTRED);
        printf("\t\t\t\t\t\t\t");
        gotoxy(1,18);
        printf("RESERVATION CANCELLED!");
        getch();
        textcolor(YELLOW);
        return NULL;
    }



    textcolor(YELLOW);
    printf("Enter age:");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.age);
        if(psn.age==0)
        {
            gotoxy(1,18);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(1,18);
            textcolor(LIGHTRED);
            printf("RESERVETION CANCELLED!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(psn.age<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,18);
            printf("Error!Age should be positive");
            valid=0;
            getch();
            gotoxy(11,6);
            printf("\t\t\t\t\t\t\t");
            gotoxy(11,6);
            textcolor(YELLOW);
            printf(" \b");
        }
    }while(valid==0);
    gotoxy(1,18);
    printf("\t\t\t\t\t\t\t\t");
    gotoxy(1,7);


    printf("Enter mobile number:");
    do
    {
        fflush(stdin);
        scanf("%s",psn.mob_no);
        if(strcmp(psn.mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,18);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(1,18);
            printf("Resesrvation cancelled");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_mob_no(psn.mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,18);
            printf("Error invalid mobile number");
            getch();
            gotoxy(21,7);
            printf("\t\t\t\t\t\t\t");
            gotoxy(21,7);
            textcolor(YELLOW);
        }
    }while(valid==0);

    return &psn;
}


int check_mob_no(char *p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;

    while(*p_mob!='\0')
    {
        if(isdigit(*p_mob)==0)
            return 0;
        p_mob++;
    }
    return 1;
}

int get_booked_ticket_count(char *train_no,char tc)
{
    FILE *fp;
    Passenger pr;
    int count=0;
    fp=fopen("h:\\railway reservation system\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0 && pr.p_class==tc)
        {
            ++count;
        }
    }
    fclose(fp);
    return count;
}


int last_ticket_no()
{
    FILE *fp;
    fp=fopen("h:\\railway reservation system\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    fseek(fp,-1*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticket_no;
}

int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==2)
    {
        textcolor(LIGHTRED);
        printf("All seats booked in train no. %s in %c class\n\n\n",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no()+1;
    p.ticket_no=ticket_no;
    FILE *fp;
    fp=fopen("h:\\railway reservation system\\allbookings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("sorry!file cannot be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return p.ticket_no;
}


int accept_ticket_no()
{
    printf("Enter ticket no:");
    int valid;
    int ticket_no;
    do
    {
        scanf("%d",&ticket_no);
        valid=1;
        if(ticket_no==0)
        {
            gotoxy(1,18);
            textcolor(LIGHTGREEN);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(1,18);
            printf("Cancelling input!!");
            getch();
            textcolor(YELLOW);
            return 0;
        }
        if(ticket_no<0)
        {
            valid=0;
            gotoxy(1,18);
            textcolor(LIGHTRED);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,18);
            printf("Error!Ticket number should be positive!!");
            getch();
            gotoxy(16,1);
            printf("\t\t\t\t\t\t\t");
            gotoxy(16,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return ticket_no;
}

void view_ticket(int ticket_no)
{
    FILE *fp;
    Passenger pr;
    fp=fopen("h:\\railway reservation system\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet!");
        return;
    }
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticket_no==ticket_no)
        {
            printf("\nNAME:%s\nGENDER:%c\nTRAIN NO:%s\nCLASS:%c\nADDRESS:%s\nAGE:%d\nMOBILE NO:%s\nTICKET NO:%d\n",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticket_no);
            printf("\n\n");
            found=1;
            break;
        }
    }
    if(!found)
    {
        textcolor(LIGHTRED);
        printf("No details of ticket no %d found!",ticket_no);
    }
    fclose(fp);
}

int cancel_ticket(int ticket_no)
{
    FILE *fp1=fopen("h:\\railway reservation system\\allbookings.dat","rb+");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");
        return -1;
    }
    FILE *fp2;
    fp2=fopen("h:\\railway reservation system\\temp.dat","wb+");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticket_no!=ticket_no)
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
        else
        {
            found=1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("h:\\railway reservation system\\temp.dat");
    }
    else
    {
        remove("h:\\railway reservation system\\allbookings.dat");
        rename("h:\\railway reservation system\\temp.dat","h:\\railway reservation system\\allbookings.dat");
    }
    return found;
}

char * accept_mob_no()
{
    static char mob_no[11];    //always put static when address of local variable is returned
    int valid;
    printf("Enter mobile number:");
    do
    {
        fflush(stdin);
        scanf("%s",mob_no);
        if(strcmp(mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,18);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,18);
            printf("Cancelling input!!!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,18);
            printf("Error!invalid mobile no.");
            getch();
            gotoxy(21,1);
            textcolor(YELLOW);
            printf("\t\t\t\t\t\t");
            gotoxy(21,1);
        }
    }while(valid==0);
    return mob_no;
}

int * get_ticket_no(char *p_mob_no)
{
    int count=0;
    FILE *fp=fopen("h:\\railway reservation system\\allbookings.dat","rb");
    if(fp==NULL)
    {
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;
    }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    int *p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            *(p+i)=pr.ticket_no;
            i++;
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}

void view_all_tickets(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry no tickets booked against mobile no. %s",pmob_no);
        textcolor(WHITE);
        printf("\n\nPress any key to go back to the main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are the tickets booked for mobile no %s",pmob_no);
    int i;
    printf("\n-------------------------------------------------------------");
    printf("\n\nticket no\n");
    for(i=0;*(pticket_no+i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));
    textcolor(WHITE);
    printf("\n\nPress any key to go back to the main screen");
    free(pticket_no);
    getch();
}

char * accept_train_no()
{
    int valid=0;
    static char tr_no[10];
    gotoxy(45,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter Train No:");
    do
    {
        fflush(stdin);
        scanf("%s",tr_no);
        if(strcmp(tr_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,18);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(1,18);
            printf("Cancelling Input....");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_train_no(tr_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,18);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,18);
            printf("Error!Invalid Train No.");
            getch();
            textcolor(YELLOW);
            gotoxy(16,1);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(16,1);
        }
    }while(valid==0);
    return tr_no;
}

int cancel_train(char *train_no)
{
    FILE *fp1=fopen("h:\\railway reservation system\\allbookings.dat","rb+");
    if(fp1==NULL)
    {
        printf("No bookings done yet!!!");
        return 0;
    }
    Passenger pr;
    int flag=0;
    FILE *fp2=fopen("h:\\railway reservation system\\temp.dat","wb+");
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(strcmp(pr.train_no,train_no)!=0)
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
        else
            flag=1;
    }
    fclose(fp1);
    fclose(fp2);
    if(flag==0)
    {
        remove("h:\\railway reservation system\\temp.dat");
        return 0;
    }
    else
    {
        remove("h:\\railway reservation system\\allbookings.dat");
        rename("h:\\railway reservation system\\temp.dat","h:\\railway reservation system\\allbookings.dat");
        return 1;
    }
}


void view_bookings(char *train_no)
{
    clrscr();
    FILE *fp;
    int found=0,i;
    fp=fopen("h:\\railway reservation system\\allbookings.dat","rb");
    if(fp==NULL)
    {
        printf("File is not there..");
        return NULL;
    }
    Passenger pr;
    printf("TICKET NO   CLASS    NAME\t   GENDER   AGE\t  MOBILE NO\n");
    for(i=1;i<=61;i++)
        printf("-");
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(train_no,pr.train_no)==0)
        {
            printf("%d\t    %c\t     %s",pr.ticket_no,pr.p_class,pr.p_name);
            gotoxy(35,row++);
            printf(" %c\t    %d\t  %s\n",pr.gender,pr.age,pr.mob_no);
            found=1;
        }
    }
    if(!found)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("\nNo details of given train no %s found!!",train_no);
    }
    textcolor(WHITE);
    printf("\n\nPress any key to go back to the main screen");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}

void view_all_bookings()
{
    clrscr();
    FILE *fp=fopen("h:\\railway reservation system\\allbookings.dat","rb");
    if(fp==NULL)
    {
        printf("No bookings done yet!!!");
        return;
    }
    Passenger pr;
    printf("TICKET NO   CLASS    NAME\t   GENDER   AGE\t  MOBILE NO\n");
    for(int i=1;i<=61;i++)
        printf("-");
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
            printf("%d\t    %c\t     %s",pr.ticket_no,pr.p_class,pr.p_name);
            gotoxy(35,row++);
            printf(" %c\t    %d\t  %s\n",pr.gender,pr.age,pr.mob_no);
    }
    textcolor(WHITE);
    printf("\n\nPress any key to go back to the main screen");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}
