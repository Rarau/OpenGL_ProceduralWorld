#pragma once

namespace engine
{
	class Scene
	{
	private:

		CameraSystem *_cameraSystem;
		ResourceManager *_resourceManager;
		PlayerInputSystem *_playerInputSystem;

		// all our objects will be children of our scene
		std::vector<Entity *> *_children;
		

	public:

		std::vector<Entity*>* GetChildren()
		{
			return _children;
		}

		Scene()
		{
			_cameraSystem = &CameraSystem::GetCameraSystem();
			_resourceManager = &ResourceManager::GetResourceManager();
			_playerInputSystem = &PlayerInputSystem::GetPlayerInputSystem();

			_children = new std::vector<Entity*>();

			//TO-DO: this is hardcoded, can't be here
			Entity *camera = new Entity(nullptr, MakeVector3(0.0f, 0.0f, 0.0f));
			camera->SetEyeVector(NormalizeVector3(MakeVector3(0.0f, 0.0f, 1.0f)));
			_children->push_back(camera);

			_cameraSystem->SetCurrentCamera(camera);
			_playerInputSystem->SetCurrentPlayer(camera);

			Entity *entity = new Entity(_resourceManager->GetVertexBufferArray()->at(0), MakeVector3(0.0f, 0.0f, 5.0f));
			entity->SetRotation(MakeVector3(30.0f, 0.0f, 0.0f));
			entity->SetScale(MakeVector3(2.0f, 2.0f, 2.0f));
			entity->SetRotationVelocity(MakeVector3(0.3f, 0.0f, 0.0f));
			_children->push_back(entity);
		}

		~Scene()
		{
			for (std::vector<Entity*>::iterator iterator = _children->begin(); iterator != _children->end(); iterator++)
			{
				delete *iterator;
			}

		}

	};
}