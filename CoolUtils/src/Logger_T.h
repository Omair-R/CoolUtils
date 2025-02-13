#pragma once

namespace co {

	template <typename ...Args>
	void LoggerManager::log(LogLevel level, std::string_view msg, Args&&...args) const {
		if (!ShouldLog(level)) return;

		try {
			std::string fmsg = formatLog(level, msg, args...);
			fmt::text_style textStyle = getTextStyle(level);

			fmt::print(textStyle, "{}", fmsg);
		}
		catch (...) {
			warn("Could not print msg, an argument is not compatible...");
		}
	}

	template <typename ...Args>
	void LoggerManager::log(std::ostream& ostm, LogLevel level, std::string_view msg, Args&&...args) const {
		if (!ShouldLog(level)) return;

		try {
			std::string fmsg = formatLog(level, msg, args...);

			fmt::print(ostm, "{}", fmsg);
		}
		catch (...) {
			warn("Could not print msg, an argument is not compatible...");
		}
	}

	template <typename ...Args>
	void LoggerManager::printLn(std::string_view msg, Args&&...args) const {
		std::string outMsg = dynamicFormat(msg, args...);
		fmt::print("{}\n", outMsg);
	}

	template <typename ...Args>
	void LoggerManager::printLn(std::ostream& ostm, std::string_view msg, Args&&...args) const {
		std::string outMsg = dynamicFormat(msg, args...);
		fmt::print(ostm, "{}\n", outMsg);
	}

	template <typename ...Args>
	std::string LoggerManager::formatLog(LogLevel level, std::string_view msg, Args&&...args) const {
		std::string fmsg = dynamicFormat(msg, args...);
		std::string outMsg = dynamicFormat("[{}]: {}\n", levelStrings[level - 1], fmsg);
		return outMsg;
	}

	template <typename ...Args>
	std::string LoggerManager::dynamicFormat(std::string_view msg, Args&&...args) const {
		std::string outMsg;
		fmt::vformat_to(std::back_inserter(outMsg), msg, fmt::make_format_args(args...));
		return outMsg;
	}
}