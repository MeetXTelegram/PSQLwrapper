#pragma once

#include <csetjmp>
#include <csignal>
#include <string>
#include <memory>

#include <pqxx/pqxx>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define createFileSink(file) std::make_shared<spdlog::sinks::basic_file_sink_mt>(file,true);
#define createStdoutSink std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

namespace db {
    inline std::shared_ptr<pqxx::connection> database;
}

namespace loggingUtils {
    void createLogger(const std::string& loggerName, std::shared_ptr<spdlog::sinks::sink> consoleSink, std::shared_ptr<spdlog::sinks::sink> fileSink, spdlog::level::level_enum level);
}

namespace signalsUtils {
    inline sigjmp_buf programBuf;
    void SIGUSR1Handler(int signal);
}

namespace exceptionsUtils {
    void TerminateHandler();
}
