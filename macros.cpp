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
  //12
    return 0; 
}
