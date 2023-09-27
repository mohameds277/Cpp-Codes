#include "vector_DS.h"


   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// CLASS Constructor/Deconstructor /////////////////////////////////
        Vector::Vector(int size) : size(size)          // member initialization  list with size value (0) as above 
        {               

            if ( size < 0 )                                                                                     
                size = 1;             // for preventing memory size errors
            capacity = size + 10;                                                        // CLASS DE/CONSTRUCTOR
            arr = new int[capacity]{};      //dynamic allocation of an array for dynamic sizing 

        }

        Vector::~Vector ()
        {
            delete[] arr;               // de-allocating the array ( opposite of new[])   // delete the data
            arr = nullptr;              // null-pointer to prevent dangling pointers     // delete the  pointer 
        }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// // CLASS METHODS/FUNCTIONS/////////////////////////////////


        void Vector::capacity_expander()          //following function of the enhanced push_back() function ( made it private because if the evil forces got their hands on this function the whole array
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


     


// BASE DS OPERATIONS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// return the desired index value , before the return index validation must be checked to prevent returning illegal address
    int Vector::get(int index)
    {                                                                                              
            assert(0 <= index && index < size);
            return arr[index];
    }


// to set specific index with a  specific value 

void Vector::set(int index , int val )
{
    assert(0 <= index && index < size);             // error handler checker macro , 
    arr[index] = val;                                // to make sure the index is valid and prevent undefined behavior 
}                                                     // (not minus value  and not out of the vector range size ) 

int Vector::get_size()
{
    return size;
}


// to print the Vector values
void Vector::print()
{
    int i;
    for (i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl; 
}


// Search and retrive value in the Vector array
int Vector::find(int value)
{
    int i;
    for (i = 0; i < size; ++i)
        if(arr[i] == value)
            return i;
        return -1; 
}

int Vector::get_front()                 // Return the first element of the Vector 
{
    return arr[0];
}

int Vector::get_back()  
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
void Vector::push_back(int value)
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
void Vector::push_back_enhanced(int value)
{
    if( size == capacity )
        capacity_expander();
    arr[size++] = value ;
}



//INSERT INTO ARRAY OPERATION !!!!!

void Vector::insert ( int index , int value )
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

void Vector::pop(int index)
{
    assert(0 <= index && index < size);     // making sure the indies of the array are within the legal  declared range

    int deleted_value = arr[index];

    for (int i = index + 1; i < size; ++i)
    {
        arr[i - 1] = arr[i];
    }
    --size;
}

// this fucntion helps imporve searching overtime , close to search history , everytime this function is
// used to find a certain element , this element get shifted 1 step left , so next time the time to find it 
// become less , Note : the left shift without rotaion when reached to the start 
int Vector::find_with_history(int value)
{
    for (int i = 0; i < size; ++i)
    {
        if(arr[i] == value)
        {
            if ( i == 0 )
                return 0;         // element already at the top 

        swap(arr[i], arr[i - 1]); // swap it with the element before
        return i - 1; 
    }
    }
    return -1; // no element found 
}
//rotation functions
// only changes the rotation order of elements without affecting the size of capacity 

// rotation fucntion to rotate the whole vector array by 1 without affecting the capacity or size ( only changing in places)
void Vector::right_rotation()  
{

    int last_element_buffer = arr[size - 1]; 
    for (int i = size - 2  ; i >= 0; --i)
    {
        arr[i + 1 ] = arr[i];
    }
    arr[0] = last_element_buffer; 
}

// left rotation fucntion rotates the set of vector array to the left 1 step 
void Vector::left_rotation()
{
    int first_element = arr[0];

    for (int i = 1; i < size; ++i)
    {
        arr[i - 1 ] = arr[i];
    }
    arr[size - 1] = first_element;
}

// rotation right n time 
void Vector::right_rotation(int n_time)      //function overload 
{
    n_time = n_time % size;     //to optimize the n_times if it it's greater than the size to prevent 
    while (n_time--)                                // rotation repetition meaning if rotation time is 10 
    {                                                                        // for list sized 5 
        right_rotation();                                                       // the roation is the same
    }
}

// rotation left n time 
void Vector::left_rotation(int n_time)      //function overload 
{
    n_time = n_time % size;         //to optimize the n_times if it it's greater than the size to prevent 
    while (n_time--)                    // rotation repetition meaning if rotation time is 10 
    {                                                 // for list sized 5
        left_rotation();                                     // the roation is the same as the list original 
    }                                                                                              // order
}

