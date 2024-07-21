/**
* Идиома RAII (Resource Acquisition Is Initialization) переводится как «захват
ресурса должен быть инициализацией объекта». Пусть программе требуется какой-то
ресурс (память, файл), который надо обязательно «вернуть», когда он будет уже не
нужен. Идея состоит в том, что лучше всего запрашивать этот ресурс в
конструкторе некоторого объекта, а освобождать — в деструкторе. На этой идее
построены стандартные контейнеры и так называемые «умные указатели» — классы
unique_ptr и shared_ptr из стандартной библиотеки.
(Источник)[https://education.yandex.ru/handbook/cpp/article/raii-and-smart-pointers]
*/
#include <cstdio>
#include <iostream>

/**
 * Прикол класса в том, что файл открывается при инициализации объекта, а
 * закрывается - при уничтожении поэтому за памятью больше можно не следить
 */
class MyFile {
 private:
  std::FILE* data;

 public:
  explicit MyFile(const std::string& file_name)
      : data(std::fopen(file_name.c_str(), "r")) {
    if (this->data == nullptr) std::cout << "Ошибка";
  }
  ~MyFile() { std::fclose(this->data); }
  std::string Read() const {
    char buf[100];
    std::fscanf(this->data, "%99s", buf);
    return buf;
  }
};

int main() {
  std::FILE* f = std::fopen("input.txt", "w");
  if (f == nullptr) std::cout << "Ошибка";
  char buf[100];
  //  std::fscanf(f, "%99s", buf);
  std::fputs("qwertgfdszxc", f);
  std::fclose(f);

  MyFile f2("input.txt");
  auto from_f2 = f2.Read();
  std::cout << from_f2 << '\n';
  return 0;
}