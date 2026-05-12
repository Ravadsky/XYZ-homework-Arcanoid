#include "GameStateMainMenu.h"

#include "Application.h"
#include "Game.h"

namespace Arcanoid
{
	GameStateMainMenuData::GameStateMainMenuData() : GameStateBase()
	{
		MenuItem startGame;
		startGame.SetTextParameters(true, "Start Game", font, 24);
		startGame.SetCallbackFunction([](MenuItem&) {
			Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing);
			});

		MenuItem options;
		options.SetTextParameters(true, "Options", font, 24);
		options.SetTextParameters(false, "Options", font, 48, sf::Color::Red);
		options.SetPositionParameters(Orientation::Vertical, Alignment::Middle, 10.f);

		MenuItem recordsItem;
		recordsItem.SetTextParameters(true, "Records", font, 24);
		recordsItem.SetCallbackFunction([](MenuItem&) {
			Application::Instance().GetGame().PushState(GameStateType::Records, true);
			});

		MenuItem yesItem;
		yesItem.SetTextParameters(true, "Yes", font, 24);
		yesItem.SetCallbackFunction([](MenuItem&) {
			Application::Instance().GetGame().SwitchStateTo(GameStateType::None);
			});

		MenuItem noItem;
		noItem.SetTextParameters(true, "No", font, 24);
		noItem.SetCallbackFunction([this](MenuItem&) {this->menu.GoBack();
			});

		MenuItem exitGameItem;
		exitGameItem.SetTextParameters(true, "Exit Game", font, 24);
		exitGameItem.SetTextParameters(false, "Are you sure?", font, 48, sf::Color::Red);
		exitGameItem.SetPositionParameters(Orientation::Horizontal, Alignment::Middle, 10.f);

		exitGameItem.AttachChild(yesItem);
		exitGameItem.AttachChild(noItem);

		MenuItem mainMenu;
		mainMenu.SetTextParameters(false, "Arcanoid", font, 48, sf::Color::Red);
		mainMenu.SetPositionParameters(Orientation::Vertical, Alignment::Middle, 10.f);

		mainMenu.AttachChild(startGame);
		mainMenu.AttachChild(options);
		mainMenu.AttachChild(recordsItem);
		mainMenu.AttachChild(exitGameItem);

		menu.Init(mainMenu);
	}

	GameStateMainMenuData::~GameStateMainMenuData()
	{
	}

	void GameStateMainMenuData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				menu.GoBack();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				menu.PressOnSelectedItem();
			}

			Orientation orientation = menu.GetCurrentContext().GetChildrenOrientation();
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				menu.SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				menu.SwitchToNextMenuItem();
			}
		}
	}

	void GameStateMainMenuData::Update(float timeDelta)
	{
	}

	void GameStateMainMenuData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = menu.GetCurrentContext().GetHintText();
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}

}
