#include <iostream>
#include <vector>
#include "header.hpp"
#define ll long long
using namespace std;

// void modifyValue(int &x) { x = 20; } // parameter x -> reference to a
// int main() {
//   int a = 10;
//   modifyValue(a);
//   cout << a << '\n';
// }

int main() {

  headerFunction();

  // int a = 10;
  // int* ptr = &a;  // holds the memory address of var
  // cout << &a << '\n';  // the address of a
  // cout << *ptr << '\n';  // the value of a (dereference)

  // int *ptr;
  // cout << ptr; // wild pointer, contain a random address

  // int *ptr = nullptr;
  // cout << ptr;
  // dangling pointer refers to memory which has already been freed or is no
  // longer valid
  // ex. a pointer points to a local variable that has gone out of scope

  // int var = 10;
  // int *ptr1 = &var; // Double Pointer: pointers that point to other pointers
  // int **ptr2 = &ptr1;
  // cout << **ptr2;

  // int x = 10;
  // int &ref = x;   // reference to the variable x,
  // cout << ref << '\n'; // ref, x refer to the same memory location
  // x = 20;
  // cout << ref << " " << x << '\n';

  // vector<int> v = {1, 2, 3};
  // // for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
  // //   cout << *it << " ";
  // // }
  // // // cout << *(v.end()-1) << '\n';
  // for (auto it = begin(); )

  // vector<int> vect{1, 2, 3};
  // for (int &x : vect) {
  //   x += 5;
  // }
  // for (int x : vect) cout << x << " ";

  
  
}
