#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

template <typename _Tp, typename _Alloc = std::allocator<_Tp>,
          typename traits_t1 = std::allocator_traits<_Alloc> >
class EasyVec {
  typedef _Alloc alloc_object;
  typedef _Tp data_type;
  typedef _Tp* data_type_ptr;

 private:
  size_t _size = 0;
  size_t _capacity = 0;
  alloc_object _alloc;
  data_type_ptr _data = nullptr;

 public:
  EasyVec() : _data(traits_t1::allocate(_alloc, 10)), _capacity(10) {}
  explicit EasyVec(size_t size)
      : _size(size),
        _data(traits_t1::allocate(_alloc, size)),
        _capacity(size) {}
  ~EasyVec() { destruct(); }

  size_t size() const { return _size; }

  _Tp& operator[](size_t index) {
    if (index > _size) throw std::out_of_range("out_of_range");
    return _data[index];
  }

  const _Tp& operator[](size_t index) const {
    if (index > _size) throw std::out_of_range("out_of_range");
    return _data[index];
  }

  void destruct() {
    if (_data) {
      traits_t1::deallocate(_alloc, _data, _capacity);
      _data = nullptr;
      _capacity = 0;
      _size = 0;
    }
  }

  /**
   * Создает новый _data, копируя информацию из старого
   * @param new_size
   * @return
   */
  data_type_ptr reallocate(size_t new_size) {
    data_type_ptr newobj = traits_t1::allocate(_alloc, new_size);
    if (_data) {
      std::copy(_data, _data + _size, newobj);
      traits_t1::deallocate(_alloc, _data, _capacity);
    }
    _capacity = new_size;
    return newobj;
  }

  void resize(const size_t new_size) {
    if (new_size > _capacity) {
      _data = reallocate(new_size);
    }
    _size = new_size;
  }
};

int main() {
  std::allocator<int> mya;

  // обычное использование
  int* ptr1 = mya.allocate(1);
  std::cout << *ptr1 << ' ' << ptr1 << '\n';
  mya.deallocate(ptr1, 1);
  // ======================

  // можно использовать и traits (что-то похожее на итератор - интерфейс для
  // работы с итератором)
  using mytrait = std::allocator_traits<decltype(mya)>;
  int* ptr2 = mytrait::allocate(mya, 1);
  mytrait::construct(mya, ptr2, 15);
  std::cout << *ptr2 << ' ' << ptr2 << '\n';
  mytrait::deallocate(mya, ptr2, 1);
  // ======================

  // мое чудо
  EasyVec<int> meow(10);
  for (int i = 0; i < 11; ++i) meow[i] = i * 4;
  for (int i = 0; i < 11; ++i) std::cout << meow[i] << ' ';
  std::cout << std::endl;

  meow.resize(5);
  for (int i = 0; i <= 5; ++i) std::cout << meow[i] << ' ';
  meow.destruct();
  // ======================

  std::cout << std::endl;
  return 0;
}
