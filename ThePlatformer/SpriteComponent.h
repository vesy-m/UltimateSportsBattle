#pragma once
#include "BaseGameObject.h"
#include <SFML/OpenGL.hpp>
#include <il.h>
#include <cstdio>
#include <string>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SpriteSheet.h"
#include "ObjectFactory.h"

#define TEXTURE_LOAD_ERROR 0

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {

	class SpriteComponent : public BaseComponent
	{
		friend class GameSystems::ObjectFactory;
	public:
		SpriteComponent(GameObjects::BaseGameObject*, const std::string&);
		virtual ~SpriteComponent();
		virtual COMPONENT_TYPE getType() const;
		virtual void Update(double);
		virtual void Init();
		virtual void sendMessage(GameMessage::Message*);
		bool revertX;
	private:
		const COMPONENT_TYPE type = COMPONENT_TYPE::SPRITE;
		GameTools::SpriteSheet *sheet;
		int rotateNum;
		
		bool revertY;
		bool isDashing;
		int currentFrame;
		int counter;
		std::string currentAnim;
		std::string _fileName;
	};
}