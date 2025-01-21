

#include "app/gfx/font.h"

#include <fontconfig/fontconfig.h>
#include <gtk/gtk.h>

#include "base/string_util.h"

namespace gfx {

Font* Font::default_font_ = NULL;

static std::wstring FindBestMatchFontFamilyName(const char* family_name) {
  FcPattern* pattern = FcPatternCreate();
  FcValue fcvalue;
  fcvalue.type = FcTypeString;
  char* family_name_copy = strdup(family_name);
  fcvalue.u.s = reinterpret_cast<FcChar8*>(family_name_copy);
  FcPatternAdd(pattern, FC_FAMILY, fcvalue, 0);
  FcConfigSubstitute(0, pattern, FcMatchPattern);
  FcDefaultSubstitute(pattern);
  FcResult result;
  FcPattern* match = FcFontMatch(0, pattern, &result);
  DCHECK(match) << "Could not find font: " << family_name;
  FcChar8* match_family;
  FcPatternGetString(match, FC_FAMILY, 0, &match_family);

  std::wstring font_family = UTF8ToWide(
      reinterpret_cast<char*>(match_family));
  FcPatternDestroy(match);
  FcPatternDestroy(pattern);
  free(family_name_copy);
  return font_family;
}

// Get the default gtk system font (name and size).
Font::Font() {
  if (default_font_ == NULL) {
    GtkSettings* settings = gtk_settings_get_default();

    gchar* font_name = NULL;
    g_object_get(G_OBJECT(settings),
                 "gtk-font-name", &font_name,
                 NULL);

    // Temporary CHECK for helping track down
    // http://code.google.com/p/chromium/issues/detail?id=12530
    CHECK(font_name) << " Unable to get gtk-font-name for default font.";

    PangoFontDescription* desc =
        pango_font_description_from_string(font_name);
    gint size = pango_font_description_get_size(desc);
    const char* family_name = pango_font_description_get_family(desc);

    // Find best match font for |family_name| to make sure we can get
    // a SkTypeface for the default font.
    // TODO(agl): remove this.
    std::wstring font_family = FindBestMatchFontFamilyName(family_name);

    default_font_ = new Font(CreateFont(font_family, size / PANGO_SCALE));

    pango_font_description_free(desc);
    g_free(font_name);

    DCHECK(default_font_);
  }

  CopyFont(*default_font_);
}

}  // namespace gfx
