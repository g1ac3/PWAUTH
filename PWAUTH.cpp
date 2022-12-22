#include <bits/stdc++.h>
#include <conio.h>
#include <functional>
#include "PWAUTH.h"
const int N = 79;
std::string ofile = "pw.txt";
//パスワード入力させて入力した文字列を返す。
std::string PWAUTH_input(){
  std::string s;
  char c;
  std::cout<<"PW : ";
  while(1){
    if(kbhit()){
      if((c=getch())=='\r') break;
      std::cout<<"*";
      s+=c;
    }
  }
  std::cout<<"\n";
  return s;
}
//string型の平文のパスワードを受け取ってハッシュ化して返す。
std::string PWAUTH_hash(std::string s){
  return std::hash<string>()(s);
}
//パスワード変更
void PWAUTH_change(){
  std::cout<<"_";
  std::ofstream ofs(ofile);
  std::cout<<"Create New Password\n";
  ofs<<PWAUTH_hash(PWAUTH_input())<<"\n";
}
//パスワードをofileで指定した名前のテキストファイルから読み取り一致するか確認
bool PWAUTH_check(){
  std::ifstream fin;
  std::string line;
  fin.open(ofile,std::ios::in);
  std::getline(fin,line);
  fin.close();
  return line == PWAUTH_hash(PWAUTH_input());
}
