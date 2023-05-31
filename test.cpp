#include<iostream>
#include<vector>

using namespace std;

struct Node{
  int b;
  Node(int a){
    b=a;
  }
};

struct A{
  vector<int> V;
  A(){
    V=vector<int>(10,3);
  }
};

int main(){
  A a;
  return 0;
}