#include <Location.h>
#include <raylib.h>

namespace testgame
{
    Location::Location(const LocationStruct& locationStruct, Vector2 screenSize)
    : locationImage(locationStruct.locationImage),
      locationDescription(locationStruct.locationDescription),
      descriptionFont(locationStruct.descriptionFont),
      forward(locationStruct.forward),
      backward(locationStruct.backward),
      left(locationStruct.left),
      right(locationStruct.right),
      screenWidth((int)screenSize.x),
      screenHeight((int)screenSize.y),
      textBox{screenWidth / 2.0f, 0, screenWidth / 2.0f, 800}
    {
        
    }

    Location::~Location()
    {
        UnloadTexture(locationImage);
    }

    Texture2D Location::getImage() const
    {
        return locationImage;
    }
    char* Location::getDescription() const
    {
        return (char*)locationDescription.c_str();
    }
    const Font Location::getDescriptionFont() const
    {
        return descriptionFont;
    }
    bool Location::isForward() const
    {
        return forward;
    }
    bool Location::isBackward() const
    {
        return backward;
    }
    bool Location::isLeft() const
    {
        return left;
    }
    bool Location::isRight() const
    {
        return right;
    }
    
    void Location::draw() const
    {
        ClearBackground(BLACK);
        DrawTexture(locationImage, 0, 0, WHITE);
        DrawRectangleLinesEx(textBox, 4, GRAY);
        DrawTextBoxed(locationDescription.c_str());
    }

    void Location::update(const LocationStruct& locationStruct)
    {
        this->locationImage = locationStruct.locationImage;
        this->locationDescription = locationStruct.locationDescription;
        this->descriptionFont = locationStruct.descriptionFont;
        this->forward = locationStruct.forward;
        this->backward = locationStruct.backward;
        this->left = locationStruct.left;
        this->right = locationStruct.right;
    }

    void Location::DrawTextBoxed(const char *text) const
    {
        // Draw text using descriptionFont inside textBoxtangle limits
        int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

        float textOffsetY = 0;          // Offset between lines (on line break '\n')
        float textOffsetX = 0.0f;       // Offset X to next character to draw

        float scaleFactor = fontSize / (float)descriptionFont.baseSize;     // Character textBoxtangle scaling factor

        // Word/character wrapping mechanism variables
        enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
        int state = wordWrap ? MEASURE_STATE : DRAW_STATE;

        int startLine = -1;         // Index where to begin drawing (where a line begins)
        int endLine = -1;           // Index where to stop drawing (where a line ends)
        int lastk = -1;             // Holds last value of the character position

        for (int i = 0, k = 0; i < length; i++, k++)
        {
            // Get next codepoint from byte string and glyph index in descriptionFont
            int codepointByteCount = 0;
            int codepoint = GetCodepoint(&text[i], &codepointByteCount);
            int index = GetGlyphIndex(descriptionFont, codepoint);

            // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
            // but we need to draw all of the bad bytes using the '?' symbol moving one byte
            if (codepoint == 0x3f) codepointByteCount = 1;
            i += (codepointByteCount - 1);

            float glyphWidth = 0;
            if (codepoint != '\n')
            {
                glyphWidth = (descriptionFont.glyphs[index].advanceX == 0) ? descriptionFont.glyphs[index].advanceX * scaleFactor : descriptionFont.glyphs[index].advanceX * scaleFactor;

                if (i + 1 < length) glyphWidth = glyphWidth + spacing;
            }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the textBox container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again textBoxursively until the end of the text (or until we get outside of the container)
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > (textBox.width - xOffset))
            {
                endLine = (endLine < 1) ? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (descriptionFont.baseSize + descriptionFont.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > (textBox.width - xOffset)))
                {
                    textOffsetY += (descriptionFont.baseSize + descriptionFont.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows textBoxtangle height limit, just stop drawing
                if ((textOffsetY + yOffset + descriptionFont.baseSize * scaleFactor) > textBox.height) break;

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    DrawTextCodepoint(descriptionFont, codepoint, (Vector2){ textBox.x + xOffset + textOffsetX, textBox.y + yOffset + textOffsetY }, fontSize, textColor);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (descriptionFont.baseSize + descriptionFont.baseSize / 2) * scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}

}