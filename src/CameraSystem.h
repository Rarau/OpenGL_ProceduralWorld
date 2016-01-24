#pragma once


namespace engine
{
	class CameraSystem
	{
	private:
		Entity *_currentCamera;
		Matrix4x4 projectionMatrix;

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

		void InitViewport(float fov, float aspectRatio, float zNear, float zFar) {
			projectionMatrix.Perspective(aspectRatio, aspectRatio, zNear, zFar);
		}

		const Matrix4x4& GetProjectionMatrix() {
			return projectionMatrix;
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