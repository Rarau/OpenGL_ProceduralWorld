namespace engine
{
	class RenderSystem
	{
	private:

		GLFWwindow *_window;

		RenderSystem() : _window(glfwGetCurrentContext())
		{

		}

		~RenderSystem()
		{

		}

	public:

		static RenderSystem& GetRenderSystem()
		{
			static RenderSystem *renderSystem = nullptr;
			if (renderSystem == nullptr)
			{
				renderSystem = new RenderSystem();
				glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
			return *renderSystem;
		}

		static void DestroyRenderSystem()
		{
			RenderSystem *renderSystem = &GetRenderSystem();
			delete renderSystem;
		}

		void Render()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glfwSwapBuffers(_window);
		}
	};
}