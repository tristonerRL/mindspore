/**
 * Copyright 2019-2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <numeric>
#include "src/ops/ops.h"
#include "include/errorcode.h"
#include "utils/log_adapter.h"
#include "src/ir/tensor.h"

namespace mindspore::lite {
int Power::InferShape(std::vector<tensor::Tensor *> inputs, std::vector<tensor::Tensor *> outputs) {
  MS_ASSERT(this->primitive != nullptr);
  auto x_tensor = inputs[0];
  MS_ASSERT(x_tensor != nullptr);
  auto exp_tensor = inputs[1];
  MS_ASSERT(exp_tensor != nullptr);
  auto output_tensor = outputs[0];
  MS_ASSERT(output_tensor != nullptr);
  if (inputs.size() < 2) {
    MS_LOG(ERROR) << "input size" << inputs.size() << " is error!";
    return RET_INPUT_TENSOR_ERROR;
  }
  if (exp_tensor->shape() != x_tensor->shape() && exp_tensor->shape().size() != 1) {
    MS_LOG(ERROR) << "Power inputs shape is not equal!";
    return RET_INPUT_TENSOR_ERROR;
  }

  int exp_size = std::accumulate(exp_tensor->shape().begin(), exp_tensor->shape().end(), 1, std::multiplies<int>());
  if (x_tensor->data_type() != exp_tensor->data_type() && exp_size != 1) {
    MS_LOG(ERROR) << "Exponent tensor's shape is wrong";
    return RET_INPUT_TENSOR_ERROR;
  }
  output_tensor->SetFormat(x_tensor->GetFormat());
  output_tensor->set_shape(x_tensor->shape());
  output_tensor->set_data_type(x_tensor->data_type());
  return RET_OK;
}
}  // namespace mindspore::lite
