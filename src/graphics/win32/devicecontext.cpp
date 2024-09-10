#include <graphics/win32/devicecontext.hpp>
#include "devicecontextimpl.hpp"

namespace mgl
{
	namespace win32
	{
		DeviceContext::DeviceContext() :
			impl(CreateOwned<DeviceContextImpl>()) {}

		DeviceContextImpl* DeviceContext::getImpl() const
		{
			return impl.get();
		}
	}
}