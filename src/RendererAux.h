namespace engine
{
	Matrix4x4 Renderer::GetProjectionMatrix()
	{
		CameraSystem cs = CameraSystem::GetCameraSystem();
		return cs.GetProjectionMatrix();
	}
}