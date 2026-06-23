#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <cstdint>

///////////////////////////////////////////////////////////////////////////////////
/// Default numeric and integer types. Passing anything else will result in an
/// implicit copy. Developers insisting on native executation of libigl on
/// single-precision (largely untested and possibly error prone) can change this
/// to float and recompile bindings at their own delight or peril.
///////////////////////////////////////////////////////////////////////////////////
using Numeric = double;
using Integer = int64_t;
using Boolean = bool;
// `Options = RowMajor` makes the MatrixX* typedefs row-major, which matters in
// two ways. (1) Return types: `Eigen::MatrixXN X; … ; return X;` is emitted to
// numpy in this order. (2) Input zero-copy: inputs use `nb::DRef1` (an
// `Eigen::Ref` with a unit inner stride; see nanobind#1263 / nanobind#1378), so
// a row-major matrix binds without a copy only when the numpy array is
// C-contiguous with a matching `dtype`; non-contiguous (e.g. F-contiguous or
// strided/sliced) inputs fall back to a copy. The unit inner stride is what
// keeps Eigen vectorization enabled — GCC otherwise loses it (~3x slower).
constexpr auto Options = Eigen::RowMajor;
namespace Eigen
{
  typedef Matrix<Numeric, Dynamic, Dynamic, Options> MatrixXN;
  typedef Matrix<Integer, Dynamic, Dynamic, Options> MatrixXI;
  typedef Matrix<Boolean, Dynamic, Dynamic, Options> MatrixXB;
  typedef Matrix<Numeric, Dynamic, 1, Eigen::ColMajor> VectorXN;
  typedef Matrix<Integer, Dynamic, 1, Eigen::ColMajor> VectorXI;
  typedef Matrix<Boolean, Dynamic, 1, Eigen::ColMajor> VectorXB;
  typedef Matrix<Numeric, 1, Dynamic, Eigen::RowMajor> RowVectorXN;
  typedef Matrix<Integer, 1, Dynamic, Eigen::RowMajor> RowVectorXI;
  typedef Matrix<Boolean, 1, Dynamic, Eigen::RowMajor> RowVectorXB;
  typedef SparseMatrix<Numeric> SparseMatrixN;
  typedef SparseMatrix<Integer> SparseMatrixI;
  typedef SparseMatrix<Boolean> SparseMatrixB;
}
