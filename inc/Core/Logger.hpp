#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Logger {
private:
	Logger();
	Logger(const Logger &) = delete;
	Logger &operator=(const Logger &) = delete;
	static Logger &getInstance();

public:
	static inline void init() { getInstance(); }
	static inline std::shared_ptr<spdlog::logger> &getLogger() { return getInstance().iGetLogger(); }

private:
	std::shared_ptr<spdlog::logger> m_logger;

	std::shared_ptr<spdlog::logger> &iGetLogger();
};

#if defined(DEBUG) || !defined(NDEBUG)
	#define LOG_TRACE(...)    Logger::getLogger()->trace(__VA_ARGS__)
	#define LOG_INFO(...)     Logger::getLogger()->info(__VA_ARGS__)
	#define LOG_WARNING(...)  Logger::getLogger()->warn(__VA_ARGS__)
#else
	#define LOG_TRACE(...)
	#define LOG_INFO(...)
	#define LOG_WARNING(...)
#endif
#define LOG_ERROR(...)    Logger::getLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Logger::getLogger()->critical(__VA_ARGS__)