#ifndef BUTTON_MGR_H
#define BUTTON_MGR_H

#include "Button.h"
#include <raylib.h>
#include <vector>

namespace testgame
{

    class ButtonMgr
    {
        public:
        ButtonMgr(Rectangle _buttonBox, Font buttonFont);
        virtual ~ButtonMgr();
        void update();
        void draw() const;
        
        bool isForwardButtonPressed() const { return forwardButtonPressed; }
        bool isBackButtonPressed() const { return backButtonPressed; }
        bool isLeftButtonPressed() const { return leftButtonPressed; }
        bool isRightButtonPressed() const { return rightButtonPressed; }
        bool isExamineButtonPressed() const { return examineButtonPressed; }
        bool isSpeakButtonPressed() const { return speakButtonPressed; }
                
        private:

        bool forwardButtonPressed = false;
        bool backButtonPressed = false;
        bool leftButtonPressed = false;
        bool rightButtonPressed = false;
        bool examineButtonPressed = false;
        bool speakButtonPressed = false;
        
        Rectangle buttonBox;
        Font buttonFont;
        std::vector<Button> buttons;

        ButtonState leftMouseButtonState = NORMAL; 
        ButtonState rightMouseButtonState = NORMAL;
    };
}


#endif /* BUTTON_MGR_H */
