

#include <stdio.h>
#include <stdlib.h>



typedef struct link{
    int num;
    struct link *next;
} link;


link *head = NULL;



int status = 0;



void createNode(int x, link *list){
    link *newNode = (link *)malloc(sizeof(link));
    newNode->num = x;
    newNode->next = NULL;
    if (head == NULL){
        head = newNode;
    }
    else {
        link *it = head;
        while (it->next != NULL){
            it = it->next;
        }
        it->next = newNode;
    }
}



void Create(link *list){
    FILE *fp = fopen("List.txt", "r");
    int ele;
    while (fscanf(fp, "%d", &ele) == 1){
        createNode(ele, list);
    }
    fclose(fp);
    printf("A new list has been successfully created!\n");
}



int Length(link *list){
    link *it = head;
    int cnt = 0;
    while (it != NULL){
        it = it->next;
        cnt++;   
    }
    if (cnt == 0){
        status = 1;
        printf("No elements in list presently!\n");
    }
    return cnt;
}



void PrintList(link *list){
    link *it = head;
    int cnt = 1;
    if (head == NULL){
        printf("No elements in list presently!\n");
        return;
    }
    printf("Enter in which order the elements of the list is to be displayed:\n1 - Left-to-right\n2 - Right to left\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1){
        printf("The elements of the list presently are as follows:\n");
        while (it != NULL){
            printf("Element in the %dth node is: %d\n", cnt, it->num);
            it = it->next;
            cnt++;
        }
        printf("The present elements of the list were successfully printed!\n");
        return;
    }
    else {
        it = head;
        cnt = Length(list);
        int arr[cnt];
        for (int i=0;i<cnt;i++){
            arr[i] = it->num;
            it = it->next;
        }
        printf("The elements of the list presently are as follows:\n");
        for (int i=cnt-1;i>=0;i--){
            printf("Element in the %dth node is: %d\n", i+1, arr[i]);
        }
        printf("The present elements of the list were successfully printed!\n");
        return;
    }
}



int Retrieve(int i, link *list){
    if (head == NULL){
        printf("No elements in the list presently!\n");
        status = 1;
        return 0;
    }
    link *p = head;
    int cnt = 1;
    while(p->next!=NULL && cnt!=i){
        p = p->next;
        cnt++;
    }
    if (i>cnt){
        printf("List ends before given position. Please input a position between 1 and %d!\n", cnt+1);
        status = 1;
        return 0;
    }
    return p->num;
}



void Store(int x, int i, link *list){
    if (head == NULL){
        printf("No elements in the list presently!\n");
        return;
    }
    link *p = head;
    int cnt = 1;
    while(p->next!=NULL && cnt!=i){
        p = p->next;
        cnt++;
    }
    if (i>cnt){
        printf("List ends before given position. Please input a position between 1 and %d!\n", cnt+1);
        status = 1;
        return;
    }
    p->num = x;
    printf("Element succesfully updated!\n");
    return;
}



void Insert(int x, int i, link *list){
    link *newRecord = malloc(sizeof(link));
    newRecord->num = x;
    int cnt = 1;
    link *p = head;
    while (p->next != NULL){
        p = p->next;
        cnt++;
    }
    if (cnt<i-1){
        printf("List ends before given position. Please input a position between 1 and %d!\n", cnt+1);
        return;
    }
    p = head;
    if (i==1){
        head = newRecord;
        newRecord->next = p;
        printf("New element inserted at the %dth position successfully!\n", i);
        return;
    }
    else if (i<=0){
        printf("The list starts at position 1. Please input a position between 1 and %d!\n", cnt+1);
        return;
    }
    else {
        cnt = 1;
        while (cnt<i-1){
            p = p->next;
            cnt++;
        }
        newRecord->next = p->next;
        p->next = newRecord;
        printf("New element inserted at the %dth position successfully!\n", i);
        return;
    }
}



void Delete(int i, link *list){
    if (head == NULL){
        printf("No elements in the list!\n");
        return;
    }
    link *p = head;
    int cnt = 1;
    while (p->next != NULL){
        p = p->next;
        cnt++;
    }
    if (cnt<i){
        printf("List ends before given position. Please input a position within %d!\n", cnt+1);
        return;
    }
    p = head;
    if (i==1){
        head = p->next;
        free(p);
        printf("Element successfully deleted!\n");    
        return;
    }
    else if (i<=0){
        printf("The list starts at position 1. Please input a position between 1 and %d!\n", cnt+1);
        return;
    }
    cnt = 1;
    while (cnt<i-1){
        p = p->next;
        cnt++;
    }
    link *q = p;
    p = p->next;
    q->next = p->next;
    free(p);
    printf("Element successfully deleted!\n");
    return;
}



int Search(int x, link *list){
    link *p = head;
    int cnt = 1;
    while (p!=NULL && p->num!=x){
        p = p->next;
        cnt++;
    }
    if (p == NULL){
        return -1;
    }   
    return cnt;
}




int main(){


    printf("A new list is going to be created, containing elements of the file 'Lists.txt'.....\n");
    link list;
    Create(&list);


    while (27){


        printf("Enter the desired operation to be done on the list:\n");
        printf("1 - Find the length of the list\n2 - Print the elements of the list\n3 - Retrieve an element from the list\n");
        printf("4 - Store a new value at a position in the list\n5 - Insert an element into the list\n");
        printf("6 - Delete an element from the list\n7 - Search for an element in the list\n0 - Exit\n");
        printf("Enter your choice: ");


        int choice;
        scanf("%d", &choice);


        switch (choice){


            case 1: {
                int length = Length(&list);
                if (status == 1){
                    status = 0;
                    break;
                }
                printf("The present length of the list is: %d\n", length);
                break;
            }


            case 2: {
                PrintList(&list);
                break;
            }


            case 3: {
                printf("Enter the position of the element that you want to retrieve: ");
                int pos;
                scanf("%d", &pos);
                int ele = Retrieve(pos, &list);
                if (status == 1){
                    status = 0;
                    break;
                }
                printf("The element at the %dth position of the list is: %d\n", pos, ele);
                break;
            }


            case 4: {
                printf("Enter the position of the list where you want to store a new element: ");
                int pos;
                scanf("%d", &pos);
                printf("Enter the new element that will update the %dth element in the list: ", pos);
                int ele;
                scanf("%d", &ele);
                Store(ele, pos, &list);
                break;
            }


            case 5: {
                printf("Enter the position of the list where you want to insert a new element: ");
                int pos;
                scanf("%d", &pos);
                printf("Enter the new element that will be inserted at the %dth position of the list: ", pos);
                int ele;
                scanf("%d", &ele);
                Insert(ele, pos, &list);
                break;
            }


            case 6: {
                printf("Enter the position of the element which needs to be deleted: ");
                int pos;
                scanf("%d", &pos);
                Delete(pos, &list);
                break;
            }


            case 7: {
                printf("Enter the element whose position needs to be searched: ");
                int ele;
                scanf("%d", &ele);
                int pos = Search(ele, &list);
                if (pos == -1){
                    printf("The desired element does not exist in the list!\n");
                    break;
                }
                printf("The first occurance of the element %d presently in the list is: %d\n", ele, pos);
                break;
            }


            case 0: {
                printf("Thank you!\n");
                return 0;
            }


            default: {
                printf("Please enter a valid choice!\n");
                break;
            }

        }

    }

    return 0;

}