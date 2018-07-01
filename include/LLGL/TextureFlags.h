/*
 * TextureFlags.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef LLGL_TEXTURE_FLAGS_H
#define LLGL_TEXTURE_FLAGS_H


#include "Export.h"
#include "Types.h"
#include "Format.h"
#include <cstddef>
#include <cstdint>


namespace LLGL
{


/* ----- Enumerations ----- */

//! Texture type enumeration.
enum class TextureType
{
    Texture1D,          //!< 1-Dimensional texture.
    Texture2D,          //!< 2-Dimensional texture.
    Texture3D,          //!< 3-Dimensional texture.
    TextureCube,        //!< Cube texture.
    Texture1DArray,     //!< 1-Dimensional array texture.
    Texture2DArray,     //!< 2-Dimensional array texture.
    TextureCubeArray,   //!< Cube array texture.
    Texture2DMS,        //!< 2-Dimensional multi-sample texture.
    Texture2DMSArray,   //!< 2-Dimensional multi-sample array texture.
};

//! Axis direction (also used for texture cube face).
enum class AxisDirection
{
    XPos = 0,   //!< X+ direction.
    XNeg,       //!< X- direction.
    YPos,       //!< Y+ direction.
    YNeg,       //!< Y- direction.
    ZPos,       //!< Z+ direction.
    ZNeg,       //!< Z- direction.
};

#if 0//TODO: currently unused
/**
\brief Texture component swizzle enumeration.
\remarks Can be used to change the order of texel components independently of a shader.
\see TextureSwizzleRGBA
*/
enum class TextureSwizzle
{
    Zero,   //!< The component is replaced by the constant zero.
    One,    //!< The component is replaced by the constant one.
    Red,    //!< The component is replaced by red component.
    Green,  //!< The component is replaced by green component.
    Blue,   //!< The component is replaced by blue component.
    Alpha   //!< The component is replaced by alpha component.
};
#endif

/**
\brief Texture creation flags enumeration.
\see TextureDescriptor::flags
*/
struct TextureFlags
{
    enum
    {
        #if 0
        /**
        \brief Texture mapping with CPU read access is required.
        \see RenderSystem::MapTexture
        */
        MapReadAccess       = (1 << 0),

        /**
        \brief Texture mapping with CPU write access is required.
        \see RenderSystem::MapTexture
        */
        MapWriteAccess      = (1 << 1),

        /*
        \brief Texture mapping with CPU read and write access is required.
        \see TextureFlags::MapReadAccess
        \see TextureFlags::MapWriteAccess
        */
        MapReadWriteAccess  = (MapReadAccess | MapWriteAccess),

        /**
        \brief Hint to the renderer that the texture will be frequently updated from the CPU.
        \see RenderSystem::WriteTexture
        */
        DynamicUsage        = (1 << 2),
        #endif

        /**
        \brief Texture will be used with MIP-mapping. This will create all MIP-map levels at texture creation time.
        \remarks This is part of the default flags.
        \see RenderSystem::GenerateMips
        \see Default
        */
        GenerateMips        = (1 << 3),

        /**
        \brief Texture can be used as render target attachment.
        \remarks This is part of the default flags.
        \see AttachmentDescriptor::texture
        \see Default
        */
        AttachmentUsage     = (1 << 4),

        /**
        \brief Texture can be used for sampling (e.g. "sampler2D" in GLSL, or "Texture2D" in HLSL).
        \remarks This is part of the default flags.
        \see Default
        */
        SampleUsage         = (1 << 5),

        //! Texture can be used as storage texture (e.g. "image2D" in GLSL, or "RWTexture2D" in HLSL).
        StorageUsage        = (1 << 6),

        /**
        \brief Multi-sampled texture has fixed sample locations.
        \remarks This can only be used with multi-sampled textures (i.e. TextureType::Texture2DMS, TextureType::Texture2DMSArray).
        \see TextureType
        \see Default
        */
        FixedSamples        = (1 << 7),

        /**
        \brief Default texture flags: (GenerateMips | AttachmentUsage | SampleUsage | FixedSamples).
        \see GenerateMips
        \see AttachmentUsage
        \see SampleUsage
        \see FixedSamples
        */
        Default             = (GenerateMips | AttachmentUsage | SampleUsage | FixedSamples),
    };
};


/* ----- Structures ----- */

#if 0//TODO: currently unused
/**
\brief Texture component swizzle structure for red, green, blue, and alpha components.
\remarks Can be used to change the order of texel components independently of a shader.
*/
struct TextureSwizzleRGBA
{
    TextureSwizzle r = TextureSwizzle::Red;     //!< Red component swizzle. By default TextureSwizzle::Red.
    TextureSwizzle g = TextureSwizzle::Green;   //!< Green component swizzle. By default TextureSwizzle::Green.
    TextureSwizzle b = TextureSwizzle::Blue;    //!< Blue component swizzle. By default TextureSwizzle::Blue.
    TextureSwizzle a = TextureSwizzle::Alpha;   //!< Alpha component swizzle. By default TextureSwizzle::Alpha.
};
#endif

/**
\brief Texture descriptor structure.
\remarks This is used to specifiy the dimensions of a texture which is to be created.
*/
struct TextureDescriptor
{
    //! Hardware texture type. By default TextureType::Texture1D.
    TextureType     type        = TextureType::Texture1D;

    //! Hardware texture format. By default Format::RGBA8UNorm.
    Format          format      = Format::RGBA8UNorm;

    /**
    \brief Specifies the texture creation flags (e.g. if MIP-mapping is required). By default TextureFlags::Default.
    \remarks This can be bitwise OR combination of the entries of the TextureFlags enumeration.
    \see TextureFlags
    */
    long            flags       = TextureFlags::Default;

    //! Texture width. By default 1.
    std::uint32_t   width       = 1;

    /**
    \brief Texture height. By default 1.
    \remarks This is only used for 2D, 3D, and Cube textures (i.e. TextureType::Texture2D, TextureType::Texture2DArray, TextureType::Texture3D,
    TextureType::TextureCube, TextureType::TextureCubeArray, TextureType::Texture2DMS, TextureType::Texture2DMSArray).
    \see TextureType
    */
    std::uint32_t   height      = 1;

    /**
    \brief Texture depth. By default 1.
    \remarks This is only used for 3D textures (i.e. TextureType::Texture3D).
    \see TextureType
    */
    std::uint32_t   depth       = 1;

    /**
    \brief Number of array layers. By default 1.
    \remarks This is only used for array textures (i.e. TextureType::Texture1DArray, TextureType::Texture2DArray,
    TextureType::TextureCubeArray, TextureType::Texture2DMSArray).
    \see TextureType
    */
    std::uint32_t   layers      = 1;

    /**
    \brief Number of samples per texel. By default 1.
    \remarks This is only used for multi-sampled textures (i.e. TextureType::Texture2DMS and TextureType::Texture2DMSArray).
    \see TextureType
    */
    std::uint32_t   samples     = 1;
};

/**
\brief Sub-texture descriptor structure.
\remarks This is used to write (or partially write) the image data of a texture MIP-map level.
*/
struct SubTextureDescriptor
{
    //! MIP-map level for the sub-texture, where 0 is the base texture, and N > 0 is the N-th MIP-map level. By default 0.
    std::uint32_t   mipLevel    = 0;

    /**
    \brief Sub-texture offset. By default (0, 0, 0).
    \remarks For array textures, the Z component specifies the array layer.
    For cube textures, the Z component specifies the array layer and cube face offset (for 1D-array textures it's the Y component).
    The layer offset for the respective cube face can be determined by the values of the AxisDirection enumeration
    \see AxisDirection
    */
    Offset3D        offset      = { 0, 0, 0 };

    /**
    \brief Sub-texture extent. By default (1, 1, 1).
    \remarks For array textures, the depth component specifies the number of array layers (for 1D-array textures it's the height component).
    For cube textures, the depthj component specifies the number of array layers and cube faces (where each cube has 6 faces).
    */
    Extent3D        extent      = { 1, 1, 1 };
};


/* ----- Functions ----- */

/**
\defgroup group_tex_util Texture utility functions to determine texture dimension and buffer sizes.
\addtogroup group_tex_util
@{
*/

/**
\brief Returns the number of MIP-map levels for a texture with the specified size.
\param[in] width Specifies the texture width.
\param[in] height Specifies the texture height or number of layers for 1D array textures. By default 1 (if 1D textures are used).
\param[in] depth Specifies the texture depth or number of layers for 2D array textures. By default 1 (if 1D or 2D textures are used).
\remarks The height and depth are optional parameters, so this function can be easily used for 1D, 2D, and 3D textures.
\return 1 + floor(log2(max{ width, height, depth })).
*/
LLGL_EXPORT std::uint32_t NumMipLevels(std::uint32_t width, std::uint32_t height = 1, std::uint32_t depth = 1);

/**
\brief Returns the number of MIP-map levels for the specified texture descriptor.
\param[in] textureDesc Specifies the descriptor whose parameters are used to determine the number of MIP-map levels.
\return Number of MIP-map levels, or 1 if the descriptor has not the 'TextureFlags::GenerateMips' flags bit set.
\see NumMipLevels(std::uint32_t, std::uint32_t, std::uint32_t)
*/
LLGL_EXPORT std::uint32_t NumMipLevels(const TextureDescriptor& textureDesc);

/**
\briefs Returns the number of array layers for the specified texture descriptor.
\param[in] textureDesc Specifies the descriptor whose parameters are used to determine the number of array layers.
\return Number of array layers, or 1 if the texture type is not an array texture.
\see IsArrayTexture
\deprecated Use TextureDescriptor::layers instead.
*/
LLGL_EXPORT std::uint32_t NumArrayLayers(const TextureDescriptor& textureDesc);

/**
\brief Returns the required buffer size (in bytes) of a texture with the specified hardware format and number of texels.
\param[in] format Specifies the texture format.
\param[in] numTexels Specifies the number of texture elements (texels).
For the DXT compressed texture formats, this must be a multiple of 16, since these formats compress the image in 4x4 texel blocks.
\return The required buffer size (in bytes), or zero if the input is invalid.
\remarks The counterpart for image data is the function ImageDataSize.
\see ImageDataSize
*/
LLGL_EXPORT std::uint32_t TextureBufferSize(const Format format, std::uint32_t numTexels);

/**
\brief Returns the texture size (in texels) of the specified texture descriptor, or zero if the texture type is invalid.
\see TextureDescriptor::type
*/
LLGL_EXPORT std::uint32_t TextureSize(const TextureDescriptor& textureDesc);

/**
\brief Returns true if the specified texture type is an array texture.
\return True if 'type' is . either TextureType::Texture1DArray, TextureType::Texture2DArray,
TextureType::TextureCubeArray, or TextureType::Texture2DMSArray.
*/
LLGL_EXPORT bool IsArrayTexture(const TextureType type);

/**
\brief Returns true if the specified texture type is a multi-sample texture.
\return True if 'type' is either TextureType::Texture2DMS, or TextureType::Texture2DMSArray.
*/
LLGL_EXPORT bool IsMultiSampleTexture(const TextureType type);

/**
\brief Returns true if the specified texture type is a cube texture.
\return True if 'type' is either TextureType::TextureCube or TextureType::TextureCubeArray.
*/
LLGL_EXPORT bool IsCubeTexture(const TextureType type);

/** @} */


} // /namespace LLGL


#endif



// ================================================================================
