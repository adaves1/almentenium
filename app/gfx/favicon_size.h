
#ifndef APP_GFX_FAVICON_SIZE_H_
#define APP_GFX_FAVICON_SIZE_H_

#include "base/compiler_specific.h"

// Size (along each axis) of the favicon.
const int kFavIconSize = 16;

static void calc_favicon_target_size(int* width, int* height) ALLOW_UNUSED;

// static
void calc_favicon_target_size(int* width, int* height) {
  if (*width > kFavIconSize || *height > kFavIconSize) {
    // Too big, resize it maintaining the aspect ratio.
    float aspect_ratio = static_cast<float>(*width) /
                         static_cast<float>(*height);
    *height = kFavIconSize;
    *width = static_cast<int>(aspect_ratio * *height);
    if (*width > kFavIconSize) {
      *width = kFavIconSize;
      *height = static_cast<int>(*width / aspect_ratio);
    }
  }
}

#endif // APP_GFX_FAVICON_SIZE_H_
