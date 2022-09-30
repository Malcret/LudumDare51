#include <PCH.hpp>
#include <Core/Logger.hpp>

Logger::Logger() {
	spdlog::set_pattern("%^[%T] (%n) %l: %v%$");

	std::cout << "Create logger...\n";

	m_logger = spdlog::stdout_color_mt("Game");
	m_logger->set_level(spdlog::level::trace);

	std::cout << "Logger created successfully.\n";
}

Logger &Logger::getInstance() {
	static Logger instance;
	return instance;
}

std::shared_ptr<spdlog::logger> &Logger::iGetLogger() {
	return m_logger;
}
