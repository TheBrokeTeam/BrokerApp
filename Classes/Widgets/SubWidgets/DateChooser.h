//
// Created by Maykon Meneghel on 22/01/22.
// Powered by Flix01 in https://github.com/Flix01/imgui
//

#ifndef BROKERAPP_DATECHOOSER_H
#define BROKERAPP_DATECHOOSER_H

#ifndef IMGUI_API
#include <imgui.h>
#endif //IMGUI_API

// USAGE
/*
#include "DatePicker.h"
//#include <time.h>   // mandatory when implementing ImGui::TestDateChooser() yourself in your code

// inside a ImGui::Window:
ImGui::TestDateChooser();
*/

struct tm;  // defined in <time.h>

namespace ImGui {

// Some example of date formats: "%d/%m/%Y" "%A %d %b %Y"
    IMGUI_API bool DateChooser(const char* label,tm& dateOut,const char* dateFormat="%d/%m/%Y",bool closeWhenMouseLeavesIt=true,bool* pSetStartDateToDateOutThisFrame=NULL,const char* leftArrow="<",const char* rightArrow=">",const char* upArrowString="   ^   ",const char* downArrowString="   v   ");
// Some helper methods (note that I cannot use tm directly in this hader file, so we can't initialize a static date directly with these methods)
    IMGUI_API void SetDateZero(tm* date);
    IMGUI_API void SetDateToday(tm* date);
    IMGUI_API long GetTimestamp(tm date, bool resetHours);
    IMGUI_API size_t DateToString(tm& d,char* buf, size_t bufferSize);
    IMGUI_API void TestDateChooser(const char* dateFormat="%d/%m/%Y",bool closeWhenMouseLeavesIt=true,const char* leftArrow="<",const char* rightArrow=">",const char* upArrowString="   ^   ",const char* downArrowString="   v   ");


} // namespace ImGui


#endif //BROKERAPP_DATECHOOSER_H
