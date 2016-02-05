namespace engine
{
	class UISystem
	{
	public:
		float amplitude	= 1.0f;
		float amplitude2 = 1.0f;
		float amplitude3 = 1.0f;

		float timeScale = 1.0f;
		float diffuseColor[3];  
		float ambientColor[3];
		float fresnelColor[3];
		float fresnelPower = 150.0f;

		float lightDirection[3];         

	private:
		TwBar *myBar;
		int testVar = 0;

		UISystem()
		{
			initTweakBars();
			lightDirection[0] = -1.0f;
			lightDirection[1] = -1.0f;
			lightDirection[2] = 0.1f;

			diffuseColor[0] = 0.16;
			diffuseColor[1] = 0.31f;
			diffuseColor[2] = 1.0f;

			ambientColor[0] = 0.015f;
			ambientColor[1] = 0.015f;
			ambientColor[2] = 0.015f;

			fresnelColor[0] = 0.1f;
			fresnelColor[1] = 0.76;
			fresnelColor[2] = 1.0f;
		}

		~UISystem()
		{
			TwTerminate();
		}

		void initTweakBars()
		{
			TwWindowSize(1280, 720);

			int success = TwInit(TW_OPENGL, NULL);
			myBar = TwNewBar("Fragment shader parameters");

			TwAddVarRW(myBar, "amplitude", TW_TYPE_FLOAT, &amplitude, "label='Amplitude'");
			TwAddVarRW(myBar, "amplitude2", TW_TYPE_FLOAT, &amplitude2, "label='Amplitude 2'");
			TwAddVarRW(myBar, "amplitude3", TW_TYPE_FLOAT, &amplitude3, "label='Amplitude 3'");

			TwAddVarRW(myBar, "timeScale", TW_TYPE_FLOAT, &timeScale, "label='Time Scale'");
			TwAddVarRW(myBar, "diffuseColor", TW_TYPE_COLOR3F, &diffuseColor, " label='Diffuse color' ");
			TwAddVarRW(myBar, "ambientColor", TW_TYPE_COLOR3F, &ambientColor, " label='Ambient color' ");

			TwAddVarRW(myBar, "fresnelColor", TW_TYPE_COLOR3F, &fresnelColor, " label='Fresnel color' ");
			TwAddVarRW(myBar, "fresnelPower", TW_TYPE_FLOAT, &fresnelPower, "label='Fresnel power'");

			TwAddVarRW(myBar, "lightDir", TW_TYPE_DIR3F, &lightDirection, " label='Light direction' ");

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