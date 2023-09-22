#include "View.h"

// Foward declarations 
bool handleMainMenu(ListManager&, View& view);
void handleTaskMenu(ListManager&, View& view);
void handleListMenu(ListManager&, View& view);

using TaskAction = ListManager::TaskActions;
using ListAction = ListManager::ListActions;

enum class MainAction
{
	Add = 1,
	Select = 2,
	Quit = 3,
};

// Handle user input in the task menu (at the same time checking for incorrect user input)
void handleTaskMenu(ListManager& lists, View& view)
{
	int input{};
	int input2{}; // This variable is used to get the correct element to remove from the vector.

	do
	{
		std::cout << "1. Add a task.\n";
		std::cout << "2. Delete a task.\n";
		std::cout << "3. Go back\n";

		std::cin >> input;

		while (input != static_cast<int>(TaskAction::Add) && 
			   input != static_cast<int>(TaskAction::Delete) && 
			   input != static_cast<int>(TaskAction::Return))
		{
			std::cout << "Error, unknown command.\n";
			utility::handleIncorrectInput();
			std::cin >> input;
		}

		switch (input)
		{
		case static_cast<int>(TaskAction::Add):
			lists.addTask();
			utility::clearScreen();
			view.updateView(lists);
			break;

		case static_cast<int>(TaskAction::Delete):
			/*
			if (lists.isTaskEmpty())
			{
				std::cout << "< No tasks found in the list. >\n";
				return;
			}
			*/
			std::cout << "Enter the number of the task that you wish to remove : ";
			std::cin >> input2;

			while (input2 > lists.returnNumOfTasks())
			{
				std::cout << "Error, index out of range ! \n";
				std::cin >> input2;
			}

			lists.removeTask(input2);
			utility::clearScreen();
			view.updateView(lists);
			break;

		case static_cast<int>(TaskAction::Return):
			utility::clearScreen();
			view.updateView(lists);
			break;

		default:
			std::cout << "Error, unknown command.\n";
			utility::handleIncorrectInput();
		}

	} while (input != static_cast<int>(TaskAction::Return));

}

// Handle user input in the list menu (at the same time checking for incorrect user input)
void handleListMenu(ListManager& lists, View& view)
{
	int input{};

	do
	{
		std::cout << "1. Modify this list tasks.\n";
		std::cout << "2. Rename this list.\n";
		std::cout << "3. Delete this list.\n";
		std::cout << "4. Go back.\n";
		std::cin >> input;

		while (input != static_cast<int>(ListAction::Modify) && 
			   input != static_cast<int>(ListAction::Rename) && 
			   input != static_cast<int>(ListAction::Delete) &&
			   input != static_cast<int>(ListAction::Return))
		{
			std::cout << "Error, unknown command.\n";
			utility::handleIncorrectInput();
			std::cin >> input;
		}

		switch (input)
		{

		case static_cast<int>(ListAction::Modify):
			utility::clearScreen();
			view.updateView(lists);
			handleTaskMenu(lists, view);
			break;

		case static_cast<int>(ListAction::Rename):
			lists.setListName();
			utility::clearScreen();
			view.updateView(lists);
			break;

		case static_cast<int>(ListAction::Delete):
			lists.removeList();
			utility::clearScreen();
			view.updateView(lists);
			break;

		case static_cast<int>(ListAction::Return):
			utility::clearScreen();
			view.updateView(lists);
			break;

		}

	} while (input != static_cast<int>(ListAction::Return));
}

// Handle user input in the main menu (at the same time checking for incorrect user input)
bool handleMainMenu(ListManager& lists, View& view)
{
	int input{};

	// The program should terminate only if the user wants to quit.
	std::cout << "1. Add a list.\n";
	std::cout << "2. Select a list.\n";
	std::cout << "3. Quit.\n";

	std::cin >> input;

	while (input != static_cast<int>(MainAction::Add) && 
		   input != static_cast<int>(MainAction::Select) &&
		   input != static_cast<int>(MainAction::Quit))
	{
		std::cout << "Error, unknown command.\n";
		utility::handleIncorrectInput();
		std::cin >> input;
	}

	switch (input)
	{

	case static_cast<int>(MainAction::Add):
		lists.addList();
		utility::clearScreen();
		view.updateView(lists);
		return true;

	case static_cast<int>(MainAction::Select):
		if (lists.isEmpty())
		{
			std::cout << "< No list found. >\n";
			return true;
		}

		if (!(lists.listSelection())) // if the function returns nullptr, then we should return early, otherwise the user will work on a non existent list.
		{
			return true;
		}

		utility::clearScreen();
		view.updateView(lists);
		handleListMenu(lists, view);
		return true;

	case static_cast<int>(MainAction::Quit):
		return false;
	}
}

int main()
{
	std::cout << "==== Welcome to the to do list program ====\n";
	std::cout << "Choose one of the following (type 1, 2 or 3 based on your choice.) : \n";
	int res{};
	ListManager lists{};
	View view{};

	while (handleMainMenu(lists, view))
	{

	}

}
