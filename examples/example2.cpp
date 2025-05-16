#include <frint.hpp>

#include <fstream>

int main(int aargc, char** argv)
{
std::ofstream file("log.txt");
print(std::string("hello"),file);
}
