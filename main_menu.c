#include"header.h"

int main() 
{
    student *head = 0;
    char choice;
    loadRecords(&head);

    while(1) 
    {
        printf("\nSTUDENT RECORD MENU\n");
        printf("a/A : Add new record\n");
        printf("d/D : Delete a record\n");
        printf("s/S : Show the list\n");
        printf("m/M : Modify a record\n");
        printf("v/V : Save records\n");
        printf("t/T : Sort records\n");
        printf("l/L : Delete all records\n");
        printf("r/R : Reverse the list\n");
        printf("e/E : Exit\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);

        switch(choice) 
        {
            case 'a': case 'A': addRecord(&head); break;
            case 'd': case 'D': deleteRecord(&head); break;
            case 's': case 'S': showRecords(head); break;
            case 'm': case 'M': modifyRecord(&head); break;
            case 'v': case 'V': saveRecords(head); break;
            case 't': case 'T': sortRecords(&head); break;
            case 'l': case 'L': deleteAll(&head); break;
            case 'r': case 'R': reverseList(&head); break;
            case 'e': case 'E': printf("Save before exit? (y/n): ");
                char ex;
                scanf(" %c", &ex);
                if(ex=='y'||ex=='Y') saveRecords(head);
                deleteAll(&head);
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

int getNextRoll(student *head) 
{
    int roll = 1;
    int found;
    while(1) 
    {
        found = 0;
        student *temp = head;
        while(temp) 
        {
            if(temp->rollno == roll) 
            {
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if(!found) 
            return roll;
        roll++;
    }
}

void addRecord(student **head) 
{
    student *newNode = malloc(sizeof(student));
    if(!newNode)
    {
        printf("Memory error!\n");
        return;
    }

    newNode->rollno = getNextRoll(*head);
    printf("Enter name and percentage: ");
    scanf("%s %f", newNode->name, &newNode->percentage);
    newNode->next = NULL;

    if(*head == NULL) 
        *head = newNode;
    else
    {
        student *temp = *head;
        while(temp->next) 
            temp = temp->next;
        temp->next = newNode;
    }
    printf("Added: Roll %d, Name %s, Percentage %.2f\n",newNode->rollno, newNode->name, newNode->percentage);
} 

void deleteRecord(student **head) 
{
    char mode;
    printf("Delete by Roll (R/r) or Name (N/n): ");
    scanf(" %c",&mode);

    if(mode=='R'||mode=='r') 
    {
        int roll;
        printf("Enter roll: "); 
        scanf("%d",&roll);
        student *temp=*head,*prev=NULL;
        while(temp && temp->rollno!=roll) 
        {
            prev=temp;
            temp=temp->next;
        }
        if(!temp)
        {
            printf("Not found!\n");
            return; 
        }
        if(!prev)
            *head=temp->next;
        else
            prev->next=temp->next;
        printf("Deleted Roll:%d Name:%s\n",temp->rollno,temp->name);
        free(temp);
    } 
    else
    {
        char nm[50]; 
        printf("Enter name: "); 
        scanf("%s",nm);
        student *temp=*head,*prev=NULL; 
        int found=0;
        while(temp) 
        {
            if(strcmp(temp->name,nm)==0) 
            {
                printf("Match: Roll %d Name %s\n",temp->rollno,temp->name);
                found=1;
            }
            temp=temp->next;
        }
        if(!found) 
        { 
            printf("No match!\n"); 
            return;
        }
        int roll; 
        printf("Enter roll to delete: "); 
        scanf("%d",&roll);
        deleteRecord(head); 
    }
}

void showRecords(student *head) 
{
    if(!head) 
    {
        printf("No student records available.\n");
        return;
    }
    printf("RollNo\tName\tPercentage\n");
    while(head)
    {
        printf("%d\t%s\t%.2f\n", head->rollno, head->name, head->percentage);
        head=head->next;
    }
}

void modifyRecord(student **head) 
{
    char mode;
    printf("Search by Roll(R), Name(N), Percentage(P): ");
    scanf(" %c",&mode);
    int roll; 
    char nm[50]; 
    float perc;
    student *temp=*head;
    if(mode=='R'||mode=='r') 
    {
        printf("Enter roll: "); 
        scanf("%d",&roll);
        while(temp && temp->rollno!=roll) 
            temp=temp->next;
    } 
    else if(mode=='N'||mode=='n') 
    {
        printf("Enter name: "); 
        scanf("%s",nm);
        while(temp && strcmp(temp->name,nm)!=0) 
            temp=temp->next;
    } 
    else 
    {
        printf("Enter percentage: "); 
        scanf("%f",&perc);
        while(temp && temp->percentage!=perc) 
            temp=temp->next;
    }
    if(!temp) 
    {
        printf("Record not found!\n"); 
        return;
    }
    printf("Current: Roll %d Name %s Perc %.2f\n",temp->rollno,temp->name,temp->percentage);
    printf("Enter new name and percentage: ");
    scanf("%s %f",temp->name,&temp->percentage);
    printf("Updated successfully.\n");
}

void saveRecords(student *head) 
{
    FILE *fp=fopen("student.dat","w");
    if(!fp) 
    {
        printf("File error!\n"); 
        return; 
    }
    while(head) 
    {
        fprintf(fp,"%d %s %.2f\n",head->rollno,head->name,head->percentage);
        head=head->next;
    }
    fclose(fp);
    printf("Records saved to student.dat\n");
}

void loadRecords(student **head) 
{
    FILE *fp=fopen("student.dat","r");
    if(!fp) 
        return;
    student *newNode,*temp=NULL;
    while(1) 
    {
        newNode=malloc(sizeof(student));
        if(fscanf(fp,"%d %s %f",&newNode->rollno,newNode->name,&newNode->percentage)==EOF) 
        {
            free(newNode); break;
        }
        newNode->next=NULL;
        if(*head==NULL) 
        { 
            *head=newNode; 
            temp=newNode; 
        }
        else 
        { 
            temp->next=newNode; 
            temp=newNode; 
        }
    }
    fclose(fp);
    printf("Records loaded from student.dat\n");
}

void sortRecords(student **head) 
{
    if(!*head) 
        return;
    char mode; 
    printf("Sort by Name(N) or Percentage(P): "); 
    scanf(" %c",&mode);
    for(student *i=*head;i->next;i=i->next) 
    {
        for(student *j=i->next;j;j=j->next) 
        {
            int swap=0;
            if((mode=='N'||mode=='n') && strcmp(i->name,j->name)>0) 
                swap=1;
            if((mode=='P'||mode=='p') && i->percentage<j->percentage) 
                swap=1;
            if(swap) 
            {
                int tr=i->rollno; float tp=i->percentage; char tn[50];
                strcpy(tn,i->name);
                i->rollno=j->rollno; i->percentage=j->percentage; strcpy(i->name,j->name);
                j->rollno=tr; j->percentage=tp; strcpy(j->name,tn);
            }
        }
    }
    printf("Records sorted.\n");
}

void deleteAll(student **head) 
{
    student *temp;
    while(*head) 
    {
        temp=*head;
        *head=(*head)->next;
        free(temp);
    }
    printf("All records deleted.\n");
}

void reverseList(student **head) 
{
    student *prev=NULL,*curr=*head,*next=NULL;
    while(curr) 
    {
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    *head=prev;
    printf("List reversed.\n");
}
