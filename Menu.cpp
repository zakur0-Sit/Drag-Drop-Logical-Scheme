#include "Menu.h"

MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("futurbold.ttf"))
	{

	}

	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color(255, 234, 89));
	mainMenu[0].setString("Start");
	mainMenu[0].setCharacterSize(40);
	mainMenu[0].setPosition(900, 225);

	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color(150, 50, 250));
	mainMenu[1].setString("Info");
	mainMenu[1].setCharacterSize(40);
	mainMenu[1].setPosition(900, 350);

	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color(150, 50, 250));
	mainMenu[2].setString("Song");
	mainMenu[2].setCharacterSize(40);
	mainMenu[2].setPosition(900, 475);

	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(Color(150, 50, 250));
	mainMenu[3].setString("Exit");
	mainMenu[3].setCharacterSize(40);
	mainMenu[3].setPosition(900, 625);

	MainMenuSelected = 0;

}
MainMenu::~MainMenu()
{

}
void MainMenu::draw(RenderWindow& window)
{
	for (int i = 0; i < Max_main_menu; i++)
		window.draw(mainMenu[i]);
}

void MainMenu::MoveUp()
{
	if (MainMenuSelected - 1 >= 0)
	{
		mainMenu[MainMenuSelected].setFillColor(Color(150, 50, 250));
		MainMenuSelected--;
		mainMenu[MainMenuSelected].setFillColor(Color(255, 234, 89));
	}
}

void MainMenu::MoveDown()
{
	if (MainMenuSelected + 1 < Max_main_menu)
	{
		mainMenu[MainMenuSelected].setFillColor(Color(150, 50, 250));
		MainMenuSelected++;
		mainMenu[MainMenuSelected].setFillColor(Color(255, 234, 89));
	}
}