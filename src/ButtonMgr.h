#ifndef BUTTON_MGR_H
#define BUTTON_MGR_H

#include <raylib.h>

namespace testgame
{
    class ButtonMgr
    {
        public:
        ButtonMgr(Rectangle _buttonBox, Font buttonFont);
        virtual ~ButtonMgr();
        void draw() const;
        private:
        Rectangle buttonBox;
        Font buttonFont;
    };
}


#endif /* BUTTON_MGR_H */
