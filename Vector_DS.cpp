
//This code is implementing and mimicing the stl::vector data structure  in C++ 
////Fetures and notes  : 

//          -Dynamic size
//          -uses pointers 
//          -user_defined data strucutre ( closer to STL vector )
//          -functions implemented inside the class body ( no fucntion prototyping )


#include <iostream>
#include <cassert>


using std::cout;
using std::endl;
using std::swap;

class Vector 
{
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////CLASS ATTRIBUTES /////////////////////////////////
    private :
        int *arr {nullptr};                
        int size {0};   // user's size 
        int capacity{}; // actual size (behind the scene size)             <----- for better performence

                          
        void capacity_expander()          //following function of the enhanced push_back() function ( made it private becuae if the evil foruces got their hands on this fucntion the whole array
        {                                                                                                                                               // world will be at risk :|)
            capacity = capacity * 2;

            int i;
            int *arr2 = new int[capacity];

            for (i = 0; i < size ; ++i)
            {
                arr2[i] = arr[i];
            }

            swap(arr, arr2);

            delete[] arr2;
            arr2 = nullptr;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// CLASS METHOD/FUNCTIONS/////////////////////////////////
    public : 
        Vector(int size) : size(size)          // member initialization  list with size value (0) as above 
        {               

            if ( size < 0 )                                                                                     
                size = 1;             // for preventing memeory size errors
            capacity = size + 10;                                                        // CLASS DE/CONSTRUCTOR
            arr = new int[capacity]{};      //dynamic allocation of an array for dynamic sizing 

        }

        ~Vector ()
        {
            delete[] arr;               // dellocating the array ( opposite of new[])   // delete the data
            arr = nullptr;              // nullpointer to prevent dangling pointers     // delete the  pointer 
        }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// // CLASS METHODS/FUNCTIONS/////////////////////////////////


// BASE DS OPERATIONS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// return the desired index valye , before the return index validation must be checked to prevent returning illegal address
    int get(int index)
    {                                                                                              
            assert(0 <= index && index < size);
            return arr[index];
    }


// to set specific index with a  specific value 

void set(int index , int val )
{
    assert(0 <= index && index < size);             // error handler checker macro , 
    arr[index] = val;                                // to make sure the index is valid and prevent undefined behavior 
}                                                     // (not minus value  and not out of the vector range size ) 

int get_size()
{
    return size;
}


// to print the Vector values
void print()
{
    int i;
    for (i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl; 
}


// Search and retrive value in the Vector array
int find(int value)
{
    int i;
    for (i = 0; i < size; ++i)
        if(arr[i] == value)
            return i;
        return -1; 
}

int get_front()                 // Return the first element of the Vector 
{
    return arr[0];
}

int get_back()  
{                               //Return the rear end of the Vector 
    return arr[size - 1];
}



// Advacned  DS OPERATIONS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// void push_back(int value)
// {
//         ++size;                                  This code function works , but it's prone to bugs and errors
//         arr[size - 1] = value;                      because the new size was not allocated into a new array 
// }                                                   


// push fucntion that appends values into the end of the Vector , better than the above function because it's more
// dynmicly allocating the new size by making new array with size + 1  then copying old array into it , then swaping the pointers 
// and finally deletating the old array after swap for saving memory space 
// Slow , Big O = O(N) if adding one element at the time , O(N^2) if adding many elements using iterattives 
void push_back(int value)
{
        int *arr2 = new int[size + 1];      // allocating the new array +1 to be pushed

        int i;
        for (i = 0; i < size; ++i)            //copy the old elements into the new array (arr2)
        {
            arr2[i] = arr[i];
        }

        arr2[size++] = value;                   // push the desired value into the last index of the new array 

        swap(arr, arr2);                        //swaping pointers , so the old array (arr) becomes the new array (arr2)
                                                // but with the name arr , because it's used mostly 


        delete[] arr2;                          // delete the swapped array (arr2) which is the old array
        arr2 = nullptr;
}


// ehanced version of push_back fucntion , better performece , only expands/dobules the vector size after the old or users's size 
// reaches the under the scene  capacity ( actual capacity ) 
void push_back_enhanced(int value)
{
    if( size == capacity )
        capacity_expander();
    arr[size++] = value ;
}



//INSERT INTO ARRAY OPERATION !!!!!

void insert ( int index , int value )
{
    assert(0 <= index && index < size);                 // making sure the index value is legal !!



    if ( size == capacity )                             // checking if the actual array size capacity is enough 
        capacity_expander();

    for (int i = size - 1; i >= index; --i)             //starts shifting from the end until reaching the desired insert index position
    {                                                   //NOTE : The right shifting process starts from the end , because if the process starts from the start or insert position 
        arr[i + 1] = arr[i];        //right shift                                               // then the value will overwrite on the shifter postion !!!! 
    }

    arr[index] = value;                                 // after the shifting process , the empty position will be asigned to the inserted value

    ++size;                                             // update the size after the insertion , 
                                                                // Reminder size is the filled elements in array , capacity is the filled elements + empty indeces . 
                                                                
}

void right_rotation()   // rotate fucntion to rotate the whole vector array by 1 without affecting the capacity or size ( only changing in places)
{

    int last_element_buffer = arr[size - 1]; 
    for (int i = size - 2  ; i >= 0; --i)
    {
        arr[i + 1 ] = arr[i];
    }
    arr[0] = last_element_buffer; 
}


};




// let's put  the Vecotr user_defined data struture to test , shall we ?  
int main()
{

    Vector v(10);             // initlized array with size 10 

    for (int i = 0; i < v.get_size();  ++i)        //fill each index array with same value of that inedex ( only fill first 10 places)
    {                                   // example : index -> 0 stores value -> 0 , index -> 1 stores value -> 1 
        v.set(i , i ) ; 
    }

    cout << v.get_size();       // Test case : size before the append

    cout << endl;


    // v.push_back(13);
    // v.push_back(15);
    // v.push_back(134);                // slow push_back function call 
    // v.push_back(10456);

    v.push_back_enhanced(15);
    v.push_back_enhanced(25);
    v.push_back_enhanced(646);          // enhanced push_back function call 
    v.push_back_enhanced(23545);


    cout << v.get_size();      //TEST case : size after the append 

    cout << endl;

    v.print();  // print test of the filled Vector , must print number from 0 to 9 + the appended numbers

    v.insert(2, 50);

    v.print();

    v.right_rotation();
    v.print();

    cout<< v.find(5) << " " << v.find(10); // find a certian value within the Vector v

    return 0;

}