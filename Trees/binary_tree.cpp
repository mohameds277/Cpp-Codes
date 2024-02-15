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



struct Node 
{

    char data{};
    struct Node *left{nullptr};                                         //                          Parent  
    struct Node *right{nullptr};                                        //                         /      \
                                                                        //                         left    right                 
    Node(int data ) : data(data) {}

    ~Node()  
    { 
        cout << " Destroying the node " << data << " that belong to the node address " << this << endl; 
    }

};

void print_in_order(Node *current_root)             // LVR ( Left , parent , right)
{
    if(!current_root) return ; 

    print_in_order(current_root->left);
    cout << current_root->data << " "; 
    print_in_order(current_root->right);

}

void print_pre_order(Node *current_root)                              // VLR (parent , left  , right)
{
    if(!current_root)   return ; 

    cout << current_root->data << " " ; 

    print_pre_order(current_root->left);
    print_pre_order(current_root->right);
}

void print_post_order(Node *current_root)           // LRV      (Left,Right,Parent)
{

    if(current_root == nullptr)  return ; 

    print_post_order(current_root->left);
    print_post_order(current_root->right);

    cout << current_root->data << " " ; 

}


char toggle(char chr)
{
     // A -> 65 / Z->90 
    if (chr >= 65 && chr <=90) // small alpha. 
            return chr + 32 ;                     //cout << char(int(chr) + 32) << endl ;
    else 
         return chr - 32 ;                                       //cout << char(int(chr) - 32) << endl ;
}


int main()
{
    Node n(1);

    Node *root = new Node('*');

    root->left = new Node('+');

    root->right = new Node('4');

    root->left->left = new Node('6');

    root->left->right = new Node('8');


//              Root 
//             /    \ 
//          node_1  node_2
//          /    \
//     node_3   node_4
    

    print_post_order(root);

    cout << endl;

    print_in_order(root);

    cout << endl;

    print_pre_order(root);

    char chr = 'h';
    chr = toggle(chr);

    cout << chr << endl; 

    int fact = 1 ; 
    int n1 = 5 ;
    for ( int i = 1 ; i <= n1 ; i++)
    {
        fact = fact * i ; 
    }
    cout << fact ; 

   
    return 0 ;
}

