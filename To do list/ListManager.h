#ifndef LISTMANAGER
#define LISTMANAGER

#include <vector>
#include "Task.h"
#include "Utility.h"

struct List
{
    std::string m_name;
    const char* m_dateOfCreation{ utility::getTime() };
    std::vector<Task> m_tasks; // keeps track of the number of tasks in a list
};

class ListManager
{
private:
    std::vector<List> m_lists; // keeps track of the lists.
    List* ptr{ nullptr }; // This pointer will point into of the elements of the vector of lists.

public:

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

    bool isEmpty()
    {
        return m_lists.empty();
    }

    /*
    bool isTaskEmpty()
    {
        return (*ptr).m_tasks.empty();
    }
    */

    void addList()
    {
        std::string name{};
        std::cout << "Enter the name of the list : \n";
        std::cin >> name;
        m_lists.push_back(List{ name });
    }

    void removeList()
    {
        m_lists.erase(m_lists.begin() + getIndexOfList(ptr->m_name));
    }

    void addTask()
    {
        std::string task{};
        std::cout << "Enter a task : ";
        std::cin >> task;
        ptr->m_tasks.push_back(Task{ task });
    }

    void removeTask(int res)
    {
        ptr->m_tasks.erase(ptr->m_tasks.begin() + res - 1);
    }

    // get the size of the m_tasks vector, 
    // will be used to check if the index that the user gave is within the vector size.
    int returnNumOfTasks()
    {
        return static_cast<int>(ptr->m_tasks.size());
    }

    // return the index of the selected list element ( based on the name ).
    int getIndexOfList(const std::string_view str)
    {
        for (int i{ 0 }; i <= static_cast<int>(m_lists.size()); ++i)
        {
            if (m_lists[i].m_name == str)
            {
                return i;
            }
        }
    }

    void setListName()
    {
        std::cout << "Enter a new name for the list : ";
        std::cin >> ptr->m_name;
    }

    /*
    List& getList(int index)
    {
        return m_lists.at(index);
    }
    */

    std::size_t getSize() const
    {
        return m_lists.size();
    }


    const std::vector<List> getLists()
    {
        return m_lists;
    }


    // Updating the console
    // Return the element of the list ( selected by the user ), if not found, return nullptr instead.
    // I tried to use reference, but references can't be null.
    // I'll admit I don't like how I wrote this function, couldn't figure out a better way.
    List* listSelection()
    {
        std::cout << "Enter the name of the list to select it : ";
        std::string res{};
        std::cin >> res;

        for (auto& target : m_lists)
        {
            if (target.m_name == res)
            {
                ptr = &target;
                return ptr;
            }
        }

        std::cout << "Error, cannot find the list name !\n";
        return nullptr;
    }
};

#endif
