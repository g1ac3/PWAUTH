#include "PWAUTH.h"
#include "BLAKE3/c/blake3.h"
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
    uint8_t output[BLAKE3_OUT_LEN];
    blake3_hasher hasher;
    blake3_hasher_init(&hasher);
    blake3_hasher_update(&hasher, s.c_str(), s.length());
    blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);
    std::string S = "";
    for (int i = 0; i < BLAKE3_OUT_LEN; i++) {
        char hex[3];
        sprintf(hex, "%02x", output[i]);
        S += hex;
    }
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
