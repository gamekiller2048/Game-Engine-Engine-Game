#include <graphics/opengl/context.hpp>
#include "errorcheck.hpp"

namespace mgl
{
    namespace gl
    {
        ContextImpl* Context::getImpl() const
        {
            return impl.get();
        }

        GLuint Context::getUnusedTexUnit() const
        {
            return unusedTexUnits[unusedTexUnits.size() - 1];
        }

        void Context::consumeTexUnit(GLuint unit)
        {
            unusedTexUnits.erase(std::find(unusedTexUnits.begin(), unusedTexUnits.end(), unit));
        }

        void Context::freeTexUnit(GLuint unit)
        {
            unusedTexUnits.push_back(unit);
        }

        GLint Context::getParameterInt(ContextParam param)
        {
            GLint result;
            GL_CALL(glGetIntegerv, (GLenum)param, &result);
            return result;
        }

        GLfloat Context::getParameterFloat(ContextParam param)
        {
            GLfloat result;
            GL_CALL(glGetFloatv, (GLenum)param, &result);
            return result;
        }

        GLboolean Context::getParameterBool(ContextParam param)
        {
            GLboolean result;
            GL_CALL(glGetBooleanv, (GLenum)param, &result);
            return result;
        }

        GLdouble Context::getParameterDouble(ContextParam param)
        {
            GLdouble result;
            GL_CALL(glGetDoublev, (GLenum)param, &result);
            return result;
        }

        GLint64 Context::getParameterInt64(ContextParam param)
        {
            GLint64 result;
            GL_CALL(glGetInteger64v, (GLenum)param, &result);
            return result;
        }

        void Context::viewport(GLuint x, GLuint y, GLuint w, GLuint h) const
        {
            GL_CALL(glViewport, x, y, w, h);
        }

        void Context::setDepthTest(bool on) const
        {
            if(on)
                GL_CALL(glEnable, GL_DEPTH_TEST);
            else
                GL_CALL(glDisable, GL_DEPTH_TEST);
        }

        void Context::setTransparency(bool on) const
        {
            if(on)
                GL_CALL(glEnable, GL_BLEND);
            else
                GL_CALL(glDisable, GL_BLEND);
        }

        void Context::setCulling(bool on) const
        {
            if(on)
                GL_CALL(glEnable, GL_BLEND);
            else
                GL_CALL(glDisable, GL_BLEND);
        }

        void Context::setDrawMode(DrawMode mode) const
        {
            GL_CALL(glPolygonMode, GL_FRONT_AND_BACK, (GLenum)mode);
        }

        void Context::setDepthFunc(DepthFunc func) const
        {
            GL_CALL(glDepthFunc, (GLenum)func);
        }

        void Context::setTransparencyFunc(TransparentFunc srcFactor, TransparentFunc dstFactor) const
        {
            GL_CALL(glBlendFunc, (GLenum)srcFactor, (GLenum)dstFactor);
        }

        void Context::setCullingFunc(FaceSide face) const
        {
            GL_CALL(glCullFace, (GLenum)face);
        }

        void Context::setFillColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const
        {
            GL_CALL(glClearColor, r, g, b, a);
        }

        void Context::clearColor() const
        {
            GL_CALL(glClear, GL_COLOR_BUFFER_BIT);
        }

        void Context::clearDepth() const
        {
            GL_CALL(glClear, GL_DEPTH_BUFFER_BIT);
        }
    }
}