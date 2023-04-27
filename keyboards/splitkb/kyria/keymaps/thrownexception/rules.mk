OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
#POINTING_DEVICE_ENABLE = yes
#POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
ENCODER_ENABLE = no       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow
KEY_OVERRIDE_ENABLE = yes

CONSOLE_ENABLE = no
LTO_ENABLE = yes
MUSIC_ENABLE = no
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
NKRO_ENABLE = no
COMBO_ENABLE = yes
CAPS_WORD_ENABLE = yes

SRC += x_osm.c
