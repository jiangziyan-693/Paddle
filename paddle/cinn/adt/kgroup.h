// Copyright (c) 2023 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <memory>
#include <vector>

#include "paddle/cinn/adt/m_expr.h"

namespace cinn::hlir::framework::pir {

struct Group;

}  // namespace cinn::hlir::framework::pir

namespace cinn::adt {

class IGroup;
using cinn::adt::LoopDescriptors;

/**
 * Kernel = KGroup = List<IGroup>.
 * KGroup is a list of IGroups, KGroup uses shardable dimension to concatenate
 * all ops. This dimension is shared by all IGroups and bound to BlockIdx.
 */
class KGroup final {
 public:
  explicit KGroup(
      const std::shared_ptr<hlir::framework::pir::Group>& cinn_group,
      const std::vector<std::shared_ptr<IGroup>>& igroups)
      : cinn_group_(cinn_group), igroups_(igroups) {}

  std::shared_ptr<hlir::framework::pir::Group> cinn_group() const {
    return CHECK_NOTNULL(cinn_group_.lock());
  }

  const std::shared_ptr<IGroup>& GetSoleIGroup() const {
    return igroups_.at(0);
  }
  const std::vector<std::shared_ptr<IGroup>>& igroups() const {
    return igroups_;
  }

  List<LoopSize> GetDefaultScheduleSizes(
      const std::shared_ptr<IGroup>& igroup) const;

 private:
  std::weak_ptr<hlir::framework::pir::Group> cinn_group_;
  // NOTE: Use single igroup temporarily. Actually KGroup contains
  // multiple IGroups
  std::vector<std::shared_ptr<IGroup>> igroups_;
  // TODO(Hongyu Jia): Add equations here to link igroups
};

}  // namespace cinn::adt
