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

				// For the moment it's just a cinematic integrator
				entity->transform().Translate(entity->GetVelocity());
				entity->transform().Rotate(Vector3(entity->GetRotationVelocity().x(), entity->GetRotationVelocity().y(), entity->GetRotationVelocity().z()));

			}
		}
	};
}