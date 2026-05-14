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

#ifndef RENDER_SERVICE_BASE_SRC_PLATFORM_IOS_RS_SURFACE_FRAME_IOS_VULKAN_H
#define RENDER_SERVICE_BASE_SRC_PLATFORM_IOS_RS_SURFACE_FRAME_IOS_VULKAN_H

#include <surface.h>

#ifdef USE_M133_SKIA
#include "include/gpu/ganesh/GrDirectContext.h"
#else
#include "include/gpu/GrDirectContext.h"
#endif

#include "rs_surface_frame_ios.h"

namespace OHOS {
namespace Rosen {

class RSSurfaceFrameIOSVulkan : public RSSurfaceFrameIOS {
public:
    RSSurfaceFrameType GetType() const override
    {
        return RSSurfaceFrameType::RS_SURFACE_FRAME_OHOS_VULKAN;
    }

    RSSurfaceFrameIOSVulkan(std::shared_ptr<Drawing::Surface> surface, int32_t width,
        int32_t height, int32_t bufferAge);
    ~RSSurfaceFrameIOSVulkan() override = default;

    Drawing::Canvas* GetCanvas() override;
    std::shared_ptr<Drawing::Surface> GetSurface() override;
    void SetDamageRegion(int32_t left, int32_t top, int32_t width, int32_t height) override;
    void SetDamageRegion(const std::vector<RectI>& rects) override;
    int32_t GetBufferAge() const override;
    void SetSwapchainImageIndex(uint32_t index) { imageIndex_ = index; }
    uint32_t GetSwapchainImageIndex() const { return imageIndex_; }
    void SetSurfacePhysicalSize(int32_t physicalWidth, int32_t physicalHeight)
    {
        surfacePhysicalWidth_ = physicalWidth;
        surfacePhysicalHeight_ = physicalHeight;
    }

private:
    std::shared_ptr<Drawing::Surface> surface_;
    int width_ = 0;
    int height_ = 0;
    int32_t surfacePhysicalWidth_ = 0;
    int32_t surfacePhysicalHeight_ = 0;
    uint32_t imageIndex_ = 0;
    int32_t bufferAge_ = -1;
};
} // namespace Rosen
} // namespace OHOS

#endif // RENDER_SERVICE_BASE_SRC_PLATFORM_IOS_RS_SURFACE_FRAME_IOS_VULKAN_H
