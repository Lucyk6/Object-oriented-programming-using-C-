#include <iostream> 
int main()
{        
  //1
   #define PI 3.14
   std::cout << PI;

   //2
  #define sum(x,y) x+y
   int x = 5;
   int y = 7;
   std::cout << "SUM: " << sum (x,y) << std::endl;
   //3
  #define SQUARE(x) x * x
  std::cout << SQUARE(5); 
  std::cout << SQUARE(2 + 3);
  #define SQUARE(x) ((x) * (x))
  std::cout << "" << std::endl;
  //4
  #define SQUARE(x) ((x) * (x))
  //5
  #define MIN(a, b) ((a) < (b) ? (a) : (b))
  std::cout << MIN(4, 3);
  //6 and 7
  #define DEBUG
  #ifdef DEBUG
  std::cout << "Debug mode\n";
  #endif
  
  //8
  #ifndef RELEASE
  std:: cout << "Not release\n";
  #endif

  //9

#define version(int)
#if version==1
  std::cout << "v1";
#else 
  std::cout << "other version\n";
#endif

  //10
  #ifndef MY_HEADER_H
  #define MY_HEADER_H

  #endif 

  //11
#define LOG(l)
  int l = 10;
  std::cout << "File: " << __FILE__ << \
      ", Line: " << __LINE__ << \
      ", Message: " << (l) << std::endl;

return 0;
}
  //12
#include <iostream>
#include <string>
using namespace std;
#define PRINT(x) cout << #x << " = " << x << endl
int main()
{
    int age = 25;
    double price = 19.99;
    string name = "Alice";
    bool isActive = true;

    PRINT(age);
    PRINT(price);
    PRINT(name);
    PRINT(isActive);
}

  //13
  #include <iostream>
#include <string>
using namespace std;

#define MAKE_VAR_NAME(prefix, num) prefix##_##num
int main()
{

   int MAKE_VAR_NAME(var, 1) = 10;
   int MAKE_VAR_NAME(var, 2) = 20;
   int MAKE_VAR_NAME(var, 3) = 30;

    
   cout << "var_1 = " << var_1 << endl;
   cout << "var_2 = " << var_2 << endl;
   cout << "var_3 = " << var_3 << endl;
  
   return 0;
   
}
//14
#include <iostream>
#include <string>
using namespace std;

#define PRINT_VAR(x) cout << #x << " = " << x << endl;
int main()
{
  int a = 10;
  PRINT_VAR(a);
  //#x превращает в строку
   return 0;
}
//15
#include <iostream>
#include <string>
using namespace std;

#define CHECK(x) \
 if (!(x)) { \
      cout << "Error: " << #x << endl; \
  }

int main()
{
  int a = 5;
  int b = 10;

  CHECK(a > 0);         
  CHECK(b < 5);           
  CHECK(a + b == 15);   
  CHECK(a == b);         

   return 0;
  
}
//16
 
 #include <iostream>

#define SAFE_DELETE(ptr) \
    do { \
        if (ptr != nullptr) { \
            delete ptr; \
            ptr = nullptr; \
        } \
    } while (false)

int main() {
    int* p1 = new int(42);
    int* p2 = nullptr;

    SAFE_DELETE(p1); 
    SAFE_DELETE(p2); 
    SAFE_DELETE(p1); 

    return 0;
}
//17
#include <iostream>
#include <chrono>

#define TIMER_START() \
    auto timer_start = std::chrono::high_resolution_clock::now()

#define TIMER_STOP() \
    auto timer_end = std::chrono::high_resolution_clock::now(); \
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer_start); \
    std::cout << "Execution time: " << duration.count() << " μs" << std::endl

int main() {
    TIMER_START();

    for (int i = 0; i < 100000; ++i) {
        volatile int x = i * i;
    }

    TIMER_STOP();
    return 0;
}

//18

#include <iostream>

#define CHECK_PTR(ptr) \
    if (ptr == nullptr) { \
        std::cout << "Error: Null pointer detected at " << __FILE__ \
                  << ":" << __LINE__ << std::endl; \
        return -1; \
    }

int main() {
    int* valid_ptr = new int(10);
    int* null_ptr = nullptr;

    CHECK_PTR(valid_ptr); 
    std::cout << "Valid pointer check passed" << std::endl;

    CHECK_PTR(null_ptr);

    delete valid_ptr;
    return 0;
}
//19

#include <iostream>
#include <cstdlib>

#define SIMPLE_ASSERT(condition) \
   do { \
       if (!(condition)) { \
            std::cerr << "Assertion failed: " << #condition \
                      << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
            std::abort(); \
        } \
    } while (false)
int main() {
    int x = 5;
    SIMPLE_ASSERT(x == 5);  
    SIMPLE_ASSERT(x == 10);
    return 0;
}

//20
#include <iostream>
using namespace std;

#define DEBUG

#ifdef DEBUG
#define DEBUG_LOG(x) cout << "DEBUG: " << x << endl;
#else
#define DEBUG_LOG(x)
#endif

int main()
{
    DEBUG_LOG("Test message");
}





