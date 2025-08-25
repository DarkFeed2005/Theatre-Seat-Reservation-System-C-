//Brought to you by KpolitX - https://github.com/DarkFeed2005
#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
using namespace std;

//STRUCTURE
typedef struct{
        char showname[20];
        char date[12];
        char time[6];
        char gate[2];
}Show;
Show show={"Avengers: Endgame","22-4-2019","20:30","7"};

typedef struct{
        char name[30];
        char booking_ID[3];
        int seats;
}Seat;
Seat choice[4][5];  

void displaymenu();
void booking();
void cancel();
void seat();
void ticket();
void records();
void looping();
void exit_();
        
//Variables
int selection;  
int i;
int j;
int seats_num[20]={0};
int booking_ID=100;
int seatsAvailable=20;



int main(void)
{

        displaymenu();
        
        
        while(selection!=5)
        {
                looping();
        }
        
        return 0;
        
}
                
        void displaymenu()
        
		{
			
        printf("\n");
        printf("\t  THEATRE SEAT RESERVATION\n"
                  "\t=============================\n"
                  "\tNow Showing: Avengers:Endgame\n"
                  "\t=============================\n"
                  "\n\t1=> FOR BOOKINGS\n"
                  "\n\t2=> FOR CANCELLING RESERVATION\n"
                  "\n\t3=> VIEW TOTAL SEATS\n"
                  "\n\t4=> VIEW RECORDS\n"
                  "\n\t5=> EXIT\n\n");
 printf("\t=============================\n");
        printf("\tPlease Enter Any : ");
        scanf("%d",&selection);
        looping();
        return;
        }

        //looping()
        void looping()
        {       
        switch(selection)
                {
                case 1:
                        booking();
                        break;
                        
                case 2: 
                        cancel();
                        break;        
                case 3:
                        seat();
                        break;
                case 4:
                        records();
                        break;
                case 5:
                        exit_();
                        break;
                default:
                printf("\tInvalid selecion.Try again\n");
        }
        return;
        }
        
        //booking       
        void booking()
        {
                for(i=0;i<4;i++)
                        for(j=0;j<5;j++)  
                {                       
                printf("\n\tPlease enter seats number   : ");
                scanf("%d",&choice[i][j].seats);
                fflush(stdin);

                if(choice[i][j].seats<=seatsAvailable)
                {
                printf("\tPlease enter customer name : ");
                scanf("%[^\n]",choice[i][j].name);
                fflush(stdin);
                ticket();
                booking_ID++;
                        }
                seatsAvailable=seatsAvailable-choice[i][j].seats;
                
                system("pause");
                system("cls");
                displaymenu();  
                }
                if(seatsAvailable<0)
                {
                        printf("\n");
                        printf("\tSORRY, The Show Is Fully Booked\n");
                        printf("\t=================END=================\n\n");
                        displaymenu();
                }
                
                if(choice[i][j].seats>seatsAvailable)
                        {
                                printf("\n");
                                printf("\tThe show leave %d seats\n",seatsAvailable);
                                displaymenu();
                        }
        return;
        }
        
        void ticket()
        {
        printf("\n\n");
        
        printf("\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb THEATER BOOKED SEATS  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
        printf("\t===================================================================\n");
        printf("\t Booking ID : %d \t\t\tShow Name : %s\n",booking_ID,show.showname);
        printf("\t Customer  : %s\n",choice[i][j].name);
        printf("\t\t\t                              Date      : %s\n",show.date);
        printf("\t                                              Time      : %s\n",show.time);
        printf("\t                                              Hall      : %s\n",show.gate);
        printf("\t                                              Seats No. : %d%c  \n\n",i+1,j+65);
        printf("\t====================================================================\n");
        return;}

        //Brought to you by KpolitX - https://github.com/DarkFeed2005
        // cancel
         void cancel()
         {
              char cancelcustomername[80];
              cout<<"Enter customer name to be cancel:";
              cin>>cancelcustomername;
              for(int i=0; i<4 ; i++)
              {
                      for (int j =0 ; j<5; j++)
                      {
                          if (strcmp(choice[i][j].name , cancelcustomername) == 0)
                          {
                                         //seats_num++;
                                         choice[i][j].seats = 1 ;
                                         system("pause");
                                         system("cls");
                                         displaymenu();
                                         return ;
                          }
                      }
              }
          }
        //seat
        void seat()
        {       
                printf("  A   B   C       D     E\n");
                for(j=0;j<5;j++)
                {
                printf("%d  ",booking_ID); 
                }
                for(i=0;i<4;i++)
                {
                        printf("\n");
                        printf("%d\n",i+1);
                }
                system("pause");
                system("cls");
                displaymenu();
        return;
        }
        //Brought to you by KpolitX - https://github.com/DarkFeed2005

        void records()   //For Staff to View the Show's records
        {       
       
        
                printf("\t====================================\n");
                printf("\tDISPLAYING ALL RECORDS\n");  
                printf("\t====================================\n");
                printf("\tSeats Available left : %d \n",seatsAvailable);
                
                ticket();
                system("pause");
                system("cls");
                displaymenu();
                      
        return;
        }

        void exit_()
        {
        printf("\tThank you for using this system\n");
        exit(1);
        return;
        }
        //Brought to you by KpolitX - https://github.com/DarkFeed2005
        
        
        
        
    
