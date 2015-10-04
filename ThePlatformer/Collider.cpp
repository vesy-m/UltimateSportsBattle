#include "Collider.h"

namespace GameComponents {
	BoxCollider::BoxCollider()
	{}

	BoxCollider::BoxCollider(glm::vec2 min, glm::vec2 max)
	{
		this->min = min;
		this->max = max;
	}

	BoxCollider::~BoxCollider()
	{}

	COMPONENT_TYPE BoxCollider::getType()
	{
		return COMPONENT_TYPE::PHYSIC;
	}

	void BoxCollider::Update()
	{
	}

	void BoxCollider::Init()
	{
	}

	bool BoxCollider::Collide(BoxCollider *other)
	{
		// Exit with no intersection if found separated along an axis
		if (this->max.x < other->min.x || this->min.x > other->max.x)
			return false;
		if (this->max.y < other->min.y || this->min.y > other->max.y)
			return false;

		// No separating axis found, therefor there is at least one overlapping axis
		return true;
	}

	bool BoxCollider::Collide(CircleCollider * other)
	{
		return false;
	}

	CircleCollider::CircleCollider()
	{}

	CircleCollider::CircleCollider(float radius, glm::vec2 pos)
	{
		this->radius = radius;
		this->pos = pos;
	}

	CircleCollider::~CircleCollider()
	{}

	COMPONENT_TYPE CircleCollider::getType()
	{
		return COMPONENT_TYPE::PHYSIC;
	}

	void CircleCollider::Update()
	{
	}

	void CircleCollider::Init()
	{
	}

	bool CircleCollider::Collide(BoxCollider * other)
	{
		return false;
	}

	bool CircleCollider::Collide(CircleCollider *other)
	{
		float r = this->radius + other->radius;
		r *= r;
		return r < pow((this->pos.x + other->pos.x), 2) + pow((this->pos.y + other->pos.y), 2);
	}

	HexagonCollider::HexagonCollider()
	{
	
	}

	HexagonCollider::HexagonCollider(float width, float height)
	{
		this->width = width;
		this->height = height;
	}

	HexagonCollider::~HexagonCollider()
	{}

	COMPONENT_TYPE HexagonCollider::getType()
	{
		return COMPONENT_TYPE::PHYSIC;
	}

	void HexagonCollider::Update()
	{
	}

	void HexagonCollider::Init()
	{
	}

	bool HexagonCollider::CollideTop(BoxCollider *other)
	{
		return (this->composition->getY() >= other->max.y);
	}

	bool HexagonCollider::CollideDown(BoxCollider *other)
	{
		return (this->composition->getY() + this->height <= other->min.y);
	}

	bool HexagonCollider::CollideTopLeft(BoxCollider *other)
	{
		return ((this->composition->getX() <= other->min.x) || (this->composition->getY() + (this->height / 5) >= other->max.y));
	}

	bool HexagonCollider::CollideTopRight(BoxCollider *other)
	{
		return ((this->composition->getX() + this->width <= other->max.x) || (this->composition->getY() + (this->height / 5) >= other->max.y));
	}

	bool HexagonCollider::CollideDownLeft(BoxCollider *other)
	{
		return ((this->composition->getX() <= other->min.x) || (this->composition->getY() + this->height - this->height / 5 <= other->min.y));
	}

	bool HexagonCollider::CollideDownRight(BoxCollider *other)
	{
		return ((this->composition->getX() + this->width <= other->max.x) || (this->composition->getY() + this->height - this->height / 5 <= other->min.y));
	}

	CollisionMessage::CollisionMessage(glm::vec2 pos, glm::vec2 velocity)
	{
		this->id = COLLISION;
		this->pos = pos;
		this->velocity = velocity;
	}

	CollisionMessage::~CollisionMessage()
	{
	}
}