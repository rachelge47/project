#include "Data.h"
#include "GameControl.h"

bool Data::m_toAddTime = false;

void Data::printData(sf::RenderWindow& window)
{
	//GameControl::getLevel();

	Manage::load1();

	m_info.setTexture(Manage::infoTexture());

	m_info.setSize({ 350, 550 });
	m_info.setPosition({ 1330, 5 });

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

	
	//m_timer.restart();
}

void Data::draw(sf::RenderWindow& window)
{
	//updateTime(0);
	m_timeText.setFont(*(Manage::getFont()));
	m_timeText.setCharacterSize({ 80 });
	m_timeText.setPosition({ 1350, 600 });
	m_timeText.setFillColor(sf::Color::Black);

	window.draw(m_timeText);
}


sf::Text Data::make(const std::string& str, const sf::Font* font)
{
	sf::Text text(str, *font);
	text.setPosition({ 1550, 20 });
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(80);

	return text;
}

void Data::setTime()
{
	m_timeAsSec += 5.f;
}