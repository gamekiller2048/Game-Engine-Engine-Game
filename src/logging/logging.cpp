#include <logging/logging.hpp>

namespace mll
{
    Logging::Logging() :
        startTime(std::chrono::high_resolution_clock::now()) {}

    void Logging::log(const Logable& logable)
    {
        auto now = std::chrono::high_resolution_clock::now();
        int elapsed = (now - startTime).count() / 10000;

        if(logable.severity < minSeverity)
            return;

        std::string debug;
        if(logable.debugInfo.funcName.size())
            debug += "(calling '" + logable.debugInfo.funcName + "')";
        if(logable.debugInfo.fileName.size())
            debug += "\n    In " + logable.debugInfo.fileName + "; Line: " + std::to_string(logable.debugInfo.line);

        switch(logable.severity)
        {
        case Severity::CRITICAL:
            std::cout << "\x1B[91m[" << elapsed << "][CRT] " << logable.getString() << debug << "\033[0m\n";
            break;
        case Severity::MAJOR:
            std::cout << "\x1B[91m[" << elapsed << "][MAJ] " << logable.getString() << debug << "\033[0m\n";
            break;
        case Severity::WARNING:
            std::cout << "\x1B[93m[" << elapsed << "][WARN] " << logable.getString() << debug << "\033[0m\n";
            break;
        case Severity::INFO:
            std::cout << "\x1B[92m[" << elapsed << "][INFO] " << logable.getString() << debug << "\033[0m\n";
            break;
        }
    }
}