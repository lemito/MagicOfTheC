/**
 * Пример ООП на C++
 */
#include <cstdint>
#include <format>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

/**
 * Пример ошибки
 */
struct WrongWeightException {
  double weight;
};

struct WrongAgeException {
  u_int8_t age;
};

struct WrongIqException {
  size_t iq;
};

/**
 * Родительский класс
 */
class Animals {
  /**
   * Приватные поля (аргументы и методы)
   */
 private:
  std::string name;
  uint8_t age{};
  double weight{};
  std::string color;

  /**
   * Публичные поля (аргументы и методы)
   */
 public:
  /**
   * Конструктор класса (без аргументов; поставим его по умолчанию)
   */
  Animals() = default;

  /**
   * Конструктор класса (с параметрами)
   * @param name имя
   * @param age возраст
   * @param weight вес
   * @param color окраска (цвет)
   */
  Animals(std::string name, u_int8_t age, double weight, std::string color) {
    /**
     * Пример ошибки
     */
    if (weight < 0 || weight > 200000) {
      throw WrongWeightException(weight);
    }
    if (age < 0 || age > 150) {
      throw WrongAgeException(age);
    }
    this->name = std::move(name);
    this->age = age;
    this->weight = weight;
    this->color = std::move(color);
  }

  /**
   * Деструктор класса
   */
  virtual ~Animals() = default;

  /**
   * Виртуальный метод, его можно перегрузить (override)
   * Её можно сначала вызвать в наследнике, потом переопределить
   */
  virtual void present() {
    std::cout << std::format("Name = {}, age = {}, weight = {}, color = {}\n",
                             name, age, weight, color);
  }

  /*
   * Всякие getter-ы и setter-ы (тут сделал Generator от CLion, дальше можно и
   * руками)
   */
  const std::string& GetName() const { return name; }
  void SetName(const std::string& name) { Animals::name = name; }
  u_int8_t GetAge() const { return age; }
  void SetAge(u_int8_t age) { Animals::age = age; }
  double GetWeight() const { return weight; }
  void SetWeight(double weight) { Animals::weight = weight; }
  const std::string& GetColor() const { return color; }
  void SetColor(const std::string& color) { Animals::color = color; }
};

class Mammals : public Animals {
 private:
  int countLegs{};

 public:
  Mammals() = default;

  // тут инициализация наследника
  Mammals([[maybe_unused]] std::string name, u_int8_t age, double weight,
          std::string color, int countLegs)
      // инициализируем родителя в наследнике (то есть класс Animals
      : Animals(std::move(name), age, weight, std::move(color)),
        // более короткая запись для инициализации класса - список инициализации
        countLegs(countLegs) {}

  virtual void eat_food() { std::cout << "Млекопитающие едят\n"; }

  virtual void feedWithMilk() { std::cout << "Млекопитающие feedWithMilk\n"; };

  int GetCountLegs() const { return countLegs; }
  void SetCountLegs(int count_legs) { countLegs = count_legs; }
};

class Birds : public Animals {
 private:
  double wingSpan{};

 public:
  Birds() = default;

  Birds(std::string name, u_int8_t age, double weight, std::string color,
        double wingSpan)
      : Animals(std::move(name), age, weight, std::move(color)) {
    this->wingSpan = wingSpan;
  }

  void present() override {
    Animals::present();
    printf("wingSpan = %f\n", wingSpan);
  }

  double GetWingSpan() const { return wingSpan; }
  void SetWingSpan(double wing_span) { wingSpan = wing_span; }
};

class Fishes : public Animals {
  // лососевый => икра красная... тип отличия
 protected:
  bool isTuna{};

 public:
  Fishes() = default;

  Fishes(std::string name, u_int8_t age, double weight, std::string color,
         bool isTuna)
      : Animals(std::move(name), age, weight, std::move(color)) {
    this->isTuna = isTuna;
  }

  void present() override {
    Animals::present();
    printf("Is tuna? -> %s\n", isTuna ? "True" : "False");
  }

  bool IsTuna() const { return isTuna; }
  void SetIsTuna(bool is_tuna) { isTuna = is_tuna; }
};

class Humans : public Mammals {
 private:
  size_t iq{};

 public:
  Humans() = default;

  Humans(std::string name, u_int8_t age, double weight, std::string color,
         size_t iq)
      : Mammals(std::move(name), age, weight, std::move(color), 2) {
    if (iq > 350) throw WrongIqException(iq);
    this->iq = iq;
  }

  void eat_food() override { std::cout << "Человек ест\n"; }

  void feedWithMilk() override { std::cout << "Человек feedWithMilk\n"; }

  void present() override {
    Mammals::Animals::present();
    printf("iq = %zu\n", iq);
  }

  size_t GetIq() const { return iq; }
  void SetIq(size_t iq) { Humans::iq = iq; }
};

int main() {
  std::vector<Animals*> zoo;

  try {
    auto* m = new Animals("q", 2, 2.5, "red");
    auto* parrot = new Birds("qq", 2, 2.5, "red", 7.5);
    auto* hu = new Humans("qqq", 2, 2.5, "red", 175);
    auto* fi = new Fishes("qqq", 2, 2.5, "red", false);
    auto* m2 = new Animals("q2", 2, 255000, "red");

    zoo.push_back(m);
    zoo.push_back(parrot);
    zoo.push_back(hu);
    zoo.push_back(fi);
    zoo.push_back(m2);


  } catch (const WrongWeightException& exception) {
    std::cerr << "Ошибка в весе " << exception.weight << '\n';
  } catch (const WrongAgeException& exception) {
    std::cerr << "Ошибка в возрасте " << exception.age << '\n';
  }
  catch (const WrongIqException& exception) {
    std::cerr << "Неправдободобный iq= " << exception.iq << '\n';
  }

  for (auto animal : zoo) {
    animal->present();
  }

  return 0;
}