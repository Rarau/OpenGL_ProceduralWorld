namespace engine
{
	class UISystem
	{
	private:
		//TwBar *myBar;
		int testVar = 0;
		float randomness = 0.0f;

		UISystem()
		{
			initTweakBars();

		}

		~UISystem()
		{
			//TwTerminate();
		}

		void initTweakBars()
		{/*
			TwWindowSize(1280, 720);

			int success = TwInit(TW_OPENGL, NULL);
			myBar = TwNewBar("Info");

			TwAddVarRO(myBar, "Tree Id", TW_TYPE_INT8, &(testVar), " label='Test field ' ");
			TwAddVarRW(myBar, "Whatever", TW_TYPE_INT32, &randomness, "label='Test field 2'");

			TwDefine(" GLOBAL help='Parameters' "); // Message added to the help bar.
			*/
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
			//TwDraw();
		}

	};
}