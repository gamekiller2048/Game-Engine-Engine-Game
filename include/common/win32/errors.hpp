#pragma once

namespace mcl
{
	class Win32Error : public mll::Error
	{
	public:
		Win32Error(uint error);
	};
}