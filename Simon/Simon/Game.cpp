/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_redRectangle{ sf::Vector2f{200.0f, 200.0f} },
	m_yellowRectangle{ sf::Vector2f{200.0f, 200.0f} },
	m_greenRectangle{ sf::Vector2f{200.0f, 200.0f} }, 
	m_blueRectangle{sf::Vector2f{200.0f, 200.0f}}, 
	m_currentGameMode{GameMode::Starting},
	m_exitGame{false} //when true game will exit
	
{
	setupTitle(); // load font 
	setUpMenuContents(); 
	setUpRectangles(); 
	resetButtons(); 
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		processGameEvents(newEvent); 
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	switch (m_currentGameMode)
	{
	case GameMode::Starting:
		startingUpdate(); 
		break; 

	case GameMode::Showing:

		break; 
	
	case GameMode::Recieveing:

		break; 

	case GameMode::GameOver:

		break; 

	}
	resetButtons(); 
}

void Game::startingUpdate()
{
	

	if (m_blueButtonPress)
	{
		noteRandomiser(); 
		m_difficulty = 8; 
		m_currentCount = 1; 
		m_currentNote = 0; 

	}
	if (m_yellowButtonPress)
	{
		noteRandomiser(); 
		m_currentGameMode = GameMode::Showing; 
		m_difficulty = 16; 
		m_currentCount = 1; 
		m_currentNote = 0; 

	}

	if (m_greenButtonPress)
	{
		noteRandomiser(); 
		m_currentGameMode = GameMode::Showing; 
		m_difficulty = 32; 
		m_currentCount = 1; 
		m_currentNote = 0; 

	}

	if (m_redButtonPress)
	{
		m_window.close(); 
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	//text
	m_window.draw(m_simonTitle);
	m_window.draw(m_easyText); 
	m_window.draw(m_normalText);
	m_window.draw(m_hardText); 
	m_window.draw(m_exitText); 
	// rectangles
	m_window.draw(m_redRectangle);
	m_window.draw(m_yellowRectangle);
	m_window.draw(m_blueRectangle); 
	m_window.draw(m_greenRectangle); 

	m_window.display();
}

/// <summary>
/// sets up the title
/// </summary>
void Game::setupTitle()
{
	if (!m_raceSportFont.loadFromFile("ASSETS\\FONTS\\Race Sport Free.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	m_simonTitle.setFont(m_raceSportFont);
	m_simonTitle.setString("Simon");
	m_simonTitle.setPosition(20.0f, 30.0f);
	m_simonTitle.setCharacterSize(80U);
	m_simonTitle.setFillColor(sf::Color::Yellow);
	m_simonTitle.setOutlineThickness(3.0f);

}

/// <summary>
/// sets up the four sets of text (easy, normal, hard and exit)
/// </summary>
void Game::setUpMenuContents()
{
	if (!m_raceSportFont.loadFromFile("ASSETS\\FONTS\\Race Sport Free.ttf"))
	{
		std::cout << "problem loading font"<<std::endl; 
	}
	// easy mode 
	m_easyText.setFont(m_raceSportFont); 
	m_easyText.setString("Easy mode"); 
	m_easyText.setPosition(20.0f, 150.0f); 
	m_easyText.setCharacterSize(35U);
	m_easyText.setFillColor(sf::Color::Blue); 
	m_easyText.setOutlineThickness(3.0f); 

	// normal mode
	m_normalText.setFont(m_raceSportFont); 
	m_normalText.setString("Normal mode"); 
	m_normalText.setPosition(20.0f, 240.0f); 
	m_normalText.setCharacterSize(35U); 
	m_normalText.setFillColor(sf::Color::Yellow); 
	m_normalText.setOutlineThickness(3.0f);
	
	//hard mode 
	m_hardText.setFont(m_raceSportFont); 
	m_hardText.setString("Hard Mode"); 
	m_hardText.setPosition(20.0f, 330.0f); 
	m_hardText.setCharacterSize(35U); 
	m_hardText.setFillColor(sf::Color::Green); 
	m_hardText.setOutlineThickness(3.0f); 

	// Exit text
	m_exitText.setFont(m_raceSportFont); 
	m_exitText.setString("Exit Game"); 
	m_exitText.setPosition(20.0f, 420.0f); 
	m_exitText.setCharacterSize(35U); 
	m_exitText.setFillColor(sf::Color::Red); 
	m_exitText.setOutlineThickness(3.0f); 

}

/// <summary>
/// loads in the rectangles 
/// </summary>
void Game::setUpRectangles()
{	
	// red rectangle set up 
	m_redRectangle.setFillColor(sf::Color(180, 0, 0, 255)); 
	m_redRectangle.setPosition(580.0f, 330.0f);

	// yellow rectangle set up 
	m_yellowRectangle.setFillColor(sf::Color::Yellow); 
	m_yellowRectangle.setPosition(580.0f, 120.0f); 

	//blue rectangle set up 
	m_blueRectangle.setFillColor(sf::Color::Blue); 
	m_blueRectangle.setPosition(370.0f, 120.0f); 

	//green rectangle set up
	m_greenRectangle.setFillColor(sf::Color::Green); 
	m_greenRectangle.setPosition(370.0f, 330.0f); 
}

/// <summary>
/// resets the buttons to detect another press after inital one 
/// </summary>
void Game::resetButtons()
{
	m_redButtonPress = false;
	m_yellowButtonPress = false; 
	m_blueButtonPress = false; 
	m_greenButtonPress = false; 
}

/// <summary>
/// detects which button is pressed
/// </summary>
/// <param name="t_event">mosue click</param>
void Game::processGameEvents(sf::Event& t_event)
{

	float row1Top = 120.0f;
	float row1Bottom = 320.0f;
	
	float colour1L = 370.0f; // blue/ green
	float colour1R = 570.0f; // blue/ green
	float colour2L = 580.0f; // yellow/ red
	float colour2R =780.0f; // yellow/ red
	
	float row2Top = 330.0f;
	float row2Bottom = 530.0f; 

	if (sf::Event::MouseButtonReleased == t_event.type)
	{
		// top row blue/ yellow 
		if (t_event.mouseButton.y > row1Top && t_event.mouseButton.y<row1Bottom) 
		{
			if (t_event.mouseButton.x> colour1L && t_event.mouseButton.x < colour1R)
			{
				m_blueButtonPress = true;
			}
			if (t_event.mouseButton.x > colour2L && t_event.mouseButton.x < colour2R)
			{
				m_yellowButtonPress = true; 
			}
		}

		// bottom row green/red
		if (t_event.mouseButton.y > row2Top && t_event.mouseButton.y < row2Bottom)
		{
			if (t_event.mouseButton.x > colour1L && t_event.mouseButton.x < colour1R)
			{
				m_greenButtonPress = true; 
			}
			if (t_event.mouseButton.x > colour2L && t_event.mouseButton.x < colour2R)
			{
				m_redButtonPress = true; 
			}
		}
	}



}

void Game::noteRandomiser()
{
	for (int index = 0; index < 32; index++)
	{
		m_notes[index] = std::rand() % 4; // trying to find some values of 0, 1, 2, 3
	}
}



