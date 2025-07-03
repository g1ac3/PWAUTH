#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <cstdio>
#include <cstdint>
#include "BLAKE3/c/blake3.h"
#include <vector>

//std::string PWAUTH_input();
//std::string PWAUTH_hash(std::string);
void PWAUTH_change(std::string);
bool PWAUTH_check(std::string);
