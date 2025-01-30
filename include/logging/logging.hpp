#pragma once
#include <chrono>
#include <logging/logable.hpp>
#include <logging/error.hpp>
#include <logging/warning.hpp>
#include <logging/info.hpp>

#define MLL_LOG(x) mll::LOG.log(x);
#define MLL_DEBUG(x) mll::LOG.log(x);
#define MLL_ASSERT(x, msg) if(!(x)) mll::LOG.log(mll::Error("ASSERT", msg));

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