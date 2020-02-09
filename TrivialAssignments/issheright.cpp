#include <iostream>

using namespace std;


int main(){
   for(int n =0; n<= 32; n++){
       cout<<bitset<32>(n-1);
       cout<<"\n";
    cout<<"n is ";
    cout<< n;
    cout<<"\n";
     cout<<" answer is ";
   cout<<((n&(n-1))==0);
   /*

   &: compares bit by bit;where if both bits are 1 , than 1 is awarded, and if the opppsoite, then a 0.
   -1:111
   //0:000
   1:001
   2: 010
   3: 011
   4: 100
   5: 101
   6: 110
   7: 0111
   8: 1000

0,1,2,3
1,2,4,8
   The expressions may be other and-expressions, or (subject to the type restrictions mentioned below) equality expressions, relational expressions, additive expressions, multiplicative expressions, pointer to member expressions, cast expressions, unary expressions, postfix expressions, or primary expressions.

The bitwise AND operator (&) compares each bit of the first operand to the corresponding bit of the second operand. 

If both bits are 1, the corresponding result bit is set to 1. 
Otherwise, the corresponding result bit is set to 0.
Both operands to the bitwise AND operator must be of integral types.
 The usual arithmetic conversions covered in Standard Conversions, are applied to the operands.

   */
  cout<<"\n";
   }

    return 0;
};
//not fully correct
//returns true if n is equal to 1
//however, if n is power of 2 , then it should be correct because
/*
based on the powers of 2 0/1 bit table,
every starting position of a power of 2 has 1 in the left most position, which if contrasted with the previous number
would be 1 in the left most position for N, and NOT FOR the prior number, which would lead the '&' which contrasts the N(power of 2) witht the previous number and it would yeild 
it being equal to 0, because none of the bits match

if n is odd, then logically, after a even number, it's one more than the previous odd number

power 2 , left most has a one and rest are all zeroes, whereas the prior number doesn't have one in the left most posiiton and has all 1 besides the first leftmost position

--> produces  a 0 
1000 & 0111 =0
1111(-1) & 0000 =0
*/