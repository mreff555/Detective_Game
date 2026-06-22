#ifndef RAYLIB_COMPAT_H
#define RAYLIB_COMPAT_H

#include <raylib.h>

inline void DrawRoundedBorder(
    Rectangle rec,
    float roundness,
    int segments,
    float lineThick,
    Color color)
{
#if defined(RAYLIB_VERSION_MAJOR) && \
    (RAYLIB_VERSION_MAJOR > 5 || \
     (RAYLIB_VERSION_MAJOR == 5 && RAYLIB_VERSION_MINOR >= 5))
    DrawRectangleRoundedLinesEx(rec, roundness, segments, lineThick, color);
#else
    DrawRectangleRoundedLines(rec, roundness, segments, lineThick, color);
#endif
}

#endif /* RAYLIB_COMPAT_H */