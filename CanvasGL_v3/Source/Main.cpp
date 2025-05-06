#include <CanvasGL.h>

int main(int argc, char *argv[]) {

	std::cout << "======================= CANVAS GL ALPHA 0.1 =======================" << std::endl << std::endl;
	std::cout << "  Shortcuts:" << std::endl << std::endl
		<< "    Arrows    : Move camera;" << std::endl << std::endl
		<< "    TAB       : Switch between objects;" << std::endl
		<< "    W,A,S,D   : Translate selected object;" << std::endl
		<< "    [,]       : Scale selected object;" << std::endl
		<< "    R         : Rotate selecter object;" << std::endl
		<< "    F         : Enframe selected object;" << std::endl
		<< "    P         : Change selected object pivot;" << std::endl
		<< "    F12       : Clear canvas;" << std::endl << std::endl
		<< "    0         : Set mouse click to SELECT OBJECT mode (default);" << std::endl
		<< "    1         : Set mouse click to BUILD DOT mode;" << std::endl
		<< "    2         : Set mouse click to BUILD LINE mode;" << std::endl
		<< "    3         : Set mouse click to BUILD TRIANGLE mode;" << std::endl
		<< "    4         : Set mouse click to BUILD RECTANGLE mode;" << std::endl
		<< "    5         : Set mouse click to BUILD CIRCLE mode;" << std::endl;
	std::cout << std::endl << "============================== LOG ================================" << std::endl;


	Global::Start(argc, argv);


	return EXIT_SUCCESS;

}