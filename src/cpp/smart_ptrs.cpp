/**
 * Умные указатели
 */
#include <iostream>
#include <memory>

// вот тут утечка памяти
char* f() { return new char('q'); }

// а вот тут её нет (умный указатель сам ее уже исправил)
std::unique_ptr<char> g() { return std::make_unique<char>('e'); }

void inc_char(std::unique_ptr<char>& in) { (*in)++; }

int main() {
  // обычный указатель - создать, делиться; необходимо удалять. Опасное...
  int* ptr = new int(52);
  std::cout << *ptr << '\n';
  auto copy_ptr = ptr;
  std::cout << *copy_ptr << '\n';
  delete ptr;
  // умный уникальный указатель - один владелец, автоочистка
  std::unique_ptr<int> ptr_uq = std::make_unique<int>(52);
  std::cout << *ptr_uq << "\n";

  std::cout << *f() << "\n";
  std::cout << *g() << "\n";

  auto ptr_g = g();
  inc_char(ptr_g);
  std::cout << *ptr_g << "\n";
  // умный shared-указатель - несколько владельцев (их учет ведется)
  std::shared_ptr<int> ptr_sh = std::make_shared<int>(51);
  std::cout << *ptr_sh << "\n";
  auto ptr_sh2 = ptr_sh;
  std::cout << ptr_sh.use_count();

  return 0;
}