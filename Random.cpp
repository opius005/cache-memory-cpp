#include<bits/stdc++.h>
using namespace std;

int main(){
    int s=10000;
    srand(time(0));
    bitset<8> b;
    long long int c=pow(2,7);
    int p;
   
        ofstream CIout("Cache_Input.txt");
        if (CIout.is_open())
        {
            for(int i=0;i<s;i++){
             p=rand()%c;
             b=p;
             CIout<<b<<endl;
             }
        }
        else
            cout << "Unable to open file"
                 << "Cache_Input.txt" << endl;
        CIout.close();
    
}