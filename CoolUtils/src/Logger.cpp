#include "Logger.h"
#include <iostream>


namespace co {
	
	void LoggerManager::SetConfigurations(const LoggerConfigs& loggerConfigs){
		m_loggerConfigs = loggerConfigs;
	}

	void LoggerManager::SetEmphasis(const fmt::text_style ts)
	{
		m_loggerConfigs.emphasis = ts.get_emphasis();
	}

	fmt::text_style LoggerManager::getTextStyle(const LogLevel& level) const
	{
		fmt::text_style textStyle;
		textStyle |= m_loggerConfigs.emphasis;

		switch (level) {
		case LogLevel::Debug:
			textStyle |= fmt::fg(m_loggerConfigs.debug_color);
			break;
		case LogLevel::Info:
			textStyle |= fmt::fg(m_loggerConfigs.info_color);
			break;
		case LogLevel::Warn:
			textStyle |= fmt::fg(m_loggerConfigs.warn_color);
			break;
		case LogLevel::Error:
			textStyle |= fmt::fg(m_loggerConfigs.error_color);
			break;
		case LogLevel::Fatal:
			textStyle |= fmt::fg(fmt::color::black) | fmt::bg(m_loggerConfigs.fatal_color);
			break;
		}
		return textStyle;
	}

}