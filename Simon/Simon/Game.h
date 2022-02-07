/// <summary>
/// 
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
#include <SFML/Audio.hpp>

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
	void startingUpdate(); 
	void render();
	
	void setupTitle(); // simon title 
	void setUpMenuContents(); // menu option 
	void setUpRectangles();// sets up the 4 rectangles
	void resetButtons();  // once button is pressed will rest them so a press on them can be detected again
	void processGameEvents(sf::Event& t_event); 
	void noteRandomiser(); 
	void setBufferAndPitch();// sets up sound for buttons 
	void buttonTimers(); // timer for button colours
	void showingUpdate(); // shows plauer seequence to copy
	void recievingUpdate(); // player input
	void overUpdate(); // game finshed 



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
	
	// colours for rectangles 

	const sf::Color RED{ 180, 0, 0, 255 };
	const sf::Color YELLOW{ 180, 180, 0, 255 }; 
	const sf::Color BLUE{ 0, 0, 180, 255 }; 
	const sf::Color GREEN{ 0, 180, 0, 255 }; 
	GameMode m_currentGameMode; // games curren stage 
	bool m_exitGame; // control exiting game
	
	// bools for button presses 
	bool m_redButtonPress; 
	bool m_yellowButtonPress; 
	bool m_blueButtonPress; 
	bool m_greenButtonPress; 

	// sound setup 
	int m_notes[32];// array for notes
	int m_difficulty;// difficulty settings
	int m_currentNote;// current note count 
	int m_currentCount;// the length of the current length of the sequence

	// sounds 
	sf::SoundBuffer m_toneBuffer; // used to store tone
	sf::Sound m_redTone; 
	sf::Sound m_yellowTone; 
	sf::Sound m_blueTone; 
	sf::Sound m_greenTone;

	// button timers for how long their colour is highlighed when they are pressed
	int m_redButtonTimer; 
	int m_yellowButtonTimer; 
	int m_blueButtonTimer; 
	int m_greenButtonTimer; 
	int m_flashTime; // hpw long button flashes for 

	// delay between the notes
	int m_modeChangeTimer; 

	bool m_win; 
	sf::Text m_statusText; 
};



#endif // !GAME_HPP