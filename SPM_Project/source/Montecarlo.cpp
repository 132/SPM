#include <spdlog/spdlog.h>
#include <spdlog/sinks/null_sink.h>
#include <Montecarlo.h>

namespace Montecarlo {

static const std::string DefaultLoggerName = "Montecarlo-log";
static const std::string NullLoggerName = "Montecarlo-null-log";

std::shared_ptr<spdlog::logger> DefaultLoggerPtr;
std::shared_ptr<spdlog::logger> NullLoggerPtr;

void Init(){
    DefaultLoggerPtr = spdlog::stdout_color_mt(DefaultLoggerName);
    DefaultLoggerPtr->set_pattern("[%l] %v");

    auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();
    NullLoggerPtr = std::make_shared<spdlog::logger>(NullLoggerName, null_sink);
}

void Shutdown(){
    spdlog::drop_all();
}

std::shared_ptr<spdlog::logger> DefaultLogger(){
    return DefaultLoggerPtr;
}

std::shared_ptr<spdlog::logger> NullLogger(){
    return NullLoggerPtr;
}

}
