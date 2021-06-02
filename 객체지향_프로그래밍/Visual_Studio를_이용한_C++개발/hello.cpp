#include <iostream>

int main() {
    std::cout << "Hello, world!\n";
    std::cout << "Hello, New World!\n";
    std::cout << "Hello, C++!!\n";
    std::cout << "!!\n";

    int sum = 0;
    for (int i = 1; i <= 10; i++)
        sum += i;
    std::cout << "1에서 10까지 더한 결과는 ";
    std::cout << sum << "입니다\n";

    for(int i=1; i<= 4; i++){
        for(int j =1; j <= i; j++)
            std::cout << "*";
        std::cout << "\n";
    }
    return 0;
}