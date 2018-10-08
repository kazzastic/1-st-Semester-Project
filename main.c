#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

void main_menu();
void login();
void delay(int);
void admin_menu();
void appointment();
void del_appointment();
void mod_appointment();
void search_appointment();
void list_appointment();
void add_doctor();
void del_doctor();
void mod_doctor();
void doctor_schedule();
void search_doctor();
void logout();
void xexit();
void count_appointment();
void reception_menu();
void rsearch_appointment();
void rsearch_doctor();
void rdoctor_schedule();
void rlist_appointment();
void rcount_appointment();
void gotoxy(int,int);

COORD coord={0,0};
void gotoxy(int x, int y)//function used for cursor positioning
{

  	coord.X=x;
    coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


struct Appointment {
   char name[30];
   int doc_type;
   int appointment_number ;
   float bill;
   int apid;
   char doc_name[30];
   char days[10];
   char doc_time[20];
}a,b;

struct Doctor {
   char name[30];
   int doc_type;
   char specialization[30];
   int age;
   char gender[10];
   char email[40];
   char day[7][10];
   char time[7][20];
   int doc_id;
   int nod;
}d;
int main()
{
    main_menu();
    return 0;
}
void main_menu(){

  system("cls");
  int choice;
  time_t t;
  time(&t);
  
  gotoxy(14,20);
  printf("Current date and time : %s",ctime(&t));
  gotoxy(0,0);
  printf("\n\n\n\n\t\t\t\t\tHospital Management System\n\n\n\t\t\t\t1) Login to Admin panel\n\t\t\t\t2) Reception\n\t\t\t\t3) Exit\n\n\t\t\t\tEnter your choice : ");
  scanf("%d",&choice);
  switch (choice) {
case 1 :
    login();
    break;
case 2:
    reception_menu();
case 3 :
    xexit();
default:
    {printf("Invalid input");
     exit(1);
    }
  }


}

void login(){
  system("cls");
  char uname[20],pswd[20],ch;
  int i=0;
  static int count=0;
  count++;

  printf("\n\n\n\n\t\t\t\t\tEnter login details \n\n\n\t\t\t\t Username : ");
  scanf(" %s",uname);
  printf("\n\n\t\t\t\t Password : ");
  while((ch=getch())!=13){

	if(ch==8){
    	if(i>0){

    	printf("\b \b");
    	i--;
    }
	}
	else{

	pswd[i++]=ch;
    printf("*");
   }

  }
  pswd[i]='\0';
  if((strcmp(uname,"user")==0)&&(strcmp(pswd,"pass")==0)){
    printf("\n\n\t\t\tWelcome to our Database.\n\n");
    delay(2);
    admin_menu();
  }
  else {
  	if(count>3){
  	printf("\n\nYou have entered the field more than 3 times incorrectly.\nReturning back in 3 seconds.\n");
  	delay(3);
  	main_menu();
   }
   else {

    printf("\n\n\t\t\tInvalid username or password.Try again.\n\n");
    delay(2);
    login();
   }
  }
  }

  void admin_menu(){
    system("cls");
    int choice;
    time_t t;
    time(&t);
  
    gotoxy(14,23);
    printf("Current date and time : %s",ctime(&t));
    gotoxy(0,0);
    printf("\n\n\t\t\t\t\tAdministration Panel\n\n\n\t\t\t\t1) Book an appointment\n\t\t\t\t2) Delete appointment\n\t\t\t\t3) Modify existing appointment\n\t\t\t\t4) Search Appointment Details\n\t\t\t\t5) List of Appointments\n\t\t\t\t6) Doctor's Schedule\n\t\t\t\t7) Add Doctor\n\t\t\t\t8) Delete Doctor\n\t\t\t\t9) Modify Doctor's record\n\t\t\t\t10) Search Doctor\n\t\t\t\t11) Total number of appointments\n\t\t\t\t12) Logout\n\t\t\t\t13) Exit\n\n\t\t\t\t Enter your choice : ");
    fflush(stdin);
	scanf("%d",&choice);
    switch(choice) {
 case 1:
    appointment();
    break;
 case 2:
    del_appointment();
    break;
 case 3:
    mod_appointment();
    break;
 case 4 :
    search_appointment();
    break;
 case 5:
    list_appointment();
	break;
 case 6 :
    doctor_schedule();
    break;
 case 7:
    add_doctor();
    break;
case 8:
    del_doctor();
    break;
case 9:
    mod_doctor();
    break;
case 10:
    search_doctor();
    break;
 case 11:
    count_appointment();
    break;
case 12:
    logout();
    break;
case 13:
    xexit();
    break;
 default :
    {
        printf("Invalid choice.Re-enter.\n");
        delay(2);
        admin_menu();
    }
    }
  }

  void appointment(){
     system("cls");

     static int acs,random=1357,ag,ap,ao;
     int ch,j=0,i,dd,cday,count=0;
     char choice,another;
     FILE *fa,*fd;
     fa = fopen("appointment.dat","rb+");
     fd = fopen("doctors.dat","rb+");
     if(fa==NULL){
        fa = fopen("appointment.dat","wb+");
        if(fa==NULL){
            printf("cannot open file.");
            exit(1);
        }
     }
     if(fd==NULL){
        fd = fopen("doctors.dat","wb+");
        if(fd==NULL){
            printf("cannot open file.");
            exit(1);
        }
     }
     while(fread(&a,sizeof(a),1,fa)==1){
        if(a.apid==random){
            random += 104;
        }
     }
     fseek(fa,0,SEEK_END);
     printf("Enter pateient name : \n");
     fflush(stdin);
     gets(a.name);
     while(1) {
     printf("\n1) Child specialist  2) General Physician  3) Psychiatrist  4) Orthodontist \nSelect Doctor's type :  ");
     scanf("%d",&ch);
     a.doc_type = ch;
     if(ch == 1){
        j=1;
        printf("\n\nList of Child specialist : \n");
        while(fread(&d,sizeof(d),1,fd)==1){
            if(strcmp(d.specialization,"Child specialist")==0){

                printf("%d) %s \n",j++,d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t%s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
            }
        }

        rewind(fd);
        printf("\nSelect Doctor : \n");
        scanf("%d",&dd);
         while(fread(&d,sizeof(d),1,fd)==1){

         	if(strcmp(d.specialization,"Child specialist")==0){
         		count++;
				 }
				 if(count==dd)
				 break;
		}
        strcpy(a.doc_name,d.name);
        printf("\nSelect Day : \n");
        scanf("%d",&cday);
        for(i=0;i<d.nod;i++){
            if(i + 1== cday){
                strcpy(a.days,d.day[i]);
                strcpy(a.doc_time,d.time[i]);
                break;
            }
        }
        a.bill = 500;
        a.appointment_number = ++acs;
        a.apid = random++;
        break;
     }
     else if(ch == 2){
            rewind(fd);
          j=1;
        printf("\n\nList of General Physician : \n");
        while(fread(&d,sizeof(d),1,fd)==1){
            if(strcmp(d.specialization,"General Physician")==0){

                printf("%d) %s \n",j++,d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
            }
        }

        rewind(fd);
        printf("\nSelect Doctor : \n");
        scanf("%d",&dd);
        while(fread(&d,sizeof(d),1,fd)==1){

         	if(strcmp(d.specialization,"General Physician")==0){
         		count++;
				 }
				 if(count==dd)
				 break;
		}
        strcpy(a.doc_name,d.name);
        printf("\nSelect Day : \n");
        scanf("%d",&cday);
        for(i=0;i<d.nod;i++){
            if(i + 1== cday){
                strcpy(a.days,d.day[i]);
                strcpy(a.doc_time,d.time[i]);
                break;
            }
        }
        a.bill = 600;
        a.appointment_number = ++ag;
        a.apid = random++;
        break;
     }
     else if(ch == 3){
          rewind(fd);
          j=1;
        printf("\n\nList of Psychiatrists : \n");
        while(fread(&d,sizeof(d),1,fd)==1){
            if(strcmp(d.specialization,"Psychiatrist")==0){

                printf("%d) %s \n",j++,d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
            }
        }

        rewind(fd);
        printf("\nSelect Doctor : \n");
        scanf("%d",&dd);
        while(fread(&d,sizeof(d),1,fd)==1){

         	if(strcmp(d.specialization,"Psychiatrist")==0){
         		count++;
				 }
				 if(count==dd)
				 break;
		}

        strcpy(a.doc_name,d.name);
        printf("\nSelect Day : \n");
        scanf("%d",&cday);
        for(i=0;i<d.nod;i++){
            if(i + 1== cday){
                strcpy(a.days,d.day[i]);
                strcpy(a.doc_time,d.time[i]);
                break;
            }
        }
        a.bill = 700;
        a.appointment_number = ++ap;
        a.apid = random++;
        break;
     }
     else if(ch == 4){
        rewind(fd);
          j=1;
        printf("\n\nList of Orthodontists : \n");
        while(fread(&d,sizeof(d),1,fd)==1){
            if(strcmp(d.specialization,"Orthodontist")==0){

                printf("%d) %s \n",j++,d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
            }
        }

        rewind(fd);
        printf("\nSelect Doctor : \n");
        scanf("%d",&dd);
        while(fread(&d,sizeof(d),1,fd)==1){

         	if(strcmp(d.specialization,"Orthodontist")==0){
         		count++;
				 }
				 if(count==dd)
				 break;
		}
        strcpy(a.doc_name,d.name);
        printf("\nSelect Day : \n");
        scanf("%d",&cday);
        for(i=0;i<d.nod;i++){
            if(i + 1== cday){
                strcpy(a.days,d.day[i]);
                strcpy(a.doc_time,d.time[i]);
                break;
            }
        }
        a.bill = 800;
        a.appointment_number = ++ao;
        a.apid = random++;
        break;
     }
     else {
        printf("\nInvalid Input.Enter again.\n\n");
     }
     }
     printf("\nPateint's Bill : %.3f ",a.bill);
     printf("\nPatient's Appointment Number : %d ",a.appointment_number);
     printf("\nDoctor : %s \nDay : %s ",a.doc_name,a.days);
     printf("\nAppointment id = %d ",a.apid);
     printf("\nConfirm appointment (y/n) ? : \n");
     choice = getche();
     if(choice == 'y'){
     fwrite(&a,sizeof(a),1,fa);
     fclose(fa);
     fclose(fd);
     printf("\n\nWant to Book another appointment (y/n) ? :\n");
     another = getche();
     if(another == 'y')
        appointment();
    else
      printf("\n\nReturning to Admin panel in 3 seconds.\n");
         delay(3);
         admin_menu();


     }
     else {
            fclose(fa);
            fclose(fd);
            printf("\n\nWant to Book another appointment (y/n) ? :\n");
            another = getche();
             if(another == 'y')
        appointment();
        else
        printf("\n\nReturning to Admin panel in 3 seconds.\n");
         delay(3);
         admin_menu();
     }
  }

void del_appointment() {
    system("cls");
    int id,flag=0;
    char ch;
    FILE *fa,*ft;
    fa = fopen("appointment.dat","rb");
    if(fa == NULL){
        printf("File cannot be open");
        exit(2);
    }
    ft = fopen("temp.dat","wb");
    printf("Enter the appointment id : \n");
    scanf("%d",&id);
    rewind(fa);
    while(fread(&a,sizeof(a),1,fa)==1){
        if(a.apid!=id){
          fwrite(&a,sizeof(a),1,ft);
        }
        else
            flag=1;
        }
    if(flag)
        printf("\nRecord deleted successfully.\n\n");
    else
        printf("\nNo record found associated with this appointment number in our database.\n\n");
    fclose(fa);
    fclose(ft);
    remove("appointment.dat");
    rename("temp.dat","appointment.dat");
    printf("\n\nWant to delete another appointment (y/n) ? : ");
    ch=getche();
    if(ch == 'y')
        del_appointment();
    else {
        printf("\n\nReturning to admin panel in 3  seconds.\n");
        delay(3);
        admin_menu();
    }
}


void mod_appointment(){
   system("cls");
   FILE *fa,*fb,*fd;
   static int random = 32012;
   int temp,flag=0,ch,nn,j,dd,cday,i,count=0;
   long int ssize = sizeof(a);
   char cc,another;
   fa = fopen("appointment.dat","rb+");
   fb = fopen("appointment.dat","rb+");
   fd = fopen("doctors.dat","rb+");
   while(fread(&a,sizeof(a),1,fa)==1){
        if(a.apid==random){
            random += 108;

        }
   }
   printf("Enter Appointment's id for modifying appointment : \n");
   scanf("%d",&nn);
   rewind(fa);
   while(fread(&a,ssize,1,fa)==1){
    if(a.apid==nn){
        temp = a.appointment_number;
        printf("\nRecord Found.\n");
        printf("Enter new Patient's name : \n");
        fflush(stdin);
        gets(a.name);
        while(1){
        printf("\n1) Child specialist  2) General Physician  3) Psychiatrist  4) Orthodontist \nSelect Doctor's type :  ");
        scanf("%d",&ch);
        a.doc_type = ch;
        if(ch == 1){
           j=1;
        printf("\n\nList of Child specialist : \n");
        while(fread(&d,sizeof(d),1,fd)==1){
            if(strcmp(d.specialization,"Child specialist")==0){

                printf("%d) %s \n",j++,d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t%s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
            }
        }

        rewind(fd);
        printf("\nSelect New Doctor : \n");
        scanf("%d",&dd);
        while(fread(&d,sizeof(d),1,fd)==1){

         	if(strcmp(d.specialization,"Child specialist")==0){
         		count++;
				 }
				 if(count==dd)
				 break;
		}
        strcpy(a.doc_name,d.name);
        printf("\nSelect Day : \n");
        scanf("%d",&cday);
        for(i=0;i<d.nod;i++){
            if(i +1== cday){
                strcpy(a.days,d.day[i]);
                strcpy(a.doc_time,d.time[i]);
                break;
            }
        }
           a.bill = 500;
           a.appointment_number = temp + 7;
           a.apid = random++;
           break;
          }
        else if(ch == 2){
        rewind(fd);
           j=1;
        printf("\n\nList of General Physician : \n");
        while(fread(&d,sizeof(d),1,fd)==1){
            if(strcmp(d.specialization,"General Physician")==0){

                printf("%d) %s \n",j++,d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
            }
        }

        rewind(fd);
        printf("\nSelect New Doctor : \n");
        scanf("%d",&dd);
        while(fread(&d,sizeof(d),1,fd)==1){

         	if(strcmp(d.specialization,"General Physician")==0){
         		count++;
				 }
				 if(count==dd)
				 break;
		}
        strcpy(a.doc_name,d.name);
        printf("\nSelect Day : \n");
        scanf("%d",&cday);
        for(i=0;i<d.nod;i++){
            if(i + 1== cday){
                strcpy(a.days,d.day[i]);
                strcpy(a.doc_time,d.time[i]);
                break;
            }
        }
           a.bill = 600;
           a.appointment_number = temp + 9;
           a.apid = random++;
           break;
          }
         else if(ch == 3){
            rewind(fd);
           j=1;
        printf("\n\nList of Psychiatrists : \n");
        while(fread(&d,sizeof(d),1,fd)==1){
            if(strcmp(d.specialization,"Psychiatrist")==0){

                printf("%d) %s \n",j++,d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
            }
        }

        rewind(fd);
        printf("\nSelect New Doctor : \n");
        scanf("%d",&dd);
        while(fread(&d,sizeof(d),1,fd)==1){

         	if(strcmp(d.specialization,"Psychiatrist")==0){
         		count++;
				 }
				 if(count==dd)
				 break;
		}
        strcpy(a.doc_name,d.name);
        printf("\nSelect Day : \n");
        scanf("%d",&cday);
        for(i=0;i<d.nod;i++){
            if(i + 1== cday){
                strcpy(a.days,d.day[i]);
                strcpy(a.doc_time,d.time[i]);
                break;
            }
        }
           a.bill = 700;
           a.appointment_number = temp + 12;
           a.apid = random++;
           break;
          }
         else if(ch == 4){
            rewind(fd);
           j=1;
        printf("\n\nList of Orthodontists : \n");
        while(fread(&d,sizeof(d),1,fd)==1){
            if(strcmp(d.specialization,"Orthodontist")==0){

                printf("%d) %s \n",j++,d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
            }
        }

        rewind(fd);
        printf("\nSelect Doctor : \n");
        scanf("%d",&dd);
        while(fread(&d,sizeof(d),1,fd)==1){

         	if(strcmp(d.specialization,"Orthodontist")==0){
         		count++;
				 }
				 if(count==dd)
				 break;
		}
        strcpy(a.doc_name,d.name);
        printf("\nSelect Day : \n");
        scanf("%d",&cday);
        for(i=0;i<d.nod;i++){
            if(i + 1== cday){
                strcpy(a.days,d.day[i]);
                strcpy(a.doc_time,d.time[i]);
                break;
            }
        }
           a.bill = 800;
           a.appointment_number = temp + 14;
           a.apid = random++;
           break;
          }
          else {
            printf("\nInvalid input.Enter again.\n");
          }
        }
     while(fread(&b,sizeof(b),1,fb)==1){
        if(a.appointment_number==b.appointment_number)
            a.appointment_number +=3;
     }

     printf("\nPateint's Bill : %.3f ",a.bill);
     printf("\nPatient's New Appointment Number : %d ",a.appointment_number);
     printf("\nNew doctor = %s \nDay = %s ",a.doc_name,a.days);
     printf("\nNew Appointment id = %d ",a.apid);
     printf("\nConfirm new appointment (y/n) ? : \n");
     cc = getche();
     if(cc == 'y'){
        fseek(fa,-ssize,SEEK_CUR);
        fwrite(&a,ssize,1,fa);
     }
       fclose(fa);
       fclose(fb);
       fclose(fd);
       flag=1;
       break;
    }

    }
    if(!flag){
        printf("No record is associated with this patient.\n");
        fclose(fa);
        fclose(fb);
    }

    printf("\n\nWant to modify another record (y/n) ? : ");
    another = getche();
    if(another == 'y'){
        mod_appointment();
    }
    else {
        printf("\n\nReturning to admin panel in 3  seconds.\n");
        delay(3);
        admin_menu();
    }

}

void search_appointment(){
   system("cls");
   int s,flag=0;
   char another;
   FILE *fa;
   fa = fopen("appointment.dat","rb");
   printf("Enter the appointment id : \n");
   scanf("%d",&s);
   while(fread(&a,sizeof(a),1,fa)==1){
    if(a.apid == s){
        printf("\nRecord Found!!\n\n");
        printf("Patient's name : %s \nAppointment id = %d \nAppointment number = %d \nDoctor : %s\n",a.name,a.apid,a.appointment_number,a.doc_name);
        if(a.doc_type==1)
            printf("Specialization : %s \n","Child Specialist");
        else if(a.doc_type==2)
            printf("Specialization : %s \n","n");
        else if(a.doc_type==3)
            printf("Specialization : %s \n","Psychiatrist");
        else if(a.doc_type ==4)
            printf("Specialization : %s \n","Orthodontist");

        printf("Day : %s \nTime : %s\nBill : %.3f Rs\n\n",a.days,a.doc_time,a.bill);
        flag=1;
        break;
    }

   }
   if(!flag){
     printf("\n\nNo record found with this appointment id.\n");
     fclose(fa);
   }
   else
    fclose(fa);
   printf("\n\nWant to search another patient's appointment details (y/n) ? \n");
   another = getche();
   if(another == 'y'){
    search_appointment();
   }
   else {
    printf("\n\nReturning to admin panel in 3  seconds.\n");
    delay(3);
    admin_menu();
   }
}

void list_appointment() {
	system("cls");
	int i=1;
	char ch;
	FILE *fa;
	fa = fopen("appointment.dat","rb");
	if(fa==NULL){
		printf("cannot open file.\n");
		exit(3);

	}

	printf("\t\t\t\tList of appointments \n\n\n");
	while(fread(&a,sizeof(a),1,fa)==1) {
		printf("\n%d)\n\n",i++);
		printf("\nAppointment id = %d",a.apid);
		printf("\nPatienst's name = %s",a.name);
		printf("\nDoctor's name : %s",a.doc_name);
		printf("\nAppointment number = %d",a.appointment_number);
		printf("\nDay  : %s",a.days);
		printf("\nTime : %s",a.doc_time);
		if(a.doc_type==1)
            printf("\nSpecialization : %s \n","Child Specialist");
        else if(a.doc_type==2)
            printf("\nSpecialization : %s \n","n");
        else if(a.doc_type==3)
            printf("\nSpecialization : %s \n","Psychiatrist");
        else if(a.doc_type==4)
            printf("\nSpecialization : %s \n","Orthodontist");

        printf("Bill : %.3f Rs\n\n\n",a.bill);
	}

	fclose(fa);
	printf("Press any key to return to admin menu.\n");
    ch = getch();
    if(ch!='\0'){
    	printf("Returning to admin panel in 2 seconds.\n");
    	delay(2);
    	admin_menu();
	}

}

void add_doctor(){
   system("cls");
   static int random=983;
   int dch,i=0;
   char gen,cd,c,ch;
   FILE *fd;
   fd = fopen("doctors.dat","rb+");
   if(fd==NULL){
    fd = fopen("doctors.dat","wb+");
    if(fd == NULL){
        printf("Cannot open file.\n");
        exit(3);
    }
   }
   while(fread(&d,sizeof(d),1,fd)==1){
        if(d.doc_id==random){
            random += 59;
         }
    }
    fseek(fd,0,SEEK_END);
    printf("Enter Doctor's name : \n");
    fflush(stdin);
    gets(d.name);
    while(1){
    printf("\n1) Child specialist  2) General Physician  3) Psychiatrist  4) Orthodontist \nSelect Doctor's specialization :  ");
    scanf("%d",&dch);
    d.doc_type=dch;
    if(dch==1){
        strcpy(d.specialization,"Child specialist");
        break;
    }
    else if(dch==2){
        strcpy(d.specialization,"General Physician");
        break;
    }
    else if(dch==3){
        strcpy(d.specialization,"Psychiatrist");
        break;
    }
    else if(dch==4){
        strcpy(d.specialization,"Orthodontist");
        break;
    }
    else {
        printf("\nInvalid Input.Enter again.\n");
    }
    }
    printf("\nEnter Doctor's age :\n");
    scanf("%d",&d.age);
    while(1){
    printf("\nGender (m for male,f for female ) :\n");
    scanf(" %c",&gen);
    if(gen == 'm'){
        strcpy(d.gender,"male");
        break;
    }
    else if(gen == 'f'){
        strcpy(d.gender,"female");
        break;
    }
    else {
        printf("\nInvalid Input.Enter again.\n\n");
    }
    }
    printf("\nEnter Doctor's email : \n");
    fflush(stdin);
    gets(d.email);
    printf("\nDescribe Availability of Doctor : \n");
    printf("On Monday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Monday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Tuesday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Tuesday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Wednesday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Wednesday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Thursday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Thursday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Friday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Friday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Saturday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Saturday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Sunday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Sunday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        gets(d.time[i]);
        i++;
    }
    d.doc_id = random++;
    d.nod = i;
    printf("\nDoctor's id = %d \n",d.doc_id);
    printf("\nConfirm to add new doctor (y/n) ? : ");
    fflush(stdin);
    c = getche();
    if(c=='y'){
        fflush(stdin);
        fwrite(&d,sizeof(d),1,fd);
        fclose(fd);
    }
    else
        fclose(fd);

    printf("\n\nWant to add another doctor (y/n) ? : ");
    fflush(stdin);
    ch = getche();
    if(ch == 'y')
        add_doctor();
    else {
        printf("\n\nReturning to admin panel in 3 seconds.\n\n");
        delay(3);
        admin_menu();
    }
}
void del_doctor() {
    system("cls");
    int id,flag=0;
    char ch;
    FILE *fd,*ft;
    fd = fopen("doctors.dat","rb+");
    if(fd == NULL){
        printf("File cannot be open");
        exit(2);
    }
    ft = fopen("temp.dat","wb");
    printf("Enter the doctor's id : \n");
    scanf("%d",&id);
    rewind(fd);
    while(fread(&d,sizeof(d),1,fd)==1){
        if(d.doc_id!=id){
          fwrite(&d,sizeof(d),1,ft);
        }
        else
            flag=1;
        }
    if(flag)
        printf("\nRecord deleted successfully.\n\n");
    else
        printf("\nNo record found associated with this doctor id in our database.\n\n");
    fclose(fd);
    fclose(ft);
    remove("doctors.dat");
    rename("temp.dat","doctors.dat");
    printf("\n\nWant to delete another doctor record (y/n) ? : ");
    ch=getche();
    if(ch == 'y')
        del_doctor();
    else {
        printf("\n\nReturning to admin panel in 3  seconds.\n");
        delay(3);
        system("cls");
    }
}

void mod_doctor(){
    system("cls");
    FILE *fd;
    fd = fopen("doctors.dat","rb+");
    long int size = sizeof(d);
    int n,random = 1863,flag=0,dch,i=0;
    char ch,gen,cd,c;
    while(fread(&d,sizeof(d),1,fd)==1){
        if(d.doc_id==random){
            random += 6;
        }
    }
    printf("Enter the doctor's id to be modified :\n");
    scanf("%d",&n);
    rewind(fd);
    while(fread(&d,size,1,fd)==1){
    if(d.doc_id==n){
    printf("\nRecord Found!");
    flag=1;
    printf("\n\nEnter Doctor's new name : \n");
    fflush(stdin);
    gets(d.name);
    while(1){
    printf("\n1) Child specialist  2) General Physician  3) Psychiatrist  4) Orthodontist \nSelect Doctor's specialization :  ");
    scanf("%d",&dch);
    d.doc_type=dch;
    if(dch==1){
        strcpy(d.specialization,"Child specialist");
        break;
    }
    else if(dch==2){
        strcpy(d.specialization,"General Physician");
        break;
    }
    else if(dch==3){
        strcpy(d.specialization,"Psychiatrist");
        break;
    }
    else if(dch==4){
        strcpy(d.specialization,"Orthodontist");
        break;
    }
    else {
        printf("\nInvalid Input.Enter again.\n");
    }
    }
    printf("\nEnter Doctor's new age :\n");
    scanf("%d",&d.age);
    while(1){
    printf("\nGender (m for male,f for female ) :\n");
    scanf(" %c",&gen);
    if(gen == 'm'){
        strcpy(d.gender,"male");
        break;
    }
    else if(gen == 'f'){
        strcpy(d.gender,"female");
        break;
    }
    else {
        printf("\nInvalid Input.Enter again.\n\n");
    }
    }
    printf("\nEnter Doctor's new email : \n");
    fflush(stdin);
    gets(d.email);
    printf("\nDescribe Availability of Doctor : \n");
    printf("On Monday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Monday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        fflush(stdin);
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Tuesday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Tuesday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        fflush(stdin);
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Wednesday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Wednesday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        fflush(stdin);
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Thursday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Thursday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        fflush(stdin);
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Friday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Friday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        fflush(stdin);
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Saturday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Saturday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        gets(d.time[i]);
        i++;
    }
    printf("\nOn Sunday (y/n)? : ");
    fflush(stdin);
    cd = getche();
    if(cd == 'y'){
        strcpy(d.day[i],"Sunday");
        printf("\nEnter timing in 24-hours format (hh:mm-hh:mm) : \n");
        fflush(stdin);
        gets(d.time[i]);
        i++;
    }
    d.doc_id = random++;
    d.nod=i;
    printf("\n\nDocotor new id = %d \n",d.doc_id);
    printf("\nConfirm to modify existing doctor (y/n) ? : ");
    fflush(stdin);
    c = getche();
    if(c=='y'){
        fseek(fd,-size,SEEK_CUR);
        fwrite(&d,sizeof(d),1,fd);
        fclose(fd);
    }
    }

    }
    if(!flag){
        printf("\nNo record is associated with this doctor's id in our database.\n");
    }
    printf("\nWant to modify another doctor record (y/n) ? : ");
    fflush(stdin);
    ch = getche();
    if(ch == 'y')
        mod_doctor();
    else {
        printf("\n\nReturning to admin panel in 3 seconds.\n\n");
        delay(3);
        admin_menu();
    }
}

void doctor_schedule(){
    system("cls");
    int i;
    char ch;
    FILE *fa;
    fa = fopen("doctors.dat","rb");
    if(fa==NULL){
        printf("Cannot open file.\n");
        exit(4);
    }
    printf("\t\t\t\tDoctor's schedule\n\n");
    printf("\nChild specialists : \n");
    while(fread(&d,sizeof(d),1,fa)==1){
        if(strcmp(d.specialization,"Child specialist")==0){
                printf(" * %s \n",d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
        }
    }
    rewind(fa);
    printf("\nGeneral Physicians : \n");
    while(fread(&d,sizeof(d),1,fa)==1){
        if(strcmp(d.specialization,"General Physician")==0){
                printf(" * %s \n",d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
        }
    }
    rewind(fa);
    printf("\nPsychiatrists : \n");
    while(fread(&d,sizeof(d),1,fa)==1){
        if(strcmp(d.specialization,"Psychiatrist")==0){
                printf(" * %s \n",d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
        }
    }
    rewind(fa);
    printf("\nOrthodontists : \n");
    while(fread(&d,sizeof(d),1,fa)==1){
        if(strcmp(d.specialization,"Orthodontist")==0){
                printf(" * %s \n",d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
        }
    }

    printf("\nPress any key for returning to admin menu.. \n");
    ch = getch();
    if(ch != '\0'){
        fclose(fa);
        printf("Returning to admin panel in 2 seconds.\n");
        delay(2);
        admin_menu();
    }
}

void search_doctor() {
  system("cls");
  int id,flag=0,i;
  char another;
  FILE *fd;
  fd = fopen("doctors.dat","rb");
  if(fd==NULL){
    printf("Cannot open file.\n");
    exit(5);
  }
  printf("Enter doctor's id : \n");
  scanf("%d",&id);
  while(fread(&d,sizeof(d),1,fd)==1){
    if(d.doc_id==id){
        flag = 1;
        printf("\nRecord Found!!\n\n");
        printf("Doctor's name : %s\nSpecialization : %s\nAge : %d\nGender : %s\nEmail : %s\nSchedule : \n",d.name,d.specialization,d.age,d.gender,d.email);
        printf("\t\t\tDays \t\t\tTiming\n\n");
        for(i=0;i<d.nod;i++){
        printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
        printf(" \n");
        }
        printf("\n");
        break;
    }
  }

  if(!flag){
     printf("\n\nNo record is associated with this doctor's id.\n");
     fclose(fd);
   }
   else
    fclose(fd);
   printf("\n\nWant to search another doctor (y/n) ? \n");
   another = getche();
   if(another == 'y'){
    search_doctor();
   }
   else {
    printf("\n\nReturning to admin panel in 3  seconds.\n");
    delay(3);
    admin_menu();
   }
}

void count_appointment() {
   system("cls");
   int count=0;
   char ch;
   FILE *fa;
   fa = fopen("appointment.dat","rb");
   if(fa==NULL){
    fa=fopen("appointment.dat","wb");
    if(fa==NULL){
        printf("File cannot be open.\n");
        exit(4);
    }
   }
   while(fread(&a,sizeof(a),1,fa)==1){
    count++;
   }
   printf("Total number of appointments = %d \n",count);
   printf("Press any key to return to admin panel...\n");
   ch = getch();
   if(ch!='\0'){
    fclose(fa);
    printf("Returning to admin panel in 2 seconds.\n");
    delay(2);
    admin_menu();
   }
}

void logout() {
 system("cls");
 printf("Thanks for using our services.Logging out in 3 seconds.\n");
 delay(3);
 main_menu();
}

void xexit() {
 system("cls");
 printf("Thanks for using our services.Exiting in 3 seconds.\n");
 delay(3);
 exit(0);
}

void reception_menu() {
   system("cls");
    int choice;
    time_t t;
    time(&t);
  
    gotoxy(14,23);
    printf("Current date and time : %s",ctime(&t));
    gotoxy(0,0);
    printf("\n\n\n\n\t\t\t\t\tReception Panel\n\n\n\t\t\t\t1) Search an appointment\n\t\t\t\t2) Search doctor\n\t\t\t\t3) List of appointments\n\t\t\t\t4) Doctor's schedule\n\t\t\t\t5) Total number of appointments\n\t\t\t\t6) Back\n\t\t\t\t7) Exit\n\n\t\t\t\tEnter your choice : ");
    scanf("%d",&choice);
    switch(choice) {
 case 1:
    rsearch_appointment();
    break;
 case 2:
    rsearch_doctor();
    break;
 case 3:
 	rlist_appointment();
 	break;
 case 4:
    rdoctor_schedule();
    break;
 case 5 :
    rcount_appointment();
    break;
 case 6 :
    delay(1);
    main_menu();
    break;
 case 7:
    xexit();
    break;
 default :
    {
        printf("Invalid choice.Re-enter.\n");
        delay(2);
        reception_menu();
    }
    }
}

void rsearch_appointment() {
   system("cls");
   int s,flag=0;
   char another;
   FILE *fa;
   fa = fopen("appointment.dat","rb");
   printf("Enter the appointment id : \n");
   scanf("%d",&s);
   while(fread(&a,sizeof(a),1,fa)==1){
    if(a.apid == s){
        printf("\nRecord Found!!\n\n");
        printf("Patient's name : %s \nAppointment id = %d \nAppointment number = %d \nDoctor : %s\n",a.name,a.apid,a.appointment_number,a.doc_name);
        if(a.doc_type==1)
            printf("Specialization : %s \n","Child Specialist");
        else if(a.doc_type==2)
            printf("Specialization : %s \n","General Physician");
        else if(a.doc_type==3)
            printf("Specialization : %s \n","Psychiatrist");
        else if(a.doc_type==4)
            printf("Specialization : %s \n","Orthodontist");

        printf("Day : %s \nTime : %s\nBill : %.3f Rs\n\n",a.days,a.doc_time,a.bill);
        flag=1;
        break;
    }

   }
   if(!flag){
     printf("\n\nNo record found with this appointment id.\n");
     fclose(fa);
   }
   else
    fclose(fa);
   printf("\n\nWant to search another patient's appointment details (y/n) ? \n");
   another = getche();
   if(another == 'y'){
    rsearch_appointment();
   }
   else {
    printf("\n\nReturning to reception panel in 3  seconds.\n");
    delay(3);
    reception_menu();
   }
}

void rsearch_doctor(){
  system("cls");
  int id,flag=0,i;
  char another;
  FILE *fd;
  fd = fopen("doctors.dat","rb");
  if(fd==NULL){
    printf("Cannot open file.\n");
    exit(5);
  }
  printf("Enter doctor's id : \n");
  scanf("%d",&id);
  while(fread(&d,sizeof(d),1,fd)==1){
    if(d.doc_id==id){
        flag = 1;
        printf("\nRecord Found!!\n\n");
        printf("Doctor's name : %s\nSpecialization : %s\nAge : %d\nGender : %s\nEmail : %s\nSchedule : \n",d.name,d.specialization,d.age,d.gender,d.email);
        printf("\t\t\tDays \t\t\tTiming\n\n");
        for(i=0;i<d.nod;i++){
        printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
        printf(" \n");
        }
        printf("\n");
        break;
    }
  }

  if(!flag){
     printf("\n\nNo record is associated with this doctor's id.\n");
     fclose(fd);
   }
   else
    fclose(fd);
   printf("\n\nWant to search another doctor (y/n) ? \n");
   another = getche();
   if(another == 'y'){
    rsearch_doctor();
   }
   else {
    printf("\n\nReturning to reception panel in 3  seconds.\n");
    delay(3);
    reception_menu();
   }

}

void rdoctor_schedule(){
system("cls");
    int i;
    char ch;
    FILE *fa;
    fa = fopen("doctors.dat","rb");
    if(fa==NULL){
        printf("Cannot open file.\n");
        exit(4);
    }
    printf("\t\t\t\tDoctor's schedule\n\n");
    printf("\nChild specialists : \n");
    while(fread(&d,sizeof(d),1,fa)==1){
        if(strcmp(d.specialization,"Child specialist")==0){
                printf(" * %s \n",d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
        }
    }
    rewind(fa);
    printf("\nGeneral Physicians : \n");
    while(fread(&d,sizeof(d),1,fa)==1){
        if(strcmp(d.specialization,"General Physician")==0){
                printf(" * %s \n",d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
        }
    }
    rewind(fa);
    printf("\nPsychiatrists : \n");
    while(fread(&d,sizeof(d),1,fa)==1){
        if(strcmp(d.specialization,"Psychiatrist")==0){
                printf(" * %s \n",d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
        }
    }
    rewind(fa);
    printf("\nOrthodontists : \n");
    while(fread(&d,sizeof(d),1,fa)==1){
        if(strcmp(d.specialization,"Orthodontist")==0){
                printf(" * %s \n",d.name);
                printf("\t\t\tDays \t\t\tTiming\n\n");
                for(i=0;i<d.nod;i++){
                printf("\t\t  %d) %s \t\t\t %s",i+1,d.day[i],d.time[i]);
                printf(" \n");
                }
                printf("\n");
        }
    }

    printf("\nPress any key for returning to reception panel.. \n");
    ch = getch();
    if(ch != '\0'){
        fclose(fa);
        printf("Returning to reception panel in 2 seconds.\n");
        delay(2);
        reception_menu();
    }

}

void rlist_appointment() {
	system("cls");
	int i=1;
	char ch;
	FILE *fa;
	fa = fopen("appointment.dat","rb");
	if(fa==NULL){
		printf("cannot open file.\n");
		exit(3);

	}

	printf("\t\t\t\tList of appointments \n\n\n");
	while(fread(&a,sizeof(a),1,fa)==1) {
		printf("\n%d)\n\n",i++);
		printf("\nAppointment id = %d",a.apid);
		printf("\nPatienst's name = %s",a.name);
		printf("\nDoctor's name : %s",a.doc_name);
		printf("\nAppointment number = %d",a.appointment_number);
		printf("\nDay  : %s",a.days);
		printf("\nTime : %s",a.doc_time);
		if(a.doc_type==1)
            printf("\nSpecialization : %s \n","Child Specialist");
        else if(a.doc_type==2)
            printf("\nSpecialization : %s \n","n");
        else if(a.doc_type==3)
            printf("\nSpecialization : %s \n","Psychiatrist");
        else if(a.doc_type==4)
            printf("\nSpecialization : %s \n","Orthodontist");

        printf("Bill : %.3f Rs\n\n\n",a.bill);
	}

	fclose(fa);
	printf("Press any key to return to reception panel.\n");
    ch = getch();
    if(ch!='\0'){
    	printf("Returning to reception in 2 seconds.\n");
    	delay(2);
    	reception_menu();
	}

}

void rcount_appointment() {
	system("cls");
   int count=0;
   char ch;
   FILE *fa;
   fa = fopen("appointment.dat","rb");
   if(fa==NULL){
    fa=fopen("appointment.dat","wb");
    if(fa==NULL){
        printf("File cannot be open.\n");
        exit(4);
    }
   }
   while(fread(&a,sizeof(a),1,fa)==1){
    count++;
   }
   printf("Total number of appointments = %d \n",count);
   printf("Press any key to return to reception panel...\n");
   ch = getch();
   if(ch!='\0'){
    fclose(fa);
    printf("Returning to reception panel in 2 seconds.\n");
    delay(2);
    reception_menu();
   }
}



void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}

