#include<vector>
#include<iostream>
#include <algorithm>
#include <random>
#include <set>
#include <thread>
#include <chrono>


#include <SFML/Graphics.hpp>
const uint16_t width = 1600;
const uint16_t height = 900;
const uint16_t elementsToSort = 100;
const float barWidth = (float)width / elementsToSort;

sf::Color getRandomColor();
uint8_t getRandomUINT_8();
void updateHeights(std::map<unsigned int, sf::RectangleShape>& mapUint8Bar);

int main()
{
	//setting up window
	sf::RenderWindow window(sf::VideoMode(width, height), "Bogosort visualization");
	window.setFramerateLimit(10);
	// numeber and bars connected to the numbers
	std::map<unsigned int, sf::RectangleShape> mapUint8Bar;

	for (unsigned int i = 0; i < elementsToSort; ++i)
	{
		mapUint8Bar[i] = sf::RectangleShape({ elementsToSort, elementsToSort });
		mapUint8Bar[i].setPosition(0.f, 0.f);
		mapUint8Bar[i].setFillColor(getRandomColor());
	}


	//loop
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
		window.clear();
		for (unsigned int i = 0; i < elementsToSort; ++i)
		{
			window.draw(mapUint8Bar[i]);
		}
		window.display();
		std::vector<float> heights(elementsToSort);
		for (unsigned int i = 0; i < elementsToSort; ++i)
		{
			heights.push_back(mapUint8Bar[i].getSize().y);
		}
		if (std::is_sorted(begin(heights), end(heights)))
		{
			std::chrono::seconds timespan(3);
			std::this_thread::sleep_for(timespan);
		}
		updateHeights(mapUint8Bar);
	}

	return 0;
}

uint8_t getRandomUINT_8()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::uniform_int_distribution<std::mt19937::result_type> dist1000(0, 1000);
	return dist1000(g);
}

sf::Color getRandomColor()
{
	return sf::Color(getRandomUINT_8(), getRandomUINT_8(), getRandomUINT_8());
}

void updateHeights(std::map<unsigned int, sf::RectangleShape>& mapUint8Bar)
{

	for (unsigned int i = 0; i < elementsToSort; ++i)
	{
		uint8_t randNumber = getRandomUINT_8();
		mapUint8Bar[i].setSize({ float(barWidth), float(randNumber * 3) });
		mapUint8Bar[i].setPosition(i * barWidth, float((height - 3 * randNumber)));
		//mapUint8Bar[i].setFillColor(sf::Color::White);
		//mapUint8Bar[i].setFillColor(getRandomColor());
		//mapUint8Bar[i].setOutlineColor(sf::Color::Black);
		//mapUint8Bar[i].setOutlineThickness(0.5f);
	}
}
