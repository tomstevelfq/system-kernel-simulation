#include<iostream>
#include<map>

using namespace std;

int main(){
    map<int,int> mp;
    mp.insert({3,4});
        mp.insert({3,6});
        cout<<mp[3]<<endl;
        return 0;
}