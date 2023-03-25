#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <shellapi.h>
#include "Tests.h"
#include "DynamicVector.h"
#include "Repository.h"
#include "Service.h"
#include "UI.h"
#define ShellExecute

int main()
{
	Repository repo = Repository();
	Service serv = Service(repo);
	Repository repoMovieList = Repository();
	Service moviePlaylist = Service(repoMovieList);
	UI ui = UI(serv, moviePlaylist);

	ui.start();
	Tests test;
	test = Tests();
	test.testAll();
}