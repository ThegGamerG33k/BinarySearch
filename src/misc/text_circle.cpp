#include <text_circle.h>
#include <SFML/Graphics.hpp>


sf::TextCircle::TextCircle()
{
	// Doesn't initialize anything.
}

sf::TextCircle::TextCircle(float x, float y, const Font& font_ref, std::string text)
{
	// Set properties except position of the text object
	mText.setFont(font_ref);
	mText.setString(text);
	mText.setCharacterSize(24);
	mText.setFillColor(sf::Color::Black);

	// Center the text
	// reference: https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
	mTextRect = mText.getLocalBounds();
	mText.setOrigin(mTextRect.left + mTextRect.width / 2.0f,
		mTextRect.top + mTextRect.height / 2.0f);
	mText.setPosition(sf::Vector2f(x, y));

	// Set the position / radius of the circle
	float radius = (mTextRect.width > mTextRect.height ? mTextRect.width : mTextRect.height) / 2.0f;
	mCircle.setPosition(x - radius, y - radius);
	mCircle.setFillColor(sf::Color(rand() % 128 + 127, rand() % 128 + 127, rand() % 128 + 127, 255));
	mCircle.setRadius(radius);
}



void sf::TextCircle::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(mCircle);
	target.draw(mText);
}

void sf::TextCircle::setCircleColor(const sf::Color& c)
{
	mCircle.setFillColor(c);

}

sf::Vector2f sf::TextCircle::get_position() const
{
	return mCircle.getPosition() + sf::Vector2f(mCircle.getRadius(), mCircle.getRadius());
}


std::string sf::TextCircle::get_string() const
{
	return mText.getString();
}

void sf::TextCircle::set_position(const sf::Vector2f& p)
{
	float radius = mCircle.getRadius();
	mCircle.setPosition(p.x - radius, p.y - radius);
	mText.setPosition(p.x, p.y);
}

bool sf::TextCircle::point_inside(sf::Vector2f v) const
{
	sf::Vector2f p = get_position();
	float dist = powf(powf(v.x - p.x, 2.0f) + powf(v.y - p.y, 2.0f), 0.5f);
	return dist <= mCircle.getRadius();
}