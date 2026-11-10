#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for sleep()

// Structure definition
typedef struct student {
    int rollno;
    char name[50];
    float percentage;
    struct student *next;
} SLL;

// Function declarations
void add_student(SLL **ptr);
void printnode(SLL *ptr);
void deletenode(SLL **ptr);
int countnode(SLL *ptr);
void modify(SLL **ptr);
void savefile(SLL *ptr);
void loadfile(SLL **ptr);
void deleteall(SLL **ptr);
void sortdata(SLL *ptr);
void reverselinks(SLL **ptr);

int main() {
    SLL *head = NULL;
    int choice;

    // Load existing records from file on startup
    loadfile(&head);

    while (1) {
        printf("\n==============================\n");
        printf("   STUDENT RECORD MANAGEMENT  \n");
        printf("==============================\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Delete Student\n");
        printf("4. Count Nodes\n");
        printf("5. Modify Record\n");
        printf("6. Sort Data\n");
        printf("7. Reverse Links\n");
        printf("8. Delete All Records\n");
        printf("9. Save & Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                add_student(&head);
                break;
            case 2:
                printnode(head);
                break;
            case 3:
                deletenode(&head);
                break;
            case 4:
                printf("Total records: %d\n", countnode(head));
                break;
            case 5:
                modify(&head);
                break;
            case 6:
                sortdata(head);
                break;
            case 7:
                reverselinks(&head);
                printf("Links reversed successfully\n");
                break;
            case 8:
                deleteall(&head);
                head = NULL;
                break;
            case 9:
                savefile(head);
                deleteall(&head);
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

// 1. Add Student
void add_student(SLL **ptr)
{
    SLL *new_node;
    int roll = 1;
    SLL *temp;

    new_node = malloc(sizeof(SLL));
    if (!new_node) {
        printf("Memory allocation failed\n");
        return;
    }

    temp = *ptr;

    while(temp != 0)
    {
        if(temp->rollno == roll)
        {
            roll++;
            temp = *ptr;
        }
        else
        {
            temp = temp->next;
        }
    }

    new_node->rollno = roll;

    printf("Enter name: ");
    scanf("%s", new_node->name);

    printf("Enter percentage: ");
    scanf("%f", &new_node->percentage);

    new_node->next = *ptr;
    *ptr = new_node;
    printf("Student added successfully with Roll No: %d\n", roll);
}

// 2. Print Nodes
void printnode(SLL *ptr)
{
    if(ptr == 0)
    {
        printf("No student records available\n");
        return;
    }

    printf("---------------------------------------------\n");
    printf("Roll No.   Name        Percentage\n");
    printf("---------------------------------------------\n");

    while(ptr)
    {
        printf("%-10d %-11s %.2f\n", ptr->rollno, ptr->name, ptr->percentage);
        ptr = ptr->next;
    }
    printf("---------------------------------------------\n");
}

// 3. Delete Node
void deletenode(SLL **ptr)
{
    if(*ptr == 0)
    {
        printf("no records found\n");
        return;
    }

    char ch;
    printf("R/r : Enter roll number to delete\n");
    printf("N/n : Enter name to delete\n");
    scanf(" %c",&ch);

    if(ch == 'R' || ch == 'r')
    {
        int roll;
        printf("Enter roll number to delete: ");
        scanf("%d",&roll);

        SLL *del = *ptr, *prev = 0;

        while(del)
        {
            if(del->rollno == roll)
            {
                if(del == *ptr)
                    *ptr = del->next;
                else
                    prev->next = del->next;

                free(del);
                printf("record deleted successfully\n");
                return;
            }

            prev = del;
            del = del->next;
        }

        printf("roll number not found\n");
    }

    else if(ch == 'N' || ch == 'n')
    {
        char name[50];

        printf("Enter name to delete: ");
        scanf("%s",name);

        SLL *del = *ptr, *prev = 0;

        while(del)
        {
            if(strcmp(name,del->name) == 0)
            {
                printf("Roll No: %d  Name: %s\n", del->rollno, del->name);

                SLL *temp = del->next;
                int count = 1;

                while(temp)
                {
                    if(strcmp(name,temp->name) == 0)
                    {
                        printf("Roll No: %d  Name: %s\n", temp->rollno, temp->name);
                        count++;
                    }
                    temp = temp->next;
                }

                if(count > 1)
                {
                    int roll;
                    printf("Enter roll number to delete: ");
                    scanf("%d",&roll);

                    del = *ptr;
                    prev = 0;

                    while(del)
                    {
                        if(del->rollno == roll)
                        {
                            if(del == *ptr)
                                *ptr = del->next;
                            else
                                prev->next = del->next;

                            free(del);
                            printf("record deleted successfully\n");
                            return;
                        }

                        prev = del;
                        del = del->next;
                    }

                    printf("roll number not found\n");
                    return;
                }

                if(del == *ptr)
                    *ptr = del->next;
                else
                    prev->next = del->next;

                free(del);
                printf("record deleted successfully\n");
                return;
            }

            prev = del;
            del = del->next;
        }

        printf("name not found\n");
    }

    else
    {
        printf("Invalid choice\n");
    }
}

// 4. Count Nodes
int countnode(SLL *ptr)
{
    int c = 0;

    while(ptr)
    {
        c++;
        ptr = ptr->next;
    }

    return c;
}

// 5. Modify Record
void modify(SLL **ptr)
{
    SLL *temp;
    char ch;
    int roll;
    char name[50];
    float percentage;

    if(*ptr == 0)
    {
        printf("No student records available\n");
        return;
    }

    printf("Enter the record to search for modification\n");
    printf("R/r : Search by roll number\n");
    printf("N/n : Search by name\n");
    printf("P/p : Search by percentage\n");
    printf("Enter your choice: ");
    scanf(" %c", &ch);

    if(ch == 'R' || ch == 'r')
    {
        printf("Enter roll number: ");
        scanf("%d", &roll);

        temp = *ptr;

        while(temp != 0)
        {
            if(temp->rollno == roll)
            {
                printf("present details:\n");
                printf("%d %s %f\n", temp->rollno, temp->name, temp->percentage);

                printf("Enter new name: ");
                scanf("%s", temp->name);

                printf("Enter new percentage: ");
                scanf("%f", &temp->percentage);

                printf("Record modified successfully\n");
                return;
            }

            temp = temp->next;
        }

        printf("Roll number not found\n");
    }

    else if(ch == 'N' || ch == 'n')
    {
        printf("Enter name: ");
        scanf("%s", name);

        temp = *ptr;
        int count = 0;

        while(temp != 0)
        {
            if(strcmp(temp->name, name) == 0)
            {
                printf("Roll No: %d  Name: %s  Percentage: %f\n", temp->rollno, temp->name, temp->percentage);
                count++;
            }
            temp = temp->next;
        }

        if(count == 0)
        {
            printf("Name not found\n");
            return;
        }

        if(count > 1)
        {
            printf("Enter roll number to modify: ");
            scanf("%d", &roll);

            temp = *ptr;

            while(temp != 0)
            {
                if(temp->rollno == roll && strcmp(temp->name, name) == 0)
                {
                    printf("Enter new name: ");
                    scanf("%s", temp->name);

                    printf("Enter new percentage: ");
                    scanf("%f", &temp->percentage);

                    printf("Record modified successfully\n");
                    return;
                }
                temp = temp->next;
            }

            printf("Record not found\n");
        }
        else
        {
            temp = *ptr;

            while(temp != 0)
            {
                if(strcmp(temp->name, name) == 0)
                {
                    printf("Enter new name: ");
                    scanf("%s", temp->name);

                    printf("Enter new percentage: ");
                    scanf("%f", &temp->percentage);

                    printf("Record modified successfully\n");
                    return;
                }
                temp = temp->next;
            }
        }
    }

    else if(ch == 'P' || ch == 'p')
    {
        printf("Enter percentage: ");
        scanf("%f", &percentage);

        temp = *ptr;
        int count = 0;

        while(temp != 0)
        {
            if(temp->percentage == percentage)
            {
                printf("Roll No: %d  Name: %s  Percentage: %.2f\n", temp->rollno, temp->name, temp->percentage);
                count++;
            }
            temp = temp->next;
        }

        if(count == 0)
        {
            printf("Percentage not found\n");
            return;
        }

        if(count > 1)
        {
            printf("Enter roll number to modify: ");
            scanf("%d", &roll);

            temp = *ptr;

            while(temp != 0)
            {
                if(temp->rollno == roll && temp->percentage == percentage)
                {
                    printf("Enter new name: ");
                    scanf("%s", temp->name);

                    printf("Enter new percentage: ");
                    scanf("%f", &temp->percentage);

                    printf("Record modified successfully\n");
                    return;
                }
                temp = temp->next;
            }

            printf("Record not found\n");
        }
        else
        {
            temp = *ptr;

            while(temp != 0)
            {
                if(temp->percentage == percentage)
                {
                    printf("Enter new name: ");
                    scanf("%s", temp->name);

                    printf("Enter new percentage: ");
                    scanf("%f", &temp->percentage);

                    printf("Record modified successfully\n");
                    return;
                }
                temp = temp->next;
            }
        }
    }

    else
    {
        printf("Invalid choice\n");
    }
}

// 6. Save File
void savefile(SLL *ptr)
{
    if(ptr == 0)
    {
        return;
    }

    FILE *fp;
    fp = fopen("student.dat", "w");
    if (!fp) {
        printf("Error opening file for saving\n");
        return;
    }

    while(ptr)
    {
        fprintf(fp, "%d %s %f\n", ptr->rollno, ptr->name, ptr->percentage);
        ptr = ptr->next;
    }

    printf("Data saved in file successfully\n");
    fclose(fp);
}

// 7. Load File
void loadfile(SLL **ptr)
{
    FILE *fp;
    SLL *new_node, *temp;

    fp = fopen("student.dat", "r");

    if(fp == 0)
        return;

    while(1)
    {
        new_node = malloc(sizeof(SLL));
        if (!new_node) break;

        if(fscanf(fp, "%d %s %f", &new_node->rollno, new_node->name, &new_node->percentage) != 3)
        {
            free(new_node);
            break;
        }

        new_node->next = 0;

        if(*ptr == 0)
        {
            *ptr = new_node;
        }
        else
        {
            temp = *ptr;
            while(temp->next != 0)
                temp = temp->next;

            temp->next = new_node;
        }
    }

    fclose(fp);
}

// 8. Delete All Nodes
void deleteall(SLL **ptr)
{
    if(*ptr == 0)
    {
        return;
    }

    int c = 1;
    SLL *del = *ptr;

    while(del)
    {
        *ptr = del->next;
        printf("node deleted : %d\n", c++);
        free(del);
        del = *ptr;
    }

    printf("all nodes deleted\n");
}

// 9. Sort Data
void sortdata(SLL *ptr)
{
    SLL *p1 = ptr, *p2, *t;
    int i, j, c = countnode(ptr);
    char ch;

    if(ptr == 0)
    {
        printf("No records found\n");
        return;
    }

    printf("R/r : Roll No\n");
    printf("N/n : Name\n");
    printf("P/p : Percentage\n");
    printf("Enter your choice: ");
    scanf(" %c", &ch);

    t = malloc(sizeof(SLL));
    if (!t) return;

    for(i = 0; i < c - 1; i++)
    {
        p2 = p1->next;

        for(j = 0; j < c - i - 1; j++)
        {
            if((ch == 'R' || ch == 'r') && p1->rollno > p2->rollno)
            {
                t->rollno = p1->rollno;
                strcpy(t->name, p1->name);
                t->percentage = p1->percentage;

                p1->rollno = p2->rollno;
                strcpy(p1->name, p2->name);
                p1->percentage = p2->percentage;

                p2->rollno = t->rollno;
                strcpy(p2->name, t->name);
                p2->percentage = t->percentage;
            }

            else if((ch == 'N' || ch == 'n') && strcmp(p1->name, p2->name) > 0)
            {
                t->rollno = p1->rollno;
                strcpy(t->name, p1->name);
                t->percentage = p1->percentage;

                p1->rollno = p2->rollno;
                strcpy(p1->name, p2->name);
                p1->percentage = p2->percentage;

                p2->rollno = t->rollno;
                strcpy(p2->name, t->name);
                p2->percentage = t->percentage;
            }

            else if((ch == 'P' || ch == 'p') && p1->percentage > p2->percentage)
            {
                t->rollno = p1->rollno;
                strcpy(t->name, p1->name);
                t->percentage = p1->percentage;

                p1->rollno = p2->rollno;
                strcpy(p1->name, p2->name);
                p1->percentage = p2->percentage;

                p2->rollno = t->rollno;
                strcpy(p2->name, t->name);
                p2->percentage = t->percentage;
            }

            p2 = p2->next;
        }

        p1 = p1->next;
    }

    free(t);
    printf("Data sorted successfully\n");
}

// 10. Reverse Links
void reverselinks(SLL **ptr)
{
    int c = countnode(*ptr);
    SLL **a, *t = *ptr;
    int i;

    if(*ptr == 0)
    {
        printf("No records found\n");
        return;
    }
    if(c > 1)
    {
        a = malloc(sizeof(SLL *) * c);
        if (!a) return;

        for(i = 0; i < c; i++)
        {
            a[i] = t;
            t = t->next;
        }

        for(i = c - 1; i > 0; i--)
        {
            a[i]->next = a[i - 1];
        }

        a[0]->next = 0;
        *ptr = a[c - 1];
        free(a);
    }
}
