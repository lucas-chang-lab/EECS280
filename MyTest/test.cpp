// #define NDEBUG      // No Debug, only active during development, prevent assert run-time execution overhead
#include <iostream>
#include <vector>
#include <cassert> // assert
#include <utility> // pair
#include <algorithm> // min_element
#include <cmath>
#include <set>
#include <queue>
#include <stack>
#include <array>
#include <fstream>
#include <list>
#include <map>
#include "header.hpp"
#define ll long long
using namespace std;

// void modifyValue(int &x) { x = 20; } // parameter x -> reference to a
// int main() {
//   int a = 10;
//   modifyValue(a);
//   cout << a << '\n';
// }

// struct Player {
//   std::string name;
//   int age;

//   Player(string name, int age) : name(name), age(age) {};
// };

// void changeNamePtr(Player *player) { player->name = "Kai"; }

// void changeNameRef(Player &player) { player.name = "Kai"; }

// int main() {
//   Player player1{"Lucas", 8};
//   Player player4("Andrew", 18);

//   cout << player1.name << " " << player1.age << '\n';
//   Player &player2 = player1;
//   changeNameRef(player2);
//   cout << player2.name << " " << player2.age << '\n';
//   cout << player1.name << " " << player1.age << '\n';

//   Player *player3 = &player1;
//   changeNamePtr(player3);
//   cout << player3->name << " " << player3->age << '\n';
//   // cout << (*player3).name << " " << (*player3).age << '\n';
// }

// class Person {
// private: // Encapsulation: Declare data member as private
//         // Use getter function to read data
//         // Use setter function to modify data after validation
//   int age;
//   string name;

// public:
//   Person (int age, string name) {  // Parameterized Constructor
//     this->age = age;
//     this->name = name;
//   }
//   // Person (int age, string name): age(age), name(name) {};
//   Person (const Person& other) { age = other.age; name = other.name; } // copy constructor
//   string getName() const {
//     return name;
//   }
//   void externalClassFunction2();

//   virtual void introduce() {
//     cout << "Person introduction\n";
//   }
// };

// void Person::externalClassFunction2() { cout << name << '\n'; }

// // only works when getName() is a const member function
// void externalClassFunction(const Person &P) { cout << P.getName() << '\n'; }

// class Student : public Person { // inheritance / derived function
// private:  // Access Specifier
//   double score;

// public:
//   Student(int a, string b, double x) : Person(a, b), score(x) {} // Member Initializer List
  
//   double getScore() const { return score; } // member variable -> read-only
//   void introduce() override {
//     // Polymorphism: 1. Compile time Polymorphism (static binding): overloading
//     // (same function name but passing different parameters)
//     // 2. Runtime Polymorphism (dynamic binding): inheritance and Virtual
//     // Function executes the specific behavior of whichever child class happens to be attached to it
//     cout << "Student Introduction\n";
//   }
// };

// int main() {
//   Person p{11, "Lucas"};
//   // Person* pp = new Person(11, "Lucas");
//   // cout << p.age << " " << p.name << '\n';
//   externalClassFunction(p);
//   p.externalClassFunction2();
//   Student s(12, "Kai", 98);
//   s.introduce();

//   Person &ptrS = s;
//   ptrS.introduce();  // Virtual/Override: ignores the type of
//   poionter/reference,
//                      // looks directly at the memory address of the object
//                      itself
// }


// class Shape { // Abstract class: structural template,  architectural contract
// protected:    // so that derived class can use
//   int length, width;

// public:
//   Shape(int length, int width): length(length), width(width) {};
//   virtual int Area() = 0;
//   virtual ~Shape() {
//     cout << "Shape is deleted!\n";
//   }; // if not delete -> memory leak
//   // memory remains "in use" after the pointers go away. frees up memory so others can use that memory blocks
// };

// int Shape::Area() {
//   return length * width;
// }

// class Rectangle : public Shape {
// public:
//   Rectangle(int length, int width) : Shape(length, width){ cout << "Rectangle is created!\n"; };

//   int Area() override { return length * width; }
//   ~Rectangle() override { cout << "Rectangle is deleted!\n"; };
// };

// class Square : public Shape {
// public:
//   Square(int length, int width) : Shape(length, width){ cout << "Square is created!\n"; };

//   int Area() override { return length * length; }
//   ~Square() override { cout << "Square is deleted!\n"; };
// };

// int main() {
//   Shape *rec = new Rectangle(4, 5);   // abstract class cannot instantiate object
//   Shape *squ = new Square(4, 5);      // memeory address that points to the child concrete class (placeholder)
//   cout << rec->Area() << " " << squ->Area() << '\n'; // squ->Shape::Area()
//   delete rec; delete squ;
// }

 // int main() {

  // headerFunction();

  // int a = 10;
  // int* ptr = &a;  // holds the memory address of var
  // cout << &a << '\n';  // the address of a
  // cout << *ptr << '\n'; // the value of a (dereference)
  // *ptr = 15;    // modifying the value of a using pointer
  // cout << a << '\n';

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
  // cout << ptr1 << " " << ptr2 << " " << *ptr2 << " " << **ptr2 << '\n';


  // int x = 10;
  // int &ref = x;   // reference to the variable x,
  // cout << ref << '\n'; // ref, x refer to the same memory location
  // x = 20;
  // cout << ref << " " << x << '\n';

  // vector<int> nums = {10, 20, 30};
  // int *ptr = &nums[0];
  // cout << ptr << " " << *ptr << '\n';
  // ptr++;
  // cout << ptr << " " << *ptr << '\n';

  // vector<int>::iterator it = nums.begin();
  // cout << *it << '\n';
  // it++;
  // cout << *it << '\n';


  // vector<int> v = {3, 2, 4};
  // int maxx = *max_element(v.begin(), v.end());
  // for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
  //   cout << *it << " ";
  // }
  // cout << *(v.end()-1) << '\n';
  // vector<int>::iterator it = v.begin();
  // v.insert(it + 2, 6);
  // it = v.begin();   // the memory layout of the vector changes after
  // insert(); v.erase(it + 2);
  // sort(v.begin(), v.end());
  // for (auto &vv: v) cout << vv << " ";
  // cout << v.size() << " " << v.capacity() << '\n';

  // vector<int> vect{1, 2, 3};
  // cout << vect.at(1);
  // for (int &x : vect) {
  //   x += 5;
  // }
  // for (int x : vect) cout << x << " ";

  // pair<int, double> p = {1, 2.3};
  // cout << p.first << " " << p.second << '\n';

  // double pi = 3.14159265;
  // double intpart = 0;
  // double fractpart = 0;
  // fractpart = modf(pi, &intpart);
  // cout << intpart << " " << fractpart << '\n';

  // const int MAXUSER = 10; // read-only, cannot be modified after it is created


// }

// int divide(int a, int b) {
//   assert(b != 0 && "divisor is equal to 0"); // terminate the program via std::abort() if b == 0; // debugging tool
//   // a debugging tool to validate developer assumptions, catch programming logic
//   // bugs early in development
//   return a / b;
// }
// int main() {
//   cout << divide(4, 0) << '\n';
// }

// Time Complexity O(f) -> Worst Case Analysis, over all possible vairation of
// input


// inline eliminate function call overhead caused by cpu constantly jumping back and forth in
// memory, directly embed the code
// inline int add(int a, int b) { return a + b; }

// int main() {
  // cout << add(4, 8) << '\n';;
  // cout << header::add(4, 8) << '\n'; 
  // set<int> st{1, 3, 2};
  // st.insert(4);
  // // cout << st.size() << '\n';
  // // for (set<int>::iterator it = st.begin(); it != st.end(); it++)
  // //   cout << *it << " ";

  // cout << *st.rbegin() << " " << *(++st.rbegin())<< '\n';
  // cout << *(--st.rend()) << " ";
  // st.erase(3);
  // // for (int x : st)
  // //   cout << x << " ";
  // // cout << st.count(3) << " ";
  // // st.clear();
  // // cout << st.empty() << " ";
  // auto search = st.find(2);
  // if (search != st.end()) cout << *search << " " ;

  // queue<int> q;
  // q.push(4);
  // q.push(5);
  // while (!q.empty()) {
  //   cout << q.front() << " ";
  //   q.pop();
  // }
  // cout << q.back() << " " << q.size() << '\n';

  // stack<int> st;
  // st.push(1);
  // st.push(2);
  // cout << st.size() << " " << st.empty() << " " << st.top() << '\n';
  // st.pop();

  // deque<int> dq;
  // dq.push_front(5);
  // dq.push_front(6);
  // dq.push_back(7);
  // dq.pop_back();
  // dq.pop_front();
  // dq.push_back(10);
  // if (!dq.empty())
  //   cout << dq.front() << " " << dq.back() << " " << dq.size() << " " << dq[1]
  //        << " " << dq.at(1) << '\n';

  // cout << *dq.cbegin() << '\n';    // constant begin()

  // cout << "Name: ";
  // string name;
  // cin >> name; // ./test.exe < inputStream.txt
  // // input redirection: feed a file into stdin/cin, instead of typing
  // manually cout << name << '\n'; // ./testexe > outputStream.txt
  // // output redirection: send stdout/cout to a file instead of the terminal
  // cout << "Age: ";
  // int age;
  // cin >> age;
  // cout << age << '\n'; // diff inputStream.txt outputStream.txt
  // ./test.exe < inputStream.txt | grep ":" > outputStream.txt
  // pipeline | ,take the output of one command and send it directly as the
  // input into another command

  // int num;
  // ifstream fin("inputStream.txt");  // Open to read inputStream.txt
  // ofstream fout("outputStream.txt"); // Create a new file for writing
  
  // if (!fin.is_open() || !fout.is_open()) {
  //   cout << "open failed\n";
  //   return 1;
  // }

  // for (int i = 0; i < 5; i++) {
  //   fin >> num;   // extraction operator
  //   fout << num << '\n';   // insertion operator
  // }
  // fin.close();
  // fout.close();

  // string lineString;
  // getline(cin, lineString);  // preserve space and tabs
  // cout << lineString;

  // int x = 5;
  // const int &ref = x;  // type qualifier -> prohibit assigmment
  // x = 6;
  // cout << x << " " << ref << '\n';
  // ref = 7; // not allowed

  // int arr[5] = {1, 2, 3};
  // // cout << arr[2] << '\n';

  // array<double, 3> arr2 = {1.1, 1.2, 1.3};
  // // cout << arr2[0] << " ";

  // for (double x : arr2)
  //   cout << x << '\n';
  // for (const auto &x : arr2)
  //   cout << x << '\n';
  // for (array<double, 3>::iterator it = arr2.begin(); it != arr2.end(); it++) {
  //   cout << *it << '\n';
  // }

// }

// int main(int argc, char* argv[]) { // argument count and vector
//   if (argc != 3) {
//     cout << "argc doesn't match\n";
//     return 1;
//   }
//   string inName = argv[1];
//   string outName = argv[2];

//   string wordToRemove;
//   cin >> wordToRemove;

//   ifstream fin{inName};
//   ofstream fout(outName);

//   if (!fin.is_open() || !fout.is_open())
//     return 1;

//   string word;
//   while (fin >> word) {
//     if (word != wordToRemove) fout << word << '\n';
//   }
//   fin.close();
//   fout.close();
// }

/*Operator overloading in C++ allows you to redefine how standard operators
  behave when used with user-defined types (classes and structs) */

// class Vector2 {
// private:
//   double a, b;
//   array<int, 3> arr;

// public:
//   Vector2(double a, double b, std::array<int, 3> &arr) : a(a), b(b), arr(arr){};

//   int &operator[](int i) { return this->arr[i]; }
//   int operator[](int i) const { return this->arr[i]; }  
//   Vector2 &operator+=(Vector2& other) {
//     this->a += other.a;
//     this->b += other.b;
//     return *this;
//   }
//   Vector2 &operator*=(Vector2 &other) {
//     this->a *= other.a;
//     this->b *= other.b;
//     return *this;
//   }
//   friend std::ostream &operator<<(ostream &os, const Vector2 &v) {    // 2 operand
//     // non-member function, jut happens to be defined in he class block
//     // proper access to private a and b;
//     os << "a: " << v.a << "\nb: " << v.b << '\n';
//     return os;  // Return the chaining to allow chaining
//   }
//   friend std::istream &operator>>(istream &is, Vector2 &v) {
//     is >> v.a >> v.b;
//     return is;
//   }
//   double getA() { return a; }
//   double getB() { return b; }

//   // 1 operand
//   Vector2 operator++(int) {   // Postfix: c++ (Saves old state, increments, returns old state by value)
//     Vector2 temp = *this; // the temp variable is a local variable that will be  destroyed the moment the function hits the closing brace }.
//     this->a++;  // dangling reference
//     this->b++;  
    
//     return temp;  // return old state  
//   }
//   inline Vector2 &operator++() {  // Prefix: ++c (Increments and returns by reference)
//     a++;
//     b++;
//   return *this; 
  
// }
// };

// inline Vector2 &operator+(Vector2 &lhs, Vector2 &rhs) { 
//   lhs += rhs;
//   return lhs;
// };


// T = placeholder
// template <typename T> void printValue(T x) { cout << x << '\n'; }
// template <typename T> T add(T a, T b) { return a + b; }

// template <typename T> class Set {
// private:
//   vector<T> element;

// public:
//   bool contain(T x) {
//     for (auto v : element) {
//       if (v == x) return true;
//     }
//     return false;
//   }
//   void insert(T x) {
//     if (!contain(x)) element.push_back(x);
//   }
//   void print() {
//     for (auto v: element) cout << v << " ";
//   }
// };

// set<string> unique_words(vector<string> words) {
//   set<string> st;
//   for (int i = 0; i < (int)words.size(); i++) {
//     st.insert(words[i]);
//   }
//   return st;
// }


// // static storage: global variable, static member function, static variable
// in
// // function [global]
// // automatic storage: a local variable lives inside the block [stack]
// // dynamic storage: new -> delete (memeory leak) [heap]

// int main() {
//   int externInt = 8;
//   inlineInt = 8;
//   staticInt = 9;
//   // Local Object (On the stack), automatic 
//   Set<int> localSet; 
//   localSet.insert(3);
//   localSet.print();

//   // Dynamic Object (On the heap) -> new -> pointer
//   Set<int>* dynamicSet = new Set<int>;
//   dynamicSet->insert(3);
//   dynamicSet->print();

//   delete dynamicSet; // Dynamic objects stay in memory until you manually
//                          // delete them, otherwise memory leak
//   // 'localSet' automatically dies when out of scope (hits the closing bracket)

//   const int Num = 10;
//   int arr[Num]; // statically allocated array -> compile time

//   int howmany;
//   cin >> howmany;
//   int *arrptr = new int[howmany]; // dynamically allocated array -> runtikme
//   delete[] arrptr;

//   vector<string> words = {"1", "1", "1"};
//   set<string> st = unique_words(words);
//   for (string x : st) cout << x << '\n';
  // printValue(3.4);
  // cout << add(4.6, 5.5) << '\n';;

  // Set<int> IntSet;
  // IntSet.insert(4);
  // IntSet.print();

  // Set<string> StringSet;
  // StringSet.insert("a");
  // StringSet.insert("b");
  // StringSet.print();

//   array<int, 3> arr = {1, 2, 3};
//   Vector2 v2{1.0, 2.0, arr};
//   Vector2 v2_1{3, 5, arr};

//   cout << arr[1];
  // cout << v2;
  // v2 += v2_1;
  // cout << v2 + v2_1;
  // ++v2;
  // cout << v2;
  // v2++;
  // cout << v2;
  // cin >> v2;
  // cout << v2;

  // operator<<(cout, v2);
  // v2.operator+=(v2_1);
  // operator<<(cout, operator+(v2, v2_1));
  // v2.operator++();
  // operator<<(cout, v2);
  // v2.operator++(0);
  // operator<<(cout, v2);

  //   v2 *= v2 += v2; // operation chaining
  // list<int> myList = {1, 3, 4};

  // auto it = myList.begin();
  // for (; it != myList.end(); it++) {
  //   cout << *it << " ";
  // }
  // Invalidated iterator-> dangling pointers
  // for (list<int>::reverse_iterator it = myList.rbegin(); it != myList.rend();
  //      it++) {
  //   cout << *it << " ";
  // }
//   myList.push_back(1);
//   myList.pop_back();
//   myList.push_front(1);
//   myList.insert(myList.begin(), 8);
//   // myList.erase(myList.begin());
//   for (int x : myList) {
//     cout << x << " ";
//   }
//   cout << myList.front() << " " << *(--myList.end()) << '\n';
//   cout << myList.size() << " " << myList.empty() << '\n';
//   cout << *max_element(myList.begin(), myList.end());

// }


// 1. store unique key-value pairs 2. keep the keys sorted dynamically
// int main() {
  // map<int, string> mp{{3, "P2"}, {4, "P3"}};
  // mp[2] = "P1";
  // mp[5] = "P5";
  // cout << mp[2] << '\n';
  // for (map<int, string>::iterator it = mp.begin(); it != mp.end(); it++) {
  //   cout << (*it).first << " " << (*it).second << '\n';
  // }
  // for (const auto &x : mp)
  //   cout << x.first << " " << x.second << '\n';
  // mp.insert({6, "P7"});

  // cout << mp.insert(pair<int, string>(7, "P8")).second
  //      << '\n'; // 1 -> insert successfully
  // cout << mp.erase(10) << '\n'; // erase unsuccessfully
  // mp.clear();
  // cout << mp.empty() << '\n';


//   unordered_map<int, string> unordered_mp{{2, "P2"}, {1, "P1"}};  //
//   Completely unsorted, hash table unordered_mp.insert({4, "P4"}); for (const
//   auto &x : unordered_mp)
//     cout << x.first << " " << x.second << '\n';
// }

void counterFunction() {
  static int count = 0; // initialized only once, not visiable outside the function
  count += 10;
  cout << count << " ";
}
int main() {
  counterFunction();
  counterFunction();
}

// Unit testing is a software development practice where individual components
// or units of code (such as functions, methods, or classes) are tested in
// isolation to verify they work exactly as expected
// Arrange -> Act -> Assert
// Edge cases, extreme operating limits