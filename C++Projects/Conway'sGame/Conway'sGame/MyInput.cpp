#include "stdafx.h"
#include "MyInput.h"
#include "MyLog.h"

void MyInput::set_is_click(bool value)
{
    if (value)
    {
        MyLog::get_instance().LogToConsole("Click.");
    }
    is_click_ = value;
}

void MyInput::set_is_drag(bool value)
{
    if (value)
    {
        MyLog::get_instance().LogToConsole("Drag Started.");
    }
    else
    {
        MyLog::get_instance().LogToConsole("Drag Finished.");
    }
    is_drag_ = value;

}
