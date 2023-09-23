
//Building block of each node of the linked list
#include<iostream>
#include<cassert>
#include<string>
#include<sstream>



using std::endl;
using std::cout;
using std::swap;
using std::string;
using std::ostringstream;

struct Node
{
  int data{} ;                // initialized to zero to prevent garbage value initialization
  struct Node *next {};

  Node(int data ) : data(data) {}     // every time a new node is constructed then
                                                // a node with data and next is nulled like below node

  ~Node()
  {
      cout << " Destroying the node " << data << " that belong to the node address " << this << endl;
  }




};                                    


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

    int search_v3(int value) {// same as before optimization but with better code writing convention convention 
      int index = 0;                //  previous  node stacked in the for body 

      for (Node *current_node = head, *previous_node = nullptr; current_node ; previous_node = current_node, current_node = current_node->next) {
        if (current_node->data == value) {
          if (!previous_node)
            return index;
          swap(previous_node->data, current_node->data);
          return index - 1;
        }
        ++index;
      }
      return -1;
    }
    //////////// Searching Section ENDED ////////////////////////////////


    void integrity_verify()
    {
        if ( list_length == 0 )    // EMPTY LIST INTEGRITY TEST 
         // if the list is empty then the head and the tail must be nulled ,they don't point at anything YET ! 
        {
            assert(head == nullptr );   //  no head yet
            assert(tail == nullptr);    // no tail yet 
        }
        else   // NON EMPTY LIST INTEGRITY TEST 
            {
                assert(head != nullptr);    // there is a head 
                assert(tail != nullptr);    // there is a tail 

                if(list_length == 1 )   // if the list is only 1 node case 
                {
                    assert(head == tail );  // head and tail pointers must point at the same node 
                }
                else    // list is > 1 length 
                {
                    assert( head != tail ); // head and tail are different pointers 
                }
                    // end of the list integrity test 
                    assert(!tail->next); // the next node of the tail is the end of the list ( nullptr)

                }
            // length integrity test 
            int length_indicator{};

            for( Node *current_node = head ; current_node  ; current_node =  current_node->next , length_indicator++ )
            {
                assert(length_indicator < 10000);   
            }
            assert( list_length == length_indicator);
         //   assert(list_length == (int)debug_data.size());

    }

    string to_string()
    {
      if(list_length == 0 ) return " ";   // empty list return empty string 

      ostringstream oss ; 

      for ( Node *current_node = head ; current_node ; current_node = current_node->next)
      {
          oss << current_node->data;
          if(current_node->next)
            oss << " " ; 
      }
      return oss.str();

    }
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

  temp_pointer_node = listA.get_position(1);
  if (!temp_pointer_node)
    cout << "node not found ";

  else
    cout << temp_pointer_node->data ; 
///////////////////////////////////////////TESTING get_position() method ////////////

  cout << endl; 
  int position;
  position = listA.search_v1(5);
  cout << position << endl;
  position = listA.search_v2(5);
  cout << position << endl;
  position = listA.search_v3(5);
  cout << position << endl;

  //listA.print();    // survey the change on the list , see when you search for a certain elements , the position gets shifted into the left 
            // indicating how the element gets more frequent so it means it will be found more faster next time 

  string buffer ; 

  buffer = listA.to_string();

  cout << buffer ; 

  
            
             
  // base linked_list ADT + ending append + printing list : functional and tested.
  return 0;
}
