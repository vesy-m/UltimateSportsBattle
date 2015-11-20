#pragma once
#include <iostream>
#include "BaseGameObject.h"
#include "Message.h"

namespace GameObjects {
	class BaseGameObject;
}

namespace GameComponents {
	enum COMPONENT_TYPE
	{
		WINDOW,
		SPRITE,
		PHYSIC,
		COLLIDER,
		DEBUGVECTOR,
		TEXT,
		BUTTON,
		FIRE
	};

	class BaseComponent
	{
	public:
		BaseComponent(GameObjects::BaseGameObject*);
		virtual ~BaseComponent();
		virtual COMPONENT_TYPE getType() = 0;
		virtual void Update(double) = 0;
		virtual void Init() = 0;
		virtual void sendMessage(GameMessage::Message*) = 0;
		GameObjects::BaseGameObject *getComposition(void) const;
	protected:
		GameObjects::BaseGameObject *composition;
	};
}
