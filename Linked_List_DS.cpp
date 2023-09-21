
//Building block of each node of the linked list
#include <iostream>


using std::endl;
using std::cout;
using std::swap;

struct Node
{
  int data{} ;                // initialized to zero to prevent garbage value initialization
  struct Node *next {};

  Node(int data ) : data(data) {}     // every time a new node is constructed then
};                                      // a node with data and next is nulled like below node
//  ---------------------
//  | Data    | next_ptr| --> nullptr
//  ---------------------


//Linked_list class
class Linked_list
{
  private:
    Node *head{};           // head pointer of the list , indicates the list , and it's beginning

    //          HEAD
    //  ---------------------
    //  | 0    | next_ptr| --> nullptr
    //  --------------------

    Node *tail{};           // Tail pointer of the list , indicates the last element of the list ,

    //      Tail
    //   --------------------
    //  | 0       | next_ptr| --> nullptr
    //   ---------------------
    //good for performance instead of
    //traversing the whole list if the target is the rear end of the list

    int list_length{} ;     // new idea : thinking in-progress

  public:
    void print()
    {

      Node *temp_node{nullptr};

      temp_node = head ;              // head is very critical , mess with the head
      // and the list goes boom
      // mess with the head stunt double (temp_head)
      while ( temp_node != nullptr)
      {
        cout << temp_node->data << "->";        // print the current node

        temp_node = temp_node->next;    // and then update to the next node
      }
      cout << "NULL(end of the list)" ;
      cout << endl;

    }


    void append_end(int data)           // only the tail will be used
    {
      Node *new_node = new Node(data);        // created a new node with value data and next
      // ptr null


      if ( !head )                     // if list is empty ( head points at null)
        head = tail = new_node;      // then new node will be the head  and the tail
      // the only one in the list ( the chosen one )
      else
      {
        tail->next = new_node;      // the current node that the tail is pointing at right now
        // will point it's next to the new node (APPENDING)

        tail = new_node;                // after the append , the  new node will be the last node
        // then it will be the new tail ( all hail the new tail)

        ++list_length;                  // new node added to the gang  -> gang counter incremented
      }

    }

    void delete_end()       // stand-by ( future work )
    {

      --list_length;
    }

    //////////// Searching Section //////////////////////////////// 3 Methods (get_position -> based on given postion  )
                                                                            // ( search_v1 based on iterating   )
                                                                            //  ( seach_v2 based on before but optimized )
    Node* get_position(int position) {     // returns the element based on it's position
      int node_counter = 0;

      for (Node* current_node = head; current_node ; current_node = current_node->next)
        if (++node_counter == position)     // this will make sure that the count starts from 1 ( if 0 then change it into node_counter++)
          return current_node;

      return nullptr;
    } //



    int search_v1(int value) {      // Search in linked_list based on the value , iterates through the lined-list until target is found
      int index = 0;
      for (Node* current_node = head; current_node; current_node = current_node->next, index++)
        if (current_node->data == value) 
          return index;
      return -1;
    }

    int search_v2(int value) {  // improved version , search using previous nodes 
      int index = 0;

      Node *previous_node = nullptr;  // making a new empty node to store previous node state 

      for (Node* current_node = head; current_node ; current_node = current_node->next, index++) {  // case 1 : best case , found on first search 
        if (current_node->data == value) {                                                          // prev_node is still null and index is returned
          if (!previous_node)                                                                       
            return index;                                                                           // case 2 : found on n-th iterate , prev_node filled with current node 
          swap(previous_node->data, current_node->data);                                            // target found !! , prev node is not null , then swap or sent current node data into preve data 
          return index - 1;                                                                         // return prev address ( index - 1 )
        }
        previous_node = current_node;
      }

      return -1;
    }

    int search_improved_v2(int value) {
      int idx = 0;

      for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
        if (cur->data == value) {
          if (!prv)
            return idx;
          swap(prv->data, cur->data);
          return idx - 1;
        }
        ++idx;
      }
      return -1;
    }
    //////////// Searching Section ENDED ////////////////////////////////
};


int main()
{

  Linked_list listA ; // new list object is created , this list is called listA  \
  // with this list creation we creat head and tail and list_length


  // time to fill it to check it

  listA.append_end(1);        // list is empty now ->  head = tail = new_node with value 1 ;


  listA.append_end(2);

  listA.append_end(3);

  listA.append_end(4);

  listA.append_end(5);

  listA.append_end(6);

  listA.append_end(534);


  listA.append_end(12134);

  listA.print();

  cout << endl;

///////////////////////////////////////////TESTING get_position() method ////////////
  Node* temp_pointer_node{nullptr};

  temp_pointer_node = listA.get_position(0);
  if (!temp_pointer_node)
    cout << "node not found ";

  else
    cout << temp_pointer_node->data ; 
///////////////////////////////////////////TESTING get_position() method ////////////






  // base linked_list ADT + ending append + printing list : functional and tested.
  return 0;
}
