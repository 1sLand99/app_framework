/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "rs_surface_frame_ios_vulkan.h"
#include "platform/common/rs_log.h"
#include "rs_trace.h"

namespace OHOS {
namespace Rosen {

RSSurfaceFrameIOSVulkan::RSSurfaceFrameIOSVulkan(std::shared_ptr<Drawing::Surface> surface, int32_t width,
    int32_t height, int32_t bufferAge)
    : RSSurfaceFrameIOS(width, height), surface_(surface), width_(width), height_(height), bufferAge_(bufferAge)
{
}

void RSSurfaceFrameIOSVulkan::SetDamageRegion(int32_t left, int32_t top, int32_t width, int32_t height)
{
    RS_TRACE_FUNC();
    std::vector<Drawing::RectI> rects;
    Drawing::RectI rect = {left, top, left + width, top + height};
    rects.push_back(rect);
    if (surface_) {
        surface_->SetDrawingArea(rects);
    }
}

void RSSurfaceFrameIOSVulkan::SetDamageRegion(const std::vector<RectI>& rects)
{
    RS_TRACE_FUNC();
    std::vector<Drawing::RectI> iRects;
    for (auto& rect : rects) {
        Drawing::RectI iRect = {rect.GetLeft(), rect.GetTop(), rect.GetRight(), rect.GetBottom()};
        iRects.push_back(iRect);
    }
    if (surface_) {
        surface_->SetDrawingArea(iRects);
    }
}

Drawing::Canvas* RSSurfaceFrameIOSVulkan::GetCanvas()
{
    if (surface_ == nullptr) {
        return nullptr;
    }
    return surface_->GetCanvas().get();
}

std::shared_ptr<Drawing::Surface> RSSurfaceFrameIOSVulkan::GetSurface()
{
    return surface_;
}

int32_t RSSurfaceFrameIOSVulkan::GetBufferAge() const
{
    return bufferAge_;
}
} // namespace Rosen
} // namespace OHOS
