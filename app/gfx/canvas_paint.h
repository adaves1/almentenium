
#ifndef APP_GFX_CANVAS_PAINT_H_
#define APP_GFX_CANVAS_PAINT_H_

#include "app/gfx/canvas.h"
#include "skia/ext/canvas_paint.h"

// Define a skia::CanvasPaint type that wraps our gfx::Canvas like the
// skia::PlatformCanvasPaint wraps PlatformCanvas.

namespace gfx {

#if defined(OS_WIN) || defined(OS_LINUX)
typedef skia::CanvasPaintT<Canvas> CanvasPaint;
#endif

}  // namespace gfx

#endif  // APP_GFX_CANVAS_PAINT_H_
