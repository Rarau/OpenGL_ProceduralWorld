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

		void Update(std::vector<Entity*> *entityArray)
		{
			for (std::vector<Entity*>::iterator iterator = entityArray->begin(); iterator != entityArray->end(); iterator++)
			{
				Entity *entity = *iterator;
				entity->SetPosition(AddVector3(entity->GetPosition(), entity->GetVelocity()));
				entity->SetRotation(AddVector3(entity->GetRotation(), entity->GetRotationVelocity()));
				entity->SetScale(AddVector3(entity->GetScale(), entity->GetScaleVelocity()));
			}
		}
	};
}