// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include <algorithm>

#include "tnn/interpreter/tnn/objseri.h"
#include "tnn_optimize_pass.h"

namespace TNN_CONVERTER {

DECLARE_OPTIMIZE_PASS(ReshapeConstFolding);

std::string TnnOptimizeReshapeConstFoldingPass::PassName() {
    return "ReshapeConstFolding";
}

TNN_NS::Status TnnOptimizeReshapeConstFoldingPass::exec(TNN_NS::NetStructure& net_structure,
                                                        TNN_NS::NetResource& net_resource) {
    auto& layers = net_structure.layers;
    for (auto iter = layers.begin(); iter < layers.end();) {
        auto cur_layer = *iter;
        if (cur_layer->type == TNN_NS::LAYER_RESHAPE) {
            auto param = dynamic_cast<TNN_NS::ReshapeLayerParam*>(cur_layer->param.get());
            if (cur_layer->inputs.size() == 1 && !param->shape.empty()) {
                iter++;
                continue;
            }
            ASSERT(cur_layer->inputs.size() == 2);
            std::string input_name = cur_layer->inputs[0];
            cur_layer->inputs.resize(1);
            cur_layer->inputs[0] = input_name;
        }
        iter++;
    }
    return TNN_NS::TNN_CONVERT_OK;
}

REGISTER_OPTIMIZE_PASS(ReshapeConstFolding);
}  // namespace TNN_CONVERTER