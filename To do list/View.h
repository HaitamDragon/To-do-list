#ifndef VIEW_H
#define VIEW_H

#include "ListManager.h"

class View
{

public:

    void updateView(ListManager& lists)
    {

        for (auto& list : lists.getLists())
        {
            int j{ 1 };
            std::cout << "------------------\n";
            std::cout << list.m_name << "\t\t  [created at] " << utility::getTime() << '\n';

            for (auto& task : list.m_tasks)
            {
                std::cout << j++ << ". " << task.getDescription() << '\n';
            }

            std::cout << "------------------\n\n\n\n\n";
        }

    }
};

#endif
