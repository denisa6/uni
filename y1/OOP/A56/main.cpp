#include "UI.h"
#include <Windows.h>

using namespace std;

int main()
{

	Repository repo{};
	Tutorial t1{"Ed Sheeran", "I see fire", Duration{4, 54}, "https://www.youtube.com/watch?v=2fngvQS_PmQ"};
	Tutorial t2{ "Two Steps From Hell", "Heart of Courage", Duration{8, 12}, "https://www.youtube.com/watch?v=XYKUeZQbMF0" };
	Tutorial t3{ "Pink Martini", "Splendour in the Grass", Duration{3, 47}, "https://www.youtube.com/watch?v=6L-_DiZlrUI" };
	Tutorial t4{ "Ed Sheeran", "Perfect", Duration{5, 48}, "https://youtu.be/2Vv-BfVoq4g" };
	repo.addTutorial(t1);
	repo.addTutorial(t2);
	repo.addTutorial(t3);
	repo.addTutorial(t4);

	Controller ctrl{ repo };
	UI ui{ ctrl };
	ui.run();


	return 0;
}