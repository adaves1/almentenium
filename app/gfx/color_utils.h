
#ifndef APP_GFX_COLOR_UTILS_H_
#define APP_GFX_COLOR_UTILS_H_

#include "third_party/skia/include/core/SkColor.h"

class SkBitmap;

namespace color_utils {

// Represents set of CIE XYZ tristimulus values.
struct CIE_XYZ {
  double X;
  double Y; // luminance
  double Z;
};

// Represents a L*a*b* color value
struct LabColor {
  int L;
  int a;
  int b;
};

// Note: these transformations assume sRGB as the source color space

// Convert between different color spaces
void SkColorToCIEXYZ(SkColor c, CIE_XYZ* xyz);
void CIEXYZToLabColor(const CIE_XYZ& xyz, LabColor* lab);

SkColor CIEXYZToSkColor(SkAlpha alpha, const CIE_XYZ& xyz);
void LabColorToCIEXYZ(const LabColor& lab, CIE_XYZ* xyz);

void SkColorToLabColor(SkColor c, LabColor* lab);
SkColor LabColorToSkColor(const LabColor& lab, SkAlpha alpha);

// Determine if a given alpha value is nearly completely transparent.
bool IsColorCloseToTransparent(SkAlpha alpha);

// Determine if a color is near grey.
bool IsColorCloseToGrey(int r, int g, int b);

// Gets a color representing a bitmap. The definition of "representing" is the
// average color in the bitmap. The color returned is modified to have the
// specified alpha.
SkColor GetAverageColorOfFavicon(SkBitmap* bitmap, SkAlpha alpha);

// Builds a histogram based on the Y' of the Y'UV representation of
// this image.
void BuildLumaHistogram(SkBitmap* bitmap, int histogram[256]);

// Returns a blend of the supplied colors, ranging from |background| (for
// |alpha| == 0) to |foreground| (for |alpha| == 255).
SkColor AlphaBlend(SkColor foreground, SkColor background, SkAlpha alpha);

// Given two possible foreground colors, return the one that is more readable
// over |background|.
SkColor PickMoreReadableColor(SkColor foreground1,
                              SkColor foreground2,
                              SkColor background);

// Gets a Windows system color as a SkColor
SkColor GetSysSkColor(int which);

} // namespace color_utils

#endif  // #ifndef APP_GFX_COLOR_UTILS_H_
