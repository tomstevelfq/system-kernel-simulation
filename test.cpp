#include<iostream>
#include<vector>
#include"cycle.h"

using namespace std;

int main(int argc, char* argv[]){
  cout<<argc<<endl;
  freopen("result","w",stdout);//输入输出重定向
  Cycle cycle;
  cycle.start();
  freopen("CON", "w", stdout);
  cout<<"hello world"<<endl;
  return 0;
}