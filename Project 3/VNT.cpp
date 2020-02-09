//Akash Sharma 381
//Readjusted my safematrix
#include <iostream>
#include <cmath>
using namespace std;

template <class T>
class SafeMatrix{
    private:
    //vars for successful sa
        int verticalLow;
        int verticalHigh;
        int horizontalLow;
        int horizontalHigh;
        int row;
        int height;
        int width;

        T** p; //pointer
    public:
    
    // default constructor
    // allows for writing things like SA a;
    SafeMatrix(){ 
        verticalLow=0;
        verticalHigh=-1;
        horizontalLow=0;
        horizontalHigh=-1;
        height = 0;
        width = 0;

        p=NULL; // ull pointer
    }
    // 2 parameter constructor lets us write
    // SA x(10,20) and get a safe 10X20 matrix;
    SafeMatrix(int verticalSize, int horizontalSize){
        verticalLow=0;
        verticalHigh=verticalSize-1;
        horizontalLow=0;
        horizontalHigh=horizontalSize-1;
        height = verticalSize;
        width = horizontalSize;

        p=new T*[height];  // dyanmically allocate to pointer p of height specified
       
        for(int i=0;i<height;i++){
            p[i]=new T[width]; //give each column a row
        }
    }

    // destructor
    ~SafeMatrix(){
        for(int i=0;i<height;i++){
            delete [] p[i];  //delete each row
        }
        delete [] p; //delete entire thing
    }
    
    
    SafeMatrix& operator=(const SafeMatrix &passed){
        if(this==&passed) return *this; // if it's itself
        
        for(int i=0;i<height;i++){
            delete [] p[i];  //delete each row
        }
        delete [] p; //delete entire thing
        
        verticalLow=passed.verticalLow;
        verticalHigh=passed.verticalHigh;
        horizontalLow=passed.horizontalLow;
        horizontalHigh=passed.horizontalHigh;
        height = verticalHigh-verticalLow+1;
        width = horizontalHigh-horizontalLow+1;
        
        p= new T*[height]; 

        for(int i=0; i<height; i++){
            p[i]= new T[width];//for each row
        } 
        for(int i=0; i<height; i++){
            for(int j=0;j<width;j++){
                p[i][j] = passed.p[i][j]; // assignment
            }
        }
        return *this; //return reference
    }
    
    class Helper { //a helper class to help with matrix operator
    private:
        T* array; //pointer
        int lowH;  //low
        int highH; //high
    public:
        Helper(T* passed, int low, int high){ //constructor taking in a pointer, low, and high of matrix
            array = passed;
            lowH = low;
            highH= high;
        }
        
        T& operator[](int index) { //type t
            if(!(index<lowH || index>highH)){
                //move on
            }else if((index<lowH || index>highH)){
                // cout<<"out of range";
                exit(1); //what else?
            }
            return array[index-lowH];
        }
    };
    
    Helper operator[](int rrow){ //type jelper
       
        if(!(rrow<verticalLow || rrow>verticalHigh)){ // is the row less than range?
            row = rrow-verticalLow; // find the row
            
        }else if(rrow<verticalLow || rrow>verticalHigh){
            // cout<<"out of range";
            exit(1);
        }
         Helper helper(p[row],horizontalLow, horizontalHigh);
             return helper;
    }
    
    SafeMatrix<T> operator*(const SafeMatrix &s){
        int answer;
        if(!(width != s.height)){
            SafeMatrix<T> answer(height,s.width);
        for (int row= 0; row < answer.height; row++) {
            for (int col = 0; col < answer.width; col++) {
                answer[row][col]=0;
                for (int in = 0; in < answer.height; in++) {
                    answer[row][col] += p[row][in]*s.p[in][col];
                }
            }
        }
                
        }else if(width != s.height){ //if width and height match
            cout<<"Width and height need to be the same"<<endl;
            exit(1);
        }
        return answer;
    }//operator*
    
    template <class U>
    friend ostream& operator<<(ostream& os, SafeMatrix<U> s);
};

template <class T>
ostream& operator<<(ostream& os, SafeMatrix<T> s){
    for(int i=0; i<s.height; i++){
        for(int j=0; j<s.width; j++){
            cout<<s.p[i][j]<<" ";
        }
        cout<<endl;
    }
    return os;
};

class VNT { //VNT

private:
    int height;
    int width;
    int MAX_INT;
    SafeMatrix<int> matrix;
public:
    
    //two parameter constructor
    VNT(int height, int width){
        this->height=height;
        this->width=width;

        matrix = SafeMatrix<int>(height,width); //construct SA
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                matrix[i][j] = INT_MAX; //set all to INT_MAX
    }
    
    bool find(int value){ //value we're looking for
        int row = height - 1; //bottom
        int column = 0; // start from the leftmost
        //basic search algoirhm
        while (row >= 0 && value < matrix[row][column]) {
            row--;
        }
        while(value > matrix[row][column] && column < width - 1) {
            column++;
        }
        if(!(matrix[row][column] == value)) { //not found
            return false;
            }
        else if(matrix[row][column] == value){ //if found
            return true;
        } ;
        return false;
    }//find
    
    //add a value to the VNT
    void add(int value){
        if (!(matrix[height - 1][width - 1] < INT_MAX)) {
            // cout << "Not Full";
        }else {
            cout << "Full";
            return;
        }
        matrix[height - 1][width - 1] = value;
        
        int row = height - 1;
        int col = width - 1;
        //start at top right
        
        while (row > 0) { //while row isn't 0 or less
            col = width - 1; 
            if (matrix[row - 1][col] > matrix[row][col]) // if the value underneath is greater
                swap(matrix[row - 1][col], matrix[row][col]); //swap
            while (col > 0) { //while col isn't 0 or less
                if (row == 1 && (matrix[row - 1][col - 1] > matrix[row - 1][col])) { //adjust when row is 2
                    swap(matrix[row - 1][col - 1], matrix[row - 1][col]);
                    swap(matrix[row][col - 1], matrix[row][col]);
                }
                else if (matrix[row][col - 1] > matrix[row][col]) {
                    swap(matrix[row][col - 1], matrix[row][col]);
                }
                col--;
            }
            row--;
        }
    }//add
    
    int getMin(){ //min
        if (matrix[0][0] == INT_MAX) { //if assigned max at first
            cout << "VNT is Empty" << endl;
            return INT_MAX;// what else is the min if not this?
        }
        
        int min = matrix[0][0]; //start 
        int row = 0;
        int column = 0;
        //top left
        
        while (row < height - 1) { //while
            column = 0; //start at beginning
            if (matrix[row + 1][column] > matrix[row][column]) //how to move around
                swap(matrix[row + 1][column], matrix[row][column]);
            while (column < width - 1) { //while we have not transcended column bounds
                if (row  == height - 2 && (matrix[row + 1][column + 1] > matrix[row + 1][column])) {
                    swap(matrix[row + 1][column + 1], matrix[row+ 1][column]);
                    swap(matrix[row][column + 1], matrix[row][column]);
                }
                else if (matrix[row][column + 1] < matrix[row][column]) {
                    swap(matrix[row][column + 1], matrix[row][column]);
                }
                column++;
            }
            row++;
        }
        matrix[height - 1][width - 1] = INT_MAX;// have we seen this idea...
        return min;
    }//gMin
    
    void sort(int arr[], int size){
        VNT sort(sqrt(size) + 1,sqrt(size) + 1); //coonstruct for sorting purposes
        
            for (int Index = 0; Index < size; ++Index){
                sort.add(arr[Index]);};
                //adding to VNT
            for (int Index = 0; Index < size; ++Index){
                arr[Index] = sort.getMin();};
                //assigning min to index from VNT
            
    }//sort
    // void print(){
    //      int row = 0; //bottom
    //     int column = 0; // start from the leftmost
    //     
    //     for(row ;row<= height-1 ; row++){
    //         for(column;column <= width-1; column++){
    //             cout<<matrix[row][column];
    //         }
    //     }
    //     cout<<endl;
        
    // };
    
    
};


int main(){
    
 
    VNT matrix(4,4); //no template t; just 
    //16
    //not 5,7
    // VNT matrix(5,7);
    //ADD
    matrix.add(9);
    matrix.add(8);
    matrix.add(7);
    matrix.add(5);
    matrix.add(2);
    matrix.add(6);
    matrix.add(2);
    matrix.add(8);
    matrix.add(100);
    matrix.add(3);
    matrix.add(5);
    matrix.add(8);
    matrix.add(9);
    matrix.add(2);
    matrix.add(7);
    matrix.add(61);
    //16 values

   
//GETMIN
    cout<<"The minimum value in VNT table is: "<<matrix.getMin()<<endl;

    int findValue = 61; //find this
   
//FIND
    if(matrix.find(findValue)){
        cout<<"Found "<<findValue << " in VNT table\n";
    }else{
        cout<<"Did not find "<<findValue << " int VNT table\n";
    }
    findValue = 999;

      if(matrix.find(findValue)){
        cout<<"Found "<<findValue << " in VNT table\n";
    }else{
        cout<<"Did not find "<<findValue << " int VNT table\n";
    }
   
    {
        //SORT
    int unsorted[20]= {21,61,19,30,43,451,78,84,47,845,820,60,9,0,3,1,8,4,7,5};
         cout<<"Unsorted array : "<<endl;
            for(int numb:unsorted){ //
                 cout<<numb<<" ";
        }//for
    cout<<endl;
    
    cout<<"Sorted array : "<<endl;
  //sort
        matrix.sort(unsorted, 20);
            for(int numb:unsorted){ //
                cout<<numb<<" ";
            }//for
    }
   
    
    
    return 0;
}
