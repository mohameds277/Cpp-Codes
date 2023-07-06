//Work in Progress library of linked-list

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// class linked_list 
// {

// public :
//     struct Node
//     {
//         int data;
//         Node *next_ptr;

//         Node (int data ) : data(data) {}                //STRUCT NODE CONSTRUCTOR , DATA ASSIGNED TO THE DATA ABOVE 
//     };






// // void create_node(int data)
// // {
// //     Node *node_1 = new Node(1);
// // }


// };


struct Node 
{
    int data;
    Node *next_ptr;

    Node(int data_) : data(data_) {} // list constructor initialized list  ( data_member = data_argument )
};



void print_list(Node* head_list)        // call by value , pass the pointer value copy ( address value ) into the function , the function works with the given address with no modifications 
{
    while(head_list != nullptr)
    {
        cout << head_list->data << "\t"; 
        head_list = head_list->next_ptr;    // update the pointer location into the next node 
    }
    cout << endl;

}



void print_list(Node* &head_list , bool dummy_par)          //call by reference  , pass the address of the pointer ( the address of the address) !!! CRITICAL FUNCTION !!! BE AWARE
{                                                                                                                                              // DON'T PLAY WITH FIRE (POINTERS)
    //uncomment this line to destroy the world 
    // head_list++;  

    while(head_list != nullptr)
    {
        cout << head_list->data << "\t"; 
        head_list = head_list->next_ptr;    // update the pointer location into the next node 
    }
    cout << endl;



}



int main()
{

    Node *node_0 = new Node(0);             // The list head 
    Node *node_1 = new Node(1);
    Node *node_2 = new Node(1);
    Node *node_3 = new Node(3);
    Node *node_4 = new Node(4);


// Manual linking of the nodes to make a useful list , instead of scattered data in the heap 
    node_0->next_ptr = node_1;
    node_1->next_ptr = node_2;
    node_2->next_ptr = node_3;
    node_3->next_ptr = node_4;
    node_4->next_ptr = nullptr;

    cout << node_0->data << endl;

    //same values , different ways of access 
    cout << node_1->data << endl;
    cout << node_0->next_ptr->data << endl; 


    //same values , different ways of access
    cout << node_4->data << endl;
    cout << node_0->next_ptr->next_ptr->next_ptr->next_ptr->data << endl;

    print_list(node_0);

    print_list(node_0 , true );



    return 0;
}
