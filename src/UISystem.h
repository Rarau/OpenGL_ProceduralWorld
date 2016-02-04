namespace engine
{
	class UISystem
	{
	public:
		float amplitude = 1.0f;
		float timeScale = 1.0f;
		float diffuseColor[3];         // Background color 

	private:
		TwBar *myBar;
		int testVar = 0;

		UISystem()
		{
			initTweakBars();
		}

		~UISystem()
		{
			TwTerminate();
		}

		void initTweakBars()
		{
			TwWindowSize(1280, 720);

			int success = TwInit(TW_OPENGL, NULL);
			myBar = TwNewBar("Info");
			float _diffuseColor[] = { 0.1f, 0.2f, 0.4f };         // Background color 

			TwAddVarRW(myBar, "amplitude", TW_TYPE_FLOAT, &amplitude, "label='Amplitude'");
			TwAddVarRW(myBar, "timeScale", TW_TYPE_FLOAT, &timeScale, "label='Time Scale'");
			TwAddVarRW(myBar, "diffuseColor", TW_TYPE_COLOR3F, &diffuseColor, " label='Diffuse color' ");

			TwDefine(" GLOBAL help='Parameters' "); // Message added to the help bar.

			//diffuseColor = _diffuseColor;
		}

	public:
		static UISystem& GetUISystem()
		{
			static UISystem *uiSystem = nullptr;
			if (uiSystem == nullptr)
			{
				uiSystem = new UISystem();
			}
			return *uiSystem;
		}

		static void DestroyUISystem()
		{
			UISystem *uiSystem = &GetUISystem();
			delete uiSystem;
		}

		void Render()
		{
			TwDraw();
		}

	};
}