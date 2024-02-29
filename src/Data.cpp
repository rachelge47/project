#include "Data.h"
#include "GameControl.h"

bool Data::m_toAddTime = false;

void Data::printData(sf::RenderWindow& window)
{
	Manage::getInstance().loadBar();

	m_info.setTexture(Manage::getInstance().infoTexture());

	m_info.setSize(INFO_SIZE);
	m_info.setPosition(INFO_POS);

	window.draw(m_info);
}

void Data::updateTime(float time)
{
	m_timeAsSec = time;
	m_timeAsSec -= m_timer.getElapsedTime().asSeconds();

	if (m_toAddTime)
	{
		setTime();
	}

	int leftTimeMin = ((int)m_timeAsSec) / 60;
	int leftTimeSec = ((int)m_timeAsSec) % 60;

	if (m_timeAsSec < 0)
	{
		m_isTimeEnd = true;
	}

	std::string minutesStr = leftTimeMin < 10 ? "0" + std::to_string(leftTimeMin) : std::to_string(leftTimeMin);
	std::string secondsStr = leftTimeSec < 10 ? "0" + std::to_string(leftTimeSec) : std::to_string(leftTimeSec);

	m_timeText.setString("Time left: " + minutesStr + ":" + secondsStr);		
}

void Data::draw(sf::RenderWindow& window)
{
	m_timeText.setFont(*(Manage::getInstance().getFont()));
	m_timeText.setCharacterSize(TEXT_SIZE);
	m_timeText.setPosition(TIME_TEXT_POS);
	m_timeText.setFillColor(sf::Color::Black);

	window.draw(m_timeText);
}


void Data::setTime()
{
	m_timeAsSec += 5.f;
}