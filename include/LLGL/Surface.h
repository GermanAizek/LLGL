/*
 * Surface.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef LLGL_SURFACE_H
#define LLGL_SURFACE_H


#include "Export.h"


namespace LLGL
{


/**
\brief The Surface interface is the base interface for Window and Canvas.
\remarks Surface provides the minimal required interface for a graphics rendering context,
such as the access to the native handle and the ability to dynamically recreate its surface
(which is required for multi-sampled framebuffers on a WGL context for instance).
\see Window
\see Canvas
*/
class LLGL_EXPORT Surface
{

    public:

        virtual ~Surface()
        {
        }

        /**
        \brief Returns the native surface handle.
        \remarks This must be casted to a platform specific structure:
        \code
        // Example for a custom Win32 window class
        #include <LLGL/Platform/NativeHandle.h>
        //...
        void YourWindowClass::GetNativeHandle(void* nativeHandle)
        {
            auto handle = reinterpret_cast<LLGL::NativeHandle*>(nativeHandle);
            //handle->window = 'some HWND window handle';
        }
        \endcode
        */
        virtual void GetNativeHandle(void* nativeHandle) const = 0;

        /**
        \brief Recreates the internal surface object with the current descriptor settings.
        This may invalidate the native handle previously returned by "GetNativeHandle".
        \remarks This function is mainly used by the OpenGL renderer on Win32 when a multi-sampled framebuffer is created.
        \see GetNativeHandle
        */
        virtual void Recreate() = 0;

};


} // /namespace LLGL


#endif



// ================================================================================
