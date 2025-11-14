#pragma once

#ifdef _WIN32
    #include <Logging/Sinks/WinColorSink.h>
#else
    #include <Logging/Sinks/AnsiColorSink.h>
#endif

#include <Logging/Factory.h>

namespace logging {
#ifdef _WIN32
using StdOutColorSinkST = WinStdOutColorSinkST;
using StdOutColorSinkMT = WinStdOutColorSinkMT;
using StdErrColorSinkST = WinStdErrColorSinkST;
using StdOutColorSinkMT = WinStdOutColorSinkMT;
#else
using StdOutColorSinkST = AnsiStdOutColorSinkST;
using StdOutColorSinkMT = AnsiStdOutColorSinkMT;
using StdErrColorSinkST = AnsiStdErrColorSinkST;
using StdOutColorSinkMT = AnsiStdOutColorSinkMT;
#endif

}  // namespace logging
