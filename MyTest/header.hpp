#ifndef headerHPP   // prevent duplicate file inclusions/ Header Guards
#define headerHPP

extern int externInt; // Declaration in hpp, definition in cpp,
                      // External Linkage: accessible by other files
inline int inlineInt;  // Shared across the entire program without ODR issues
static int staticInt;  // Each file including this header gets a unique
                       // independent variable
                       // Internal linkage: strictly private to the file


void headerFunction();
namespace header {
inline int add(int a, int b) {  // Enables header only libraries, avoid "multiple definition linker error"
  return a + b;
}
}


#endif

// interface

/* Specification Comments (RMEs)
  Requires: prerequisites for the function to make sense
  (implementation only needs to cover cases allowed by the interface's REQUIRE clause)
  Modifies: which things are potentially changed.
  Effects: specifies what the function does.
*/
