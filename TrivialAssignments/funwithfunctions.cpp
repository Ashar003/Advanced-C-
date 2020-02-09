#include <iostream>
#include <initializer_list>
using namespace std;

template<typename T>
T sum(T v){
    return v;
}

template<typename T, typename... Args>
T sum(T first, Args... args){
    return first + sum(args...);

}
int main(){
    // cout<< "answer \n";
    cout<<sum(1,2,3) ;
    cout<< "\n";
    cout<<sum(10,20,3) ;
    cout<< "\n";

    return 0;
};


