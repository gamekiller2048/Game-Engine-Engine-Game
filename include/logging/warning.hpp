#pragma once
#include <logging/logable.hpp>

namespace mll
{
	class Warning : public Logable
	{
	public:
		Warning(const std::string& name, const std::string message="");
	};
}