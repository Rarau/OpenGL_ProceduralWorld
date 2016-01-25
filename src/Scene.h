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

			//TO-DO: this is hardcoded, can't be here -----------------------------------------------------------------------------

			Entity *camera = new Entity(nullptr, Matrix4x4());
			_children->push_back(camera);
			// set the camera entity
			_cameraSystem->SetCurrentCamera(camera);

			// set the "player" entity
			_playerInputSystem->SetCurrentPlayer(camera);

			// CREATE RESOURCES

			// add renderers:
			TerrainRenderer* terrainRenderer = new TerrainRenderer(camera);
			(&ResourceManager::GetResourceManager())->GetRendererArray()->push_back(terrainRenderer);

			GeometryRenderer* geometryRenderer = new GeometryRenderer(camera);
			(&ResourceManager::GetResourceManager())->GetRendererArray()->push_back(geometryRenderer);

			// CREATE ENTITIES


						

			//// Terrain entity
			Entity *entity = new Entity(nullptr, Matrix4x4());
			// Add terrain renderer.
			entity->SetRenderer(_resourceManager->GetRendererArray()->at(0));
			entity->SetRotationVelocity(Vector3(0.0f, 0.0f, 0.3f));
			
			_children->push_back(entity);

			// rotating Sphere
			Entity *entity2 = new Entity(_resourceManager->GetVertexBufferArray()->at(0), Matrix4x4());
			entity2->transform().Translate(0.0f, 0.0f, 5.0f);
			entity2->transform().Scale(2.0f, 2.0f, 2.0f);
			
			entity2->SetRotationVelocity(Vector3(0.3f, 0.0f, 0.0f));
			entity2->SetRenderer(_resourceManager->GetRendererArray()->at(1));
			_children->push_back(entity2);			

			//TO-DO: this is hardcoded, can't be here -----------------------------------------------------------------------------

			
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