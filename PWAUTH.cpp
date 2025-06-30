#include "PWAUTH.h"
#ifdef _WIN32
    // Windows専用の処理（例：conio.h）
    #include <conio.h>
#else
    // Linux/macOS用の処理（例：termios）
    #include <termios.h>
    #include <unistd.h>

    int getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif /*_WIN32*/

const int N = 79;
//パスワード入力させて入力した文字列を返す。
std::string PWAUTH_input(){
    std::string s;
    char c;
    std::cout<<"PW : ";
        while (true) {
            c = getch();
            if (c == '\n' || c == '\r') break; // Enterで終了
            s += c;
            std::cout << '*';
            std::cout.flush();
        }
    std::cout<<"\n";
    return s;
}
//string型の平文のパスワードを受け取ってハッシュ化して返す。
std::string PWAUTH_hash(std::string s){
    size_t tmp = std::hash<std::string>()(s);
    std::string S = "";
    while(tmp>0){
        S += (tmp%10) + '0';
        tmp /= 10;
    }
    reverse(S.begin(),S.end());
    return S;
}
//パスワード変更
void PWAUTH_change(std::string ofile){
    std::ofstream ofs(ofile);
    std::cout<<"Create New Password\n";
    ofs<<PWAUTH_hash(PWAUTH_input())<<"\n";
}
//パスワードをofileで指定した名前のテキストファイルから読み取り一致するか確認
bool PWAUTH_check(std::string ofile){
    std::ifstream fin;
    std::string line;
    fin.open(ofile,std::ios::in);
    std::getline(fin,line);
    fin.close();
    return line == PWAUTH_hash(PWAUTH_input());
}
