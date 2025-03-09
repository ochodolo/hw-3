#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot) {
  if(head == NULL){
    smaller = NULL;
    larger = NULL;
    return;
  }
  Node* temp = head;
  temp->next = NULL;

  Node *smallerList = NULL;
  Node *largerList = NULL;
  llpivot(head, smallerList, largerList, pivot);

  if(temp->val <= pivot){
    temp->next = smallerList;
    smaller = temp;
    larger = largerList;
  } else if(temp->val > pivot){
    temp->next = largerList;
    larger = temp;
    smaller = smallerList;
  }
}
