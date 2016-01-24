namespace engine
{
	class Entity;

	class Renderer
	{
		

	protected:
		Renderer()
		{

		}
	public:
		Renderer(const Renderer &) = default;

		~Renderer()
		{

		}

		virtual void Render(Entity* entity)
		{

		}

		Matrix4x4 GetProjectionMatrix();
	};
}