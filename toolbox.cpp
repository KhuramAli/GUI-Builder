#include "toolbox.h"

ToolBox::ToolBox()
{
        this->setWindowTitle("Tool Box");
        toolBoxLayout->addWidget(button1);
        controlWidget->setLayout(toolBoxLayout);
        this->setWidget(controlWidget);



}


