#pragma once
#include "patterns/Singlton.h"
#include <memory>
#include <iostream>
#include <string>
#include <stdint.h>
#include <string_view>
#include "fmt/core.h"
#include "fmt/ostream.h"
#include "fmt/color.h"
#include <ostream>
#include <list>
#include <filesystem>

namespace co {

	enum LogLevel {
		Debug = 1,
		Info = 2,
		Warn = 3,
		Error = 4,
		Fatal = 5
	};

	struct LoggerConfigs {
		fmt::color debug_color = fmt::color::light_salmon;
		fmt::color info_color = fmt::color::deep_sky_blue;
		fmt::color warn_color = fmt::color::yellow;
		fmt::color error_color = fmt::color::red;
		fmt::color fatal_color = fmt::color::red;
		fmt::emphasis emphasis;
		LogLevel minLogLevel = LogLevel::Debug;
	};

	class LoggerManager: public SafeAbstractSinglton<LoggerManager> {

	public:
		template <typename ...Args>
		void log(LogLevel level, std::string_view msg, Args&&...args) const;

		template <typename ...Args>
		void log(std::ostream& ostm, LogLevel level, std::string_view msg, Args&&...args) const;

		template <typename ...Args>
		void printLn(std::string_view msg, Args&&...args) const;

		template <typename ...Args>
		void printLn(std::ostream& ostm, std::string_view msg, Args&&...args) const;

		inline void breakLine() const {
			fmt::print("=======================================================\n");
		}

		inline void breakLine(std::ostream& ostm) const {
			fmt::print(ostm, "=======================================================\n");
		}

		template <typename ...Args>
		void debug(std::string_view msg, Args&&...args) const {
			log(LogLevel::Debug, msg, args...);
		}

		template <typename ...Args>
		void debug(std::ostream& ostm, std::string_view msg, Args&&...args) const {
			log(ostm, LogLevel::Debug, msg, args...);
		}

		template <typename ...Args>
		void info(std::string_view msg, Args&&...args) const {
			log(LogLevel::Info, msg, args...);
		}

		template <typename ...Args>
		void info(std::ostream& ostm, std::string_view msg, Args&&...args) const {
			log(ostm, LogLevel::Info, msg, args...);
		}

		template <typename ...Args>
		void warn(std::string_view msg, Args&&...args) const {
			log(LogLevel::Warn, msg, args...);
		}

		template <typename ...Args>
		void warn(std::ostream& ostm, std::string_view msg, Args&&...args) const {
			log(ostm, LogLevel::Warn, msg, args...);
		}

		template <typename ...Args>
		void error(std::string_view msg, Args&&...args) const {
			log(LogLevel::Error, msg, args...);
		}

		template <typename ...Args>
		void error(std::ostream& ostm, std::string_view msg, Args&&...args) const {
			log(ostm, LogLevel::Error, msg, args...);
		}

		template <typename ...Args>
		void fatal(std::string_view msg, Args&&...args) const {
			log(LogLevel::Fatal, msg, args...);
		}

		template <typename ...Args>
		void fatal(std::ostream& ostm, std::string_view msg, Args&&...args) const {
			log(ostm, LogLevel::Fatal, msg, args...);
		}

		void SetConfigurations(const LoggerConfigs& loggerConfigs);
		void SetEmphasis(const fmt::text_style ts);
		fmt::text_style getTextStyle(const LogLevel& level) const;


	private:
		inline bool ShouldLog(LogLevel currentLevel) const {
			return currentLevel >= m_log_level;
		}

		template <typename ...Args>
		std::string formatLog(LogLevel level, std::string_view msg, Args&&...args) const;

		template <typename ...Args>
		std::string dynamicFormat(std::string_view msg, Args&&...args) const;

		LogLevel m_log_level{ Debug };
		LoggerConfigs m_loggerConfigs;
		const char* levelStrings[5]{ "Debug", "Info", "Warn", "Error", "Fatal" };
	};
}

#include "Logger_T.h"

#define log_debug(...) co::LoggerManager::GetInstance()->debug(__VA_ARGS__)
#define log_info(...) co::LoggerManager::GetInstance()->info(__VA_ARGS__)
#define log_warn(...) co::LoggerManager::GetInstance()->warn(__VA_ARGS__)
#define log_error(...) co::LoggerManager::GetInstance()->error(__VA_ARGS__)
#define log_fatal(...) co::LoggerManager::GetInstance()->fatal(__VA_ARGS__)
#define log_println(...) co::LoggerManager::GetInstance()->printLn(__VA_ARGS__)
#define log_break(...) co::LoggerManager::GetInstance()->breakLine(__VA_ARGS__)
