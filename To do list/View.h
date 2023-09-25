#ifndef VIEW_H
#define VIEW_H

#include "Controller.h"

enum class ListActions
{
    Modify = 1,
    Rename = 2,
    Delete = 3,
    Return = 4,
};

enum class TaskActions
{
    Add = 1,
    Delete = 2,
    Return = 3,
};

enum class MainActions
{
    Add = 1,
    Select = 2,
    Quit = 3,
};

class View
{

public:
	
    void updateView(Controller& lists)
    {
		std::cout << "------------------\n";
		lists.printLists();
        std::cout << "------------------\n\n\n\n\n";
    }

	// Handle user input in the task menu (at the same time checking for incorrect user input)
	void handleTaskMenu(Controller& lists, int listID)
	{
		int input{};
		int input2{}; // This variable is used to get the correct element to remove from the vector.
		int taskID{};

		do
		{
			std::cout << "1. Add a task.\n";
			std::cout << "2. Delete a task.\n";
			std::cout << "3. Go back\n";

			std::cin >> input;

			while (input != static_cast<int>(TaskActions::Add) &&
				input != static_cast<int>(TaskActions::Delete) &&
				input != static_cast<int>(TaskActions::Return))
			{
				std::cout << "Error, unknown command.\n";
				utility::handleIncorrectInput();
				std::cin >> input;
			}

			switch (input)
			{
				case static_cast<int>(TaskActions::Add):
				{

					std::string task{};
					std::cout << "Enter a task : ";
					std::cin >> task;

					lists.addTaskInList(listID, task);
					utility::clearScreen();
					updateView(lists);
					break;
				}
				case static_cast<int>(TaskActions::Delete):
				{
					
					if (lists.isTaskEmpty(listID))
					{
						std::cout << "< No tasks found in the list. >\n";
						return;
					}
					
					std::cout << "Enter the number of the task that you wish to remove : ";
					std::cin >> input2;

					taskID = lists.getList(listID).getTaskID(input2);

					while (taskID == -1) // retry if the user provided with taskID that doesn't exist, or with an incorrect input.
					{
						std::cout << "Error, index out of range ! \n";
						utility::handleIncorrectInput();
						std::cin >> input2;
						taskID = lists.getList(listID).getTaskID(input2);
					}

					lists.removeTaskInList(listID, taskID);
					utility::clearScreen();
					updateView(lists);
					break;
				}
				case static_cast<int>(TaskActions::Return):
				{
					utility::clearScreen();
					updateView(lists);
					break;
				}
			}

		} while (input != static_cast<int>(TaskActions::Return));
	}

	// Handle user input in the list menu (at the same time checking for incorrect user input)
	void handleListMenu(Controller& lists, int listID)
	{
		int input{};

		do
		{
			std::cout << "1. Modify this list tasks.\n";
			std::cout << "2. Rename this list.\n";
			std::cout << "3. Delete this list.\n";
			std::cout << "4. Go back.\n";
			std::cin >> input;

			while (input != static_cast<int>(ListActions::Modify) &&
				input != static_cast<int>(ListActions::Rename) &&
				input != static_cast<int>(ListActions::Delete) &&
				input != static_cast<int>(ListActions::Return))
			{
				std::cout << "Error, unknown command.\n";
				utility::handleIncorrectInput();
				std::cin >> input;
			}

			switch (input)
			{

				case static_cast<int>(ListActions::Modify):
				{
					utility::clearScreen();
					updateView(lists);
					handleTaskMenu(lists, listID);
					break;
				}
				case static_cast<int>(ListActions::Rename):
				{

					std::string name;
					std::cout << "Enter a new name for the list : ";
					std::cin >> name;

					lists.setNewListName(listID, name);
					utility::clearScreen();
					updateView(lists);
					break;
				}

				case static_cast<int>(ListActions::Delete):
				{

					std::string name{};
					std::cout << "Enter the name of the list : \n";
					std::cin >> name;

					lists.removeList(listID);
					utility::clearScreen();
					updateView(lists);
					break;

				}

				case static_cast<int>(ListActions::Return):
				{
					utility::clearScreen();
					updateView(lists);
					break;
				}
			}

		} while (input != static_cast<int>(ListActions::Return));
	}

	// Handle user input in the main menu (at the same time checking for incorrect user input)
	bool handleMainMenu(Controller& lists)
	{
		int input{};
		int listID{};

		// The program should terminate only if the user wants to quit.
		std::cout << "1. Add a list.\n";
		std::cout << "2. Select a list.\n";
		std::cout << "3. Quit.\n";

		std::cin >> input;

		while (input != static_cast<int>(MainActions::Add) &&
			input != static_cast<int>(MainActions::Select) &&
			input != static_cast<int>(MainActions::Quit))
		{
			std::cout << "Error, unknown command.\n";
			utility::handleIncorrectInput();
			std::cin >> input;
		}

		switch (input)
		{
			case static_cast<int>(MainActions::Add):
			{
				std::string name;
				std::cout << "Enter the name of the list : \n";
				std::cin >> name;

				lists.addList(name);
				utility::clearScreen();
				updateView(lists);
				return true;
			}

			case static_cast<int>(MainActions::Select):
			{
				if (lists.isEmpty())
				{
					std::cout << "< No list found. >\n";
					return true;
				}

				std::cout << "Enter the name of the list to select : ";
				std::string input2;
				std::cin >> input2;

				listID = lists.getListID(input2);

				if (listID == -1) // check if the ID exists first.
				{
					std::cout << "Cannot find the list name !\n";
					return true;
				}

				utility::clearScreen();
				updateView(lists);
				handleListMenu(lists, listID);
				return true;
			}
			case static_cast<int>(MainActions::Quit):
			{
				return false;
			}
		}
	}

	void run()
	{
		std::cout << "==== Welcome to the to do list program ====\n";
		std::cout << "Choose one of the following (type 1, 2 or 3 based on your choice.) : \n";
		Controller lists{};

		while (handleMainMenu(lists))
		{

		}

	}

};

#endif
