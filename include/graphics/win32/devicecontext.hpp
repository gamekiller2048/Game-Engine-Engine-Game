#pragma once

namespace mgl
{
	namespace win32
	{
		class DeviceContextImpl;
		class DeviceContext
		{
		public:
			DeviceContext();

			DeviceContextImpl* getImpl() const;

		protected:
			Owned<DeviceContextImpl> impl;
		};
	}
}