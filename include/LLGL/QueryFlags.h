/*
 * QueryFlags.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef LLGL_QUERY_FLAGS_H
#define LLGL_QUERY_FLAGS_H


#include "Constants.h"
#include <cstdint>


namespace LLGL
{


/* ----- Enumerations ----- */

/**
\brief Query type enumeration.
\see QueryDescriptor::type
*/
enum class QueryType
{
    //! Number of samples that passed the depth test. This can be used as render condition.
    SamplesPassed,

    //! Non-zero if any samples passed the depth test. This can be used as render condition.
    AnySamplesPassed,

    //! Non-zero if any samples passed the depth test within a conservative rasterization. This can be used as render condition.
    AnySamplesPassedConservative,

    //! Elapsed time (in nanoseconds) between the begin- and end query command.
    TimeElapsed,

    //! Number of vertices that have been written into a stream output (also called "Transform Feedback").
    StreamOutPrimitivesWritten,

    //! Non-zero if any of the streaming output buffers (also called "Transform Feedback Buffers") has an overflow.
    StreamOutOverflow,

    /**
    \brief Pipeline statistics such as number of shader invocations, generated primitives, etc.
    \see QueryPipelineStatistics
    */
    PipelineStatistics,
};


/* ----- Structures ----- */

/**
\brief Query data structure for pipeline statistics.
\remarks If the renderer does not support individual members of this structure, they will be set to QueryPipelineStatistics::invalidNum.
\see QueryType::PipelineStatistics
\see CommandBuffer::Query
\todo Rename to "PipelineStatistics"
*/
struct QueryPipelineStatistics
{
    //! Number of generated primitives which are send to the rasterizer (either emitted from the geometry or vertex shader).
    std::uint64_t numPrimitivesGenerated                = Constants::invalidQueryResult;

    //! Number of vertices submitted to the input-assembly.
    std::uint64_t numVerticesSubmitted                  = Constants::invalidQueryResult;

    //! Number of primitives submitted to the input-assembly.
    std::uint64_t numPrimitivesSubmitted                = Constants::invalidQueryResult;

    //! Number of vertex shader invocations.
    std::uint64_t numVertexShaderInvocations            = Constants::invalidQueryResult;

    //! Number of tessellation-control shader invocations.
    std::uint64_t numTessControlShaderInvocations       = Constants::invalidQueryResult;

    //! Number of tessellation-evaluation shader invocations.
    std::uint64_t numTessEvaluationShaderInvocations    = Constants::invalidQueryResult;

    //! Number of geometry shader invocations.
    std::uint64_t numGeometryShaderInvocations          = Constants::invalidQueryResult;

    //! Number of fragment shader invocations.
    std::uint64_t numFragmentShaderInvocations          = Constants::invalidQueryResult;

    //! Number of compute shader invocations.
    std::uint64_t numComputeShaderInvocations           = Constants::invalidQueryResult;

    //! Number of primitives generated by the geometry shader.
    std::uint64_t numGeometryPrimitivesGenerated        = Constants::invalidQueryResult;

    //! Number of primitives that reached the primitive clipping stage.
    std::uint64_t numClippingInputPrimitives            = Constants::invalidQueryResult;

    //! Number of primitives that passed the primitive clipping stage.
    std::uint64_t numClippingOutputPrimitives           = Constants::invalidQueryResult;
};

/**
\brief Query descriptor structure.
\see RenderSystem::CreateQuery
*/
struct QueryDescriptor
{
    QueryDescriptor() = default;

    //! Constructor to initialize the query type and optionally the render condition.
    inline QueryDescriptor(QueryType type, bool renderCondition = false) :
        type            { type            },
        renderCondition { renderCondition }
    {
    }

    //! Specifies the type of the query. By default QueryType::SamplesPassed (occlusion query).
    QueryType   type            = QueryType::SamplesPassed;

    /**
    \brief Specifies whether the query is to be used as a render condition. By default false.
    \remarks If this is true, 'type' can only have one of the following values:
    QueryType::SamplesPassed, QueryType::AnySamplesPassed, QueryType::AnySamplesPassedConservative, or QueryType::StreamOutOverflow.
    */
    bool        renderCondition = false;
};


} // /namespace LLGL


#endif



// ================================================================================
