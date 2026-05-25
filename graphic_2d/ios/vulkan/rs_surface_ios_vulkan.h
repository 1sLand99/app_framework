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

#ifndef RENDER_SERVICE_BASE_SRC_PLATFORM_IOS_RS_SURFACE_IOS_VULKAN_H
#define RENDER_SERVICE_BASE_SRC_PLATFORM_IOS_RS_SURFACE_IOS_VULKAN_H

#include <cstdint>

#include "include/third_party/vulkan/vulkan/vulkan_core.h"
#include "render_context/new_render_context/render_context_vk.h"
#include "image/image.h"
#include "platform/common/rs_surface_ext.h"
#include "platform/drawing/rs_surface.h"
#include "platform/drawing/rs_surface_frame.h"
#include "rs_surface_frame_ios_vulkan.h"
#include "rs_surface_swap_chain.h"

namespace OHOS {
namespace Rosen {
class RSSurfaceIOSVulkan : public RSSurface {
public:
    explicit RSSurfaceIOSVulkan(void* metalLayer);
    ~RSSurfaceIOSVulkan() override;

    bool IsValid() const override;
    bool CheckLayerAndContext();
    std::unique_ptr<RSSurfaceFrame> RequestFrame(
        int32_t width, int32_t height, uint64_t uiTimestamp, bool useAFBC = true, bool isProtected = false) override;
    bool FlushFrame(std::unique_ptr<RSSurfaceFrame>& frame, uint64_t uiTimestamp) override;
    void SetColorSpace(GraphicColorGamut colorSpace) override;
    void ClearBuffer() override;
    void ClearAllBuffer() override;
    void SetUiTimeStamp(const std::unique_ptr<RSSurfaceFrame>& frame, uint64_t uiTimestamp) override;
    uint32_t GetQueueSize() const override;
    void ResetBufferAge() override;
    GraphicColorGamut GetColorSpace() const override;
    std::shared_ptr<RenderContext> GetRenderContext() override;
    void SetRenderContext(std::shared_ptr<RenderContext> context) override;
    RSSurfaceExtPtr CreateSurfaceExt(const RSSurfaceExtConfig& config) override;
    RSSurfaceExtPtr GetSurfaceExt(const RSSurfaceExtConfig& config) override;
    void DestroyOnRenderThread();
    std::shared_ptr<Drawing::Surface> CreateSkiaSurfaceFromSwapchainImage(
        uint32_t imageIndex, int32_t width, int32_t height, bool isProtected);

private:
    bool SetupGrContext();
    bool RecreateSwapchainIfNeeded(int32_t width, int32_t height);
    uint32_t AcquireSwapchainImage();
    std::shared_ptr<Drawing::Surface> GetOrCreateSkiaSurface(
        uint32_t imageIndex, int32_t swapchainWidth, int32_t swapchainHeight, bool isProtected);
    bool FlushSkiaSurface(std::shared_ptr<Drawing::Surface> surface, VkSemaphore renderFinishedSemaphore);
    void WaitAndSubmitSkiaContext(VkSemaphore waitSemaphore);
    bool PresentSwapchainImage(VkQueue queue, uint32_t imageIndex, VkSemaphore renderFinishedSemaphore);
    void ReleaseAcquiredSwapchainImage(uint32_t imageIndex);
    Drawing::ColorType ConvertVkFormatToSkiaColorType(VkFormat imageFormat);

    void* metalLayer_ = nullptr;
    std::shared_ptr<RenderContext> renderContext_;
    std::shared_ptr<Drawing::GPUContext> mSkContext_;
    GraphicColorGamut colorSpace_ = GraphicColorGamut::GRAPHIC_COLOR_GAMUT_SRGB;
    RSSurfaceSwapChain swapChain_;
    RSSurfaceExtPtr texture_;
    std::vector<std::shared_ptr<Drawing::Surface>> skiaSurfaces_;
    uint32_t lastPresentedImageIndex_ = UINT32_MAX;
    size_t currentFrame_ = 0;
    int32_t currentWidth_ = -1;
    int32_t currentHeight_ = 0;
};

} // namespace Rosen
} // namespace OHOS

#endif // RENDER_SERVICE_BASE_SRC_PLATFORM_IOS_RS_SURFACE_IOS_VULKAN_H
