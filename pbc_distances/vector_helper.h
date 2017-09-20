#ifndef VECTOR_HELPER_H
#define VECTOR_HELPER_H
#include <vector>

template <typename T>
std::vector<T> operator*(const std::vector<T> &a, const T b) {
  auto res = std::vector<T>(a.size());
  for (auto i = 0u; i < a.size(); ++i) {
    res[i] = a[i] * b;
  }
  return res;
}

template <typename T>
std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b) {
  auto res = std::vector<T>(a.size());
  for (auto i = 0u; i < a.size(); ++i) {
    res[i] = a[i] - b[i];
  }
  return res;
}

template <typename T>
std::vector<T> operator-(const T a, const std::vector<T> &b) {
  auto res = std::vector<T>(b.size());
  for (auto i = 0u; i < b.size(); ++i) {
    res[i] = a - b[i];
  }
  return res;
}

template <typename T>
std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b) {
  auto res = std::vector<T>(a.size());
  for (auto i = 0u; i < a.size(); ++i) {
    res[i] = a[i] + b[i];
  }
  return res;
}

template <typename T> T norm2(const std::vector<T> &v) {
  auto n = T(0);
  for (const auto el : v) {
    n += el * el;
  }
  return n;
}

#endif // VECTOR_HELPER_H
