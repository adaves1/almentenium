embed "cplus.System";
embed "cplus.Window";
embed "readcss.cp";

object WINDOW {
  "width": Display.Screen.getlength(),
  "height": Display.Screen.getbreadth(),
  "openState": "MAX",
  "closeButton": Window.Assets.closeButton(),
  "maxButton": Window.Assets.maxButton(),
  "minButton": Window.Assets.minButton(), 
  "unpackButton": Window.Assets.unpackButton()
}

window WIN;
WIN.w = WINDOW.width;
WIN.b = WINDOW.height;
WIN.O = WINDOW.openState;
WIN.CLB = WINDOW.closeButton;
WIN.MXB = WINDOW.maxButton;
WIN.MNB = WINDOW.minButton;
WIN.UPB = WINDOW.unpackButton;

WIN.S = css(attrib.css);

// rest attributes in attrib.css
