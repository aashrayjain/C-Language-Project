#include <stdio.h>
#include <stdlib.h>
#include "rlyres.h"
#include "conio.h"
#include "conio2.h"
int main()
{
    int choice;
    int a;
    int result;
    Passenger *ptr;
    char *tr;
    int ticket_no;
    char *pmob_no;
    int *pticket_no;
    add_trains();
    while(1)
    {
        choice=enterchoice();
        if(choice==9)
            exit(0);
    switch(choice)
    {
    case 1:
        clrscr();
        view_trains();
        textcolor(WHITE);
        printf("\npress any key to go back to the main screen");
        getch();
        clrscr();
        break;
    case 2:
        ptr=get_passenger_details();
        clrscr();
        if(ptr!=NULL)
           {
               ticket_no=book_ticket(*ptr);
               if(ticket_no==-1)
               {
                   textcolor(LIGHTRED);
                   printf("booking failed!");
               }
               else
                {
                    textcolor(LIGHTGREEN);
                    printf("ticket successfully booked\nyour ticket no. is %d",ticket_no);
                }
                textcolor(WHITE);
                printf("\nPress any key to go back to the main screen");
                getch();
                clrscr();
           }
        break;
    case 3:
        clrscr();
        ticket_no=accept_ticket_no();
        if(ticket_no!=0)
        {
            view_ticket(ticket_no);
        }
        textcolor(WHITE);
        printf("\nPress any key to go back to the main screen");
        getch();
        clrscr();
        break;
    case 4:
        clrscr();
        pmob_no=accept_mob_no();
        if(pmob_no!=NULL)
        {
            pticket_no=get_ticket_no(pmob_no);
            view_all_tickets(pmob_no,pticket_no);
        }
        clrscr();
        break;
    case 5:
        view_all_bookings();
        break;
    case 6:
        //train booking details
        clrscr();
        tr=accept_train_no();
        if(tr!=NULL)
        {
            view_bookings(tr);
        }
        clrscr();
        break;
    case 7:
        //remove()=stdio.h header file mai hai file delete ho jayegi  rename()=fun is used to remove the file.....
        clrscr();
        ticket_no=accept_ticket_no();
        if(ticket_no!=0)
            {
                result=cancel_ticket(ticket_no);
                if(result==0)
                   {
                        textcolor(LIGHTRED);
                        printf("Sorry! No tickets booked against ticket no %d",ticket_no);

                   }
                else if(result==1)
                    {
                        textcolor(LIGHTGREEN);
                        printf("Ticket no %d successfully cancelled!",ticket_no);
                    }
            textcolor(WHITE);
            printf("\n\nPress any key to go back to the main screen");
            }
            getch();
            clrscr();
        break;
    case 8:
        clrscr();
        tr=accept_train_no();
        a=cancel_train(tr);
        if(a==1)
        {
            printf("\nTrain no. %s successfully cancelled!!!",tr);
        }
        else
            printf("Train cannot be cancelled!!!");
        getch();
        break;
    default:
        textcolor(RED);
        printf("wrong choice!Try again\n");
        getch();
        clrscr();
    }
    }
    getch();
    return 0;
}
