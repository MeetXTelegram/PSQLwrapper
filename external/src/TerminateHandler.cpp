#include <Definitions.hpp>

#include <sys/wait.h>

#include <iostream>
#include <vector>

void exceptionsUtils::TerminateHandler() {
    if (std::uncaught_exceptions() > 0) {
        spdlog::get("TerminateHandler")->log(spdlog::level::warn, "Uncaught exceptions: {}(It looks like this handler was calle as a result of throwing an exception), what should i do?\n\n1 -- Normal shutdown of MeetX\n2 -- Try to restart the process");
    } else {
        spdlog::get("TerminateHandler")->log(spdlog::level::warn, "No uncaught exceptions were found(It looks like std::terminate was called explicitly), what should i do?\n\n1 -- Normal shutdown of MeetX\n2 -- Try to restart the process");
    }

    while (true) {
        int action; std::cin >> action;

        switch (action) {
            case 1: {
                spdlog::get("TerminateHandler")->log(spdlog::level::info, "Selected action 1(shutdown)");
                std::exit(-1);
            }

            case 2: {
                spdlog::get("TerminateHandler")->log(spdlog::level::info, "Selected action 2(restart)\nOk, now enter the arguments(one argument at a time)");
                std::vector<std::string> args;
                char** argsRaw;
                args.emplace_back("./MeetX");
                while (true) {
                    std::string buffer; std::getline(std::cin, buffer);
                    if (buffer.empty()) {
                        spdlog::get("TerminateHandler")->log(spdlog::level::info, "Fine, {} command line arguments will be passed", args.size() - 1 /* Remove the required argument */);
                        break;
                    } else
                        args.emplace_back(buffer);
                }

                std::uint16_t argIndex = 0;
                for (auto& element : args) {
                    argsRaw[argIndex] = (char*)element.c_str();
                    ++argIndex;
                }

                auto pid = fork();
                if (pid == 0) {
                    execvp(argsRaw[0], argsRaw);
                    spdlog::get("TerminateHandler")->log(spdlog::level::critical, "Failed to create a new process(execvp() failed)");
                    std::exit(-2);
                } else if (pid > 0) {
                    waitpid(pid, nullptr, 0);
                } else {
                    spdlog::get("TerminateHandler")->log(spdlog::level::critical, "Failed to create a new process(fork() failed)");
                    std::exit(-3);
                }

                std::abort();
            }

            default: {
                spdlog::get("TerminateHandler")->log(spdlog::level::info, "Invalid action provided, please try again");
                continue;
            }
        }
    }
}
