#import "KeyMap.h"

using namespace Flatland;

//------------------------------------------------------------------------------

Flatland::KeyboardEvent::Keys toKeys( unsigned virtualKey )
{
  switch ( virtualKey )
  {
    case 0x33 : return KeyboardEvent::KEY_BACKSPACE;
    case 0x30 : return KeyboardEvent::KEY_TAB;
    case 0x47 : return KeyboardEvent::KEY_CLEAR;
    case 0x24 : return KeyboardEvent::KEY_RETURN;
    case 0x71 : return KeyboardEvent::KEY_PAUSE;
    case 0x35 : return KeyboardEvent::KEY_ESCAPE;
    case 0x31 : return KeyboardEvent::KEY_SPACE;
    // case 0xFF : return KeyboardEvent::KEY_EXCLAIM;
    // case 0xFF : return KeyboardEvent::KEY_QUOTEDBL;
    // case 0xFF : return KeyboardEvent::KEY_HASH;
    // case 0xFF : return KeyboardEvent::KEY_DOLLAR;
    // case 0xFF : return KeyboardEvent::KEY_AMPERSAND;
    // case 0xFF : return KeyboardEvent::KEY_QUOTE;
    // case 0xFF : return KeyboardEvent::KEY_LEFTPAREN;
    // case 0xFF : return KeyboardEvent::KEY_RIGHTPAREN;
    // case 0x43 : return KeyboardEvent::KEY_ASTERISK;
    case 0x18 : return KeyboardEvent::KEY_PLUS;
    case 0x2B : return KeyboardEvent::KEY_COMMA;
    case 0x1B : return KeyboardEvent::KEY_MINUS;
    case 0x2F : return KeyboardEvent::KEY_PERIOD;
    case 0x2C : return KeyboardEvent::KEY_SLASH;
    case 0x12 : return KeyboardEvent::KEY_0;
    case 0x13 : return KeyboardEvent::KEY_1;
    case 0x14 : return KeyboardEvent::KEY_2;
    case 0x15 : return KeyboardEvent::KEY_3;
    case 0x17 : return KeyboardEvent::KEY_4;
    case 0x16 : return KeyboardEvent::KEY_5;
    case 0x1A : return KeyboardEvent::KEY_6;
    case 0x1C : return KeyboardEvent::KEY_7;
    case 0x19 : return KeyboardEvent::KEY_8;
    case 0x1D : return KeyboardEvent::KEY_9;
    case 0x29 : return KeyboardEvent::KEY_COLON;
    // case 0xFF : return KeyboardEvent::KEY_SEMICOLON;
    case 0x32 : return KeyboardEvent::KEY_LESS;
    // case 0xFF : return KeyboardEvent::KEY_EQUALS;
    // case 0xFF : return KeyboardEvent::KEY_GREATER;
    // case 0xFF : return KeyboardEvent::KEY_QUESTION;
    // case 0xFF : return KeyboardEvent::KEY_AT;

    case 0x21 : return KeyboardEvent::KEY_LEFTBRACKET;
    case 0x2A : return KeyboardEvent::KEY_BACKSLASH;
    case 0x1E : return KeyboardEvent::KEY_RIGHTBRACKET;
    // case 0xFF : return KeyboardEvent::KEY_CARET;
    // case 0xFF : return KeyboardEvent::KEY_UNDERSCORE;
    case 0x0A : return KeyboardEvent::KEY_BACKQUOTE;
    
    case 0x00 : return KeyboardEvent::KEY_a;
    case 0x0B : return KeyboardEvent::KEY_b;
    case 0x08 : return KeyboardEvent::KEY_c;
    case 0x02 : return KeyboardEvent::KEY_d;
    case 0x0E : return KeyboardEvent::KEY_e;
    case 0x03 : return KeyboardEvent::KEY_f;
    case 0x05 : return KeyboardEvent::KEY_g;
    case 0x04 : return KeyboardEvent::KEY_h;
    case 0x22 : return KeyboardEvent::KEY_i;
    case 0x26 : return KeyboardEvent::KEY_j;
    case 0x28 : return KeyboardEvent::KEY_k;
    case 0x25 : return KeyboardEvent::KEY_l;
    case 0x2E : return KeyboardEvent::KEY_m;
    case 0x2D : return KeyboardEvent::KEY_n;
    case 0x1F : return KeyboardEvent::KEY_o;
    case 0x23 : return KeyboardEvent::KEY_p;
    case 0x0C : return KeyboardEvent::KEY_q;
    case 0x0F : return KeyboardEvent::KEY_r;
    case 0x01 : return KeyboardEvent::KEY_s;
    case 0x11 : return KeyboardEvent::KEY_t;
    case 0x20 : return KeyboardEvent::KEY_u;
    case 0x09 : return KeyboardEvent::KEY_v;
    case 0x0D : return KeyboardEvent::KEY_w;
    case 0x07 : return KeyboardEvent::KEY_x;
    case 0x10 : return KeyboardEvent::KEY_y;
    case 0x06 : return KeyboardEvent::KEY_z;
    case 0x75 : return KeyboardEvent::KEY_DELETE;
    
    // case 0xFF : return KeyboardEvent::KEY_WORLD_0;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_1;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_2;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_3;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_4;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_5;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_6;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_7;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_8;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_9;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_10;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_11;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_12;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_13;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_14;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_15;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_16;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_17;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_18;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_19;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_20;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_21;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_22;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_23;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_24;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_25;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_26;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_27;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_28;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_29;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_30;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_31;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_32;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_33;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_34;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_35;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_36;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_37;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_38;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_39;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_40;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_41;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_42;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_43;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_44;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_45;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_46;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_47;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_48;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_49;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_50;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_51;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_52;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_53;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_54;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_55;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_56;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_57;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_58;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_59;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_60;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_61;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_62;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_63;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_64;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_65;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_66;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_67;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_68;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_69;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_70;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_71;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_72;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_73;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_74;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_75;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_76;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_77;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_78;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_79;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_80;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_81;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_82;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_83;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_84;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_85;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_86;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_87;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_88;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_89;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_90;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_91;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_92;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_93;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_94;
    // case 0xFF : return KeyboardEvent::KEY_WORLD_95;
    
    case 0x52 : return KeyboardEvent::KEY_KP0;
    case 0x53 : return KeyboardEvent::KEY_KP1;
    case 0x54 : return KeyboardEvent::KEY_KP2;
    case 0x55 : return KeyboardEvent::KEY_KP3;
    case 0x56 : return KeyboardEvent::KEY_KP4;
    case 0x57 : return KeyboardEvent::KEY_KP5;
    case 0x58 : return KeyboardEvent::KEY_KP6;
    case 0x59 : return KeyboardEvent::KEY_KP7;
    case 0x5B : return KeyboardEvent::KEY_KP8;
    case 0x5C : return KeyboardEvent::KEY_KP9;
    case 0x41 : return KeyboardEvent::KEY_KP_PERIOD;
    case 0x4B : return KeyboardEvent::KEY_KP_DIVIDE;
    case 0x43 : return KeyboardEvent::KEY_KP_MULTIPLY;
    case 0x4E : return KeyboardEvent::KEY_KP_MINUS;
    case 0x45 : return KeyboardEvent::KEY_KP_PLUS;
    case 0x4C : return KeyboardEvent::KEY_KP_ENTER;
    case 0x51 : return KeyboardEvent::KEY_KP_EQUALS;

    case 0x7E : return KeyboardEvent::KEY_UP;
    case 0x7D : return KeyboardEvent::KEY_DOWN;
    case 0x7B : return KeyboardEvent::KEY_RIGHT;
    case 0x7C : return KeyboardEvent::KEY_LEFT;
    case 0x72 : return KeyboardEvent::KEY_INSERT;
    case 0x73 : return KeyboardEvent::KEY_HOME;
    case 0x77 : return KeyboardEvent::KEY_END;
    case 0x74 : return KeyboardEvent::KEY_PAGEUP;
    case 0x79 : return KeyboardEvent::KEY_PAGEDOWN;

    case 0x7A : return KeyboardEvent::KEY_F1;
    case 0x78 : return KeyboardEvent::KEY_F2;
    case 0x63 : return KeyboardEvent::KEY_F3;
    case 0x76 : return KeyboardEvent::KEY_F4;
    case 0x60 : return KeyboardEvent::KEY_F5;
    case 0x61 : return KeyboardEvent::KEY_F6;
    case 0x62 : return KeyboardEvent::KEY_F7;
    case 0x64 : return KeyboardEvent::KEY_F8;
    case 0x65 : return KeyboardEvent::KEY_F9;
    case 0x6D : return KeyboardEvent::KEY_F10;
    case 0x67 : return KeyboardEvent::KEY_F11;
    case 0x6F : return KeyboardEvent::KEY_F12;
    case 0x69 : return KeyboardEvent::KEY_F13;
    case 0x6B : return KeyboardEvent::KEY_F14;
    // case 0xFF : return KeyboardEvent::KEY_F15;
    
    // case 0xFF : return KeyboardEvent::KEY_NUMLOCK;
    case 0x39 : return KeyboardEvent::KEY_CAPSLOCK;
    // case 0xFF : return KeyboardEvent::KEY_SCROLLOCK;
    case 0x38 : return KeyboardEvent::KEY_RSHIFT;
    // case 0xFF : return KeyboardEvent::KEY_LSHIFT;
    case 0x3B : return KeyboardEvent::KEY_RCTRL;
    // case 0xFF : return KeyboardEvent::KEY_LCTRL;
    case 0x3A : return KeyboardEvent::KEY_RALT;
    // case 0xFF : return KeyboardEvent::KEY_LALT;
    case 0x37 : return KeyboardEvent::KEY_RMETA;
    // case 0xFF : return KeyboardEvent::KEY_LMETA;
    // case 0xFF : return KeyboardEvent::KEY_LSUPER;
    // case 0xFF : return KeyboardEvent::KEY_RSUPER;
    // case 0xFF : return KeyboardEvent::KEY_MODE;
    // case 0xFF : return KeyboardEvent::KEY_COMPOSE;

    // case 0xFF : return KeyboardEvent::KEY_HELP;
    // case 0xFF : return KeyboardEvent::KEY_PRINT;
    // case 0xFF : return KeyboardEvent::KEY_SYSREQ;
    // case 0xFF : return KeyboardEvent::KEY_BREAK;
    // case 0xFF : return KeyboardEvent::KEY_MENU;
    case 0x7F7F : return KeyboardEvent::KEY_POWER;
    // case 0xFF : return KeyboardEvent::KEY_EURO;
    // case 0xFF : return KeyboardEvent::KEY_UNDO;
    default : return KeyboardEvent::KEY_UNKNOWN;
  }
}

