/*
 * SwapChain.cpp
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2019 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <LLGL/SwapChain.h>
#include <LLGL/Window.h>
#include <LLGL/Canvas.h>
#include <LLGL/Display.h>
#include "CheckedCast.h"
#include "../Core/Helper.h"


namespace LLGL
{


SwapChain::SwapChain(const SwapChainDescriptor& desc) :
    resolution_ { desc.resolution }
{
}

/* ----- Render Target ----- */

Extent2D SwapChain::GetResolution() const
{
    return resolution_;
}

std::uint32_t SwapChain::GetNumColorAttachments() const
{
    return 1u;
}

bool SwapChain::HasDepthAttachment() const
{
    return IsDepthFormat(GetDepthStencilFormat());
}

bool SwapChain::HasStencilAttachment() const
{
    return IsStencilFormat(GetDepthStencilFormat());
}

bool SwapChain::ResizeBuffers(const Extent2D& resolution, long flags)
{
    const bool toggleFullscreen = ((flags & (ResizeBuffersFlags::FullscreenMode | ResizeBuffersFlags::WindowedMode)) != 0);
    const bool adaptSurface     = (toggleFullscreen || (flags & ResizeBuffersFlags::AdaptSurface) != 0);

    if (adaptSurface)
    {
        /* Reset fullscreen mode or store surface position for windowed mode */
        bool fullscreen = ((flags & ResizeBuffersFlags::FullscreenMode) != 0);

        if (toggleFullscreen)
        {
            if (fullscreen)
                StoreSurfacePosition();
            else
                ResetDisplayFullscreenMode();
        }

        /* Adapt surface for new resolution */
        auto size = resolution;
        if (GetSurface().AdaptForVideoMode(&size, (toggleFullscreen ? &fullscreen : nullptr)))
        {
            if (ResizeBuffersPrimary(size))
            {
                resolution_ = size;
                return true;
            }
        }

        /* Switch to fullscreen or restore surface position for windowed mode */
        if (toggleFullscreen)
        {
            if (fullscreen)
                SetDisplayFullscreenMode(size);
            else
                RestoreSurfacePosition();
        }
    }
    else
    {
        /* Only resize swap buffers */
        if (ResizeBuffersPrimary(resolution))
        {
            resolution_ = resolution;
            return true;
        }
    }

    return false;
}

/* ----- Configuration ----- */

bool SwapChain::SwitchFullscreen(bool enable)
{
    bool result = false;
    if (enable)
    {
        StoreSurfacePosition();
        GetSurface().AdaptForVideoMode(nullptr, &enable);
        result = SetDisplayFullscreenMode(GetResolution());
    }
    else
    {
        result = ResetDisplayFullscreenMode();
        GetSurface().AdaptForVideoMode(nullptr, &enable);
        RestoreSurfacePosition();
    }
    return result;
}


/*
 * ======= Protected: =======
 */

void SwapChain::SetOrCreateSurface(const std::shared_ptr<Surface>& surface, const Extent2D& size, bool fullscreen, const void* windowContext)
{
    /* Use specified surface size as resolution by default */
    Extent2D resolution = size;

    if (surface)
    {
        /* Get and output resolution from specified window */
        resolution = surface->GetContentSize();
        surface_ = surface;
    }
    else
    {
        #ifdef LLGL_MOBILE_PLATFORM

        /* Create new canvas for this swap-chain */
        CanvasDescriptor canvasDesc;
        {
            canvasDesc.borderless = fullscreen;
        }
        surface_ = Canvas::Create(canvasDesc);

        #else

        /* Create new window for this swap-chain */
        WindowDescriptor windowDesc;
        {
            windowDesc.size             = size;
            windowDesc.borderless       = fullscreen;
            windowDesc.centered         = !fullscreen;
            windowDesc.windowContext    = windowContext;
        }
        surface_ = Window::Create(windowDesc);

        #endif
    }

    /* Switch to fullscreen mode before storing new video mode */
    if (fullscreen)
        SetDisplayFullscreenMode(resolution);
}

void SwapChain::ShareSurfaceAndConfig(SwapChain& other)
{
    surface_    = other.surface_;
    resolution_ = other.resolution_;
}

bool SwapChain::SetDisplayFullscreenMode(const Extent2D& resolution)
{
    if (surface_)
    {
        if (auto display = surface_->FindResidentDisplay())
        {
            /* Change display mode resolution to video mode setting */
            auto displayModeDesc = display->GetDisplayMode();
            displayModeDesc.resolution = resolution;
            return display->SetDisplayMode(displayModeDesc);
        }
    }
    return false;
}

bool SwapChain::ResetDisplayFullscreenMode()
{
    if (surface_)
    {
        if (auto display = surface_->FindResidentDisplay())
        {
            /* Reset display mode to default */
            return display->ResetDisplayMode();
        }
    }
    return false;
}


/*
 * ======= Private: =======
 */

void SwapChain::StoreSurfacePosition()
{
    #ifndef LLGL_MOBILE_PLATFORM
    if (!normalModeSurfacePosStored_)
    {
        auto& window = static_cast<Window&>(GetSurface());
        normalModeSurfacePos_       = window.GetPosition();
        normalModeSurfacePosStored_ = true;
    }
    #endif
}

void SwapChain::RestoreSurfacePosition()
{
    #ifndef LLGL_MOBILE_PLATFORM
    if (normalModeSurfacePosStored_)
    {
        auto& window = static_cast<Window&>(GetSurface());
        window.SetPosition(normalModeSurfacePos_);
        normalModeSurfacePosStored_ = false;
    }
    #endif
}


} // /namespace LLGL



// ================================================================================
