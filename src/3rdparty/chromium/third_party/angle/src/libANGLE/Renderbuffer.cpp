//
// Copyright 2002 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Renderbuffer.cpp: Implements the renderer-agnostic gl::Renderbuffer class,
// GL renderbuffer objects and related functionality.
// [OpenGL ES 2.0.24] section 4.4.3 page 108.

#include "libANGLE/Renderbuffer.h"

#include "common/utilities.h"
#include "libANGLE/Context.h"
#include "libANGLE/FramebufferAttachment.h"
#include "libANGLE/Image.h"
#include "libANGLE/Renderbuffer.h"
#include "libANGLE/Texture.h"
#include "libANGLE/formatutils.h"
#include "libANGLE/renderer/GLImplFactory.h"
#include "libANGLE/renderer/d3d/RenderTargetD3D.h"

namespace gl
{
namespace
{
angle::SubjectIndex kRenderbufferImplSubjectIndex = 0;
}  // namespace

// RenderbufferState implementation.
RenderbufferState::RenderbufferState()
    : mWidth(0),
      mHeight(0),
      mFormat(GL_RGBA4),
      mSamples(0),
      mMultisamplingMode(MultisamplingMode::Regular),
      mInitState(InitState::MayNeedInit)
{}

RenderbufferState::~RenderbufferState() {}

GLsizei RenderbufferState::getWidth() const
{
    return mWidth;
}

GLsizei RenderbufferState::getHeight() const
{
    return mHeight;
}

const Format &RenderbufferState::getFormat() const
{
    return mFormat;
}

GLsizei RenderbufferState::getSamples() const
{
    return mSamples;
}

MultisamplingMode RenderbufferState::getMultisamplingMode() const
{
    return mMultisamplingMode;
}

InitState RenderbufferState::getInitState() const
{
    return mInitState;
}

void RenderbufferState::update(GLsizei width,
                               GLsizei height,
                               const Format &format,
                               GLsizei samples,
                               MultisamplingMode multisamplingMode,
                               InitState initState)
{
    mWidth             = width;
    mHeight            = height;
    mFormat            = format;
    mSamples           = samples;
    mMultisamplingMode = multisamplingMode;
    mInitState         = InitState::MayNeedInit;
}

// Renderbuffer implementation.
Renderbuffer::Renderbuffer(rx::GLImplFactory *implFactory, RenderbufferID id)
    : RefCountObject(implFactory->generateSerial(), id),
      mState(),
      mImplementation(implFactory->createRenderbuffer(mState)),
      mLabel(),
      mImplObserverBinding(this, kRenderbufferImplSubjectIndex)
{
    mImplObserverBinding.bind(mImplementation.get());
}

void Renderbuffer::onDestroy(const Context *context)
{
    (void)(orphanImages(context));

    if (mImplementation)
    {
        mImplementation->onDestroy(context);
    }
}

Renderbuffer::~Renderbuffer() {}

void Renderbuffer::setLabel(const Context *context, const std::string &label)
{
    mLabel = label;
}

const std::string &Renderbuffer::getLabel() const
{
    return mLabel;
}

angle::Result Renderbuffer::setStorage(const Context *context,
                                       GLenum internalformat,
                                       GLsizei width,
                                       GLsizei height)
{
    ANGLE_TRY(orphanImages(context));
    ANGLE_TRY(mImplementation->setStorage(context, internalformat, width, height));

    mState.update(width, height, Format(internalformat), 0, MultisamplingMode::Regular,
                  InitState::MayNeedInit);
    onStateChange(angle::SubjectMessage::SubjectChanged);

    return angle::Result::Continue;
}

angle::Result Renderbuffer::setStorageMultisample(const Context *context,
                                                  GLsizei samples,
                                                  GLenum internalformat,
                                                  GLsizei width,
                                                  GLsizei height,
                                                  MultisamplingMode mode)
{
    ANGLE_TRY(orphanImages(context));

    // Potentially adjust "samples" to a supported value
    const TextureCaps &formatCaps = context->getTextureCaps().get(internalformat);
    samples                       = formatCaps.getNearestSamples(samples);

    ANGLE_TRY(mImplementation->setStorageMultisample(context, samples, internalformat, width,
                                                     height, mode));

    mState.update(width, height, Format(internalformat), samples, mode, InitState::MayNeedInit);
    onStateChange(angle::SubjectMessage::SubjectChanged);

    return angle::Result::Continue;
}

angle::Result Renderbuffer::setStorageEGLImageTarget(const Context *context, egl::Image *image)
{
    ANGLE_TRY(orphanImages(context));
    ANGLE_TRY(mImplementation->setStorageEGLImageTarget(context, image));

    setTargetImage(context, image);

    mState.update(static_cast<GLsizei>(image->getWidth()), static_cast<GLsizei>(image->getHeight()),
                  Format(image->getFormat()), 0, MultisamplingMode::Regular,
                  image->sourceInitState());
    onStateChange(angle::SubjectMessage::SubjectChanged);

    return angle::Result::Continue;
}

rx::RenderbufferImpl *Renderbuffer::getImplementation() const
{
    ASSERT(mImplementation);
    return mImplementation.get();
}

GLsizei Renderbuffer::getWidth() const
{
    return mState.mWidth;
}

GLsizei Renderbuffer::getHeight() const
{
    return mState.mHeight;
}

const Format &Renderbuffer::getFormat() const
{
    return mState.mFormat;
}

GLsizei Renderbuffer::getSamples() const
{
    return mState.mMultisamplingMode == MultisamplingMode::Regular ? mState.mSamples : 0;
}

MultisamplingMode Renderbuffer::getMultisamplingMode() const
{
    return mState.mMultisamplingMode;
}

GLuint Renderbuffer::getRedSize() const
{
    return mState.mFormat.info->redBits;
}

GLuint Renderbuffer::getGreenSize() const
{
    return mState.mFormat.info->greenBits;
}

GLuint Renderbuffer::getBlueSize() const
{
    return mState.mFormat.info->blueBits;
}

GLuint Renderbuffer::getAlphaSize() const
{
    return mState.mFormat.info->alphaBits;
}

GLuint Renderbuffer::getDepthSize() const
{
    return mState.mFormat.info->depthBits;
}

GLuint Renderbuffer::getStencilSize() const
{
    return mState.mFormat.info->stencilBits;
}

const RenderbufferState &Renderbuffer::getState() const
{
    return mState;
}

GLint Renderbuffer::getMemorySize() const
{
    GLint implSize = mImplementation->getMemorySize();
    if (implSize > 0)
    {
        return implSize;
    }

    // Assume allocated size is around width * height * samples * pixelBytes
    angle::CheckedNumeric<GLint> size = 1;
    size *= mState.mFormat.info->pixelBytes;
    size *= mState.mWidth;
    size *= mState.mHeight;
    size *= std::max(mState.mSamples, 1);
    return size.ValueOrDefault(std::numeric_limits<GLint>::max());
}

void Renderbuffer::onAttach(const Context *context, rx::Serial framebufferSerial)
{
    addRef();
}

void Renderbuffer::onDetach(const Context *context, rx::Serial framebufferSerial)
{
    release(context);
}

GLuint Renderbuffer::getId() const
{
    return id().value;
}

Extents Renderbuffer::getAttachmentSize(const gl::ImageIndex & /*imageIndex*/) const
{
    return Extents(mState.mWidth, mState.mHeight, 1);
}

Format Renderbuffer::getAttachmentFormat(GLenum /*binding*/,
                                         const ImageIndex & /*imageIndex*/) const
{
    return getFormat();
}
GLsizei Renderbuffer::getAttachmentSamples(const ImageIndex & /*imageIndex*/) const
{
    return getSamples();
}

bool Renderbuffer::isRenderable(const Context *context,
                                GLenum binding,
                                const ImageIndex &imageIndex) const
{
    if (isEGLImageTarget())
    {
        return ImageSibling::isRenderable(context, binding, imageIndex);
    }
    return getFormat().info->renderbufferSupport(context->getClientVersion(),
                                                 context->getExtensions());
}

InitState Renderbuffer::initState(const gl::ImageIndex & /*imageIndex*/) const
{
    if (isEGLImageTarget())
    {
        return sourceEGLImageInitState();
    }

    return mState.mInitState;
}

void Renderbuffer::setInitState(const gl::ImageIndex & /*imageIndex*/, InitState initState)
{
    if (isEGLImageTarget())
    {
        setSourceEGLImageInitState(initState);
    }
    else
    {
        mState.mInitState = initState;
    }
}

rx::FramebufferAttachmentObjectImpl *Renderbuffer::getAttachmentImpl() const
{
    return mImplementation.get();
}

GLenum Renderbuffer::getImplementationColorReadFormat(const Context *context) const
{
    return mImplementation->getColorReadFormat(context);
}

GLenum Renderbuffer::getImplementationColorReadType(const Context *context) const
{
    return mImplementation->getColorReadType(context);
}

angle::Result Renderbuffer::getRenderbufferImage(const Context *context,
                                                 const PixelPackState &packState,
                                                 Buffer *packBuffer,
                                                 GLenum format,
                                                 GLenum type,
                                                 void *pixels) const
{
    return mImplementation->getRenderbufferImage(context, packState, packBuffer, format, type,
                                                 pixels);
}

void Renderbuffer::onSubjectStateChange(angle::SubjectIndex index, angle::SubjectMessage message)
{
    ASSERT(message == angle::SubjectMessage::SubjectChanged);
    onStateChange(angle::SubjectMessage::ContentsChanged);
}
}  // namespace gl