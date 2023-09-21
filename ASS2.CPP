#include <iostream>
#include <cstring>
using namespace std;

char *revword(char *string);
void revline(char styx[], int x);
void countVowels(char **ptr, char *s);
void rev(char *A[]);

int main()
{
    int choice;
    char s[69];
    char styx[20];
    char *A[4];
    for (int i = 0; i < 4; i++)
    {
        A[i] = new char[100];
        cout << "Enter Line " << (i + 1) << " : ";
        cin.getline(A[i], 99);
    }
    cout << "Reversed Array :" << endl;
    rev(A);
    cout << "Which line to reverse ? ";
    cin >> choice;
    revline(A[choice - 1], choice);
    
    countVowels(A, s);

    return 0;
}

void rev(char *A[])
{
    char *rev[4];
    for (int i = 0; i < 4; i++)
    {
        rev[i] = new char[101];
        rev[i] = A[3 - i];
        cout << rev[i] << endl;
    }
    delete[] *rev;
}

void countVowels(char **ptr, char *s)
{

    int vc = 0;
    for (int i = 0; i < 4; i++)
    {
        char *p = ptr[i];
        while (*p != '\0')
        {
            switch (*p)
            {
            case 'A':
            case 'a':
            case 'E':
            case 'e':
            case 'I':
            case 'i':
            case 'U':
            case 'u':
            case 'O':
            case 'o':
                s[vc] = *p;
                vc++;
                break;
            }
            p++;
        }
    }
    if (vc > 0)
    {
        cout << "Vowels: ";
        for (int i = 0; i < vc; i++)
            cout << s[i];
    }
    else
        cout << "No vowels in the array." << endl;
}


char *revword(char *string)
{
    char *rev = new char[strlen(string) + 1];
    char *p1 = rev, *p2;
    for (p2 = &string[strlen(string) - 1]; p2 >= string; p1++, p2--) // Fixed the loop condition
    {
        *p1 = *p2;
    }
    *p1 = '\0';

    return rev;
}
void revline(char styx[], int x)
{
    int ch = x - 1;
    char nStyx[100];
    strcpy(nStyx, "");
    char *token = strtok((styx), " ");
    while (token != NULL)
    {
        strcat(nStyx, revword(token));
        strcat(nStyx, " ");
        token = strtok(NULL, " ");
    }
    cout << nStyx << endl;
}