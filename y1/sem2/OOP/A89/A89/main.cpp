#include "UI.h"
#include "TextFiles.h"
#include <Windows.h>
#include"CSV.h"
#include <iostream>
#include "HTML.h"
using namespace std;

//void test_all()
//{
//	test_Tutorial();
//	test_repo();
//	test_ctrl();
//}

void start()
{
	Repository* repo;
	//cout << "1111";


	HTML repo2{ "html.html" };

	TextFiles repo1{ "Data.txt" };
	;

	WatchList* watch_list{ };
	//CSV f { "data_csv.txt" };
	watch_list = &repo2;
	repo = &repo1;
	/*Tutorial t1{ "Anna", "Tutorial 1", Duration{4, 54}, "https://www.youtube.com/watch?v=2fngvQS_PmQ" };
	Tutorial t2{ "Brad", "Tutorial 2", Duration{8, 12}, "https://www.youtube.com/watch?v=XYKUeZQbMF0" };
	Tutorial t3{ "Lily", "Tutorial 3", Duration{1, 0}, "https://www.youtube.com/watch?v=6L-_DiZlrUI" };
	Tutorial t4{ "Nora", "Tutorial 4", Duration{20, 11}, "https://youtu.be/v4pi1LxuDHc" };
	Tutorial t5{ "John", "Tutorial 5", Duration{4, 20}, "https://youtu.be/kfXd4UJS1BE" };
	Tutorial t6{ "Louis", "Tutorial 6", Duration{2, 48}, "https://youtu.be/L2IJzVAOvaU" };
	Tutorial t7{ "Anna", "Tutorial 7", Duration{6, 5}, "https://youtu.be/_OoShtF4_yQ" };
	Tutorial t8{ "Lily", "Tutorial 8", Duration{59, 59}, "https://youtu.be/BP6KxfuHXoA" };
	Tutorial t9{ "Lily", "Tutorial 9", Duration{7, 49}, "https://youtu.be/9DySfgEj1hY" };
	Tutorial t10{ "Harry", "Tutorial 10", Duration{1, 12}, "https://youtu.be/8xtg-ntDZGk" };
	repo.addTutorial(t1);
	repo.addTutorial(t2);
	repo.addTutorial(t3);
	repo.addTutorial(t4);
	repo.addTutorial(t5);
	repo.addTutorial(t6);
	repo.addTutorial(t7);
	repo.addTutorial(t8);
	repo.addTutorial(t9);
	repo.addTutorial(t10);*/
	Controller ctrl{ repo, watch_list };
	UI ui{ ctrl };
	//repo.load_file();
	ui.run();

}

int main()
{
	//test_all();
	start();


	return 0;
}