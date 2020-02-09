//Akash Sharma 381
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

//provided node class
template<class T> class node{
    private://nothing
    public:
     T coe;
     T power;
    node* train = NULL; 

    //no parameter
    node(){}
    node(T c, T p){//2  parameter: coefficient and power
        power=p;
        coe = c;
        } 
};//Node

 class Polynomial{
    private://nothing
    public: 
        string input;  //how it initally comes in
        node<int> *f; //where canonical form is stored
   
    //Let us create a 1 parameter
        Polynomial(string eq){
            // cout<<eq<<"nothing";
            input = eq;
//vector
            vector<int> n;
            stringstream s(eq); //convert and rq string
            string b;
                while(s >> b){ //while it's available
                    // cout<<b;
                    n.push_back(stoi(b)); //add element to back of vector & parse using stoi
                };

        cout<<"going to make it canonical"<<endl;
            f=makeCanonical(n); // store result in the node of the polynomial
        };
//method 
        node<int>* makeCanonical( vector<int> n){
            if(!isitValid(n)) { //check!
                exit(1);
            }
        node<int> *f = new node<int>(n[0],n[1]); // with the first node
            for(int i =2; i< n.size(); i = i+2){ // have taken care of the first two
                node<int> *s = new node<int>(n[i],n[i+1]); 
                    if(connect(f,s) ==1){ // is it connectable?
                    }
                    else {            
                        if(f->power < s->power) { //if power is less , thans witch
                            s->train = f;
                            f = s;
                        }
                        else {
                            while (f->train != NULL && f->train->power > s->power) { // is it null and is the power of collective node class greater?
                                f = f->train;
                            }
                            s->train = f->train; //switch
                            f->train = s;
                        }
                    }
                    s = NULL; //for the next iteration
                }
                return f; //set it equal
    }//makeCanonical
        
        int connect(node<int> *hq, node<int> *j) {
            bool iterative = true;
            while(iterative == true) { //break out only by returning
                if(hq->power == j->power) { //if powers are similar then we can connect the coe
                    hq->coe += j->coe;
                    return 1; // 
                }
                else if (hq->train != NULL) { //check if it's null
                    hq = hq->train; // connect 
                }
                else { 
                    return -1; 
                    } // if none, then exit
    }
    return -1;
}//connect 
   Polynomial operator+(const Polynomial &s) { // prevent change
    //    cout<<addition<<"add"<<endl;
       Polynomial add(input +" "+ s.input);
       return add;
       //return combined;
   }//+
   Polynomial operator-(const Polynomial &s) {
    //    cout<<"sub"<<endl;
    //    string subtract = this->input - s.input;
    while(s.f->coe != s.f->coe){ // while it does not loop around to itself, multiply coefficients by -1
    s.f->coe = s.f->coe * -1;
    }
    Polynomial sub(input +" "+ s.input);
       return sub;
    
   }//-
   Polynomial operator*(const Polynomial &s) {
        while(s.f->power != s.f->power || this->f->power !=this->f->power){ // while it does not loop around to itself, multiply coefficients by -1
        if(s.f->power == this->f->power) {
            this->f->coe= s.f->coe * this->f->coe;
        }
       
    }
       Polynomial mult(input + " "+ ""); // since one holds the coefficients
        return mult;
   }//*


bool isitValid(vector<int> n){ //size check
    if(n.size() % 2 != 0 || n.size() == 0){
                cout<<"size of vector"<<n.size()<< "not suffice"<<endl;
                return false;
            }
    return true;
}//isitValid
 };//polynomial

 void print(node<int>* p, ofstream &file_out) {
    //  cout<<"i was here"<<endl;
    
   if(p == NULL) { //segmentation fault
       file_out << endl;
       return;
   }
   
//    cout<<"was i here"<<endl;
   file_out << p->coe << "" <<"x^" <<p->power;
   //file_out<<"+";
   print(p->train, file_out);
   
}//print
 
   




int main(int argc, char* argv[]) { //number of, and array to file
    if (argc < 3) { //checks for input and output files
    cout<<"arguments number "<<argc<< " not sufficient"<<endl;
		exit(1);
    }

    ifstream file_in(argv[2]);
    ofstream file_out(argv[3]);
    string line;
    // cout<<"going in"<<endl;

   while(getline(file_in, line)) {
    //    cout<<line;
       Polynomial f(line);
       getline(file_in, line);
       Polynomial s(line);
       print(f.f,file_out);
       print(s.f, file_out);//print to output file

       Polynomial addition(f+s);
      print(addition.f, file_out);
       Polynomial subtraction(f-s);
    print(subtraction.f, file_out);
       Polynomial multiply(f*s);
    print(multiply.f, file_out);
        
      
   }
//close both
    file_in.close();
    file_out.close();
    return 0;
}
