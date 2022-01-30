/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

enum class GameMode {
	Showing, 
	Recieveing, 
	GameOver, 
	Starting
};
class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupTitle(); // simon title 
	void setUpMenuContents(); // menu option 
	void setUpRectangles();// sets up the 4 rectangles
	void resetButtons();  // once button is pressed will rest them so a press on them can be detected again
	void processGameEvents(sf::Event& t_event); 

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_raceSportFont; // font 
	
	// text
	sf::Text m_simonTitle; // text used for message on screen
	sf::Text m_easyText; // text for easy mode
	sf::Text m_normalText; // text for normal mode
	sf::Text m_hardText; // Text for hard mode
	sf::Text m_exitText; // exit text
	
	// different rectangles
	sf::RectangleShape m_redRectangle; 
	sf::RectangleShape m_yellowRectangle;
	sf::RectangleShape m_blueRectangle; 
	sf::RectangleShape m_greenRectangle; 
	
	GameMode m_currentGameMode; // games curren stage 
	bool m_exitGame; // control exiting game

	bool m_redButtonPress = false; 
	bool m_yellowButtonPress = false; 
	bool m_blueButtonPress = false; 
	bool m_greenButtonPress = false; 

};

#endif // !GAME_HPP

