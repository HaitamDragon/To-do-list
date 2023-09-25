#ifndef MODEL_H
#define MODEL_H

#include <string_view>
#include <string>
#include <vector>
#include "Utility.h"

class Task
{
private:
    std::string m_description;
    unsigned int ID{ nextID() };

public:

    Task(std::string_view description) : m_description{ description }
    {

    }

    std::string_view getDescription() const
    {
        return m_description;
    }

    static unsigned int nextID()
    {
        static unsigned int counter{ 1 };
        return counter++;
    }

    int getID() const
    {
        return ID;
    }
};

class List
{
    std::string m_name;
    const char* m_dateOfCreation{ utility::getTime() };
    std::vector<Task> m_tasks;
    unsigned int ID{ nextID() };

public:

    List(std::string_view name) : m_name {name}
    {

    }

    static unsigned int nextID()
    {
        static unsigned int counter{ 1 };
        return counter++;
    }

    std::string_view getName() const
    {
        return m_name;
    }

    const char* getCreationDate() const
    {
        return m_dateOfCreation;
    }

    void setListName(std::string_view name)
    {
        m_name = name;
    }
    
    bool isTaskEmpty()
    {
        return m_tasks.empty();
    }

    void addTask(std::string_view name)
    {
        m_tasks.push_back(name);
    }
    
    void removeTask(int taskID)
    {
        m_tasks.erase(m_tasks.begin() + taskID - 1); // vector elements start from zero, the view will output task numbers from 1
    }
    
    void printTasks() const
    {
        for (const auto& task : m_tasks)
        {
            std::cout << task.getID() << ". " << task.getDescription() << '\n';
        }
    }

    int getID() const
    {
        return ID;
    }

    std::vector<Task>& getTasks()
    {
        return m_tasks;
    }

    // search for the task ID based on the value that the user provided. If the task doesn't exist, return -1 instead.

    int getTaskID(int taskID)
    {

        for (const auto& task : m_tasks)
        {
            if (task.getID() == taskID)
            {
                return task.getID();
            }
        }

        return -1; 
    }
};


#endif
