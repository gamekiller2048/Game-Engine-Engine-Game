#include <logging/warning.hpp>

namespace mll
{
	Warning::Warning(const std::string& name, const std::string message) :
		Logable(Severity::WARNING, name, message) {}
}