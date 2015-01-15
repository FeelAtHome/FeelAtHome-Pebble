#ifndef GLOBALS_H
# define GLOBALS_H
# include <pebble.h>

typedef enum e_message_out_type
{
  PREV,
  NEXT,
  PLAY,
  PAUSE
}            t_message_out_type;

typedef enum e_message_in_type
{
  SONG_INFO
}            t_message_in_type;
#endif //GLOBALS_H