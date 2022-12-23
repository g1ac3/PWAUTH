#include <bits/stdc++.h>
#include <functional>
#include <conio.h>
//#include <termios.h>
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
  size_t tmp = std::hash<std::string>()(s);
  std::cout<<tmp<<std::endl;
  std::string S = "";
  while(tmp>0){
    S += (tmp%10) + '0';
    tmp /= 10;
    std::cout<<tmp<<std::endl;
  }
  reverse(S.begin(),S.end());
  std::cout<<S<<std::endl;
  return S;
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
int main(){
  int t;
  std::cout<<"0 : input\n";
  std::cout<<"1 : setting\n";
  std::cin>>t;
  if(t == 0&&PWAUTH_check())std::cout<<"\nok";
  else if(t == 1) PWAUTH_change();
}
