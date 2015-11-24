#include "BoxCollider.h"
#include "CircleCollider.h"


namespace GameComponents {
	CircleCollider::CircleCollider(GameObjects::BaseGameObject *object) : ColliderComponent(object)
	{
	}


	CircleCollider::~CircleCollider()
	{
	}

	void CircleCollider::Init(void)
	{
		this->radius = this->composition->getHeight() / 2.0f;
		this->centerPos = glm::vec2(this->composition->getX() + this->composition->getHeight() / 2.0f, this->composition->getY() + this->composition->getHeight() / 2.0f);
		this->minPoint = glm::vec2(this->composition->getX(), this->composition->getY());
		this->maxPoint = glm::vec2(this->composition->getX() + this->composition->getHeight(), this->composition->getY() + this->composition->getHeight());
	}

	COMPONENT_TYPE CircleCollider::getType()
	{
		return COMPONENT_TYPE::CIRCLE_COLLIDER;
	}

	void CircleCollider::Update(double dt)
	{
		this->centerPos = glm::vec2(this->composition->getX() + this->composition->getHeight() / 2.0f, this->composition->getY() + this->composition->getHeight() / 2.0f);
		this->minPoint = glm::vec2(this->composition->getX(), this->composition->getY());
		this->maxPoint = glm::vec2(this->composition->getX() + this->composition->getHeight(), this->composition->getY() + this->composition->getHeight());
		bool collide = false;

		if (this->composition->getType() != GameObjects::NONE)
		{
			std::list<GameObjects::BaseGameObject*> listObjects = GameSystems::ObjectFactory::getInstance().getCurrentObjects();
			for each(GameObjects::BaseGameObject* object in listObjects)
			{
				if (this->composition->getType() == GameObjects::PLAYER) {
					if (object->getType() == GameObjects::PROJECTILE && object->getName().compare(this->composition->getName()) == 0)
						continue;
					else if (object->getType() == GameObjects::PLAYER)
						continue;
				}

				if (this->composition->getType() == GameObjects::PROJECTILE) {
					if (object->getType() == GameObjects::PLAYER && object->getName().compare(this->composition->getName()) == 0)
						continue;
				}
				if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER))
				{
					if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER) == this) continue;

					Manifold *manifold = new Manifold();
					if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER)->getType() == COMPONENT_TYPE::BOX_COLLIDER)
					{
						BoxCollider *otherObject = dynamic_cast<BoxCollider*>(object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER));

						manifold->A = this;
						manifold->B = otherObject;
						if (CollideWithBox(manifold))
						{
							ResolveCollision(manifold);
							collide = true;
						}
					}
				}
			}
			if (!collide)
			{
				this->composition->sendMessage(new GameMessage::Message(GameMessage::Message::NO_COLLISION));
			}
		}
	}

	bool CircleCollider::CollideWithBox(Manifold *manifold) 
	{
		CircleCollider *A = dynamic_cast<CircleCollider*>(manifold->A);
		BoxCollider *B = dynamic_cast<BoxCollider*>(manifold->B);
		
		bool inside = false;

		glm::vec2 closestPoint = glm::vec2(Clamp(A->centerPos.x, B->minPoint.x, B->maxPoint.x),
										   Clamp(A->centerPos.y, B->minPoint.y, B->maxPoint.y));
		//glm::vec2 closestPoint = ClampTest(A->centerPos, B->minPoint, B->maxPoint);

		float x_extent = (A->maxPoint.x - A->minPoint.x) / 2;
		float y_extent = (A->maxPoint.y - A->minPoint.y) / 2;

		glm::vec2 velocity = A->velocity;

		glm::vec2 fakeCenterPos = A->centerPos;

		// Circle is inside the AABB, so we need to clamp the circle's center
		// to the closest edge
		if (A->centerPos == closestPoint)
		{
			std::cout << "Clamp" << std::endl;

			inside = true;

			fakeCenterPos += glm::normalize(-A->velocity) * A->radius;
		}

		// Calculate the distance between the circle's center and this closest point
		glm::vec2 fakeDistance = fakeCenterPos - closestPoint;


		glm::vec2 compass[] = {
			glm::vec2(0.0f, 1.0f),	// down
			glm::vec2(1.0f, 0.0f),	// right
			glm::vec2(0.0f, -1.0f),	// up
			glm::vec2(-1.0f, 0.0f)	// left
		};
		float max = 0.0f;
		int dir = -1;
		for (int i = 0; i < 4; i++)
		{
			float dot_product = glm::dot(glm::normalize(fakeDistance), compass[i]);
			if (dot_product > max)
			{
				max = dot_product;
				dir = i;
			}
		}

		glm::vec2 distance = A->centerPos - closestPoint;


		// If the distance is less than the circle's radius, an intersection occurs
		//float distanceSquared = (distance.x * distance.x) + (distance.y * distance.y);
		if (glm::length(distance) <= A->radius)
		{
			//std::cout << "Collision -> Distance = " << distance.x << " / " << distance.y << std::endl;

			if (dir == 0 || dir == 2) {
				manifold->normal = compass[dir];
				if (dir == 0)
					manifold->penetration = (A->radius - std::abs(distance.y));
				else
					manifold->penetration = (A->radius - std::abs(distance.y));
			}
			else {
				manifold->normal = compass[dir];
				manifold->penetration = (A->radius - std::abs(distance.x));
			}

			// Collision normal needs to be flipped to point outside if circle was
			// inside the AABB
			/*if (inside) manifold->normal = glm::normalize(-distance);
			else manifold->normal = glm::normalize(distance);

			manifold->penetration = A->radius - std::abs(distance);*/

			return true;
		}
		return false;
	}

	void CircleCollider::sendMessage(GameMessage::Message *message)
	{
		if (message->id == GameMessage::Message::VELOCITY_VECTOR)
			this->velocity = ((GameMessage::VectorMessage*)message)->vector;
	}
}
