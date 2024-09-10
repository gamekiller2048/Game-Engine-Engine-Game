#include <graphics/errors.hpp>
#include <Windows.h>

namespace mgl
{
	Win32Error::Win32Error(uint error) :
		mll::Error("Win32")
	{
		if(!error)
			severity = mll::Severity::WARNING;
		LPSTR msgBuf = nullptr;

		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&msgBuf, 0, NULL);

		message = std::string(msgBuf, size);
		LocalFree(msgBuf);
	}
}