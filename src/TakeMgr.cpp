#include <TakeMgr.h>
#include <SceneLoader.h>
#include <algorithm>

namespace testgame
{

namespace
{
    const Color kPanelFill = {28, 26, 34, 255};
    const Color kPanelBorder = {168, 138, 72, 255};
    const Color kPanelAccent = {96, 78, 48, 255};
    const Color kSectionLabel = {132, 122, 104, 255};
    const Color kScrollTrack = {48, 44, 56, 255};
    const Color kScrollThumb = {140, 118, 72, 255};
    const Color kScrollThumbHover = {168, 142, 88, 255};
    const Color kSlotFill = {40, 38, 50, 255};
    const Color kSlotHover = {54, 50, 64, 255};
    const Color kCloseHover = {210, 178, 108, 255};
    const Color kTakeAllFill = {54, 50, 64, 255};
    const Color kTakeAllHover = {72, 64, 82, 255};
    const Color kTakeAllText = {228, 220, 198, 255};
}

const float TakeMgr::kScrollbarWidth = 16.0f;
const float TakeMgr::kCloseButtonSize = 28.0f;
const float TakeMgr::kItemSlotSize = 76.0f;
const float TakeMgr::kItemGap = 12.0f;
const float TakeMgr::kTakeAllButtonHeight = 44.0f;

TakeMgr::TakeMgr() = default;

TakeMgr::~TakeMgr()
{
    unloadItemTextures();
}

void TakeMgr::unloadItemTextures()
{
    for (TakeableItem& item : items)
    {
        if (item.icon.id != 0)
            UnloadTexture(item.icon);
        item.icon = Texture2D{};
    }
}

void TakeMgr::setPanelBounds(Rectangle bounds)
{
    panelBounds = bounds;
}

void TakeMgr::setFont(Font font)
{
    panelFont = font;
}

void TakeMgr::setAssetRoots(
    const std::string& primaryRoot,
    const std::string& fallbackRoot)
{
    primaryAssetRoot = primaryRoot;
    fallbackAssetRoot = fallbackRoot;
}

bool TakeMgr::loadItemTexture(const std::string& relativePath, Texture2D& outTexture) const
{
    if (relativePath.empty())
        return false;

    const std::string fullPath = std::string("resources/") + relativePath;

    if (loadResourceTexture(primaryAssetRoot, fullPath, outTexture))
        return true;

    if (fallbackAssetRoot != primaryAssetRoot &&
        loadResourceTexture(fallbackAssetRoot, fullPath, outTexture))
    {
        return true;
    }

    return false;
}

void TakeMgr::loadItemTextures()
{
    for (TakeableItem& item : items)
    {
        if (item.icon.id != 0)
        {
            UnloadTexture(item.icon);
            item.icon = Texture2D{};
        }

        if (!item.iconPath.empty() && loadItemTexture(item.iconPath, item.icon))
            SetTextureFilter(item.icon, TEXTURE_FILTER_BILINEAR);
    }
}

void TakeMgr::setTakeables(const std::vector<TakeableItem>& takeables)
{
    unloadItemTextures();
    items = takeables;
    loadItemTextures();
    scrollY = 0.0f;
}

void TakeMgr::open()
{
    isPanelOpen = true;
    scrollY = 0.0f;
    clickedItemId.clear();
    takeAllClicked = false;
}

void TakeMgr::close()
{
    isPanelOpen = false;
    scrollY = 0.0f;
    clickedItemId.clear();
    takeAllClicked = false;
}

void TakeMgr::removeTakeable(const std::string& id)
{
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        if (it->id == id)
        {
            if (it->icon.id != 0)
                UnloadTexture(it->icon);
            items.erase(it);
            return;
        }
    }
}

std::string TakeMgr::consumeClickedItemId()
{
    const std::string id = clickedItemId;
    clickedItemId.clear();
    return id;
}

bool TakeMgr::consumeTakeAllClick()
{
    const bool clicked = takeAllClicked;
    takeAllClicked = false;
    return clicked;
}

Rectangle TakeMgr::getCloseButtonBounds() const
{
    const float pad = 14.0f;
    return {
        panelBounds.x + panelBounds.width - pad - kCloseButtonSize,
        panelBounds.y + pad,
        kCloseButtonSize,
        kCloseButtonSize
    };
}

Rectangle TakeMgr::getTakeAllButtonBounds() const
{
    const float pad = 14.0f;
    return {
        panelBounds.x + pad,
        panelBounds.y + panelBounds.height - pad - kTakeAllButtonHeight,
        panelBounds.width - pad * 2.0f - kScrollbarWidth - 4.0f,
        kTakeAllButtonHeight
    };
}

float TakeMgr::getContentVisibleHeight() const
{
    const float pad = 14.0f;
    const float headerHeight = 28.0f;
    const float footerGap = 10.0f;
    return panelBounds.height - pad * 2.0f - headerHeight - kTakeAllButtonHeight - footerGap;
}

void TakeMgr::handleCloseButtonInput()
{
    const Rectangle closeBounds = getCloseButtonBounds();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), closeBounds))
    {
        close();
    }
}

void TakeMgr::handleTakeAllInput()
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;

    const Rectangle takeAllBounds = getTakeAllButtonBounds();
    if (CheckCollisionPointRec(GetMousePosition(), takeAllBounds) && !items.empty())
        takeAllClicked = true;
}

void TakeMgr::handleItemGridInput()
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;

    const Vector2 mousePos = GetMousePosition();
    for (size_t i = 0; i < itemSlotBounds.size(); ++i)
    {
        if (i >= items.size())
            break;

        if (CheckCollisionPointRec(mousePos, itemSlotBounds[i]))
        {
            clickedItemId = items[i].id;
            return;
        }
    }
}

void TakeMgr::handleScrollInput()
{
    if (!isPanelOpen)
        return;

    const float pad = 14.0f;
    const float headerHeight = 28.0f;
    const float visibleHeight = getContentVisibleHeight();
    const float maxScroll = std::max(0.0f, contentHeight - visibleHeight);
    const float lineHeight = 24.0f;
    const float contentY = panelBounds.y + pad + headerHeight;

    const Rectangle scrollTrack = {
        panelBounds.x + panelBounds.width - kScrollbarWidth - pad,
        contentY,
        kScrollbarWidth,
        visibleHeight
    };

    const float thumbHeight = (contentHeight <= 0.0f)
        ? visibleHeight
        : std::max(24.0f, visibleHeight * (visibleHeight / contentHeight));
    const float thumbTravel = std::max(0.0f, visibleHeight - thumbHeight);
    const float thumbY = scrollTrack.y + (maxScroll > 0.0f
        ? (scrollY / maxScroll) * thumbTravel
        : 0.0f);

    const Rectangle scrollThumb = {
        scrollTrack.x + 2.0f,
        thumbY,
        scrollTrack.width - 4.0f,
        thumbHeight
    };

    const Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mousePos, scrollThumb))
        {
            scrollbarDragging = true;
            scrollbarDragOffsetY = mousePos.y - scrollThumb.y;
        }
        else if (CheckCollisionPointRec(mousePos, scrollTrack) && thumbTravel > 0.0f)
        {
            scrollY = ((mousePos.y - scrollTrack.y - thumbHeight * 0.5f) / thumbTravel) * maxScroll;
        }
    }

    if (scrollbarDragging)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && thumbTravel > 0.0f)
            scrollY = ((mousePos.y - scrollTrack.y - scrollbarDragOffsetY) / thumbTravel) * maxScroll;
        else
            scrollbarDragging = false;
    }

    const Rectangle scrollArea = {
        panelBounds.x + pad,
        contentY,
        panelBounds.width - pad * 2.0f - kScrollbarWidth - 4.0f,
        visibleHeight
    };

    if (CheckCollisionPointRec(mousePos, scrollArea))
        scrollY -= GetMouseWheelMove() * lineHeight * 2.0f;

    scrollY = std::max(0.0f, std::min(scrollY, maxScroll));
}

void TakeMgr::layoutItemSlots()
{
    const float pad = 14.0f;
    const float headerHeight = 28.0f;
    const float contentX = panelBounds.x + pad;
    const float contentY = panelBounds.y + pad + headerHeight;
    const float contentW = panelBounds.width - pad * 2.0f - kScrollbarWidth - 4.0f;

    const int columns = std::max(1, (int)((contentW + kItemGap) / (kItemSlotSize + kItemGap)));
    const int rows = (int)items.size() / columns + ((int)items.size() % columns > 0 ? 1 : 0);
    contentHeight = rows > 0
        ? rows * kItemSlotSize + (rows - 1) * kItemGap
        : 0.0f;

    itemSlotBounds.clear();
    itemSlotBounds.reserve(items.size());

    for (size_t i = 0; i < items.size(); ++i)
    {
        const int col = (int)i % columns;
        const int row = (int)i / columns;
        itemSlotBounds.push_back({
            contentX + col * (kItemSlotSize + kItemGap),
            contentY + row * (kItemSlotSize + kItemGap),
            kItemSlotSize,
            kItemSlotSize
        });
    }
}

void TakeMgr::update()
{
    if (!isPanelOpen)
        return;

    layoutItemSlots();
    handleCloseButtonInput();
    handleItemGridInput();
    handleTakeAllInput();
    handleScrollInput();
}

void TakeMgr::drawCloseButton() const
{
    const Rectangle closeBounds = getCloseButtonBounds();
    const bool hovered = CheckCollisionPointRec(GetMousePosition(), closeBounds);
    const Color lineColor = hovered ? kCloseHover : kSectionLabel;

    DrawLineEx(
        { closeBounds.x + 8.0f, closeBounds.y + 8.0f },
        { closeBounds.x + closeBounds.width - 8.0f, closeBounds.y + closeBounds.height - 8.0f },
        2.0f,
        lineColor);
    DrawLineEx(
        { closeBounds.x + closeBounds.width - 8.0f, closeBounds.y + 8.0f },
        { closeBounds.x + 8.0f, closeBounds.y + closeBounds.height - 8.0f },
        2.0f,
        lineColor);
}

void TakeMgr::drawItemGrid() const
{
    const float pad = 14.0f;
    const float headerHeight = 28.0f;
    const float contentX = panelBounds.x + pad;
    const float contentY = panelBounds.y + pad + headerHeight;
    const float contentW = panelBounds.width - pad * 2.0f - kScrollbarWidth - 4.0f;
    const float visibleHeight = getContentVisibleHeight();

    const float borderPad = 3.0f;
    BeginScissorMode(
        (int)(contentX - borderPad),
        (int)(contentY - borderPad),
        (int)(contentW + borderPad * 2.0f),
        (int)(visibleHeight + borderPad * 2.0f));

    for (size_t i = 0; i < items.size() && i < itemSlotBounds.size(); ++i)
    {
        Rectangle slot = itemSlotBounds[i];
        slot.y -= scrollY;

        if (slot.y + kItemSlotSize < contentY || slot.y > contentY + visibleHeight)
            continue;

        const bool hovered = CheckCollisionPointRec(GetMousePosition(), slot);
        const Color fill = hovered ? kSlotHover : kSlotFill;

        DrawRectangleRounded(slot, 0.18f, 8, fill);

        if (items[i].icon.id != 0)
        {
            const float iconPad = 10.0f;
            const Rectangle iconArea = {
                slot.x + iconPad,
                slot.y + iconPad,
                slot.width - iconPad * 2.0f,
                slot.height - iconPad * 2.0f
            };
            DrawTexturePro(
                items[i].icon,
                { 0.0f, 0.0f, (float)items[i].icon.width, (float)items[i].icon.height },
                iconArea,
                { 0.0f, 0.0f },
                0.0f,
                WHITE);
        }
        else
        {
            const float labelSize = 13.0f;
            const Vector2 textSize = MeasureTextEx(panelFont, items[i].name.c_str(), labelSize, 1);
            DrawTextEx(
                panelFont,
                items[i].name.c_str(),
                {
                    slot.x + (slot.width - textSize.x) * 0.5f,
                    slot.y + (slot.height - textSize.y) * 0.5f
                },
                labelSize,
                1,
                kTakeAllText);
        }
    }

    EndScissorMode();

    for (size_t i = 0; i < items.size() && i < itemSlotBounds.size(); ++i)
    {
        Rectangle slot = itemSlotBounds[i];
        slot.y -= scrollY;

        if (slot.y + kItemSlotSize < contentY || slot.y > contentY + visibleHeight)
            continue;

        DrawRectangleRoundedLines(slot, 0.18f, 8, 2.0f, kPanelAccent);
    }
}

void TakeMgr::drawScrollbar() const
{
    const float visibleHeight = getContentVisibleHeight();
    const float maxScroll = std::max(0.0f, contentHeight - visibleHeight);
    if (maxScroll <= 0.0f)
        return;

    const float pad = 14.0f;
    const float headerHeight = 28.0f;
    const float contentY = panelBounds.y + pad + headerHeight;

    const Rectangle scrollTrack = {
        panelBounds.x + panelBounds.width - kScrollbarWidth - pad,
        contentY,
        kScrollbarWidth,
        visibleHeight
    };

    DrawRectangleRec(scrollTrack, kScrollTrack);

    const float thumbHeight = std::max(24.0f, visibleHeight * (visibleHeight / contentHeight));
    const float thumbTravel = std::max(0.0f, visibleHeight - thumbHeight);
    const float thumbY = scrollTrack.y + (scrollY / maxScroll) * thumbTravel;

    const Rectangle scrollThumb = {
        scrollTrack.x + 2.0f,
        thumbY,
        scrollTrack.width - 4.0f,
        thumbHeight
    };

    const bool thumbHovered = CheckCollisionPointRec(GetMousePosition(), scrollThumb);
    DrawRectangleRounded(scrollThumb, 0.4f, 6, thumbHovered ? kScrollThumbHover : kScrollThumb);
}

void TakeMgr::drawTakeAllButton() const
{
    const Rectangle bounds = getTakeAllButtonBounds();
    const bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);
    const bool enabled = !items.empty();
    const Color fill = enabled ? (hovered ? kTakeAllHover : kTakeAllFill) : kSlotFill;
    const Color border = enabled ? kPanelBorder : kPanelAccent;
    const Color textColor = enabled ? kTakeAllText : kSectionLabel;

    DrawRectangleRounded(bounds, 0.18f, 8, fill);
    DrawRectangleRoundedLines(bounds, 0.18f, 8, 2.0f, border);

    const char* label = "Take All";
    const float labelSize = 16.0f;
    const Vector2 textSize = MeasureTextEx(panelFont, label, labelSize, 1);
    DrawTextEx(
        panelFont,
        label,
        {
            bounds.x + (bounds.width - textSize.x) * 0.5f,
            bounds.y + (bounds.height - textSize.y) * 0.5f
        },
        labelSize,
        1,
        textColor);
}

void TakeMgr::draw() const
{
    if (!isPanelOpen)
        return;

    DrawRectangleRounded(panelBounds, 0.04f, 10, kPanelFill);
    DrawRectangleRoundedLines(panelBounds, 0.04f, 10, 3.0f, kPanelBorder);

    Rectangle accentBar = {
        panelBounds.x + 8.0f,
        panelBounds.y + 8.0f,
        panelBounds.width - 16.0f,
        4.0f
    };
    DrawRectangleRounded(accentBar, 1.0f, 4, kPanelAccent);

    const float pad = 14.0f;
    DrawTextEx(panelFont, "TAKE", { panelBounds.x + pad, panelBounds.y + pad }, 15.0f, 1, kSectionLabel);

    drawCloseButton();
    drawItemGrid();
    drawScrollbar();
    drawTakeAllButton();
}

}