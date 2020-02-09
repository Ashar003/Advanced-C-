//Akash Sharma
//Polynomial using map
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

template<class T>
class Polynomial {
  private:
    map<int,int>* p; //  <exponent, coefficient> setup
  //instead of p1,p2, and sum, I made a single p* and intialized...
  public:
   //ans polynomial to set equal
    Polynomial(const Polynomial& s){  
      p = new ::map<int,int>(*(s.p));
    }//set equal to another
  //destructor
  ~Polynomial()
    {
      delete p;
    }
  //empty constructor
    Polynomial() {
      p= new ::map<int,int>();
    }//empty

    //passing in map by ref constructor
    Polynomial(map<int,int>& map){
      p = new ::map<int,int>(map);
    }//pass-in constructor

    //string constructor
    Polynomial(string polyInput){
      p = new ::map<int,int>();
      vector<string> n;
      stringstream ss(polyInput);
      string temp;

      while(ss >> temp) //while there is input stream from ss going to temp string
        n.push_back(temp); //push to vector, but at the end of it, the string temp that is being pushed to from while
      
      map<int,int> &referencedPolynomial = *p; //pointer
      for (auto increment=1; increment<n.size(); increment+=2) { 
          //n
        T coeff = stoi(n[increment-1]);
        T expo = stoi(n[increment]); //stoi:: string to int
            if (referencedPolynomial.find(expo) != referencedPolynomial.end()){ //find expo
                T co = referencedPolynomial[expo]; 
                coeff = coeff + co; 
                referencedPolynomial[expo] = coeff; //set
        } else
        {
          referencedPolynomial[expo] = coeff;
        }
      }

    }//constructor with string

    void print(){
      ::map<int,int> &referencedPolynomial = *p; //pointer
      typename map<int,int>::reverse_iterator i; // return backend
        //map method
      for (auto increment=referencedPolynomial.rbegin(); increment != referencedPolynomial.rend(); increment++){
            int expo = increment->first;
            int coeff = increment->second; //set
        if (!(coeff > 0)){ cout << coeff << "x^" << expo;} 
            else{ cout << "+" << coeff << "x^" << expo;}        
      }
      cout<<endl; //newline
    }//print

    string convString() const{
      string answer; //empty
      map<int,int> &referencedPolynomial = *p; //pointer
      typename ::map<int,int>::reverse_iterator i; //typename template; returns backend

        for (auto increment=referencedPolynomial.rbegin(); increment != referencedPolynomial.rend(); increment++){
                int expo = increment->first;
                int coeff = increment->second; //set
                //use index to refer
            if (!(coeff < 0)){ answer = answer + "+" + ::to_string(coeff) + "x^" + ::to_string(expo);}  //if coefficient is greater than 0, then add +
                else if(coeff < 0){ answer = answer + ::to_string(coeff) + "x^" + ::to_string(expo);}    //else don't.    
        }
      return answer; //string
    }//convString

    
    map<int,int> operator+(const Polynomial& s){
      map<int,int> summation(*p); 
      map<int,int> &sPoly = *(s.p);
      //two maps: one being added and the other one
      for (auto increment=sPoly.begin(); increment!=sPoly.end(); increment++){ 
            T expo = increment->first; //set expo T type
            T coeff = increment->second; //set coeff T type
            //set coeff and expo with index
            //if there's more to the 3xpo
        if (sPoly.find(expo) != sPoly.end()){
            T co = summation[expo]; //set
            coeff = coeff + co; //coeff add
            summation[expo] = coeff; //set
        } else{
          summation[expo] = coeff; //set
        }
      }
      return summation;
    }//+

    map<int,int> operator-(const Polynomial& s){ //type map
        //pointers
      map<int,int> subtraction(*p); 
      map<int,int> &sPoly = *(s.p);
      //begin and end method of map
      for (auto increment=sPoly.begin(); increment!=sPoly.end(); increment++) {
            T expo = increment->first; //expo
            T coeff = increment->second; //coeff
        if (!(sPoly.find(expo) != sPoly.end())){
          subtraction[expo] = -1 * coeff; // *-1
        } else if(sPoly.find(expo) != sPoly.end()) {  
            T co = subtraction[expo]; //set
            co = co + (-1 * coeff); //-1
          subtraction[expo] = co; //set
        }
      }
      return subtraction;    
    }//-

    map<int,int> operator*(const Polynomial& s){
      map<int,int> product;
      map<int,int> &referencedPolynomial = *p;
      map<int,int> &sPoly = *(s.p);

      //auto makes it very easy 
      //begin and end of map
      for (auto increment=sPoly.begin(); increment!=sPoly.end(); increment++){ //start at beginning and increment as long as you don't touch the end
            T expo = increment->first;
            T coeff = increment->second; // point  that index to the expo/coeff
        for (auto jincrement=referencedPolynomial.begin(); jincrement!=referencedPolynomial.end(); jincrement++){
            T coeff_product = coeff * jincrement->second;      //mult
            T expo_summation = expo + jincrement->first;     //add    
          if (!(product.find(expo_summation) == product.end())){ // if the 
                coeff_product = coeff_product + product[expo_summation]; //coeff + expo
                product[expo_summation] = coeff_product; 
          } 
          product[expo_summation] = coeff_product;
        }
      }
      return product;
    }//*

     Polynomial& operator=(const Polynomial& s){ 
      if (this == &s){ return *this; }
      //if it's itself return.
      //otherwise
      delete p; //deallocate p
      p = new map<int,int>(*(s.poly)); //set equal
      return *this;  //retur refeence
    }//=


};

//global
    vector<string> inputNumbers;
    ifstream inputfile("input.txt");
    ofstream outputFile("output.txt");
    string take;

     void chickenScratch(string output, int lineNumb ){
       //SEPERATE OUTPUT method
       outputFile<<"Line number: "<< lineNumb<<endl;
       outputFile<<output<<endl; 
    }//OgInputOuput

    void keepInputting(){ //inputting line by line
        int line = 0; // for output purposes
        while (getline(inputfile, take )){
             inputNumbers.push_back(take); // while there is more, push it onto the vector
            chickenScratch(take, line++);
        }
    }//input

    void keepOutputting(string output,Polynomial<int> to ){
        cout<<output<<endl;
        to.print();
        //print to terminal
        //print to file
        outputFile<<output<<endl;
        //convert to string
        outputFile<<to.convString()<<endl;
    }//outputResults

int main(){
  
    keepInputting(); //takes input from file and does the main work

  Polynomial<int> EquationOne(inputNumbers[0]); //file line 0  //p1
  Polynomial<int> EquationTwo(inputNumbers[1]); //file line 1 //p2
  ::map<int,int> addition = EquationOne + EquationTwo; //+
  ::map<int,int> subtraction = EquationOne - EquationTwo; //-
  ::map<int,int> mutlipication = EquationOne * EquationTwo; //*
 

 //OUTPUT TO TERMINAL AND FILE!
  keepOutputting("Polynomial Equation One: ", EquationOne);
  keepOutputting("Polynomial Equation Two: ", EquationTwo);
  keepOutputting("Polynomial Equation One added to Equation Two ", addition);
  keepOutputting("Polynomial Equation One subtracted against Equation Two: ", subtraction);
  keepOutputting("Polynomial Equation One multiplied with Equation Two: ", mutlipication);


    outputFile.close(); //close file writer
  return 0;
}

