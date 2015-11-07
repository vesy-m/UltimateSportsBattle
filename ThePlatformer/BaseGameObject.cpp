#include "BaseGameObject.h"

namespace GameObjects {
	BaseGameObject::BaseGameObject()
	{
		this->componentsList = std::vector<GameComponents::BaseComponent*>();
		x = 0;
		y = 0;
		height = 0;
		width = 0;
		depth = 0;
		rotate = 0;
		scale = 1;
		mass = 1.0f;
		to_destroy = false;
		type = objectType::NONE;
	}

	void BaseGameObject::Init(void) {
		for (auto it = this->componentsList.begin(); it != this->componentsList.end(); ++it) (*it)->Init();
	}

	BaseGameObject::~BaseGameObject()
	{
		for (auto it = this->componentsList.begin(); it != this->componentsList.end(); ++it) {
			delete *it;
		}
	}

	GameComponents::BaseComponent *BaseGameObject::getComponent(GameComponents::COMPONENT_TYPE type) {
		for (auto component : this->componentsList) {
			if (component->getType() == type) return component;
		}
		return NULL;
	}

	void BaseGameObject::attachComponent(GameComponents::BaseComponent *component)
	{
		this->componentsList.push_back(component);
	}

	void BaseGameObject::sendMessage(GameMessage::Message *message)
	{
		for each (GameComponents::BaseComponent *component in this->componentsList) component->sendMessage(message);
	}

	void BaseGameObject::setX(int x)
	{
		if (x < 0) this->x = 1;
		else if (x + this->getWidth() >= 1280) this->x = 1280 - this->getWidth();
		else this->x = x;

	}
	int BaseGameObject::getX()
	{
		return this->x;
	}
	void BaseGameObject::setY(int y)
	{
		this->y = y;
	}
	int BaseGameObject::getY()
	{
		return this->y;
	}
	int BaseGameObject::getHeight()
	{
		return this->height;
	}

	int BaseGameObject::getWidth()
	{
		return this->width;
	}
	void BaseGameObject::setDepth(int depth)
	{
		this->depth = depth;
	}
	int BaseGameObject::getDepth()
	{
		return this->depth;
	}
	void BaseGameObject::setHeight(int height)
	{
		this->height = (int)(height * scale);
	}
	void BaseGameObject::setWidth(int width)
	{
		this->width = (int)(width * scale);
	}
	void BaseGameObject::setScale(float scale)
	{
		this->scale = scale;
	}
	float BaseGameObject::getScale()
	{
		return this->scale;
	}
	void BaseGameObject::setMass(float mass)
	{
		this->mass = mass;
	}
	float BaseGameObject::getMass()
	{
		return this->mass;
	}
	void BaseGameObject::setRotate(int rotate)
	{
		this->rotate = rotate;
	}
	int BaseGameObject::getRotate()
	{
		return this->rotate;
	}
	void BaseGameObject::setName(std::string name)
	{
		this->name = name;
	}
	std::string BaseGameObject::getName()
	{
		return name;
	}
	void BaseGameObject::setType(objectType newtype)
	{
		this->type = newtype;
	}
	objectType BaseGameObject::getType()
	{
		return this->type;
	}

	void BaseGameObject::destroy(bool des) {
		to_destroy = des;
	}

	bool BaseGameObject::destroy(void) {
		return to_destroy;
	}
}
