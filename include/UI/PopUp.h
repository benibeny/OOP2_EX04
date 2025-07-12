#pragma once

#include <vector>
#include <memory>

#include "UI/Button.h"
#include "Managers/ResourceManager.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class PopUp 
{
public:
	PopUp(std::string titleName,std::string spriteName);

	void addButtons(std::unique_ptr<Button> button);
	void setUp();
	void render(sf::RenderWindow& window);
	void handleMouseClick(const sf::Vector2f& mousePos);
	void handleMouseHover(const sf::Vector2f& mousePos);

	void setVisible(bool visible);
	bool isVisible() const;

private:

	std::vector<std::unique_ptr<Button>> m_buttons;
	bool m_visible;

	sf::Sprite m_background;
	sf::Text m_title;

};