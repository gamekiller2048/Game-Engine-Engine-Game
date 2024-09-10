#pragma once
#include <logging/logable.hpp>

namespace mll
{
	class Info : public Logable
	{
	public:
		Info(const std::string& name, const std::string message="");
	};
}