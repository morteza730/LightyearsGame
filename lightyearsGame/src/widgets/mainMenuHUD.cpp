#include "widgets/mainMenuHUD.hpp"

ly::MainMenuHUD::MainMenuHUD()
{
    m_titleText.setString("Ligt Years");
    m_titleText.setCharacterSize(30);
    m_startButton.setText("Start");
    m_quitButton.setText("Quit");
}

void ly::MainMenuHUD::draw(sf::RenderWindow &windowRef)
{
    m_titleText.nativeDraw(windowRef);
    m_quitButton.nativeDraw(windowRef);
    m_startButton.nativeDraw(windowRef);
}

bool ly::MainMenuHUD::handleEvent(const sf::Event &event)
{
    return m_quitButton.handleEvent(event) ||
           m_startButton.handleEvent(event) ||
           HUD::handleEvent(event);
}

void ly::MainMenuHUD::init(const sf::RenderWindow &windowRef)
{
    sf::Vector2u windowSize = windowRef.getSize();
    m_titleText.setLocation({windowSize.x / 2.f - m_titleText.getBound().width / 2.f, 100.f});
    m_startButton.setLocation({windowSize.x / 2.f - m_startButton.getBound().width / 2.f, windowSize.y / 2.f});
    m_quitButton.setLocation(m_startButton.getLocation() + sf::Vector2f{0.f, 50.f});
    m_startButton.onButtonClicked.bindAction(getWeakRef(),&MainMenuHUD::startButtonClicked);
    m_quitButton.onButtonClicked.bindAction(getWeakRef(), &MainMenuHUD::quitButtonClicked);
}

void ly::MainMenuHUD::startButtonClicked()
{
    onStartButtonClicked.broadCast();
}

void ly::MainMenuHUD::quitButtonClicked()
{
    onQuitButtonClicked.broadCast();
}
