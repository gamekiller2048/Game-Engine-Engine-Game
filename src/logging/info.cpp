#include <logging/info.hpp>

namespace mll
{
	Info::Info(const std::string& name, const std::string message) :
		Logable(Severity::INFO, name, message) {}
}