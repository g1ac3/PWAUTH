#include "PWAUTH.h"
std::string ofile = "pw.txt";
int main(){
    int t;
    std::cout<<"0 : check\n";
    std::cout<<"1 : setting\n";
    std::cin>>t; std::cin.ignore();
    if(t == 0&&PWAUTH_check(ofile))std::cout<<"\nok";
    else if(t == 1) PWAUTH_change(ofile);
}
