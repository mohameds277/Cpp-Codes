#include <iostream>
#include <cassert>

//Array-based Stack data structure 
class Stack{

    private : 
        int size{};         // Stack size
        int top{};          // stack array top indicator 
        int* stack_array{};       // stack array 

    public :
        Stack(int size ) :         // stack object constructor with  
                                        //initializer list size when making an object and -1 for top 
                size(size) , top(-1)
        {
            stack_array = new int[size];      // Dynamicly allocating the array for the stack 
        } 

        // array-based stack ADT operations 

        //Push (insert to stack ) , first checks an assertion if the stack is full ( stack overflow) , if all good to go , then the data 
        // that was passed from argument will be filled in the array stack indexed in (top++) because top initially is -1 and to keep the top of stack synced with the last pushed element 
        void push(int data)
        {
            assert(!is_full_stack());       // making sure that the stack has enough space ( prevents stack overflow problem )
            stack_array[++top] = data ;     // because  top starts with -1 , then in each push the top indicator get updated first then 
        }                                                    // the data fills in the stack 
                                                                // in order to sync the data in stack with the top indicator


        //Pop (delete from stack ) , first checks an assertion if the stack is not empty , if all good to go , returns the popped value and updates the top (top--)
        int pop()                                                                                               
        {
            assert(!is_empty_stack()); 
            return stack_array[top--];
        }

        void peek()
        {

        }

        bool is_full_stack()
        {
            return top == size - 1 ;
        }

        
        bool is_empty_stack()
        {
            return top == -1  ;
        }












};









int main()
{

}