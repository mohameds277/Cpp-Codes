#ifndef VECTOR_DS_H
#define VECTOR_DS_H



#include <iostream>
#include <cassert>



using std::cout;
using std::endl;
using std::swap;



class Vector 
{

    private :
        int *arr {nullptr};                
        int size {0};  
        int capacity{}; 
        void capacity_expander();

        
    public :
        Vector(int size);
        ~Vector();

        void set(int index, int val);
        int get_size();
        void print();

        int find(int value);

        int get(int index);

        int get_front();

        int get_back();

        void push_back(int value);

        void push_back_enhanced(int value);

        void insert(int index, int value);

        void pop(int index);

        int find_with_history(int value);

        void right_rotation();
        void left_rotation();

        void right_rotation(int n_time);
        void left_rotation(int n_time);
};

#endif