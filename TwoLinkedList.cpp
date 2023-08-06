#include <iostream>
#include "TwoLinkedList.h"
using namespace std;
using namespace TwoLinkedList;
int main(){
    int choice = 1;
    double tmp_data;
    cout<<"Add the first element:";
    cin>>tmp_data;
    Node *start = make_first(tmp_data);
    Node *end = start;
    while(choice){
        cout<<"Operations:\n1)add element to the list\n2)find the element of list from key\n3)remove element from the list\n4)show list\n5)insert after key\n6)insert undo key\n7)insert with sorting\nX)Any other number to exit\n";
        cin>>choice;
        switch (choice){
        case 1:
            cout<<"Enter the key:";
            cin>>tmp_data;
            add(&end,tmp_data);        
            break;
        case 2:
            cout<<"Enter key to find:";
            cin>>tmp_data;
            find(start,tmp_data) ? cout<<"[!!!]Key found[!!!]\n":cout<<"[!!!]Key not found![!!!]\n";    
            break;
        case 3:
            cout<<"Enter key to remove:";
            cin>>tmp_data;
            remove(&start,&end,tmp_data)?cout<<"[!!!]Key removed[!!!]\n":cout<<"[!!!]Key not found[!!!]\n";
            break;
        case 4:
            show(start);
            break;
        case 5:
            double new_data;
            cout<<"Enter the key to insert after: ";
            cin>>tmp_data;
            cout<<"Enter the new key: ";
            cin>>new_data;
            insert(start,&end,tmp_data,new_data)?cout<<"[!!!]Key inserted[!!!]\n":cout<<"[!!!]Key not found[!!!]\n";
            break;
        case 6:
            double new_key;
            cout<<"Enter key to insert undo: ";
            cin>>tmp_data;
            cout<<"Enter the new key: ";
            cin>>new_key;
            insert_undo(&start,tmp_data,new_key) ? cout<<"[!!!]Key inserted[!!!]\n" : cout<<"[!!!]Key not found[!!!]\n";
            break;
        case 7:
            cout<<"Enter the data: ";
            cin>>tmp_data;
            add_sort(&start,&end,tmp_data);
            cout<<"[!!!]Key inserted[!!!]\n";
            break;
        default:
            cout<<"[!!!]Exiting...[!!!]";
            return 0;
            break;
        }//switch (choice)
    }//while (choice)
    return 0;
}