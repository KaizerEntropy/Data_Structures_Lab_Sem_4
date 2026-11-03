#include <stdio.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int n;
} array;

int status = 0;

void Create(array *list){
    FILE *fp;
    fp = fopen("List.txt", "r");
    list->n = 0;
    while (fscanf(fp, "%d", &list->arr[list->n]) == 1){
        list->n++;
    }
    fclose(fp);
}

int Length(array *list){
    if (list->n==0){
        status=1;
        return 0;
    }
    return list->n;
}

void PrintList(array *list){
    printf("Enter how you want to display the elements:\n1 - Left-to-right\n2 - Right-to-left\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    if (choice==1){

        for (int i=0;i<list->n;i++){
            printf("%d ", list->arr[i]);
        }
    }
    else {
        for (int i=list->n-1;i>=0;i--){
            printf("%d ", list->arr[i]);
        }
    }
    printf("\n");
    return;
}

int Retrieve(int i, array *list){
    return list->arr[i-1];
}

void Store(int x, int i, array *list){
    list->arr[i-1] = x;
}

void Insert(int x, int i, array *list){
    i = i-1;
    for (int j=list->n-1;j>=i;j--){
        list->arr[j+1] = list->arr[j];
    }
    list->arr[i] = x;
    list->n++;
    return;
}

void Delete(int i, array *list){
    i = i-1;
    for (int j=i+1;j<list->n;j++){
        list->arr[j-1] = list->arr[j];
    }
    list->n--;
    return;
}

int Search(int x, array *list){
    for (int i=0;i<list->n;i++){
        if (list->arr[i]==x){
            return i+1;
        }
    }
    return -1;
}

int main(){
    printf("A new list is going to be created, containing elements of the file 'Lists.txt'.....\n");
    array list;
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