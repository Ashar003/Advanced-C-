//Akash Sharma
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
using namespace std;
//global vars
    int numberLine;
    string lineRead;
    map<string,pair<int,list<pair<int,int> > > > Inverted;
    ifstream inputfile("Gettysburg Address.txt");
    int incrementer;
    string word;

bool checkArgs(int i){
    return lineRead[i] != ' '&& lineRead[i] != ',' && lineRead[i] != '.' && lineRead[i] != '-'; //uneeded ; chars that are not essential; by line
} //check

void Add(string lineRead, map<string,pair<int,list<pair<int,int>>>> &Inverted, int lineNumber){
    string word;
    int incrementer = 0;

    while(lineRead.length() > incrementer){
        while(checkArgs(incrementer)){
            word = word + lineRead[incrementer++]; //append word with the string array part
        }
        // addWordToMap(word, Inverted, lineNumber, i);
        for_each(word.begin(), word.end(), [](char & c){ //for each in stl
        c = ::tolower(c); // to lower case
    });
    if(Inverted.find(word) == Inverted.end()){ // if word is found
        list<pair<int,int>> locations;
        locations.push_back({lineNumber,incrementer}); //pair wiht location
        Inverted.insert({word,{1,locations}}); //insert that into inverted index
    }
    else{ //if word is not found
        Inverted.at(word).first++;
        Inverted.at(word).second.push_back({lineNumber,incrementer});
    }
        word=""; //reset word
        while(!checkArgs(incrementer)){ //
            incrementer++;
        }
    }
}//Add:; main part


void initalizeVars(){
    numberLine =1; //at first line
    word = ""; //empty

};//intialize

int main(){
//    cout<<"Adjust the file location."<<endl;// archived 
   
    // File.open("/Users/381proj/Gettysburg Address.txt"); //getting file
    
    initalizeVars(); //intialize vars
    while(getline(inputfile,lineRead)){ //for each line
        Add(lineRead, Inverted, numberLine++); //add which adds to inverted index, pairs, puts in to lowercase
    }
    inputfile.close(); //close to prevent leak
     //auto :: C+11
        auto begin = Inverted.begin();
        auto end = Inverted.end();

    for (auto index = begin; index != end; ++index) { //auto for letting the compiler choose the data type
         stringstream finalAns; //appending 
         list<pair<int,int>> Paired = index->second.second;
          finalAns<<"[ "; //encapsulation
            for(auto styff = Paired.begin(); styff != Paired.end(); ++styff)
                finalAns <<"("<<styff->first<<","<<styff->second<<") ";
        finalAns <<" ]"; //encapsulation
        cout<<index->first<<" "<<index->second.first<<finalAns.str()<<endl; //printing of the paired items
    }
cout<<"Done."<<endl; //when everything is done!
    return 0;
}