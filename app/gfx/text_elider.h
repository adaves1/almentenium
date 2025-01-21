
#ifndef APP_GFX_TEXT_ELIDER_H_
#define APP_GFX_TEXT_ELIDER_H_

#include <unicode/coll.h>
#include <unicode/uchar.h>

#include "app/gfx/font.h"
#include "base/basictypes.h"
#include "base/string16.h"

class FilePath;
class GURL;

// TODO(port): this file should deal in string16s rather than wstrings.
namespace gfx {

std::wstring ElideUrl(const GURL& url,
                      const gfx::Font& font,
                      int available_pixel_width,
                      const std::wstring& languages);

std::wstring ElideText(const std::wstring& text,
                       const gfx::Font& font,
                       int available_pixel_width);

// Elide a filename to fit a given pixel width, with an emphasis on not hiding
// the extension unless we have to. If filename contains a path, the path will
// be removed if filename doesn't fit into available_pixel_width.
std::wstring ElideFilename(const FilePath& filename,
                           const gfx::Font& font,
                           int available_pixel_width);

// SortedDisplayURL maintains a string from a URL suitable for display to the
// use. SortedDisplayURL also provides a function used for comparing two
// SortedDisplayURLs for use in visually ordering the SortedDisplayURLs.
//
// SortedDisplayURL is relatively cheap and supports value semantics.
class SortedDisplayURL {
 public:
  SortedDisplayURL(const GURL& url, const std::wstring& languages);
  SortedDisplayURL() {}

  // Compares this SortedDisplayURL to |url| using |collator|. Returns a value
  // < 0, = 1 or > 0 as to whether this url is less then, equal to or greater
  // than the supplied url.
  int Compare(const SortedDisplayURL& other, icu::Collator* collator) const;

  // Returns the display string for the URL.
  const string16& display_url() const { return display_url_; }

 private:
  // Returns everything after the host. This is used by Compare if the hosts
  // match.
  string16 AfterHost() const;

  // Host name minus 'www.'. Used by Compare.
  string16 sort_host_;

  // End of the prefix (spec and separator) in display_url_.
  size_t prefix_end_;

  string16 display_url_;
};

} // namespace gfx.

#endif  // APP_GFX_TEXT_ELIDER_H_
