
//Building block of each node of the linked list
#include<iostream>
#include<cassert>
#include<string>
#include<sstream>
#include<algorithm>
#include<vector>



using std::endl;
using std::cout;
using std::swap;
using std::string;
using std::ostringstream;
using std::vector;
using std::find;



struct Node // 8 bytes total ( 4 bytes for data , )
{
  int data{} ;                // initialized to zero to prevent garbage value initialization
  struct Node *next{nullptr};       // initialized to nullptr to prevent wild pointers 

  Node(int data) : data(data) {}     // every time a new node is constructed then
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
    //  --------------------
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



    vector<Node*> debug_data;   // backup , vector stores in it each struct node in term of list corruption . 

    //debugging functions
    void add_node_vector(Node* node)
    {
      debug_data.push_back(node);
    }

    void debug_remove_node(Node* node) 
    {
		auto delete_target = find(debug_data.begin(), debug_data.end(), node);
		if (delete_target == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(delete_target);
	  }

  public:

  Linked_list() {}    // default constructor 


  // to prevent copying ( unintended duplication of the object. ) , could be used as a singleton class design pattern 
  Linked_list(const Linked_list&) = delete;
  Linked_list &operator = (const Linked_list &another) = delete ; 


  // Destructor 
  ~Linked_list()
  {
    cout << "\nclearing the list from memory  ..... \n" ; 
    
    //HEADSHOT
    // destroying nodes from the start to the end 
    //make a temp node , assign it to the next node after the head node ->  shoot the head -> put a next target ( assign head into current )
    // Repeat the KILLING STREAK 
    // Time cComplex. = O(n) traversal through the whole list ocurred 
    // Space Complex. = O(1)
    
    while (head)
    {

      Node *temp_target_node = head->next; 
      delete head ; // HEADSHOT the head  
      head = temp_target_node ; // new target 

    }
  }



///////////////printing functions
  void print_head()
  {
    cout << "head address : " <<  head << endl; 
    cout << "head data : " << head->data << endl; 
  }


  void print_tail()
  {
    cout << "tail address : " <<  tail << endl; 
    cout << "tail data : " << tail->data << endl;  
  }

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

    void print_in_details(Node *node )
    {
      if(node == nullptr)
      {
        cout << "empty or end of the list ";
        return ; 
      }

      cout << node->data << " " ; 
      if( node->next == nullptr  )
      {
        cout << "X" ; 
      }
      else 
        cout << node->next->data << "  "; 

      if(node == head )
      {
        cout << "Head\n";
      }
      else if (node == tail)
      {
        cout << "tail\n" ; 
      }
      else 
        cout << "\n";
    }

// appending ( inserting ) functions
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

    void append_front(int data)
    {
      Node *new_node = new Node(data);
      new_node->next = nullptr;

      if (!head)
      {
        head = tail = new_node ; 
        ++list_length; 
      }
      else 
      {
        new_node->next = head;  
        head = new_node;  
        ++list_length; 
      }


    }


    // Deleting functions 


    void delete_node(Node *node_to_delete)
    {
      delete node_to_delete ; 
      node_to_delete = nullptr; 
    }

    void delete_front()
    {

      assert(list_length); // if list is empty , deletion is prohibited

      
      Node *current_node = head->next ;
      delete head; 
      head = current_node;

      --list_length;
    }


    void delete_end()       // stand-by ( future work )
    {
      if(list_length <= 1 )
      {

      }

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

    Node * get_position_from_back(int position)
    {
      assert(list_length);    // check first if the list is not empty 

      if( list_length < position) // check if the position is valid 
      {
        return nullptr;
      }
      return get_position( list_length - position + 1 ); 
    }

    bool same_comparision(const Linked_list &list_to_compare) // passed by reference , to save memory instead of making another copy of the object 
    {
      Node *head_1 = head;
      Node *head_2 = list_to_compare.head; 

      while ( head_1 && head_2) // check if both list head is not nulled ( not empty )
      {
        if(head_1->data != head_2->data)
          return false;
        head_1 = head_1->next;  //update to next nodes  
        head_2 = head_2->next; 
      }
      return !head_1 && !head_2; // to make sure both lists ends with each others 
    }                             // the logic used is when list 1 and list 2 reach end which is null 
                                  // the false will be casted to 1 , and 1 && 1 = 1 else 0 false 


    bool same_comparision_length_based(const Linked_list &list_to_compare)
    {
      if(list_length != list_to_compare.list_length)
      {
        return false;
      }

      Node *head_2 = list_to_compare.head;

      for (Node *current_node = head ; current_node ; current_node = current_node->next )
      {
        if(current_node->data != head_2->data )
          return false;
         head_2 = head_2->next; 
      }
      return true; 

    }

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



// integrity functions
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





  
  listA.append_front(13);
  listA.append_front(12);

 

  string true_values = "12 13 1 2 3 4 5 6 534 12134";
  string actual_values = listA.to_string();
  if(true_values != actual_values)
  {
    cout << "List error , no match between the expected list and the actual resulting list \n"; 
    cout << true_values << " is not matched with " << actual_values ;
    assert(false);  // terminate immediately 
  }

  listA.delete_front();
  listA.print();


  listA.print_head();

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
             
  return 0;
}
