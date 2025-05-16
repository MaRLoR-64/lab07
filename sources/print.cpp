#include <print.hpp>

void print(const std::string& text, std::ostream& out)
{
    out << text;  // Исправлено: вывод вместо ввода
}

void print(const std::string& text, std::ofstream& out)
{
    out << text;  // Верно, но можно удалить (дублирует первую перегрузку)
}
