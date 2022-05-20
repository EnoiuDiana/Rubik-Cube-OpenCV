// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <map>
#include <queue>
#include <random>
#include <math.h>
#include <fstream>
#include "Headers.h"
#include "RubikCubeIdentifier.h"


int main()
{
	int op;
	RubikCubeIdentifier rubikCubeIdentifier = RubikCubeIdentifier();
	do
	{
		system("cls");
		destroyAllWindows();
		printf("Menu:\n");
		printf(" 1 - Identify rubik cube by using 6 pictures with one face\n");
		printf(" 2 - Identify rubik cube by using 3 pictures with two faces\n");
		printf(" 3 - Identify spectrum of colors\n");
		printf(" 0 - Exit\n\n");
		printf("Option: ");
		scanf("%d",&op);
		switch (op)
		{
			case 1:
				rubikCubeIdentifier.callRubikCubeIdentifierUsingOneFace();
				break;
			case 2:
				rubikCubeIdentifier.callRubikCubeIdentifierUsingTwoFaces();
				break;
			case 3:
				rubikCubeIdentifier.identifySpectrumOfColors();
				break;
		}
	}
	while (op!=0);

	return 0;
}