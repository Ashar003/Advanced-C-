// //Akash Sharma
//Waxman's template

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector> 

template<class T> 
 class SA_STL{
    private:
    int low, high;
    int* p;
    
//priv
    public:
    // default constructor
// allows for writing things like SA_STL a;
SA_STL(){
    low=0; 
    high=-1;
    p=nullptr;
    }

// 2 parameter constructor lets us write // SA_STL x(10,20);

SA_STL(int l, int h){ 
    if((h-l+1)<=0){
    std::cout<< "constructor error in bounds definition"<<std::endl;
     exit(1);
     }
        low=l;
        high=h;
        p=new int[h-l+1]; 
        }

        // single parameter constructor lets us
// create a SA_STL almost like a "standard" one by writing 
// SA_STL x(10); and getting an array x indexed from 0 to 9

SA_STL(int i){ 
    low=0; 
    high=i-1;
     p=new int[i];
}
// copy constructor for pass by value and 
// initialization
SA_STL(const SA_STL & s){
    int size=s.high-s.low+1;
    p=new int[size];
    
    for(int i=0; i<size; i++)
        p[i]=s.p[i]; 
        low=s.low;
        high=s.high; }

// destructor
~SA_STL(){
delete [] p;
}

//overloaded [] lets us write
 //SA_STL x(10,20); x[15]= 100;

int& operator[](int i){ 
    if(i<low || i>high)
{
    std::cout<< "index "<<i<<" out of range"<<std::endl; 
    exit(1);}

    return p[i-low];
}

bool findValue(int value, int size){   //find value
      int *start = p;
      int *end = p + size;

      if (!(end == std::find(start, end, value))) return true; // find of stl
      //if found
        return false; //default
    }//find

// overloaded assignment lets us assign 
// one SA_STL to another

SA_STL & operator=(const SA_STL & s){
     if(this==&s)return *this; // if it's itself
        
        delete [] p; //
     int size=s.high-s.low+1; //pull the high and low
     p=new int[size]; //point to dynamically allocated

//set the properties
    for(int i=0; i<size; i++)
        p[i]=s.p[i]; 
        low=s.low;
        high=s.high; 
    return *this;  //return ref
}; //=

void sortIt(int size)
    {
     //sort of stl   
      int *start = p;
      int *end = p + size;
      int index = 0;
      //pointers for vector sorting; beginning and ending
      std::vector<int> myvector (start, end); //make
      std::sort (myvector.begin(), myvector.begin()+size);  //sort

      //as long as we have not hit the end keep overwriting array's value with pointer
      for (std::vector<int>::iterator i=myvector.begin(); i!=myvector.end(); ++i)
        p[index++] = *i;
    }//sort

 void arrayCon(T array[], int sizeA){
        for (int index=0; index <sizeA; index++) p[index] = array[index]; // give it a new array and copy vals
      }//convet Array

    void print(int size){
        for(int index = 0; index< size; index++){
            std::cout << p[index] << std::endl;
        }
    }//print

 };

// overloads << so we can directly print SA_STLs 

// friend std::ostream& operator<<(std::ostream& os, SA_STL<T> s);
 
// template<class T>
// std::ostream& operator<<(std::ostream& os, SA_STL<T> s){
//      int size=s.high-s.low+1;
//         for(int i=0; i<size; i++)
//         std::cout<<s.p[i]<<std::endl; 
//         return os;
// };

int main(){

//STL SA
SA_STL<int> a(0,10);
 
  int value = 33;
  int array[] = {1,99,10,88,187,21,33,0,5,9,3};
  int size = *(&array + 1) - array; // SIZE OF ARRAY
    
    //size passed in for ease in functions
  a.arrayCon(array, size); // convertArray

//   std::cout << "Originally: "<< a.print(size)<<std::endl;
std::cout << "Originally: "<<std::endl;
a.print(size);//print

//SORT
  a.sortIt(size); //sort
//  std::cout<< std::endl;
 std::cout<< "Sorted Array: " << std::endl;
  a.print(size);

//FIND
if(a.findValue(value , size)){
    std::cout << "Found value: " << std::to_string(value) << std::endl;
} else
  {
    std::cout << "Did not find value: " << std::to_string(value) << std::endl;
  }
value = 1349;
  if(a.findValue(value , size)){
    std::cout << "Found value: " << std::to_string(value) << std::endl;
} else
  {
    std::cout << "Did not find value: " << std::to_string(value) << std::endl;
  }


return 0;
}
 
