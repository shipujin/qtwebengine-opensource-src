/*
* Copyright 2016 Google Inc.
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#ifndef GrVkUniformHandler_DEFINED
#define GrVkUniformHandler_DEFINED

#include "include/gpu/vk/GrVkTypes.h"
#include "src/gpu/GrSamplerState.h"
#include "src/gpu/GrShaderVar.h"
#include "src/gpu/GrTBlockList.h"
#include "src/gpu/glsl/GrGLSLUniformHandler.h"
#include "src/gpu/vk/GrVkSampler.h"

class GrVkUniformHandler : public GrGLSLUniformHandler {
public:
    static const int kUniformsPerBlock = 8;

    enum {
        /**
         * Binding a descriptor set invalidates all higher index descriptor sets. We must bind
         * in the order of this enumeration. Samplers are after Uniforms because GrOps can specify
         * GP textures as dynamic state, meaning they get rebound for each draw in a pipeline while
         * uniforms are bound once before all the draws. We bind input attachments after samplers
         * so those also need to be rebound if we bind new samplers.
         */
        kUniformBufferDescSet = 0,
        kSamplerDescSet = 1,
        kInputDescSet = 2,

        kLastDescSet = kInputDescSet,
    };
    static constexpr int kDescSetCount = kLastDescSet + 1;

    // The bindings within their respective sets for various descriptor types.
    enum {
        kUniformBinding = 0,
        kInputBinding = 0,
    };
    enum {
        kDstInputAttachmentIndex = 0
    };

    struct VkUniformInfo : public UniformInfo {
        VkUniformInfo(UniformInfo u, uint32_t offset, const GrVkSampler* samp) : UniformInfo(u), fUBOffset(offset), fImmutableSampler(samp) {}
        // fUBOffset is only valid if the GrSLType of the fVariable is not a sampler
        uint32_t                fUBOffset;
        // fImmutableSampler is used for sampling an image with a ycbcr conversion.
        const GrVkSampler*      fImmutableSampler = nullptr;
    };
    typedef GrTBlockList<VkUniformInfo> UniformInfoArray;

    ~GrVkUniformHandler() override;

    const GrShaderVar& getUniformVariable(UniformHandle u) const override {
        return fUniforms.item(u.toIndex()).fVariable;
    }

    const char* getUniformCStr(UniformHandle u) const override {
        return this->getUniformVariable(u).c_str();
    }

    /**
     * Returns the offset that the RTHeight synthetic uniform should use if it needs to be created.
     */
    uint32_t getRTHeightOffset() const;

    int numUniforms() const override {
        return fUniforms.count();
    }

    UniformInfo& uniform(int idx) override {
        return fUniforms.item(idx);
    }
    const UniformInfo& uniform(int idx) const override {
        return fUniforms.item(idx);
    }

private:
    explicit GrVkUniformHandler(GrGLSLProgramBuilder* program)
        : INHERITED(program)
        , fUniforms(kUniformsPerBlock)
        , fSamplers(kUniformsPerBlock)
        , fCurrentUBOOffset(0) {
    }

    UniformHandle internalAddUniformArray(const GrFragmentProcessor* owner,
                                          uint32_t visibility,
                                          GrSLType type,
                                          const char* name,
                                          bool mangleName,
                                          int arrayCount,
                                          const char** outName) override;

    SamplerHandle addSampler(const GrBackendFormat&,
                             GrSamplerState,
                             const GrSwizzle&,
                             const char* name,
                             const GrShaderCaps*) override;

    SamplerHandle addInputSampler(const GrSwizzle& swizzle, const char* name) override;

    int numSamplers() const { return fSamplers.count(); }
    const char* samplerVariable(SamplerHandle handle) const override {
        return fSamplers.item(handle.toIndex()).fVariable.c_str();
    }
    GrSwizzle samplerSwizzle(SamplerHandle handle) const override {
        return fSamplerSwizzles[handle.toIndex()];
    }
    uint32_t samplerVisibility(SamplerHandle handle) const {
        return fSamplers.item(handle.toIndex()).fVisibility;
    }

    const GrVkSampler* immutableSampler(UniformHandle u) const {
        return fSamplers.item(u.toIndex()).fImmutableSampler;
    }

    const char* inputSamplerVariable(SamplerHandle handle) const override {
        // Currently we will only ever have one input sampler variable, though in the future we may
        // expand to allow more inputs. For now assert that any requested handle maps to index 0,
        // to make sure we didn't add multiple input samplers.
        SkASSERT(handle.toIndex() == 0);
        return fInputUniform.fVariable.c_str();
    }
    GrSwizzle inputSamplerSwizzle(SamplerHandle handle) const override {
        SkASSERT(handle.toIndex() == 0);
        return fInputSwizzle;
    }

    void appendUniformDecls(GrShaderFlags, SkString*) const override;

    const VkUniformInfo& getUniformInfo(UniformHandle u) const {
        return fUniforms.item(u.toIndex());
    }

    UniformInfoArray    fUniforms;
    UniformInfoArray    fSamplers;
    SkTArray<GrSwizzle> fSamplerSwizzles;
    UniformInfo         fInputUniform;
    GrSwizzle           fInputSwizzle;

    uint32_t            fCurrentUBOOffset;

    friend class GrVkPipelineStateBuilder;
    friend class GrVkDescriptorSetManager;

    using INHERITED = GrGLSLUniformHandler;
};

#endif