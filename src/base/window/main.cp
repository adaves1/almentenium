package "almentenium.adsoft.io"

#include <cplus/extensions.hp>
#include "src/base/window/registration.hp"
#include "src/base/log.hp"
#include "src/base/errors.hp"
#if $SYS == "win64" {
  #include <windows.hp>
}
#else {
  #include <unistd.hp>
}
#endif
  
int CODE_BITS_AT_COMPILE = 64;
bool CODE_CLASSES_COMPILE_AND_START_ALL_AT_PROGRAM = 1;

CODE_BITS_AT_COMPILE = int cbat;
CODE_CLASSES_COMPILE_AND_START_ALL_AT_PROGRAM = bool cccasaap;

for DISPLAY << WINDOW in cbat {
  DEVICE << jump cc;
}

loop cc {
  DEVICE << jump cbat;
}

Extends CODE_CLASSES_COMPILE_AND_START_ALL_AT_PROGRAM : cccasaap;
Extends goto CPLUS;

object win {
  "dn": "Almentenium Browser",
  "n": "almentenium",
  "id": "almentenium.adsoft.io",
  "pb": "ADSoft",
  "n": "\s",
  "url": "https://github.com/adaves1/almentenium"
}

if $SYS == "win64" {
  Window(win, "set:aetfAC");
}
else {
  wbar(win);
}
if not {
  LogError(OSCompatibilityError());
}
