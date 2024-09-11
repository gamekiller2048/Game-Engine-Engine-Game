#include <graphics/errors.hpp>
#include <unordered_map>
#include <Windows.h>
#include <glad/gl.h>

namespace mgl
{
	Win32Error::Win32Error(uint error) :
		mll::Error("Win32")
	{
		// this condition should not happen
		if(!error)
			severity = mll::Severity::WARNING;

		LPSTR msgBuf = nullptr;

		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&msgBuf, 0, NULL);

		message = std::string(msgBuf, size);
		LocalFree(msgBuf);
	}

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