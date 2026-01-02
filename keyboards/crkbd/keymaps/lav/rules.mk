CONVERT_TO = rp2040_ce
VPATH += keyboards/gboards

VIA_ENABLE          = no
LTO_ENABLE          = yes
RAW_ENABLE          = yes
CONSOLE_ENABLE      = yes

RGBLIGHT_ENABLE     = no
RGB_MATRIX_ENABLE   = no

MOUSEKEY_ENABLE     = yes
OLED_ENABLE         = yes
OLED_DRIVER         = ssd1306
EXTRAKEY_ENABLE     = no
COMBO_ENABLE        = yes

CAPS_WORD_ENABLE = yes
KEY_LOCK_ENABLE = yes
LAYER_LOCK_ENABLE = no
REPEAT_KEY_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
LEADER_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
