#pragma once
#include "InputComponent.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class KeyboardInputComponent : public InputComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		KeyboardInputComponent(GameObjects::BaseGameObject*, std::string);
	public:
		virtual ~KeyboardInputComponent();
		virtual void UpdateInputState(sf::Event, double);
		virtual void Init();
		virtual void sendMessage(GameMessage::Message*);
		int	ParseInputFile(GameTools::JsonValue);
		void setMousePosition(sf::Event);
	private:
		int mouseX;
		int mouseY;
		std::map<INPUT_TYPE, int> keyboardMap;
		std::map<INPUT_TYPE, sf::Mouse::Button> mouseMap;
		std::string inputFilename;
	};
}

