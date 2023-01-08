#include <iostream>
#include <concepts>



//g++ -g -std=c++20 main.cpp -o client.exe
// cat .\main.cpp
// let vscode know 


template <typename T>
requires std::integral<T>
T add (T a, T b)
{
	return a + b;
}


int main(){

std::cout << "Hello HANG, Here is from C++ 20 with Cmake on Linux/Windows" << std::endl;

std::cout << "666+888 的结果为: " <<add(1024,999) << std::endl;
return 0;




}
