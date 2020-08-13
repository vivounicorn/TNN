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

#include "tnn/network/tensorrt/layer_builder/tensorrt_layer_builder.h"

namespace TNN_NS {

TensorRTLayerBuilder::TensorRTLayerBuilder(LayerType type) : TensorRTBaseLayerBuilder(type) {
}

TensorRTLayerBuilder::~TensorRTLayerBuilder() {
}

Status TensorRTLayerBuilder::Init(Context* context, LayerParam* param, LayerResource* resource, std::vector<Blob*>& input_blobs,
        std::vector<Blob*>& output_blobs, AbstractDevice* device) {
    input_blobs_  = input_blobs;
    output_blobs_ = output_blobs;

    param_    = param;
    resource_ = resource;

    Build();
    auto status = InferOutputDataType();
    if (status != TNN_OK) {
        return status;
    }

    status = InferOutputShape();
    LOGD("InferOutputShape: name:%s shape:%d %d %d %d \n", param->name.c_str(), output_blobs[0]->GetBlobDesc().dims[0],
         output_blobs[0]->GetBlobDesc().dims[1], output_blobs[0]->GetBlobDesc().dims[2],
         output_blobs[0]->GetBlobDesc().dims[3]);
    if (status != TNN_OK) {
        return status;
    }
    auto dims = output_blobs[0]->GetBlobDesc().dims;
    for (auto item : dims) {
        if (item <= 0) {
            LOGE("Error: layer(%s) output dims is invalid\n", layer_name_.c_str());
            return Status(TNNERR_LAYER_ERR, "layer output dims is invalid");
        }
    }

    return TNN_OK;
}

Status TensorRTLayerBuilder::Reshape() {
    return TNN_OK;
}

Status TensorRTLayerBuilder::Forward() {
    return TNN_OK;
}

Status TensorRTLayerBuilder::Build() {
    return TNN_OK;
}

}  //  namespace TNN_NS