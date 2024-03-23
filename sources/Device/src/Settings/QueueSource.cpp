// 2024/03/23 17:08:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/QueueSource.h"


void QueueSource::Push(Source::E)
{

}


void QueueSource::Pop()
{

}


bool QueueSource::IsConsist(Source::E source) const
{
    for (int i = 0; i < size; i++)
    {
        if (buffer[i] == source)
        {
            return true;
        }
    }

    return false;
}



