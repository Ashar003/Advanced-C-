#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;
//Akash Sharma 381, some functions are defunt/some aspects are defunct.
//cout functions as well

//to solve the error
template <class T> // no candidate function
class SA;

template <class T> //no candidate function
ostream& operator<<(ostream& os, SA<T> s);

template <class T> // no candidate function
class Matrix;

template <class T> //no candidate function
ostream& operator<<(ostream& os, Matrix<T> s);

//Provided code
template <class T>
class SA {
    private:
		int low, high;
		T* p; //template
    public:
		// default constructor
		// allows for writing things like SA a;
		SA() {
			low=0;
			high=-1;
			p=NULL;
		}
		// 2 parameter constructor lets us write
		// SA x(10,20);
		SA(int l, int h){
			if((h-l+1)<=0) {
				cout << "constructor error in bounds definition" << endl;
				exit(1);
			}
			low=l;
			high=h;
			p=new T[h-l+1]; //Template T
		}
		// single parameter constructor lets us
		// create a SA almost like a "standard" one by writing
		// SA x(10); and getting an array x indexed from 0 to 9
		SA(int i) {
			low=0;
			high=i-1;
			p=new T[i]; //Template T
		}
		// copy constructor for pass by value and
		// initialization
		SA(const SA & s){
			int size=s.high-s.low+1;
			p=new T[size];
			for(int i=0; i<size; i++)
				p[i]=s.p[i];
			low=s.low;
			high=s.high;
		}
		// destructor
		~SA(){
			delete [] p;
		}
		//overloaded [] lets us write
		//SA x(10,20); x[15]= 100;
		T& operator[](int i){
			if(i<low || i>high){
				cout<< "index "<<i<<" out of range"<<endl;
				exit(1);
			}
			return p[i-low];
		}
		// overloaded assignment lets us assign
		// one SA to another
		SA & operator=(const SA & s){
			if(this==&s)return *this;
			delete [] p;
			int size=s.high-s.low+1;
			p=new T[size];
			for(int i=0; i<size; i++)
				p[i]=s.p[i];
			low=s.low;
			high=s.high;
			return *this;
		}
		// overloads << so we can directly print SAs
		friend ostream& operator<< <T>(ostream& os, SA<T> s);
}; //SafeArray

template <class T>
ostream& operator<<(ostream& os, SA<T> s){
    int size=s.high-s.low+1;
    for(int i=0; i<size; i++)
		os<<s.p[i]<<endl;
    return os;
};

template <class T>
class Matrix {
    private:
		int rl, rh, cl, ch; // upper and lower bounds specifiable on each of the dimesnions
		SA<SA<T> > p; //SafeArray ontop of another to mimic an matrix ;TEMPLATE
    public:

//TO HELP WITH INSTANIATION OF DIFFERENT KINDS OF PARAMETERS
    void Instaniate2(int j, int k){
        cout<<"called 2"<<endl;
        SA<SA<T> > row(j); // create row
		for (int i=0; i<j; i++) {
			row[i] = SA<T>(k); // make a safe array in each row
            // cout<<"called 2 forloop";
		}
        p = row; // assign p to matrix

    } //Instaniate2
    void Instaniate1(int j){
        cout<<"called 1"<<endl;
        SA<SA<T> > row(j);
		for (int i=0; i<j; i++) {
			row[i] = SA<T>(j); // make a safe array in each row
            // cout<<"called 1 forloop";
		}
        p = row;

    } //Instaniate1
    void Instaniate4(int a, int b, int c, int d){
        cout<<"called 4"<<endl;
       SA<SA<T> > row(a, b); 
		for (int i=a; i<=b; i++) {
			row[i] = SA<T>(c, d); // make a safe array in each row
            // cout<<"called 4 forloop";
		}
		p = row;

    }// Instaniate4

    // 0 parameter constructor lets us write
    // Matrix x();
    Matrix(){
		rl = 0;
		rh = 0;
		cl = 0;
		ch = 0;
    }    
    // 1 parameter constructor lets us write
    // Matrix x(10);
    Matrix(int o){
		cl = rl = 0;
		ch = rh = o; 
		SA<SA<T> > row(o);
		Instaniate1(o);
    }
    // 2 parameter constructor lets us write
    // Matrix x(10,20);
    Matrix(int r, int c){
		cl = rl = 0;
		rh = r-1;
		ch = c-1;
		Instaniate2(r,c);
		
	}

	// 4 parameter constructor lets us write
    // Matrix x(10,20,10,20);
    Matrix(int a, int b, int c, int d){
		if (b + 1 <= a || d + 1 <= c) {
			cout << "constructor error in bounds definition" << endl;
            exit(1);
		}
        //class protocol assingment
		rl = a;
		rh = b;
		cl = c;
		ch = d;
        Instaniate4(rl,rh,cl,ch); // call to 4 function parameter
    }
    // destructor
    // ~Matrix(){
    //     int i;
    //     SA<SA<T> > row(i);
	// 	for ( i=rl; i<=rh; i++) {
    //         delete [] row;
	// 	} //defunt not working

    // }
    //overloaded () lets us write
    //Matrix x(10,20)
    T& operator()(int i, int j){
		if(i< rl || i>rh || j< cl || j>ch){ //check what's out of range 
			cout<< "Row or column index"<<i<<" is out of range" <<"please check again"<<endl;
			exit(1);
		}
		return p[i][j]; //if not then return //SUCCESSFUL
    }

    // overloaded assignment lets us assign
    // one Matrix to another
    Matrix & operator=(Matrix & s){
		if(this==&s)return *this; // if it's the same..
		rl = s.rl;
		rh = s.rh;
		cl = s.cl;
		ch = s.ch;
        //assign for ease

		SA<SA<T> > row(rl, rh); // 2 parameter
		for (int i=rl; i<=rh; i++) {
			row[i] = SA<T>(cl, ch); //assign into each
			for(int j=cl; j<=ch; j++) {
				row[i][j] = s(i,j);
			}
		}
		p = row;//
		return *this; // return a ref/
    }

    // overloading of * multiplication lets us multiply 
    // one Matrix to another
    Matrix operator*(Matrix & s){
		if (ch - cl != s.rh - s.rl) { // ARE THEY EQUAL IN SIZE?
			cout<<"not equal"<<endl; 
            exit(1); //if not exit!
		}
		Matrix<T> multi(rl, rh, s.cl, s.ch); // CALLS UPON 4 PARAMETER! also whats the matrix that's being called second
        int mrl = multi.rl;
        int mch = multi.ch;
        int mrh = multi.rh;
        int mcl = multi.cl;
        //SO WE DO'T HAVE TO EVAULATE EACH TIME!!
		for (int i = mrl; i <= mrh; i++) { //USING THAT WE ACCESS PROPERTIES, row
			for (int j = mcl; j <= mch; j++) { //column
				for (int k=0; k<=ch-cl; k++) {  // how much space 
					if (k > 0) {  //at 0, we need cannot add nothing , so must set eequal
                        multi.p[i][j] = multi.p[i][j] + p[i][k + cl] * s.p[k + s.rl][j]; //ACCESS VIA 4 PARANETER FUNCTION THE MATRIX
					} 
                    if(k ==0 ) multi.p[i][j] = p[i][k + cl] * s.p[k + s.rl][j]; // 0!!
					}
				}
			}
		return multi; // return the matrix multipleied
    
	}//operator *
	
    // overloads << so we can directly print SAs
    friend ostream& operator<< <T>(ostream& os, Matrix<T> s);
};

template <class T>
ostream& operator<<(ostream& os, Matrix<T> s){
    for(int i=s.rl; i<=s.rh; i++) { //low row & high row
		for (int j=s.cl; j<=s.ch; j++) { // low col and high col
			os<<s.p[i][j] << " "; 
		}
		os<<endl;
	}
    return os;
};



int main(){
//  Matrix<int> ~m(10,10); //destructor check
//empty array multipication
//haven't implennted putting into array
Matrix<int> m(10,10);
Matrix<int> g(10,10);
Matrix<int> c(20,10);
Matrix<int> h(10,20);
 cout<<m*g<<endl;
 cout<<c*m<<endl;
//  cout<<c*g<<endl;
//  cout<<m*c<<endl;

return 0;
}//main

