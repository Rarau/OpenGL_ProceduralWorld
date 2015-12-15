namespace engine
{
	class MovementSystem
	{
	private:
		MovementSystem()
		{

		}

		~MovementSystem()
		{

		}

	public:		

		static MovementSystem& GetMovementSystem()
		{
			static MovementSystem* movementSystem = nullptr;
			if (movementSystem == nullptr)
			{
				movementSystem = new MovementSystem();
			}
			return *movementSystem;
		}

		static void DestroyMovementSystem()
		{
			MovementSystem *movementSystem = &GetMovementSystem();
			delete movementSystem;
		}

		void Update(Entity *entity)
		{
			entity->SetPosition(AddVector3(entity->GetPosition(), entity->GetVelocity()));
			entity->SetRotation(AddVector3(entity->GetRotation(), entity->GetRotationVelocity()));
			entity->SetScale(AddVector3(entity->GetScale(), entity->GetScaleVelocity()));
		}
	};
}