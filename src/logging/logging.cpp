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

        switch(logable.severity)
        {
        case Severity::CRITICAL:
            std::cout << "\x1B[91m[" << elapsed << "][CRITICAL] " << logable.getString() << "\033[0m\n";
            break;
        case Severity::MAJOR:
            std::cout << "\x1B[91m[" << elapsed << "][MAJOR] " << logable.getString() << "\033[0m\n";
            break;
        case Severity::WARNING:
            std::cout << "\x1B[93m[" << elapsed << "][WARNING] " << logable.getString() << "\033[0m\n";
            break;
        case Severity::INFO:
            std::cout << "\x1B[92m[" << elapsed << "][INFO] " << logable.getString() << "\033[0m\n";
            break;
        }
    }
}