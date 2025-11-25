#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct student{
   	char name[30];
        int roll;
       	int snum; 
        char subjects[7][30];
        struct student* next;
};

struct prof{
        char name[30];
        int id;
        char subject[30];
        struct student* clhead;
        struct prof* next;
};

FILE* calendar;

typedef struct prof Prof;
typedef struct student Student;

Prof* new_prof( char name[] ,int id, char subject[]){
	Prof* temp = malloc(sizeof(Prof));
	strcpy(temp->name,name);
	strcpy(temp->subject,subject);
	temp->id=id;
	temp->next= NULL;
	return temp;
}
Student* new_student(char name[],int roll,int snum,char subjects[][30]){
	Student* temp=malloc(sizeof(Student));
	strcpy(temp->name,name);
	temp->roll=roll;
	temp->snum = snum;
	for(int i =0;i<snum;i++){
		strcpy(temp->subjects[i],subjects[i]);
	}
	temp->next;
	return temp;
}

Student* iboots(){
	FILE *fptr;
	fptr = fopen("student.txt","r");
	char name[30];
	int roll;
	int snum;
	char subjects[7][30];
	fscanf(fptr,"%s %d %d",name,&roll,&snum);
	int i =0;
	while(i<snum){
		fscanf(fptr," %s",subjects[i]);
			i++;
	}
	Student* head;
	head = new_student(name,roll,snum,subjects);
	Student* temp= head;
	while(fscanf(fptr , "%s %d %d",name,&roll,&snum)==3){
		int i =0;
        	while(i<snum){
                	fscanf(fptr," %s",subjects[i]);
                        i++;
        		}
		Student* temp2= new_student(name,roll,snum,subjects);
		temp->next=temp2;
		temp = temp->next;
	}
	fclose(fptr);
	return head;
}

Student* boots(Prof* prof){
	FILE* fptr;
	fptr=fopen(prof->subject,"w");
	FILE* F;
	F = fopen("student.txt","r");
	char buffer[256];
	int t=0;
	while(fgets(buffer,sizeof(buffer),F)!=NULL){
		char p[30];
		strcpy(p," ");
		strcat(p,prof->subject);
		strcat(p," ");
		if(strstr(buffer,p)!=NULL){
			fprintf(fptr,"%s",buffer);
			t=1;
		}
	}
	fclose(fptr),fclose(F);
	if(t==0){
		return NULL;
	}
	else{
	fptr = fopen(prof->subject,"r");
	char name[30];
        int roll;
        int snum;
        char subjects[7][30];
        fscanf(fptr,"%s %d %d",name,&roll,&snum);
        int i =0;
        while(i<snum){
                fscanf(fptr," %s",subjects[i]);
                        i++;
        }
        Student* head;
        head = new_student(name,roll,snum,subjects);
        Student* temp= head;
        while(fscanf(fptr , "%s %d %d",name,&roll,&snum)==3){
                int i =0;
                while(i<snum){
                        fscanf(fptr," %s",subjects[i]);
                        i++;
                        }
                Student* temp2= new_student(name,roll,snum,subjects);
                temp->next=temp2;
                temp = temp->next;
        }
        fclose(fptr);
	return head;
	}
}




Prof* bootp(){
        FILE *fptr;
        fptr = fopen("prof.txt","r");
	char name[20];
	int id;
	char subject[20];
	fscanf(fptr,"%s %d %s",name,&id,subject);
	Prof* head;
	head = new_prof(name,id,subject);
	Prof *temp=head;
	while(fscanf(fptr,"%s %d %s",name,&id,subject)==3){
		Prof* temp2 = new_prof(name,id,subject);
		temp ->next=  temp2;
		temp= temp->next;	
	}
	fclose(fptr);
	return head;

}
void Student_data(int rollnumber,Student* head_student,Prof* head_prof){
	Student* l=head_student;
	Prof* h=head_prof;
	int c = 0;
	for(l=head_student;l!=NULL;l=l->next){
		if(l->roll == rollnumber){
			c=1;
			break;
		}
	}
	while(1){
		if(c == 0){
			printf("-----------------------------------------\n");
			printf("Roll number not Found, contact Professor\n");
			break;
		}
		else{
			printf("-----------------------------------------\n");
			printf("\033[36mStudent name: %s\nRoll number: %d\n\n",l->name,l->roll);
			printf("Courses: \n");
			for(int i = 0;i<l->snum;i++){
				printf("%d.%s\n",i+1,l->subjects[i]);
			}
			printf("\033[0m-----------------------------------------\n");
		}
		int x=1;
		printf("1.Courses details\n2.Academic calendar\n3.Exit\n");
		printf("-----------------------------------------\n");
		scanf("%d",&x);
		if(x == 3){
			system("cls");
			break;
		}
		else if(x == 2){
			char s[256];
			calendar = fopen("Academic_calendar.txt","r");
			while(fgets(s,sizeof(s),calendar)!=NULL){
				printf("%s",s);
			}
		}
		else if(x == 1){
			char sub[30];
			printf("Enter the Name of the Course as in the list : \n");
			for(int i = 0;i<l->snum;i++){
				printf("%d.%s\n",i+1,l->subjects[i]);
			}
			scanf("%s",sub);
			int c1=0;
			for(int i = 0;i<l->snum;i++){
				if(strcmp(sub,l->subjects[i])==0){
					c1 = 1;
					break;
				}
			}
			if(c1 == 0){
				printf("Invalid Course name. Try again\n");
			}
			else{
				Prof* temp;
				for(temp=head_prof;temp!=NULL;temp=temp->next){
					if(strcmp(temp->subject,sub)==0){
						Student* student_head = boots(h);
						Student* p;
						for(p=student_head;p!=NULL;p=p->next){
							if(p->roll == rollnumber){
								break;
							}
						}
						printf("-----------------------------------------\n");
						printf("\033[36mProfessor Name : %s\nProfessor Id : %d\033[0m\n",temp->name,temp->id);
						printf("-----------------------------------------\n");
					}
				}
			}
		}
		else{
			printf("Invalid input  Try again\n");
		}
		int y=0;
		printf("-----------------------------------------\n");
		printf("1.Return Home\n2.Stay\n");
		printf("-----------------------------------------\n");
		scanf("%d",&y);
		if(y==1){
			system("cls");
			break;
		}
	}
}

void removeS(Prof* prof){
		char name[30];
                scanf ("%s",name);
 		int p=0;
                FILE *fptr;
                FILE *newfp;
                fptr = fopen("student.txt","r");
                newfp=fopen("new.txt","w");
                char buffer[256];
                char temp[256];
                while(fgets(buffer,sizeof(buffer),fptr) != NULL){
                        if(strstr(buffer,name) != NULL){
                                strcpy(temp,buffer);
                                p=1;
                                continue;
			}
                        fputs(buffer,newfp);
                }
                if(p==1){
                        int l = strlen(temp);
                        temp[l-1]=' ';
                        char name[20];
                        int roll,snum;
                        char subjects[7][20];
                        sscanf(temp,"%s %d %d",name,&roll,&snum);
                        int i=0;
                        char c[5];
                        sprintf(c,"%d",snum);
                        c[1]=c[0];
			c[2]=' ';
			c[0]=' ';
                        c[3]='\0';
                        int len=3;
                        while(i<snum){
                                char* y = strstr(temp,c);
                                if(y!=NULL){
                                sscanf((y+len),"%s",subjects[i]);
                                len= len+strlen(subjects[i])+1;
                                i++;
                                }
                        }
                        snum--;
                        char temp1[256];
                        sprintf(temp1,"%s %d %d",name,roll,snum);
                        for(i=0;i<(snum+1);i++){
				if(strcmp(subjects[i],prof->subject)==0){
					continue;
				}
				strcat(temp1, " ");
                                strcat(temp1,subjects[i]);
                        }
                        fprintf(newfp,"%s \n",temp1);
		fclose(newfp);
		fclose(fptr);	
		remove("student.txt");
                rename("new.txt","student.txt");
}
}

void removePK(Prof* prof){;
                FILE *fptr;
                FILE *newfp;
                fptr = fopen("student.txt","r");
                newfp=fopen("new.txt","w");
                char buffer[256];
                char temp[256];
                while(fgets(buffer,sizeof(buffer),fptr) != NULL){
			strcpy(temp,buffer);
                        int l = strlen(temp);
                        temp[l-1]=' ';
                        char name[20];
                        int roll,snum;
                        char subjects[7][20];
                        sscanf(temp,"%s %d %d",name,&roll,&snum);
                        int i=0;
                        char c[5];
                        sprintf(c,"%d",snum);
                        c[1]=c[0];
			c[2]=' ';
			c[0]=' ';
                        c[3]='\0';
                        int len=3;
                        while(i<snum){
                                char* y = strstr(temp,c);
                                if(y!=NULL){
                                sscanf((y+len),"%s",subjects[i]);
                                len= len+strlen(subjects[i])+1;
                                i++;
                                }
                        }
			int k=0;
                        snum--;
                        char temp1[256];
                        sprintf(temp1,"%s %d %d",name,roll,snum);
                        for(i=0;i<(snum+1);i++){
				if(strcmp(subjects[i],prof->subject)==0){
					k=1;
					continue;
				}
				strcat(temp1, " ");
                                strcat(temp1,subjects[i]);
                        }
		if(k==1){
                        fprintf(newfp,"%s \n",temp1);
		}
		else{
			fprintf(newfp,"%s",buffer);
		}
		}
		fclose(newfp);
		fclose(fptr);	
		remove("student.txt");
                rename("new.txt","student.txt");

}


Prof* profm(Prof* prof,int k){
	
	Student* head;
	head= boots(prof);


	if(k==1){
		printf("\033[36mName: %s\n",prof->name);
              printf("Id: %d\n",prof->id);
                printf("Subject: %s\n",prof->subject);
		printf("\033[0m\n");
	}
	else if(k==2){
		Student* temp;
		if(head== NULL){
			printf("No students under this professor yet\n");
		}
		for(temp=head;temp != NULL ; temp = temp->next){
		printf("\033[36mName: %s\n",temp->name );
		printf("Roll Number: %d\n",temp->roll);
		printf("Number of courses: %d\n",temp->snum);
		printf("Subjects: ");
		for(int i=0;i<(temp->snum);i++){
			printf("%s ",(temp->subjects)[i]);
		}
		printf("\033[0m\n\n");
	}
	}
	else if(k==3){
		//addS function
		printf("Enter the name of the student you want to add to your course:\n");
		char name[30];
		int p=0;
		int check=0;
		Student* temp;
		scanf("%s",name);
		for(temp = head ; temp != NULL;temp = temp->next){
			if(strcmp(temp->name,name)==0){
				check=1;
			}
		}
		if(check!=1){
		FILE *fptr;
		FILE *newfp;
		fptr = fopen("student.txt","r");
		newfp=fopen("new.txt","w");
		char buffer[256];
		char temp[256];
		while(fgets(buffer,sizeof(buffer),fptr) != NULL){
			if(strstr(buffer,name) != NULL){
				strcpy(temp,buffer);
				p=1;
				continue;
			}
			fputs(buffer,newfp);
		}
		if(p==1){
			int l = strlen(temp);
			temp[l-1]=' ';
			char name[20];
			int roll,snum;
			char subjects[7][20];
			sscanf(temp,"%s %d %d",name,&roll,&snum);
			int i=0;
			char c[5];
			sprintf(c,"%d",snum);
			c[1]=c[0];
			c[0]=' ';
			c[2]=' ';
			c[3]='\0';
			int len=3;
			while(i<snum){
				char* y = strstr(temp,c);
				if(y!=NULL){
				sscanf((y+len),"%s",subjects[i]);
				len= len+strlen(subjects[i])+1;
				i++;
				}	
			}
			snum++;
			char temp1[256];
			sprintf(temp1,"%s %d %d",name,roll,snum);
			for(i=0;i<(snum-1);i++){
				strcat(temp1, " ");
				strcat(temp1,subjects[i]);
				
			}
			strcat(temp1," ");
			strcat(temp1,prof->subject);
			fprintf(newfp,"%s \n",temp1);
		}
		else{
			printf("Student not in database\n");
		}
		fclose(fptr);
		fclose(newfp);
		remove("student.txt");
		rename("new.txt","student.txt");
	}
	else{
		printf("Student already enrolled in course\n.");
	}
	}
	else if(k==4){
		printf("Enter the name of the student you want to remove: \n");
		removeS(prof);
	}
	else if(k==5){
		system("cls");
		return prof;
	}
	else{
	printf("Invalid Input :( \n");
	}
	printf("-----------------------------------------\n");
        printf("\033[32m1.My Info\n");
   	  	printf("2.My Students list\n");
    	printf("3.Add Student\n");
    	printf("4.Remove Student\n");
   		printf("5.Return HOME\033[0m\n");
        printf("-----------------------------------------\n");
	int t;
	scanf("%d",&t);
	prof = profm(prof,t);	
}
	
Prof *fire(Prof *head, int del_id){
    FILE *fptr, *newfp;
    char line[200];
    fptr = fopen("prof.txt", "r");
    newfp = fopen("new_prof.txt", "w");
    while(fgets(line, sizeof(line), fptr)){
        char name[100], sub[100];
        int id;
        if(sscanf(line, "%s %d %s", name, &id, sub)==3){
            if(id==del_id){
                continue;
            }
        }
        fputs(line, newfp);
    }
    fclose(fptr);
    fclose(newfp);
    remove("prof.txt");
    rename("new_prof.txt", "prof.txt");
    if(head->id==del_id){
        Prof *temp = head->next;
	removePK(head);
        free(head);
        return temp;
    }
    Prof *ind = head;
    Prof *prev = NULL;
    while(ind!= NULL && ind->id!=del_id){
        prev = ind;
        ind = ind->next;
    }
    if(ind==NULL){
        return head;
    }
    prev->next = ind->next;
    removePK(ind);
    free(ind);
    return head;
}

void add_calendar(char file[]){
	FILE* sourceFile;
	char c;
	calendar = fopen("Academic_calendar.txt","w");
	sourceFile = fopen(file,"r");

	if(sourceFile == NULL){
		printf("File not found");
	}
	while((c = fgetc(sourceFile)) != EOF){
		fputc(c,calendar);
	}
	fclose(calendar);
	fclose(sourceFile);
}

Prof* admin(Prof* head,int k){
	Student* HEAD;
	HEAD = iboots();
        if(k==1){
                struct prof* temp;
                for(temp = head; temp != NULL ; temp = temp -> next){
                        printf("\033[36mName: %s\n",temp->name);
                        printf("Id: %d\n",temp->id);
                        printf("Subject: %s\n",temp->subject);
                        printf("\033[0m\n");
        	}
	}
        else if(k==2){
                FILE *fptr;
                fptr = fopen("prof.txt", "a");
                char pn[30];
		int pid;
		char psub[30];
		printf("Enter the prof data in the format {name} {id} {subject(in one word)}\n");
		scanf("%s %d %s",pn, &pid, psub);
		int flag = 0;
		Prof *ind = head;
		for(; ind!=NULL; ind = ind->next){
			if(ind->id==pid){
				flag = 1;
			}
		}
		if(flag==0){
			fprintf(fptr,"%s %d %s \n",pn,pid,psub);
			Prof* temp;
			for(temp = head ; temp->next != NULL ; temp = temp->next);
			temp->next= new_prof(pn,pid,psub);
		}
		else{
			printf("Professor ID already in database\n");
		}
		fclose(fptr);
	}
        else if(k==3){
                printf("Enter the ID of the prof you want to FIRE!\n");
                int id;                
		scanf("%d",&id);
               	head=fire(head,id);
	}
	else if(k==4){
		Student* temp;
                for(temp=HEAD;temp != NULL ; temp = temp->next){
                printf("\033[36mName: %s\n",temp->name );
                printf("Roll Number: %d\n",temp->roll);
                printf("Number of courses: %d\n",temp->snum);
                printf("Subjects: ");
                for(int i=0;i<(temp->snum);i++){
                        printf("%s ",(temp->subjects)[i]);
                }
                printf("\033[0m\n\n");
        }
	}
	else if(k==5){
		printf("Enter student name\n");
		char name[30];
		scanf("%s",name);
		int j=0;
		int max = 1;
		Student* temp;
		for(temp = HEAD ; temp!= NULL ; temp = temp->next){
			if(temp->roll > max){
				max = temp->roll;
			}
			if(strcmp(name,temp->name)==0){
				j=1;
				break;
			}
		}
		if(j==0){
			FILE *fptr;
			fptr = fopen("student.txt","a");
			int snum = 0;
			fprintf(fptr,"%s %d %d ",name ,++max,snum);
			fclose(fptr);
		}
		else{
		printf("Name already in database\n");
		}
	}
	
	else if(k==6){
		int g5;
		printf("1.Enter 1 if the calender file is already in the same folder as the code.\n");
		printf("2.Enter 2 if you have to add the file.\n");
		scanf("%d",&g5);
		if(g5 == 1){
			char file_name[30];
			printf("Please enter the name the file with txt: ");
			scanf("%s",file_name);
			printf("\n");
			add_calendar(file_name);
		}
		else if(g5 == 2){
			printf("The code will be terminating now, add the calender file(In txt format) to the same folder as the code.\n");
			exit(0);
		}
	}

	else if(k==7){
		system("cls");
		return head;
	}
	else{
		printf("Invalid Input :( \n");
	}
	 printf("-----------------------------------------\n");
        printf("\033[32m1.List of Professors\n");
        printf("2.Add new Professor\n");
        printf("3.FIRE a Professor\n");
		printf("4.Access Student list\n");
		printf("5.Add a student\n");
		printf("6.Add calendar\n");
		printf("7.Return HOME\033[0m\n");
        printf("-----------------------------------------\n");
        int t;
        scanf("%d",&t);
	head = admin(head,t);

}

int main(){
        struct prof *HEAD;
        HEAD=bootp();
	Student* head;
	head=iboots();
	printf("\033[1;35mWELCOME TO LEARNING MANAGEMENT SYSTEM!!\033[0m\n");
	while(1){
	printf("-----------------------------------------\n");
        printf("\033[32mSelect the mode you want to access: \n");
        printf("1.Professor\n");
        printf("2.Student\n");
        printf("3.Admin\n");
	printf("4.Close\033[0m\n");
	printf("-----------------------------------------\n");
	int k;
        scanf("%d",&k);
        if(k==1){
		system("cls");
		printf("\033[1;33m-------------PROFESSOR MODE-------------\033[0m\n");
		Prof* temp;
		int j=0;
		head = iboots();
		while(j==0){
		printf("Please Enter your Id:\n");
                int id;
                scanf("%d",&id);
		for(temp =HEAD; temp!= NULL; temp = temp->next){
			if(temp->id == id){
				j=1;
				break;
			}
		}
		if(j==1){
				break;
		}
			printf("Invalid ID!\n");
            
			}
	 	 	printf("-----------------------------------------\n");
       		printf("\033[32m1.My Info\n");
   	  	 	printf("2.My Students list\n");
       		printf("3.Add Student\n");
        	printf("4.Remove Student\n");
       		printf("5.Return HOME\033[0m\n");
        	printf("-----------------------------------------\n");
		 int t;
		 scanf("%d",&t);
		temp = profm(temp,t);
	}
        else if(k==2){
			system("cls");
			printf("\033[1;33m---------------STUDENT MODE---------------\033[0m\n");
			printf("Please Enter your roll number:\n");
			int rn;
			scanf("%d",&rn);
			Student_data(rn,head,HEAD);
        }
	else if(k==3){
		system("cls");
		printf("\033[1;33m----------------ADMIN MODE---------------\033[0m\n");
		printf("Enter the password: \n");
		char pas[20];
		scanf("%s", pas);
		if(strcmp(pas,"ARV")==0){
	printf("-----------------------------------------\n");
        printf("\033[32m1.List of Professors\n");
        printf("2.Add new Professor\n");
        printf("3.FIRE a Professor\n");
		printf("4.Access Student list\n");
		printf("5.Add a student\n");
		printf("6.Add calendar\n");
		printf("7.Return HOME\033[0m\n");
        printf("-----------------------------------------\n");
        int t;
        scanf("%d",&t);
		HEAD = admin(HEAD,t);
		}
		else{
			printf("Wrong password\n");
		}
	}
	else if(k==4){
		break;
	}
	else{
		printf("Invalid Input :( \n");
	}
}
printf("\033[1;35mThanks for using our LMS :) \033[0m\n");
}

