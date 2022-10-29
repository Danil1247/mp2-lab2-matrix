// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t Size;
  T* pMem;
public:
  TDynamicVector(size_t _size = 1) : Size(_size)
  {
    if (Size <= 0 || Size > MAX_VECTOR_SIZE)
      throw "error";
    pMem = new T[Size];// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : Size(s)
  {
    if (arr != nullptr)
    {
      pMem = new T[Size];

      for (int i = 0; i < Size; i++)
      {
        pMem[i] = arr[i];
      }
    }
    else
      throw "error";
  }
  TDynamicVector(const TDynamicVector& v)
  {
    Size = v.Size;
    pMem = new T[Size];
    for (int i = 0; i < Size; i++)
    {
      pMem[i] = v.pMem[i];
    }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    Size = v.Size;
    pMem = v.pMem;

    v.Size = 0;
    v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
    if (pMem != nullptr)
      delete[]pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (*this == v)
      return *this;
    if (Size != v.Size)
    {
      delete[] pMem;
      Size = v.Size;
      pMem = new T[Size];
    }
    for (int i = 0; i < Size; i++)
    {
      pMem[i] = v.pMem[i];
    }
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    Size = v.Size;
    pMem = v.pMem;

    v.Size = 0;
    v.pMem = nullptr;

    return *this;
  }

  size_t size() const noexcept
  {
    return Size;
  }

  // индексация
  T& operator[](size_t _index)
  {
    return pMem[_index];
  }
  const T& operator[](size_t _index) const
  {
    return pMem[_index];
  }

  // индексация с контролем
  T& at(size_t _index)
  {
    if (_index >= Size)
      throw "error";
    return pMem[_index];
  }
  const T& at(size_t _index) const
  {
    if (_index >= Size)
      throw "error";
    return pMem[_index];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (v.Size != Size)
      return false;
    for (int i = 0; i < Size; i++)
    {
      if (pMem[i] != v.pMem[i])
        return false;
    }

    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T _value)
  {
    TDynamicVector res(Size);
    for (size_t i = 0; i < Size; i++)
      res.pMem[i] = pMem[i] + _value;
    return res;
  }
  TDynamicVector operator-(double _value)
  {
    TDynamicVector res(Size);
    for (size_t i = 0; i < Size; i++)
      res.pMem[i] = pMem[i] - _value;
    return res;
  }
  TDynamicVector operator*(double _value)
  {
    TDynamicVector res(Size);
    for (size_t i = 0; i < Size; i++)
      res.pMem[i] = pMem[i] * _value;
    return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (Size != v.Size)
      throw "error";
    TDynamicVector res(Size);
    for (size_t i = 0; i < Size; i++)
      res.pMem[i] = pMem[i] + v.pMem[i];
    return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (Size != v.Size)
      throw "error";
    TDynamicVector res(Size);
    for (int i = 0; i < Size; i++)
      res.pMem[i] = pMem[i] - v.pMem[i];
    return res;
  }
  T operator*(const TDynamicVector& v)
  {
    if (Size != v.Size)
      throw "error";
    T res = 0;
    for (size_t i = 0; i < Size; i++)
      res += pMem[i] * v.pMem[i];
    return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.Size, rhs.Size);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.Size; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.Size; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::Size;
public:
  TDynamicMatrix(size_t _size = 1) : TDynamicVector<TDynamicVector<T>>(_size)
  {
    if (Size <= 0 || Size > MAX_MATRIX_SIZE)
      throw "error";
    for (size_t i = 0; i < Size; i++)
      pMem[i] = TDynamicVector<T>(Size);
  }
  TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& s) : TDynamicVector<TDynamicVector<T>>(s) {}

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& _value)
  {
    return TDynamicVector<TDynamicVector<T>>::operator*(_value);
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    TDynamicVector res(Size);
    for (size_t i = 0; i < Size; i++)
      res[i] = pMem[i] * v;
    return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    return TDynamicVector<TDynamicVector<T>>::operator+(m);
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    return TDynamicVector<TDynamicVector<T>>::operator-(m);
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (m.Size != Size)
      throw "error";
    TDynamicMatrix res(Size);
    for (size_t i = 0; i < Size; i++)
      for (size_t j = 0; j < Size; j++)
        for (int k = 0; k < Size; k++)
          res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
    return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (int i = 0; i < sz; i++)
      istr >> v.pMem[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (int i = 0; i < v.Size; i++)
      ostr << v.pMem[i] << endl;
    return ostr;
  }
};

#endif
