#include"vector_DS.h"



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

    cout << "vector list print test : ";
    v.print(); // print test of the filled Vector , must print number from 0 to 9 + the appended numbers


    v.insert(2, 50);
    cout << "vector insertion list print test : ";
    v.print();

    cout << "vector right rotate list print test : ";
    v.right_rotation();
    v.print();

    cout << "vector left rotate list print test : ";
    v.left_rotation();
    v.print();


    cout << "vector right rotate 5 times  list print test : ";
    v.right_rotation(5);
    v.print();

    cout << "vector left rotate 5 times  list print test : ";
    v.left_rotation(5);
    v.print();

    cout << v.find(5) << " " << v.find(10); // find a certian value within the Vector v

    
    return 0;

}
