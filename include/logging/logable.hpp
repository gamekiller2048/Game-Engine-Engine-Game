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

	class Logable
	{
	public:
		Severity severity;

		Logable(Severity severity, const std::string& name, const std::string message="");
		std::string getString() const;

	protected:
		std::string name;
		std::string message;
	};
}
