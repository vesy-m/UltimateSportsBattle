#pragma once
#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include <vector>
#include <list>
#include "BaseGameObject.h"
#include "Projectile.h"
#include "gason.h"
#include "GameEngine.h"
#include "SpriteComponent.h"
#include "Menu.h"

namespace GameComponents {
	class SpriteComponent;
}

namespace GameSystems {
	class ObjectFactory
	{
		enum gameState
		{
			MENU,
			LEVEL,
			NONE
		};

	public:
		static ObjectFactory& getInstance()
		{
			static ObjectFactory    instance;
			return instance;
		}
		~ObjectFactory();
		GameObjects::BaseGameObject *parseObject(GameTools::JsonValue&);
		GameObjects::BaseGameObject *createArrow(GameObjects::BaseGameObject*, unsigned int, unsigned int, float, glm::vec2);
		static void attachObject(GameObjects::BaseGameObject*);
		void buildLevel(GameTools::JsonValue&);
		GameEngine::Core::Level &getCurrentLevel();
		void buildMenu(GameTools::JsonValue & value);
		void LoadLevelFileAsCurrent(const std::string & filename);
		void LoadMenuFileAsCurrent(const std::string & filename);
		void cleanupObjects(void);
		std::list<GameObjects::BaseGameObject*>& getCurrentObjects();
		const std::list<GameSystems::BaseSystem *> &getSystems();
		void initSystems();
		void addSystems(GameSystems::BaseSystem *);
	private:
		ObjectFactory();
		ObjectFactory(ObjectFactory const&) = delete;
		void operator=(ObjectFactory const&) = delete;
		void putObjectDepthOrdered(GameObjects::BaseGameObject*);
		std::list<GameObjects::BaseGameObject *> old_objects;
		std::list<GameSystems::BaseSystem *>		m_systems;

		std::vector<GameEngine::Core::Level> listLevels;
		GameEngine::Core::Level currentLevel;
		Menu currentMenu;
		gameState stateGame;

	};
}

#endif // !_OBJECTFACTORY_H_