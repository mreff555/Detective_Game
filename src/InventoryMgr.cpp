#include <InventoryMgr.h>
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
    const Color kSlotSelected = {62, 52, 34, 255};
    const Color kCloseHover = {210, 178, 108, 255};
    const Color kLeatherDeep = {42, 26, 16, 255};
    const Color kLeatherDark = {62, 38, 22, 255};
    const Color kLeatherMid = {92, 58, 34, 255};
    const Color kLeatherLight = {128, 84, 50, 255};
    const Color kLeatherHighlight = {168, 118, 72, 180};
    const Color kLeatherGrain = {74, 48, 30, 90};
    const Color kStitch = {186, 158, 108, 255};
    const Color kBrass = {156, 124, 62, 255};
    const Color kBrassHighlight = {214, 186, 118, 255};
    const Color kBillFace = {196, 188, 158, 255};
    const Color kBillEdge = {148, 162, 118, 255};
    const Color kBillShadow = {88, 78, 54, 255};
    const Color kPaperSlip = {220, 210, 186, 255};
    const Color kNoirShadow = {14, 12, 18, 220};
    const Color kAmberGlow = {168, 118, 58, 40};

    void drawLeatherGrain(Rectangle area, float roundness, Color base, Color highlight, Color shadow)
    {
        DrawRectangleRounded(area, roundness, 10, base);

        const int startY = (int)area.y;
        const int endY = (int)(area.y + area.height);
        for (int y = startY + 2; y < endY - 2; y += 2)
        {
            const float t = (float)(y - startY) / area.height;
            Color grain = kLeatherGrain;
            grain.a = (unsigned char)(50 + (int)(t * 40.0f));
            DrawLineEx(
                { area.x + 4.0f, (float)y },
                { area.x + area.width - 4.0f, (float)y },
                1.0f,
                grain);
        }

        DrawRectangleRoundedLines(area, roundness, 10, 1.5f, shadow);
        DrawLineEx(
            { area.x + 5.0f, area.y + 4.0f },
            { area.x + area.width * 0.55f, area.y + area.height * 0.35f },
            2.0f,
            highlight);
        DrawLineEx(
            { area.x + area.width - 8.0f, area.y + area.height - 6.0f },
            { area.x + area.width * 0.45f, area.y + area.height * 0.7f },
            1.5f,
            shadow);
    }

    void drawStitchLine(Vector2 start, Vector2 end, int stitches)
    {
        for (int i = 0; i <= stitches; ++i)
        {
            const float t = (float)i / (float)stitches;
            const Vector2 point = {
                start.x + (end.x - start.x) * t,
                start.y + (end.y - start.y) * t
            };
            DrawCircleV(point, 1.2f, kStitch);
        }
    }

    void drawProtrudingBills(float centerX, float topY, float width, int count, float spread)
    {
        for (int i = 0; i < count; ++i)
        {
            const float offset = ((float)i - (count - 1) * 0.5f) * spread;
            const Rectangle bill = {
                centerX - width * 0.5f + offset,
                topY - 4.0f - i * 1.5f,
                width - std::abs(offset) * 0.25f,
                14.0f + i * 1.2f
            };
            DrawRectangleRounded(bill, 0.08f, 4, (i % 2 == 0) ? kBillFace : kBillEdge);
            DrawRectangleRoundedLines(bill, 0.08f, 4, 1.0f, kBillShadow);
            DrawLineEx(
                { bill.x + 4.0f, bill.y + bill.height * 0.5f },
                { bill.x + bill.width - 4.0f, bill.y + bill.height * 0.5f },
                1.0f,
                {118, 108, 82, 120});
        }
    }

    void drawPaperSlipTip(Rectangle pocket, float protrudeX, float protrudeY)
    {
        const Rectangle slip = {
            pocket.x + pocket.width - protrudeX,
            pocket.y + pocket.height - protrudeY,
            protrudeX + 4.0f,
            protrudeY + 2.0f
        };
        DrawRectangleRounded(slip, 0.15f, 4, kPaperSlip);
        DrawRectangleRoundedLines(slip, 0.15f, 4, 1.0f, {168, 138, 72, 180});
        DrawLineEx(
            { slip.x + 3.0f, slip.y + 3.0f },
            { slip.x + slip.width - 2.0f, slip.y + slip.height - 3.0f },
            1.0f,
            {168, 158, 132, 140});
    }

    void drawBrassSnap(Vector2 center, float radius)
    {
        DrawCircleGradient((int)center.x, (int)center.y, radius, kBrassHighlight, kBrass);
        DrawCircleLinesV(center, radius, kLeatherDeep);
        DrawCircleV({ center.x - radius * 0.25f, center.y - radius * 0.25f }, radius * 0.18f, {236, 220, 170, 120});
    }

    const char* kWalletExamineText =
        "The wallet is worked from thick full-grain leather, hand-stitched along the edges "
        "with waxed thread the color of strong tea. The dye is uneven in the way of good hides, "
        "not factory perfect. A maker's stamp inside the flap is too worn to read. It sits heavy "
        "in your palm, the sort of piece a man buys once and carries for years.\n\n"
        "You count what it holds. Twenty dollars in worn notes, nothing more. No credit cards. "
        "No identification. The pockets are otherwise empty except for a small slip of paper, "
        "tucked deep into a corner seam as though someone meant to forget it and could not quite.";
}

const float InventoryMgr::kScrollbarWidth = 16.0f;
const float InventoryMgr::kCloseButtonSize = 28.0f;
const float InventoryMgr::kItemSlotSize = 76.0f;
const float InventoryMgr::kItemGap = 12.0f;

InventoryMgr::InventoryMgr()
{
    createDefaultItems();
}

InventoryMgr::~InventoryMgr()
{
    for (InventoryItem& item : items)
    {
        if (item.icon.id != 0)
            UnloadTexture(item.icon);
        if (item.examineImage.id != 0)
            UnloadTexture(item.examineImage);
    }
}

void InventoryMgr::setPanelBounds(Rectangle bounds)
{
    panelBounds = bounds;
}

void InventoryMgr::setFont(Font font)
{
    panelFont = font;
}

Texture2D InventoryMgr::createWalletIconTexture() const
{
    const int size = 128;
    RenderTexture2D target = LoadRenderTexture(size, size);
    BeginTextureMode(target);
    ClearBackground({0, 0, 0, 0});

    DrawCircleGradient(size / 2, size / 2, 52, {36, 30, 24, 60}, {0, 0, 0, 0});

    const Rectangle body = {24.0f, 34.0f, 80.0f, 68.0f};
    drawLeatherGrain(body, 0.18f, kLeatherMid, kLeatherHighlight, kLeatherDeep);

    const Rectangle flap = {24.0f, 24.0f, 80.0f, 26.0f};
    drawLeatherGrain(flap, 0.24f, kLeatherDark, kLeatherLight, kLeatherDeep);
    DrawLineEx({flap.x + 6.0f, flap.y + flap.height - 2.0f}, {flap.x + flap.width - 6.0f, flap.y + flap.height - 2.0f}, 1.5f, kLeatherDeep);

    const Rectangle cardSlot = {34.0f, 58.0f, 34.0f, 30.0f};
    DrawRectangleRounded(cardSlot, 0.12f, 6, kLeatherDeep);
    DrawRectangleRoundedLines(cardSlot, 0.12f, 6, 1.0f, {54, 34, 20, 255});
    drawPaperSlipTip(cardSlot, 10.0f, 8.0f);

    const Rectangle billPocket = {62.0f, 58.0f, 32.0f, 30.0f};
    DrawRectangleRounded(billPocket, 0.12f, 6, kLeatherDeep);
    DrawRectangleRoundedLines(billPocket, 0.12f, 6, 1.0f, {54, 34, 20, 255});

    drawProtrudingBills(body.x + body.width * 0.5f, body.y + 2.0f, 34.0f, 4, 3.0f);

    drawBrassSnap({body.x + body.width - 12.0f, body.y + 24.0f}, 6.0f);

    drawStitchLine({body.x + 8.0f, body.y + body.height - 6.0f}, {body.x + body.width - 8.0f, body.y + body.height - 6.0f}, 14);
    drawStitchLine({body.x + 6.0f, flap.y + 6.0f}, {body.x + 6.0f, body.y + body.height - 8.0f}, 10);
    drawStitchLine({body.x + body.width - 6.0f, flap.y + 6.0f}, {body.x + body.width - 6.0f, body.y + body.height - 8.0f}, 10);

    DrawRectangle(
        (int)(body.x + 10.0f),
        (int)(body.y + 12.0f),
        18,
        8,
        {kLeatherLight.r, kLeatherLight.g, kLeatherLight.b, 55});

    EndTextureMode();

    Image image = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&image);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    UnloadRenderTexture(target);
    return texture;
}

Texture2D InventoryMgr::createWalletExamineTexture() const
{
    const int width = 420;
    const int height = 260;
    RenderTexture2D target = LoadRenderTexture(width, height);
    BeginTextureMode(target);
    ClearBackground({22, 20, 28, 255});

    DrawRectangleGradientV(0, 0, width, height, {34, 28, 22, 255}, {18, 16, 24, 255});
    DrawCircleGradient(width - 70, 48, 120, kAmberGlow, {0, 0, 0, 0});
    DrawRectangleGradientH(0, 0, width / 3, height, kNoirShadow, {0, 0, 0, 0});

    const Rectangle surface = {28.0f, 34.0f, 364.0f, 196.0f};
    DrawRectangleRounded(surface, 0.05f, 8, {30, 26, 22, 255});
    DrawRectangleRoundedLines(surface, 0.05f, 8, 2.0f, kPanelBorder);

    for (int i = 0; i < 7; ++i)
    {
        const float y = surface.y + 18.0f + i * 22.0f;
        DrawLineEx(
            {surface.x + 12.0f, y},
            {surface.x + surface.width - 12.0f, y + 3.0f},
            1.0f,
            {42, 36, 30, 80});
    }

    const Rectangle wallet = {72.0f, 72.0f, 276.0f, 132.0f};
    drawLeatherGrain(wallet, 0.14f, kLeatherMid, kLeatherHighlight, kLeatherDeep);

    const Rectangle flap = {72.0f, 48.0f, 276.0f, 48.0f};
    drawLeatherGrain(flap, 0.18f, kLeatherDark, kLeatherLight, kLeatherDeep);
    DrawLineEx(
        {flap.x + 10.0f, flap.y + flap.height - 3.0f},
        {flap.x + flap.width - 10.0f, flap.y + flap.height - 3.0f},
        2.0f,
        kLeatherDeep);

    drawProtrudingBills(wallet.x + wallet.width * 0.48f, wallet.y + 4.0f, 92.0f, 5, 7.0f);

    const Rectangle leftPocket = {88.0f, 112.0f, 96.0f, 72.0f};
    DrawRectangleRounded(leftPocket, 0.1f, 8, kLeatherDeep);
    DrawRectangleRoundedLines(leftPocket, 0.1f, 8, 1.5f, {48, 30, 18, 255});
    drawPaperSlipTip(leftPocket, 22.0f, 16.0f);

    const Rectangle rightPocket = {236.0f, 112.0f, 96.0f, 72.0f};
    DrawRectangleRounded(rightPocket, 0.1f, 8, kLeatherDeep);
    DrawRectangleRoundedLines(rightPocket, 0.1f, 8, 1.5f, {48, 30, 18, 255});

    for (int i = 0; i < 3; ++i)
    {
        const Rectangle note = {
            rightPocket.x + 14.0f,
            rightPocket.y + 12.0f + i * 6.0f,
            rightPocket.width - 28.0f,
            18.0f
        };
        DrawRectangleRounded(note, 0.08f, 4, (i == 0) ? kBillFace : kBillEdge);
        DrawRectangleRoundedLines(note, 0.08f, 4, 1.0f, kBillShadow);
    }

    drawBrassSnap({wallet.x + wallet.width - 28.0f, wallet.y + 42.0f}, 14.0f);

    drawStitchLine({wallet.x + 14.0f, wallet.y + wallet.height - 10.0f}, {wallet.x + wallet.width - 14.0f, wallet.y + wallet.height - 10.0f}, 24);
    drawStitchLine({wallet.x + 12.0f, flap.y + 10.0f}, {wallet.x + 12.0f, wallet.y + wallet.height - 12.0f}, 18);
    drawStitchLine({wallet.x + wallet.width - 12.0f, flap.y + 10.0f}, {wallet.x + wallet.width - 12.0f, wallet.y + wallet.height - 12.0f}, 18);
    drawStitchLine({flap.x + 20.0f, flap.y + 8.0f}, {flap.x + flap.width - 20.0f, flap.y + 8.0f}, 18);

    DrawEllipse(
        (int)(wallet.x + wallet.width * 0.35f),
        (int)(wallet.y + 52.0f),
        48.0f,
        16.0f,
        {kLeatherLight.r, kLeatherLight.g, kLeatherLight.b, 35});

    const Font labelFont = (panelFont.glyphs != nullptr) ? panelFont : GetFontDefault();
    DrawTextEx(labelFont, "TOP GRAIN LEATHER", {wallet.x + 18.0f, wallet.y + 18.0f}, 11.0f, 1, {kSectionLabel.r, kSectionLabel.g, kSectionLabel.b, 180});

    EndTextureMode();

    Image image = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&image);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    UnloadRenderTexture(target);
    return texture;
}

void InventoryMgr::createDefaultItems()
{
    InventoryItem wallet;
    wallet.id = "wallet";
    wallet.name = "Wallet";
    wallet.icon = createWalletIconTexture();
    wallet.examineImage = createWalletExamineTexture();
    wallet.examineText = kWalletExamineText;
    items.push_back(wallet);
}

void InventoryMgr::open()
{
    viewState = InventoryViewState::ItemList;
    selectedItemId.clear();
    inventoryScrollY = 0.0f;
}

void InventoryMgr::close()
{
    viewState = InventoryViewState::Closed;
    selectedItemId.clear();
    inventoryScrollY = 0.0f;
}

void InventoryMgr::returnToItemList()
{
    viewState = InventoryViewState::ItemList;
    inventoryScrollY = 0.0f;
}

bool InventoryMgr::canExamineSelectedItem() const
{
    if (viewState != InventoryViewState::ItemList || selectedItemId.empty())
        return false;

    const InventoryItem* item = findItem(selectedItemId);
    return item != nullptr && !item->examineText.empty();
}

void InventoryMgr::examineSelectedItem()
{
    if (!canExamineSelectedItem())
        return;

    viewState = InventoryViewState::ExaminingItem;
}

const InventoryItem* InventoryMgr::findItem(const std::string& id) const
{
    for (const InventoryItem& item : items)
    {
        if (item.id == id)
            return &item;
    }
    return nullptr;
}

int InventoryMgr::findItemIndex(const std::string& id) const
{
    for (size_t i = 0; i < items.size(); ++i)
    {
        if (items[i].id == id)
            return (int)i;
    }
    return -1;
}

Rectangle InventoryMgr::getCloseButtonBounds() const
{
    const float pad = 14.0f;
    return {
        panelBounds.x + panelBounds.width - pad - kCloseButtonSize,
        panelBounds.y + pad,
        kCloseButtonSize,
        kCloseButtonSize
    };
}

float InventoryMgr::getInventoryVisibleHeight() const
{
    const float pad = 14.0f;
    const float headerHeight = 28.0f;
    return panelBounds.height - pad * 2.0f - headerHeight;
}

void InventoryMgr::handleCloseButtonInput()
{
    const Rectangle closeBounds = getCloseButtonBounds();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), closeBounds))
    {
        close();
    }
}

void InventoryMgr::handleItemGridInput()
{
    if (viewState != InventoryViewState::ItemList)
        return;

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;

    const Vector2 mousePos = GetMousePosition();
    for (size_t i = 0; i < itemSlotBounds.size(); ++i)
    {
        if (CheckCollisionPointRec(mousePos, itemSlotBounds[i]))
        {
            if (i < items.size())
                selectedItemId = items[i].id;
            return;
        }
    }
}

void InventoryMgr::handleInventoryScrollInput()
{
    if (viewState == InventoryViewState::Closed)
        return;

    const float visibleHeight = getInventoryVisibleHeight();
    const float maxScroll = std::max(0.0f, inventoryContentHeight - visibleHeight);
    const float lineHeight = 24.0f;
    const float pad = 14.0f;
    const float headerHeight = 28.0f;
    const float contentY = panelBounds.y + pad + headerHeight;

    const Rectangle scrollTrack = {
        panelBounds.x + panelBounds.width - kScrollbarWidth - pad,
        contentY,
        kScrollbarWidth,
        visibleHeight
    };

    const float thumbHeight = (inventoryContentHeight <= 0.0f)
        ? visibleHeight
        : std::max(24.0f, visibleHeight * (visibleHeight / inventoryContentHeight));
    const float thumbTravel = std::max(0.0f, visibleHeight - thumbHeight);
    const float thumbY = scrollTrack.y + (maxScroll > 0.0f
        ? (inventoryScrollY / maxScroll) * thumbTravel
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
            inventoryScrollbarDragging = true;
            inventoryScrollbarDragOffsetY = mousePos.y - scrollThumb.y;
        }
        else if (CheckCollisionPointRec(mousePos, scrollTrack) && thumbTravel > 0.0f)
        {
            inventoryScrollY = ((mousePos.y - scrollTrack.y - thumbHeight * 0.5f) / thumbTravel) * maxScroll;
        }
    }

    if (inventoryScrollbarDragging)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && thumbTravel > 0.0f)
            inventoryScrollY = ((mousePos.y - scrollTrack.y - inventoryScrollbarDragOffsetY) / thumbTravel) * maxScroll;
        else
            inventoryScrollbarDragging = false;
    }

    const Rectangle scrollArea = {
        panelBounds.x + pad,
        contentY,
        panelBounds.width - pad * 2.0f - kScrollbarWidth - 4.0f,
        visibleHeight
    };

    if (CheckCollisionPointRec(mousePos, scrollArea))
        inventoryScrollY -= GetMouseWheelMove() * lineHeight * 2.0f;

    inventoryScrollY = std::max(0.0f, std::min(inventoryScrollY, maxScroll));
}

void InventoryMgr::layoutItemSlots()
{
    const float pad = 14.0f;
    const float headerHeight = 28.0f;
    const float contentX = panelBounds.x + pad;
    const float contentY = panelBounds.y + pad + headerHeight;
    const float contentW = panelBounds.width - pad * 2.0f - kScrollbarWidth - 4.0f;

    const int columns = std::max(1, (int)((contentW + kItemGap) / (kItemSlotSize + kItemGap)));
    const int rows = (int)items.size() / columns + ((int)items.size() % columns > 0 ? 1 : 0);
    inventoryContentHeight = rows > 0
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

void InventoryMgr::update()
{
    if (viewState == InventoryViewState::Closed)
        return;

    layoutItemSlots();
    handleCloseButtonInput();
    handleItemGridInput();
    handleInventoryScrollInput();
}

void InventoryMgr::drawCloseButton() const
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

void InventoryMgr::drawItemGrid() const
{
    const float pad = 14.0f;
    const float headerHeight = 28.0f;
    const float contentX = panelBounds.x + pad;
    const float contentY = panelBounds.y + pad + headerHeight;
    const float contentW = panelBounds.width - pad * 2.0f - kScrollbarWidth - 4.0f;
    const float visibleHeight = getInventoryVisibleHeight();

    BeginScissorMode(
        (int)contentX,
        (int)contentY,
        (int)contentW,
        (int)visibleHeight);

    for (size_t i = 0; i < items.size() && i < itemSlotBounds.size(); ++i)
    {
        Rectangle slot = itemSlotBounds[i];
        slot.y -= inventoryScrollY;

        if (slot.y + kItemSlotSize < contentY || slot.y > contentY + visibleHeight)
            continue;

        const bool selected = items[i].id == selectedItemId;
        const bool hovered = CheckCollisionPointRec(GetMousePosition(), slot);
        const Color fill = selected ? kSlotSelected : (hovered ? kSlotHover : kSlotFill);

        DrawRectangleRounded(slot, 0.18f, 8, fill);
        DrawRectangleRoundedLines(slot, 0.18f, 8, 2.0f, selected ? kPanelBorder : kPanelAccent);

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
    }

    EndScissorMode();
}

void InventoryMgr::drawInventoryScrollbar() const
{
    const float visibleHeight = getInventoryVisibleHeight();
    const float maxScroll = std::max(0.0f, inventoryContentHeight - visibleHeight);
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

    const float thumbHeight = std::max(24.0f, visibleHeight * (visibleHeight / inventoryContentHeight));
    const float thumbTravel = std::max(0.0f, visibleHeight - thumbHeight);
    const float thumbY = scrollTrack.y + (inventoryScrollY / maxScroll) * thumbTravel;

    const Rectangle scrollThumb = {
        scrollTrack.x + 2.0f,
        thumbY,
        scrollTrack.width - 4.0f,
        thumbHeight
    };

    const bool thumbHovered = CheckCollisionPointRec(GetMousePosition(), scrollThumb);
    DrawRectangleRounded(scrollThumb, 0.4f, 6, thumbHovered ? kScrollThumbHover : kScrollThumb);
}

void InventoryMgr::draw() const
{
    if (viewState == InventoryViewState::Closed)
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
    DrawTextEx(panelFont, "INVENTORY", { panelBounds.x + pad, panelBounds.y + pad }, 14.0f, 1, kSectionLabel);

    drawCloseButton();
    drawItemGrid();
    drawInventoryScrollbar();
}

const InventoryItem* InventoryMgr::getSelectedItem() const
{
    return findItem(selectedItemId);
}

}