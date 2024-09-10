#pragma once
#include <logging/logable.hpp>
#include <logging/error.hpp>
#include <logging/warning.hpp>
#include <logging/info.hpp>
#include <chrono>

#define MLL_LOG(x) mll::LOG.log(x);
#define MLL_DEBUG(x) mll::LOG.log(x);

namespace mll
{
    class Logging
    {
    public:
        Severity minSeverity = Severity::INFO;

        Logging();
        void log(const Logable& logable);

    protected:
        std::chrono::high_resolution_clock::time_point startTime;
    };

    inline Logging LOG;

}