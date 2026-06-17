# libigl-python-bindings memory

## Project
Python bindings for libigl C++ geometry library using nanobind + scikit-build-core.
C++ libigl source lives at `build/_deps/libigl-src/include/igl/` (fetched by CMake).

## Binding Architecture
- Each `src/<name>.cpp` → corresponds to `build/_deps/libigl-src/include/igl/<name>.h`
- CMake globs all `.cpp` files, generates `BINDING_DECLARATIONS.in` / `BINDING_INVOCATIONS.in`, `module.cpp` includes them — adding a `.cpp` auto-registers it
- Types centralized in `include/default_types.h`: `Numeric=double`, `Integer=int64_t`, `RowMajor`
- Zero-copy input: `nb::DRef1<const Eigen::MatrixXN>` (requires C-contiguous float64). The unit inner stride keeps Eigen vectorization enabled (fixes the GCC ~3x slowdown of nanobind issue #1263); non-C-contiguous float64 input falls back to a copy
- Multiple C++ output params → `std::make_tuple(...)` → Python tuple unpacking
- Sparse output: `Eigen::SparseMatrixN` + `<nanobind/eigen/sparse.h>` → scipy CSR automatically

## Submodules
- `src/` → `igl` (core, MPL2)
- `src/copyleft/` → `igl.copyleft` (GPL)
- `src/copyleft/cgal/` → `igl.copyleft.cgal`
- `src/embree/` → `igl.embree`
- `src/triangle/` → `igl.triangle`

## Key Gotchas
- numpy `int32`/`float32` silently copies; always use `int64`/`float64` in tests
- In-place mutation: use `Eigen::Ref<>` + `.noconvert()` on the arg
- Class templates must be typedef'd to concrete type before `nb::class_<>`
- Sparse inputs must be `scipy.sparse.csr_matrix`
