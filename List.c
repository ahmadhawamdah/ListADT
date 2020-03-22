//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{ //to rename the struct as node
   int data; // to show the actual data in the node
   struct NodeObj* before; // points to the node before current
   struct NodeObj* after; //points to the node after current
} NodeObj;

// private Node type
typedef struct NodeObj* Node;

// private ListObj type "the 5 fields we talked about in class"
typedef struct ListObj{
   Node front;  // front of the list
   Node back; // back of the list
   Node curser; // the arrow/curser to traverse through the list

   int index; //the location of the chars
   int length; // size of the list
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj)); // allocating dynamic memory,could be 2-4 bytes depending on the compiler
   N->data = data;
   N->before = NULL;
   N->after = NULL;

   return(N);
}


// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){ // this frees the list
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// Constructor generates a newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->curser = NULL;
   L->length = 0;
   L->index = -1; 
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( !isEmpty(*pL) ) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}



// getLength()
// Returns the length of L.
int length(List L){
   if(L==NULL){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}



// returns the index where the cursor is sitting
int getIndex(List L) {
   if(L==NULL){
   printf("List Error: calling index() on NULL List reference\n");
   exit(1);
   }
   return(L->index);
}





// getFront()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
   if(L==NULL){
      printf("List Error: calling getFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling getFront() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}



// getBack()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L){
   if(L==NULL){
      printf("List Error: calling getFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling getFront() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}



// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L){
	if (L == NULL){
		printf("List Error: calling get() on NULL List \n");
		exit(1);
	}
	if (length(L) <= 0){
		printf("List Error: calling get() on empty List \n");
	}
	if (L->curser == NULL){
		printf("List Error: cursor is NULL \n");
	}
	return L->curser->data;
}




// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if(A==NULL || B==NULL){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }

   eq = (A->length == B->length);
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->after;
      M = M->after;
   }
   return eq;
}

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
   if(L==NULL){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return(L->length==0);
}



// Resets L to its original empty state.
void clear(List L){
	if (L == NULL){
		printf("List Error: calling clear() on NULL List \n");
	}
	while (length(L) > 0){
		deleteFront(L);
	}
	L->front = NULL;
	L->back = NULL;
	L->curser = NULL;
    L->length = 0;
	L->index = -1;
}


// Manipulation procedures ----------------------
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L){
   if(L==NULL){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling moveFront on an empty List\n");
      exit(1);
   }
    if (length(L) > 0) {
        L->curser = L->front;
        L->index = 0;
    }
}



// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
   if(L==NULL){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling moveBack() on an empty List\n");
      exit(1);
   }
    if (length(L) > 0) {
        L->curser = L->back;
        L->index = L -> length - 1;
    }
}



 // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void movePrev(List L){
	if (L == NULL){
		printf("List Error: calling movePrev() on NULL List \n");
		exit(1);
	}
    if(L->index != -1) {
        L->curser = L->curser->before;
        L->index--;
        if(L->curser == NULL){
            L->index = -1;
        }
    }
}


// If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L){
	if (L == NULL){
		printf("List Error: calling moveNext() on NULL List \n");
		exit(1);
    }

    if (L->index != -1) {
        L->curser = L->curser->after;
        L->index++;
        if(L->curser == NULL){
            L->index = -1;
        }
    }
}



void prepend(List L, int data){


  if(L==NULL){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }

    Node N = newNode(data);

    if (length(L) == 0){ // if the list is empty
         L->back = L->front = N;
    } else {

         L->front->before = N;
         N->after = L->front;
         L->front = N;
    }
    L->length++; // increase the lenght
    L->index++; // increase the index
}


// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, int data) {

   if(L==NULL){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   
    Node N = newNode(data);
    
   	if (length(L) == 0){ // if the list is empty
		L->front = L->back = N;
	} else {
		L->back->after = N;
        N->before = L->back;
		L->back = N;
	}
   L->length++; // increase the lenght
}




 // Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, int data){
        if (L == NULL){
                printf("List Error: insertBefore() called on NULL List \n");
                exit(1);
        }
        if (L->length <= 0){
                printf("List Error: insertBefore() called on empty List \n");
                exit(1);
        }
        if (L->index < 0) {
        printf("List Error: insertBefore() called on NULL cursor \n");
        exit(1);
        }
    Node N = newNode(data);
        if (L->index == 0){
        L->front->before = N;
        N->after = L->front;
        L->front = N;
    } else {
        N->after = L->curser;
        N->before = L->curser->before;
        L->curser->before->after = N;
        L->curser->before = N;
    }
    L->index++;
    L->length++;
}


// Insert new element before curser.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
        if (L == NULL){
                printf("List Error: insertAfter() called on NULL List \n");
                exit(1);
        }
        if (L->length <= 0){
                printf("List Error: insertAfter() called on empty List \n");
                exit(1);
        }
        if (L->index < 0) {
                printf("List Error: insertAfter() called on NULL cursor \n");
                exit(1);
        }
        Node N = newNode(data);
       if (L->index == L->length-1){
           L->back->after = N;
           N->before = L->back;
           L->back = N;
       } else {
           N->before = L->curser;
           N->after = L->curser->after;
           L->curser->after->before = N;
           L->curser->after = N;
       }
       L->length++;
}

// Delete front element of the List.
void deleteFront(List L){
	if (L == NULL){
		printf("List Error: deleteFront() calling on NULL List \n");
		exit(1);
	}
	if (L->length <= 0){
		printf("List Error: deleteFront() calling on empty List \n");
		exit(1);
	}
	Node N = L->front;
	if (L->length > 1){
		L->front = L->front->after;
	} else {
		L->front = L->back = NULL;
	}
	freeNode(&N);
	L -> index--;
	L -> length--;
}

// Delete back element of the List.
void deleteBack(List L){
    if (length(L) <= 0){
        printf("List Error: deleteBack() calling on Empty List \n");
        exit(1);
    }
    Node N = L -> back;
    if (length(L) == 1){
        L->front = NULL;
        L->back = NULL;
        freeNode(&N);
        L->index = -1;
    } else {
        L->back = L->back->before;
        L->back->after = NULL;
        if (L->index == L->length -1){
            L->index = -1;
        }
        freeNode(&N);
    }
    L -> length--;
}





// Delete cursor
void delete(List L){
	if (length(L) <= 0){
		printf("List Error: calling delete() on empty List \n");
		exit(1);
	}

    Node N = L->curser;
    if(L->curser == L->front) {
        deleteFront(L);
    }
    if(L->curser == L->back) {
        deleteBack(L);
    }
    if (L->index > -1 && L->length > 1){
        L->curser = NULL;
        N->before->after = N->after;
        N->after->before = N->before;
    }
    freeNode(&N);
    L->length--;
}


// Other Functions ------------------------------------------------------------



// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(List L) {

   if( L==NULL ){
      printf("Queue Error: calling printQueue() on NULL Queue reference\n");
      exit(1);
   }
        
    moveFront(L);
    while (while N!= NULL) {
        int x = get(L);
        printf("%d \n", x);
        N= N->after;
    }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
	List B = newList();
    Node N = L -> back;
    
    for(N=L->back ; N!=NULL ; N=N->before) {
        prepend(B,N->data);
    }
    return(B);
}





