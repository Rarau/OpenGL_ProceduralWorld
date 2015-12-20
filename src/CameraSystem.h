#pragma once


namespace engine
{
	class CameraSystem
	{
	private:
		Entity *_currentCamera;
		
		CameraSystem()
		{

		}

		~CameraSystem()
		{

		}

	public:

		Entity* GetCurrentCamera()
		{
			return _currentCamera;
		}

		void SetCurrentCamera(Entity *newCamera)
		{
			_currentCamera = newCamera;
			RenderSystem *renderSystem = &RenderSystem::GetRenderSystem();
			renderSystem->SetCurrentCamera(_currentCamera);
		}

		static CameraSystem& GetCameraSystem()
		{
			static CameraSystem *cameraSystem = nullptr;
			if (cameraSystem == nullptr)
			{
				cameraSystem = new CameraSystem();
			}
			return *cameraSystem;
		}

		static void DestroyCameraSystem()
		{
			CameraSystem *cameraSystem = &GetCameraSystem();
			delete cameraSystem;
		}
	};
}