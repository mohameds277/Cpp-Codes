#ifndef VECTOR_UF_H
#define VECTOR_UF_H


class Vector 
{

    private :
        int *arr {nullptr};                
        int size {0};  
        int capacity{}; 
        void capacity_expander();

        
    public :
        Vector(int size) : size(size) {};
        ~Vector();

        void set(int index, int val);
        int get_size();
        void print();

        int find(int value);

        int get_front();

        int get_back();

        void push_back(int value);

        void push_back_enhanced(int value);

        void insert(int index, int value);

        void pop(int index);

        void right_rotation();
        void left_rotation();

        void right_rotation(int n_time);
        void left_rotation(int n_time);
};

#endif