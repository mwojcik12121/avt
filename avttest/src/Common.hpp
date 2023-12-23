#pragma once

#include <chrono>

namespace avt
{
    using clock = std::chrono::system_clock;
    using stopwatch = std::chrono::steady_clock;

    using StageMap = std::tuple<int, std::string>;

    enum class AVType
    {
        None,
        ClamAV,
        Comodo,
        DrWeb,
        Sophos
    };
}


