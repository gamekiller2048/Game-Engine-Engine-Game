#include <logging/logable.hpp>

namespace mll
{
	Logable::Logable(Severity severity, const std::string& name, const std::string message, const DebugInfo& debugInfo) :
		severity(severity), name(name), message(message), debugInfo(debugInfo) {}

	std::string Logable::getString() const
	{
		if(!name.empty())
			return '(' + name + ')' + message;
		return message;
	}
}