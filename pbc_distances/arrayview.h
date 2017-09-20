///////////////////////////////////////////////////////////////////
// pbc_distances - Max Linke - 2017                              //
// Under MIT Licence, please you must read the LICENCE.txt file. //
///////////////////////////////////////////////////////////////////
#ifndef ARRAYVIEW_H
#define ARRAYVIEW_H

// Sometimes I don't want to use parameters provided by the overloaded API's.
// This will silence compiler warnings and result in a noop. Be careful if x is
// volatile.
#define UNUSED(x) (void)x;

class RowMajor {
public:
  static const bool IsRowMajor = true;

  inline static int IndexOf(const int idxRow, const int idxCol,
                            const int inNbRows, const int inNbCols) {
    UNUSED(inNbCols);
    return inNbRows * idxCol + idxRow;
  }
};

class ColumnMajor {
public:
  static const bool IsRowMajor = false;

  inline static int IndexOf(const int idxRow, const int idxCol,
                            const int inNbRows, const int inNbCols) {
    UNUSED(inNbRows);
    return inNbCols * idxRow + idxCol;
  }
};

template <typename T, typename Ordering = RowMajor> class ArrayView {
public:
  static const bool IsRowMajor = Ordering::IsRowMajor;

  explicit ArrayView(const int rows_, const int cols_, const T *data_)
    : m_rows(rows_), m_cols(cols_), m_pData(data_) {}
  explicit ArrayView(const std::size_t rows_, const std::size_t cols_, const T *data_)
      : m_rows(static_cast<int>(rows_)), m_cols(static_cast<int>(cols_)),
        m_pData(data_) {}
  // support moving
  ArrayView(ArrayView &&rhs) = delete;
  ArrayView &operator=(ArrayView &&rhs) = delete;
  // do not support copying
  ArrayView(const ArrayView &rhs) = delete;
  ArrayView &operator=(const ArrayView &rhs) = delete;

  const T& operator()(int row, int col) const {
    return m_pData[Ordering::IndexOf(row, col, m_rows, m_cols)];
  }

  T &operator()(int row, int col) { return m_pData[Ordering::IndexOf(row, col, m_rows, m_cols)]; }

  int rows() const noexcept { return m_rows; };
  int cols() const noexcept { return m_cols; };

private:
  const int m_rows;
  const int m_cols;
  const T *m_pData;
};

#endif // ARRAYVIEW_H
