//
//  main.c
//  Quicksort
//
//  Created by Stephen Kelehan on 02/11/2016.
//  Copyright © 2016 Stephen Kelehan. All rights reserved.
//


// malloc( sizeof(struct node)
//struct node *new_node = (struct node*) malloc (sizeof (struct node));


#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

void create_sorted_list(int[], int);        // linked list sort funtion
void print_list();

int partition( int[], int, int);            // quciksort funtions
void QuickSort( int[] , int , int);

void bubble_sort(int[], int);               // bubble sort funtion

void swap(int*, int*);                      // globle funtion (used by bubble and quicksort )

int count_quicksort = 0;                    // globle vars
struct Node* head;

int main()
{
    // test data

    int a[] = { 1,3,9,4,5,7,6,8,0, 11,31,91,41,15,71,16,18,01,111,311,119,114,511,711,16,28,30, 211,311,291,431,154,715,166,138,101};
    int b[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int c[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1};
    
    int i;
    
    // calling sort funtions
    
    printf("\n\nUnsorted array for quick sort is:  ");
    for(i = 0; i < 36; ++i)
        printf(" %d ", a[i]);
    
    QuickSort( a, 0, 35);
    
    printf("\n\n The number of probes for the quicksort is: %i", count_quicksort);
    
    printf("\n\nSorted array by quick sort is:  ");
    for(i = 0; i < 36 ; ++i)
        printf(" %d ", a[i]);
    
    printf("\n\n\n");
    
    printf("\n\nUnsorted array for linked list is:  ");
    for(i = 0; i < 9; ++i)
        printf(" %d ", b[i]);
    
    create_sorted_list(b, 9);
    
    print_list();
    
    printf("\n\n\n");
    
    printf("\n\nUnsorted array for buuble sort is:  ");
    for(i = 0; i < 9; ++i)
        printf(" %d ", c[i]);
    
    bubble_sort(c, 9);
    
    //swap(&c[0],&c[1]);
    
    printf("\n\nSorted array by bubble sort is:  ");
    for(i = 0; i < 9; ++i)
        printf(" %d ", c[i]);
    
    printf("\n\n\n");
    
    
    return 0;
    
}

void swap(int *x, int *y)       // takes two var x and y, swaps them using XOR! when you proform XOR like this it reverses the two var.
{                               // ie. x = 1010, y = 1111  x = x ^ y => 0101 = x, y = y ^ x => 1010 = y, finally x = x^ y => 1111
    *x ^= *y;                   // x and y have switched
    *y ^= *x;
    *x ^= *y;
}

/*
        Soudo Code
    qucikSort( array, first , last)
    {
        if first < last
        {
            par = partiction (array, first, last);
            quicksort( array, first, par - 1);
            quicksort( array, par + 1, first);
        }
    }
 
    partition( array, first, last )
    {
        x = array[last]
        i = first - 1
        for j = first -> last - 1
            if array[j] <= x
                i += 1
                swap( array[i], array[j] )
        swap( array[i + 1], array[ last ]
        return i + 1
    }
 
 */

void QuickSort( int a[], int first, int last)
{
    int par;
    
    if( first < last )                              // checks to see if there is more than one element in the array partition
    {
        par = partition( a, first, last);           // creates partition
        QuickSort( a, first, par - 1);              // sorts first half of partition
        QuickSort( a, par + 1, last);               // sorts second half of partition
    }
}

int partition ( int a[], int first, int last)
{
    int pivot = a[last];                            // last val picked as pivot
    int par = first;                                // wall/par set to first index
    
    for( int i = first; i < last; i++)              // increments from the start of partition/ full array to the end
    {
        if ( a[i] <= pivot)                         // if the element been assest ins <= to pivit move the parr up one and swap
        {                                           // with par
            if( i == par );                         // this i statment ot stop unnessasery swaps
            else
            {
                swap(&a[i], &a[par]);
            }
            par ++;
        }
        count_quicksort++;
    }
    if( par == last );                              // swap par with last element
    else
    {
        swap(&a[par], &a[last]);
    }
    return par ;
}

void create_sorted_list(int b[], int array_size)
{
    int count = 0;

    head = NULL;
    for ( int i = 0; i < array_size; i ++)
    {
        int flag = 0;                                                           // creating a new node
        struct Node* curr = head;
        struct Node* prev = NULL;
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        
        newNode -> data = b[i];                                                 // assigning data to the node
        
        if(head == NULL)                                                        // if no head sent newNode to head
        {
            head = newNode;
            curr = head;
            count++;
        }
        else if(b[i] <= head -> data)                                           // if data is < head make the newNode head
        {
            newNode -> next = head;
            head = newNode;
            count++;
        }
        else if(b[i] > head -> data)                                            // if data greater than head, go through list until
        {                                                                       // node found with data greater than newNode adn puts it before
            while(curr->next != NULL)
            {
                if(curr->data >= b[i])
                {
                    newNode -> next = curr;
                    prev -> next = newNode;
                    flag = 1;
                    count++;
                    break;
                }
                prev = curr;
                curr = curr -> next;
                count++;
            }
            if( curr -> next == NULL && flag == 0)                              // if itterates through the whole list and needs to go at the
            {                                                                   // end
                curr->next = newNode;
                count++;
            }
        }
    }
    printf("\n\nThe number of probes for the Linked List sort is: %i", count);
}

void print_list()
{
    printf( "\n\nSorted array by linked list is: ");
    struct Node* curr = head;
    while(curr != NULL)
    {
        printf("%d   ", curr->data);
        curr = curr -> next;
    }
}

void bubble_sort(int c[], int array_size)
{
    int flag = 1, i, count = 0;
    
    while(flag == 1)                                    // while there is still swaps
    {
        flag = 0;
        for(i = 0; i < array_size; i++)                 // go through the array
        {
            if(c[i] > c[i+1])                           // if the i index is greater than the i + 1 swap them
            {
                swap(&c[i],&c[i+1]);
                flag = 1;
            }
            count++;
        }
    }
    printf("\n\nNumber of Probes for Bubble sort: %i", count);
}
