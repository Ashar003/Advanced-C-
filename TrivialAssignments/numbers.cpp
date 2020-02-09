
#include<iostream> 
using namespace std;
int main(){ int n;
cin>>n; int s=0;
for (int i=1;i<=n;i++){ int k=0;
int j=i; while(j>0){
if(j%10==1){ k+=1;
}
j=j/10; }
s+=k; }
cout<<s; }

