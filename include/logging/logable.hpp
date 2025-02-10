#pragma once

namespace mll
{
	enum class Severity
	{
		INFO,
		WARNING,
		MAJOR,
		CRITICAL
	};

	struct DebugInfo
	{
		std::string funcName;
		std::string fileName;
		uint line;
	};

	class Logable
	{
	public:
		Severity severity;
		DebugInfo debugInfo;

		Logable(Severity severity, const std::string& name, const std::string message="", const DebugInfo& debugInfo={});
		std::string getString() const;

	protected:
		std::string name;
		std::string message;
	};
}
