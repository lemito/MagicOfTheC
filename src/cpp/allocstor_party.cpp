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
  ~EasyVec() { traits_t1::deallocate(_alloc, _data, _capacity); }

  size_t size() const { return _size; }

  _Tp& operator[](size_t index) { return _data[index]; }

  const _Tp& operator[](size_t index) const { return _data[index]; }

  void destruct() { traits_t1::deallocate(_alloc, _data, _capacity); }
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

  EasyVec<int> meow;
  meow[0] = 5;
  meow[1] = 4;
  for (int i = 0; i < 2; ++i) std::cout << meow[i] << ' ';
  meow.destruct();
  std::cout << std::endl;
  return 0;
}