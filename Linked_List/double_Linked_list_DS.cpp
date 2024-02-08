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


//Building block of each node of the linked list
struct Node //
{
  int data{} ;                // initialized to zero to prevent garbage value initialization
  struct Node *next{nullptr};       // initialized to nullptr to prevent wild pointers 
  struct Node *previous{nullptr};

  Node(int data) : data(data) {}     // every time a new node is constructed then
                                                // a node with data and next is nulled like below node

    void set_pointers(Node *nxt , Node *prv)
    {
        this->next = nxt;
        this->previous = prv;
    }

  ~Node()
  {
      cout << " Destroying the node " << data << " that belong to the node address " << this << endl;
  }
};                                    

//              ----------------------------
//  nullptr <--| prev_ptr|Data    | next_ptr| --> nullptr
//              ----------------------------


//Double linked list class 
class D_Linked_list 
{
    private:
        Node *head{nullptr};
                        // Head 
//              ----------------------------
//  nullptr <--| prev_ptr|Data    | next_ptr| --> nullptr(replaced with node after insertion )
//              ----------------------------


        Node *tail{nullptr};

                    // Tail 
//              ----------------------------
//  pre-node <--| prev_ptr|Data    | next_ptr| --> nullptr
//              ----------------------------



        int list_length{};          // list length , to maintain a base logic for addition and deletion operation also to help assertion checks.



        // for Backup and debugging

        vector<Node*> debug_data;	// add/remove nodes you use

	    void debug_add_node(Node* node) 
        {
		    debug_data.push_back(node);
	    }
	    void debug_remove_node(Node* node) 
        {
		    auto it = std::find(debug_data.begin(), debug_data.end(), node);
		    if (it == debug_data.end())
			    cout << "Node does not exist\n";
		    else
			    debug_data.erase(it);
	    } 



    public:
        D_Linked_list() {}
	    D_Linked_list(const D_Linked_list&) = delete;
	    D_Linked_list &operator=(const D_Linked_list &another) = delete;





            
        void print() 
        {
            for (Node* cur = head; cur; cur = cur->next)
                cout << cur->data << " ";
            cout << "\n";
        }

        
        void print_reversed()  {
            for (Node* cur = tail; cur; cur = cur->previous)
                cout << cur->data << " ";
            cout << "\n";
        }

        // backup functions
        void delete_node(Node* node) {
            debug_remove_node(node);
            --list_length;
            delete node;
        }

        void add_node(Node* node) {
            debug_add_node(node);
            ++list_length;
        }

        // Linker function ( IMPORTANT FUNCTION THAT DISTINGUISH SINGLE LINKED LIST from THE DOUBLE  )

        void nodes_linker(Node *pre_node , Node *post_node)
        {
            if(pre_node) pre_node->next = post_node;
            if(post_node) post_node->previous = pre_node ; 
        }


        // Double linked-list ADT operations 

        //1) Insertion operations


        void insert_front(int data )
        {
            Node *inserted_node = new Node(data);

            if(!head) head = tail = inserted_node ;
            else 
            {
                nodes_linker(inserted_node , head);
                head = inserted_node ; 
            } 
        }

        void insert_end(int data )
        {
            Node *inserted_node = new Node(data);
            debug_add_node(inserted_node);

            if(!head)
            {
                head = tail = inserted_node ;
            }
            else 
            {
                nodes_linker(tail ,inserted_node );
                tail = inserted_node;
            }
            ++list_length;

        }
};



int main()
{
    D_Linked_list DL1 ; 

    DL1.insert_end(1);
    DL1.insert_end(2);
    DL1.insert_end(3);
    DL1.insert_end(4);
    DL1.insert_end(5);
    DL1.insert_end(6);
    DL1.insert_end(7);


    DL1.print();
    DL1.print_reversed();

    D_Linked_list DL2 ;

    DL2.insert_front(1); 
    DL2.insert_front(2); 
    DL2.insert_front(3); 
    DL2.insert_front(4); 
    DL2.insert_front(5); 
    DL2.insert_front(6); 
    DL2.insert_front(7);


    DL2.print();





    
















    return 0; 
}
