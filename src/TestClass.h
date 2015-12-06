namespace engine
{
	class TestClass
	{
	private:
		int a;
	public:
		int x;

		TestClass(int _a, int _x)
		{
			a = _a;
			x = _x;
		}

		void print_stuff()
		{
			printf("A = %d, X = %d\n", a, x);
		}
	};



}