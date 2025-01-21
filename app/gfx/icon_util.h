
#ifndef APP_ICON_UTIL_H_
#define APP_ICON_UTIL_H_

#include <windows.h>
#include <string>
#include <vector>
#include "base/basictypes.h"

namespace gfx {
  class Size;
}
class SkBitmap;

class IconUtil {
 public:
  // Given an SkBitmap object, the function converts the bitmap to a Windows
  // icon and returns the corresponding HICON handle. If the function can not
  // convert the bitmap, NULL is returned.
  //
  // The client is responsible for destroying the icon when it is no longer
  // needed by calling ::DestroyIcon().
  static HICON CreateHICONFromSkBitmap(const SkBitmap& bitmap);

  // Given a valid HICON handle representing an icon, this function converts
  // the icon into an SkBitmap object containing an ARGB bitmap using the
  // dimensions specified in |s|. |s| must specify valid dimensions (both
  // width() an height() must be greater than zero). If the function can
  // convert the icon to a bitmap (most probably due to an invalid parameter),
  // the return value is NULL.
  //
  // The client owns the returned bitmap object and is responsible for deleting
  // it when it is no longer needed.
  static SkBitmap* CreateSkBitmapFromHICON(HICON icon, const gfx::Size& s);

  // Given an initialized SkBitmap object and a file name, this function
  // creates a .ico file with the given name using the provided bitmap. The
  // icon file is created with multiple icon images of varying predefined
  // dimensions because Windows uses different image sizes when loading icons,
  // depending on where the icon is drawn (ALT+TAB window, desktop shortcut,
  // Quick Launch, etc.). |icon_file_name| needs to specify the full path for
  // the desired .ico file.
  //
  // The function returns true on success and false otherwise.
  static bool CreateIconFileFromSkBitmap(const SkBitmap& bitmap,
                                         const std::wstring& icon_file_name);

 private:
  // The icon format is published in the MSDN but there is no definition of
  // the icon file structures in any of the Windows header files so we need to
  // define these structure within the class. We must make sure we use 2 byte
  // packing so that the structures are layed out properly within the file.
#pragma pack(push)
#pragma pack(2)

  // ICONDIRENTRY contains meta data for an individual icon image within a
  // .ico file.
  struct ICONDIRENTRY {
    BYTE bWidth;
    BYTE bHeight;
    BYTE bColorCount;
    BYTE bReserved;
    WORD wPlanes;
    WORD wBitCount;
    DWORD dwBytesInRes;
    DWORD dwImageOffset;
  };

  // ICONDIR Contains information about all the icon images contained within a
  // single .ico file.
  struct ICONDIR {
    WORD idReserved;
    WORD idType;
    WORD idCount;
    ICONDIRENTRY idEntries[1];
  };

  // Contains the actual icon image.
  struct ICONIMAGE {
    BITMAPINFOHEADER icHeader;
    RGBQUAD icColors[1];
    BYTE icXOR[1];
    BYTE icAND[1];
  };
#pragma pack(pop)

  // Used for indicating that the .ico contains an icon (rather than a cursor)
  // image. This value is set in the |idType| field of the ICONDIR structure.
  static const int kResourceTypeIcon = 1;

  // The dimensions of the icon images we insert into the .ico file.
  static const int icon_dimensions_[];

  // Returns how many icon dimensions are defined.
  static int GetIconDimensionCount();

  // A helper function that initializes a BITMAPV5HEADER structure with a set
  // of values.
  static void InitializeBitmapHeader(BITMAPV5HEADER* header, int width,
                                     int height);

  // Given a single SkBitmap object and pointers to the corresponding icon
  // structures within the icon data buffer, this function sets the image
  // information (dimensions, color depth, etc.) in the icon structures and
  // also copies the underlying icon image into the appropriate location.
  //
  // The function will set the data pointed to by |image_byte_count| with the
  // number of image bytes written to the buffer. Note that the number of bytes
  // includes only the image data written into the memory pointed to by
  // |icon_image|.
  static void SetSingleIconImageInformation(const SkBitmap& bitmap,
                                            int index,
                                            ICONDIR* icon_dir,
                                            ICONIMAGE* icon_image,
                                            int image_offset,
                                            int* image_byte_count);

  // Copies the bits of an SkBitmap object into a buffer holding the bits of
  // the corresponding image for an icon within the .ico file.
  static void CopySkBitmapBitsIntoIconBuffer(const SkBitmap& bitmap,
                                             unsigned char* buffer,
                                             int buffer_size);

  // Given a single bitmap, this function creates a set of bitmaps with
  // specific dimensions by resizing the given bitmap to the appropriate sizes.
  static void CreateResizedBitmapSet(const SkBitmap& bitmap_to_resize,
                                     std::vector<SkBitmap>* bitmaps);

  // Given a set of bitmaps with varying dimensions, this function computes
  // the amount of memory needed in order to store the bitmaps as image icons
  // in a .ico file.
  static int ComputeIconFileBufferSize(const std::vector<SkBitmap>& set);

  static void ComputeBitmapSizeComponents(const SkBitmap& bitmap,
                                          int* xor_mask_size,
                                          int* and_mask_size,
                                          int* bytes_in_resource);

  // Prevent clients from instantiating objects of that class by declaring the
  // ctor/dtor as private.
  DISALLOW_IMPLICIT_CONSTRUCTORS(IconUtil);
};

#endif  // APP_ICON_UTIL_H_
