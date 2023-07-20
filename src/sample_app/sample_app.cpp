#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

#include <CLI/CLI.hpp>
#include <memory>
#include <thread>

#include "modern_cpp_template/fibonacci.h"
#include "modern_cpp_template/macros.h"
#include "modern_cpp_template/system_constants.h"

namespace modern_cpp_template::modern_cpp_template_sample_app {

void run_simple_thread(int32_t fibonacci_number) {
  spdlog::debug("Calling fibonacci with number {}", fibonacci_number);
  auto result = modern_cpp_template::algorithms::fibonacci(fibonacci_number);
  spdlog::info("F_{} = {}", fibonacci_number, result);
}

void run_sample_app(spdlog::level::level_enum console_log_level,
                    spdlog::level::level_enum file_log_level,
                    int32_t fibonacci_number) {
  // Create a sink to console with default pattern
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_level(console_log_level);

  // Create a sing to error logs
  auto error_console_sink =
      std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
  error_console_sink->set_level(spdlog::level::critical);

  // Create a sink to file with custom pattern
  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
      "logs/modern_cpp_template_sample_app.log", true);
  file_sink->set_level(file_log_level);
  file_sink->set_pattern("%Y%m%d %R:%S.%F %z [%P] [%t] %n::%l - %v");

  // Set the root custom logger details
  std::initializer_list<std::shared_ptr<spdlog::sinks::sink>> sinks = {
      console_sink, file_sink, error_console_sink};
  auto logger =
      std::make_shared<spdlog::logger>("modern_cpp_template_sample_app", sinks);
  spdlog::set_default_logger(logger);
  spdlog::set_level(spdlog::level::debug);

  spdlog::info("Application {} Started",
               modern_cpp_template::options::kProjectName);

  // Start a thread - it will automatically join on destruction
  std::jthread t1(run_simple_thread, fibonacci_number);
}

}  // namespace modern_cpp_template::modern_cpp_template_sample_app

int main(int argc, char** argv) {
  CLI::App app{"modern_cpp_template sample application"};

  app.set_version_flag("--version",
                       modern_cpp_template::options::kProjectVersion.data());

  spdlog::level::level_enum console_log_level{spdlog::level::level_enum::info};
  app.add_option("--console_log_level", console_log_level,
                 "Max log level for the console");

  spdlog::level::level_enum file_log_level{spdlog::level::level_enum::debug};
  app.add_option("--file_log_level", file_log_level,
                 "Max log level for the file");

  int32_t fibonacci_number{0};
  app.add_option("--fibonacci_number", fibonacci_number,
                 "Enter the fibonacci number to compute")
      ->required();

  CLI11_PARSE(app, argc, argv);

  modern_cpp_template::modern_cpp_template_sample_app::run_sample_app(
      console_log_level, file_log_level, fibonacci_number);

  return 0;
}
