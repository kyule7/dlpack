/*!
 *  Copyright (c) 2017 by Contributors
 * \file dlpackcpp.h
 * \brief Example C++ wrapper of DLPack
 */
#ifndef DLPACKCPP_H_
#define DLPACKCPP_H_

#include <vector>
#include <memory>
#include "./dlpack.h"

namespace dlpack {

// Example container wrapping of DLTensor.
class DLTContainer {
 public:
  DLTContainer() {
    // default to float32
    handle_.data = nullptr;
    handle_.dtype.code = kFloat;
    handle_.dtype.bits = 32U;
    handle_.dtype.lanes = 1U;
    handle_.ctx.device_type = kCPU;
    handle_.ctx.device_id = 0;
    handle_.shape = nullptr;
    handle_.strides = nullptr;
    handle_.byte_offset = 0;
  }
  ~DLTContainer() {
    if (origin_ == nullptr) {
      free(handle_.data);
    }
  }
  operator DLTensor() {
    return handle_;
  }
  operator DLTensor*() {
    return &(handle_);
  }
  void Reshape(const std::vector<int64_t>& shape) {
    shape_ = shape;
    int64_t sz = 1;
    for (int64_t s : shape) {
      sz *= s;
    }
    handle_.data = aligned_alloc(256, sz);
    handle_.shape = &shape_[0];
    handle_.ndim = static_cast<uint32_t>(shape.size());
  }

 private:
  DLTensor handle_;
  std::vector<int64_t> shape_;
  std::vector<int64_t> strides_;
  // original space container, if
  std::shared_ptr<DLTContainer> origin_;
};

}  // namespace dlpack
#endif  // DLPACKCPP_H_
