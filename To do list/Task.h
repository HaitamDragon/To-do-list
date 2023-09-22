#ifndef TASK_H
#define TASK_H

#include <string_view>
#include <string>

class Task
{
private:
    std::string m_description;

public:

    Task(std::string_view description) : m_description{ description }
    {

    }

    std::string_view getDescription() const
    {
        return m_description;
    }

};

#endif
