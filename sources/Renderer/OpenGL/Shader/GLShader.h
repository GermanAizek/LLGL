/*
 * GLShader.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2019 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef LLGL_GL_SHADER_H
#define LLGL_GL_SHADER_H


#include <LLGL/Shader.h>
#include "../OpenGL.h"
#include "../../../Core/LinearStringContainer.h"


namespace LLGL
{


struct GLShaderAttribute
{
    GLuint          index;
    const GLchar*   name;
};

class GLShader final : public Shader
{

    public:

        void SetName(const char* name) override;

        bool HasErrors() const override;

        std::string GetReport() const override;

    public:

        // Compiles a native GL shader from source.
        static void CompileShaderSource(GLuint shader, const char* source);

        // Compiles a native GL shader from source and adds the specified macro definitions at the top of the source but after the '#version'-directive.
        static void CompileShaderSourceWithOptions(
            GLuint              shader,
            const char*         source,
            const ShaderMacro*  defines,
            bool                pragmaOptimizeOff   = false,
            const char*         vertexTransformStmt = nullptr
        );

        // Returns true if the native GL shader was compiled successfully.
        static bool GetCompileStatus(GLuint shader);

        // Returns the native GL shader log and returns true on success. Otherwise, there is no log available.
        static std::string GetGLShaderLog(GLuint shader);

    public:

        GLShader(const ShaderDescriptor& desc);
        ~GLShader();

        // Returns the native shader ID.
        inline GLuint GetID() const
        {
            return id_;
        }

        // Returns the vertex input attributes:
        const GLShaderAttribute* GetVertexAttribs() const;
        std::size_t GetNumVertexAttribs() const;

        // Returns the vertex input attributes:
        const GLShaderAttribute* GetFragmentAttribs() const;
        std::size_t GetNumFragmentAttribs() const;

        // Returns the transform feedback varying names.
        inline const std::vector<const char*>& GetTransformFeedbackVaryings() const
        {
            return transformFeedbackVaryings_;
        }

    private:

        void BuildShader(const ShaderDescriptor& shaderDesc);
        void ReserveAttribs(const ShaderDescriptor& desc);
        void BuildVertexInputLayout(std::size_t numVertexAttribs, const VertexAttribute* vertexAttribs);
        void BuildFragmentOutputLayout(std::size_t numFragmentAttribs, const FragmentAttribute* fragmentAttribs);
        void BuildTransformFeedbackVaryings(std::size_t numVaryings, const VertexAttribute* varyings);

        void CompileSource(const ShaderDescriptor& shaderDesc);
        void LoadBinary(const ShaderDescriptor& shaderDesc);

    private:

        GLuint                          id_                         = 0;

        LinearStringContainer           shaderAttribNames_;
        std::vector<GLShaderAttribute>  shaderAttribs_;
        std::size_t                     numVertexAttribs_           = 0;
        std::vector<const char*>        transformFeedbackVaryings_;

};


} // /namespace LLGL


#endif



// ================================================================================
