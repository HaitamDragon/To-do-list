#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"

class Controller
{

private:
    std::vector<List> m_lists; // keeps track of the lists.
    
public:
    
    void addList(std::string_view name)
    {    
        m_lists.push_back(name);
    }
    
    void removeList(int listID)
    {
        m_lists.erase(m_lists.begin() + listID - 1); // vector elements start from zero, list IDs start from 1, 
                                                     // -1 is the offset to take account the elements starting from zero. 
    }

    void addTaskInList(int listID, std::string_view name)
    {
        auto& list = getList(listID);
        list.addTask(name);
    }

    void removeTaskInList(int listID, int taskID)
    {
        auto& list = getList(listID);
        list.removeTask(taskID);
    }

    void setNewListName(int listID, std::string_view name)
    {
        auto& list = getList(listID);
        list.setListName(name);
    }
    
    bool isEmpty()
    {
        return m_lists.empty();
    }

    bool isTaskEmpty(int listID)
    {
        auto& tasks = getList(listID).getTasks();
        return tasks.empty();
    }

    // search for the list ID based on the name that the user provided. If the list doesn't exist, return -1 instead.
    int getListID(std::string_view input)  
    {
        for (auto& list : m_lists)
        {
            if (list.getName() == input)
            {
                return list.getID();
            }
        }

        return -1; 
    }

    List& getList(int listID)
    {
        return m_lists.at(listID - 1); // vector elements start from 0, but listID start from 1, -1 is an offset to take account for the vector element.
    }

    void printLists()
    {
        for (const auto& list : m_lists)
        {
            std::cout << list.getName() << "Created at " << utility::getTime() << '\n';
            list.printTasks();
        }
    }

};

#endif
