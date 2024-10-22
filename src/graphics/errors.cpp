#include <graphics/errors.hpp>
#include <unordered_map>
#include <Windows.h>
#include <glad/gl.h>

namespace mgl
{
	const static std::unordered_map<int, std::string> GLErrorMap = {
		{GL_INVALID_ENUM, "Invalid Enum"},
		{GL_INVALID_VALUE, "Invalid Value"},
		{GL_INVALID_OPERATION, "Invalid Operation"},
		{GL_STACK_OVERFLOW, "Stack Overflow"},
		{GL_STACK_UNDERFLOW, "Stack Underflow"},
		{GL_OUT_OF_MEMORY, "Out Of Memory"},
		{GL_NO_ERROR, "No Error"}
	};


	GLError::GLError(uint error) :
		mll::Error("GL", GLErrorMap.find(error)->second) {}

	GLError::GLError(const std::string& msg) :
		mll::Error("GL", msg) {}

	GLSLError::GLSLError(const std::string& stage, const std::string& msg) :
		GLError(stage + " failed: " + msg) {}
}