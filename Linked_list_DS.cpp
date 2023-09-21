
//Building block of each node of the linked list 
#include <iostream>

using std::cout;
using std::endl;
using std::swap;

struct Node 
{
    int data{} ;                // initialized to zero to prevent garbage value initialization 
    struct Node *next{};            

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
            while( temp_node != nullptr)
            {
                cout << temp_node->data << "->";        // print the current node 
                                                
                temp_node = temp_node->next;    // and then update to the next node 
            }
            cout << "NULL(end of the list)" ; 
            cout <<endl;

        }

        void print_method_2()   // more compressed and convenient   print method using for_loop
        {
            for (Node *current_node = head; current_node; current_node = current_node->next)
            {
                cout << current_node->data << " ";

            }
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

        Node* get_nth_element(int number_position)
        {
            int start_counter{};
            for (Node *current_node{head}; current_node; current_node = current_node->next)
            {
                if(start_counter++ == number_position)
                    return current_node; 
            }
            return NULL;
        }

        void search_by_value(int searched_data) // only print the location based on value , can be modified to return index by replacing
        {                                                               // cout<<index ; return ;  with return index ; 
            int index_number{};
            for (Node *current_node{head}; current_node; current_node = current_node->next , index_number++) 
            {                                                       // Remember , never mess with the head !!! 
                if ( current_node->data == searched_data  )
                {
                    cout << index_number;
                    return;
                }
 
            }
            cout << "-1";
        }

        //(optimized solution version 1 ! )
        void search_by_value_optimized_MK1(int searched_data) // optimized from above method , when value is searched , the node 
        {                                                    // shifts one left for faster search for the SAME ELEMENT (most requested)
            int index_number{};
            Node *previous_node{};      //to keep previous node 

            for (Node *current_node{head}; current_node; current_node = current_node->next, index_number++)
            { // Remember , never mess with the head !!! 
                if ( current_node->data == searched_data  )
                {   
                    if(!previous_node)  // in case the node reached the head of the list ( no previous node available  )
                    {                        // when occurs , the rest of the  program will be spared 
                        cout << index_number;
                        return;
                    }

                    swap(previous_node->data, current_node->data) ;  //only the data nodes  swaps , not the whole nodes (optimized solution!)
                    cout << index_number - 1   ;
                    return;
                }
                previous_node = current_node;   //store the previous node state 
            }
            cout << "-1"; 
        }

        //(optimized solution Version 2 !! )
        void search_by_value_optimized_MK2(int searched_data) // optimized from above method , when value is searched , the node 
        {                                                    // shifts one left for faster search for the SAME ELEMENT (most requested)
            int index_number{};

            for (Node *current_node{head} , *previous_node{nullptr} ; current_node ;  previous_node = current_node  , 
            current_node = current_node->next ,index_number++ )
            { // Remember , never mess with the head !!! 
                if ( current_node->data == searched_data  )
                {   
                    if(!previous_node)  // in case the node reached the head of the list ( no previous node available  )
                    {                        // when occurs , the rest of the  program will be spared 
                        cout << index_number;
                        return;
                    }

                    swap(previous_node->data, current_node->data) ;  //only the data nodes  swaps , not the whole nodes (optimized solution!)
                    cout << index_number - 1   ;
                    return;
                }
            }
            cout << "-1"; 
        }

        void delete_end()
        {
            
            --list_length; 
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
    listA.print_method_2();



    // base linked_list ADT + ending append + printing list : functional and tested.

    
    Node *temp{};
    temp = listA.get_nth_element(9); // test for  get_nth_element() method
    if(!temp)
        cout << "NULL";
    else 
        cout << temp->data;                 // if data returns , position found , else NULL
    

    cout << endl; 


    listA.search_by_value(4);       //print search

    cout << endl;


    listA.search_by_value_optimized_MK1(3); // print search optimized (prints the location - 1 )

    cout << endl;

    listA.search_by_value_optimized_MK2(3); // print search optimized (prints the location - 1 , not same as  the above 
                                                                // method because MK1 was tested before it ) 
                                                                // don't believe me ? comment it then ! 

    return 0;
}
