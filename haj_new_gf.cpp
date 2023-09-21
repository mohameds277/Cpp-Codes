//Assignment 2
// Student name : Ahmad AlHaj


//Assignment description  :
//Assume the array of char pointers char* A[4] and the user prompted to enter the values from keyboard.
// // 1.Write a function to reverse the array.
// // 2.Write a function to reverse a selected line.
// Extra feature : if user enters wrong number , the program picks random ranged number instead of error
// // 3.Write a function to print the most repeated character in the array.
// // 4.Write a function that returns a string of all vowel characters in the array.



//////////////////Used libraries
#include <iostream>                //for standard input/output
#include <cstring>                 //for strings built-in functions 
#include <cstdlib>                 // for dynamic memory allocation and random fucntion
#include <ctime>                   //for time functions


#define word_size 25                // pre-proccess value for the word size 

#define pointers_array_size 4       // pre-process value for the array of char pointers size ( 4 words )



using std::cin;
using std::cout;                       // directives  for specific names
using std::endl;
using std::string;



//////////////////Used functions
void print_array(char *A[]);                          // prints the array
void print_element(char A[]);                        // prints specific array element
void fill_array(char *A[]);                          // dynamically fills array from standard input ( user input )
void reverse_array(char *A[]);                      // reverse array
void reverse_line(char *A[], int selected_line);    // reverse specific line word
char get_most_frequent_character(char *A[]);         // counts most repeated/frequent char in array
string find_vowels(char *A[]);                        // finds all vowels occurrences in the array





// prints the array
void print_array(char *A[])
{
  for (int i = 0; i < pointers_array_size; ++i)
  {
    cout << A[i] << " ";
  }
  cout << endl;
}


// prints specific array element
void print_element(char A[])
{
  cout << A;
  cout << endl;
}
// dynamically fills array from standard input ( user input )
void fill_array(char *A[])
{
  for (int i = 0; i < pointers_array_size ; ++i)
  {
    A[i] = new char[word_size];
    cin.getline(A[i], word_size );
  }

}


// reverse array
void reverse_array(char* A[]) {
  for (int i = 0; i < pointers_array_size / 2; ++i) {
    char* temp = A[i];
    A[i] = A[pointers_array_size - i - 1];
    A[pointers_array_size - i - 1] = temp;
  }
}

// reverse specific line word
void reverse_line(char* A[], int selected_line) {        // generic swap
  for (int i = 0; i < pointers_array_size / 2; i++) {

    char temp = A[selected_line][i];
    A[selected_line][i] = A[selected_line][pointers_array_size - i - 1];
    A[selected_line][pointers_array_size - i - 1] = temp;

  }
}


// counts most repeated/frequent char in array
char get_most_frequent_character(char* A[]) {
  int char_count[256] {};

  char most_frequent_char = '\0';
  int max_char_count = 0;

  for (int i = 0; i < pointers_array_size; i++) {
    char* current_char_pointer = A[i];
    while (*current_char_pointer != '\0') {
      char_count[*current_char_pointer]++;
      if (char_count[*current_char_pointer] > max_char_count) {
        max_char_count = char_count[*current_char_pointer];
        most_frequent_char = *current_char_pointer;
      }
      current_char_pointer++;
    }
  }

  return most_frequent_char;
}


// finds all vowels occurrences in the array
string find_vowels(char* A[] )  {
  string vowels = "aeuioAEUIO";
  string detected_vowels_string;

  for (int i = 0; i < pointers_array_size; ++i ) {
    char* current = A[i];
    while (*current != '\0') {
      if (strchr(vowels.c_str(), *current)) {
        detected_vowels_string += *current;
      }
      current++;
    }
  }

  return  detected_vowels_string;
}



//---->Program entry point<----//
int main() {
  char* A[4];
  int line_num_to_reverse;
  char most_repeated_char ;
  int random_valid_selection;
  srand(time(0));

  fill_array(A);
  print_array(A);

  reverse_array(A);
  print_array(A);

  cout << "Enter the line number to reverse  it's word \n";
  cin >> line_num_to_reverse;
  if (line_num_to_reverse == 1 )
    line_num_to_reverse = line_num_to_reverse - 1;

  if (line_num_to_reverse > -1 && line_num_to_reverse < 4)
  {
    reverse_line(A, line_num_to_reverse);
    print_element(A[line_num_to_reverse]);
  }
  else
  {
    cout << "Wrong index entry \n";
    random_valid_selection = rand() % 3 + 1 ;
    cout << "assuming your selection number is " + random_valid_selection;
    reverse_line(A, random_valid_selection);
    print_element(A[random_valid_selection]);
  }



  most_repeated_char = get_most_frequent_character(A);
  cout << "Most repeated/frequent character: " << most_repeated_char << endl;

  string vowels = find_vowels(A);
  cout << "Vowels: " << vowels << endl;

  return 0;
}
