#include "Engine.h"
#include "../GameManager.h"

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	engine::GameManager *gameManager = &(engine::GameManager::GetGameManager());
	// register callbacks
	//glutDisplayFunc(renderScene);

	//glutMainLoop();
	engine::GameManager::DestroyGameManager();
}

//void renderScene(void)
//{
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClearColor(1.0, 0.0, 0.0, 1.0);//clear red
//
//	glutSwapBuffers();
//}
//
//int main(int argc, char **argv)
//{
//
//	engine::TestClass test = engine::TestClass(1, 3);
//	test.print_stuff();
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(500, 500);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("OpenGL First Window");
//
//	glEnable(GL_DEPTH_TEST);
//
//	// register callbacks
//	glutDisplayFunc(renderScene);
//
//	glutMainLoop();
//
//	return 0;
//}