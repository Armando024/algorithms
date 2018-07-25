//
// Created by Armando 
//
#include <iostream>
using namespace std;

struct listnode {
    struct listnode* next;
    int key;
};
/*
 * My function is from line 15 to 55, the rest of the code is for a simple example that shows the sorting is working and it sorts random numbers.
 */

struct listnode* merge(struct listnode* theleft,struct listnode* theright);
struct listnode * sort(struct listnode* a ) {
    if (a== nullptr || a->next== nullptr) {
        return a;}

    int size=0;
    listnode* temp=a;
    listnode* right=a;

    while(temp!= nullptr) {
        temp=temp->next;
        size++;
    }

    int mid=size-(size/2);
    while(mid>0) {
        temp=right;
        right=right->next;
        mid--;
    }
    temp->next= nullptr;

    return merge(sort(a),sort(right)); //I had two pointers called left and head, but I realize my code could be simplify more by putting it in the return.
}
struct listnode* merge(struct listnode* theleft,struct listnode* theright){
    if (theright==nullptr) { //the left is for the left array and the righ is for the right array
        return theleft;
    }
    if (theleft == nullptr) {
        return theright;
    }
    listnode* newlist=nullptr;
    if (theright->key <= theleft->key  ) { //simple comparion, and just simply point the new list(head) to the small value, and recurse it until I reach null pointer and vice versa.
        newlist=theright;
        newlist->next=merge(theleft,theright->next);
    } else {
        newlist=theleft;
        newlist->next=merge(theleft->next,theright);
    }
    return newlist;
}


//utilities, to print list quickly
void printlist(struct listnode* copy) {
    listnode* temp=copy;
    while (temp!= nullptr) {
        cout<<temp->key<<" ";
        temp=temp->next;
    }
    cout<<endl;
}
int main () {
    listnode list;
    listnode list2;
    listnode list3;
    listnode list4;
    listnode list5;
    listnode list6;
    listnode list7;

    list.next= &list2;
    list2.next=&list3;
    list3.next=&list4;
    list4.next=&list5;
    list5.next= &list6;
    list6.next= &list7;
    list7.next= nullptr;

     listnode* temp4=&list;
    while(temp4!= nullptr) {
        temp4->key = rand() % 11;
        temp4=temp4->next;
    }
cout<<"unsorted list\n";
printlist(&list);

    listnode* sortedlist=sort(&list);

    cout<<"printing sorted elements\n";
    printlist(sortedlist);
    return 0;
}

