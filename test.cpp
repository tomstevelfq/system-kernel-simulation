#include<iostream>
#include<vector>
#include"cycle.h"
#include<fstream>

using namespace std;

int main(int argc, char* argv[]){
  cout<<argc<<endl;
  freopen("result","w",stdout);//输入输出重定向
  string path=argv[1];
  string replace=argv[2];
  Cycle cycle(path,replace);
  cycle.start();
  #ifdef _WIN32
    freopen("CON", "w", stdout);
  #else
    freopen("/dev/console", "w", stdout);
  #endif

  ifstream inputFile("result");  // 打开输入文件
  std::string line;
  while (std::getline(inputFile, line)) {
      std::cout << line << std::endl;  // 将每一行内容输出到屏幕
  }
  inputFile.close();  // 关闭文件

  return 0;
}