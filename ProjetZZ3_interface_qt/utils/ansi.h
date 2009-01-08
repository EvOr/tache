// ----------------------------------------------------------------------------
// ansi.h : routines de modification de la position du curseur et des couleurs
// dans un terminal. Placees dans un namespace ansi.
//
// creation    : dec 10, 2003
// last modif. : nov 22, 2005
// Christophe Duhamel
// ----------------------------------------------------------------------------

#ifndef __ANSI_CODES__
#define __ANSI_CODES__

#include <string>

namespace ansi
{
  typedef enum {NORMAL=0, BRIGHT, UNDERLINE=4, BLINK, INVERSE=7, INVIS}  Style;
  typedef enum {BLACK=0, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE} Color;

  std::string clear_screen    (void);
  std::string clear_line      (void);
  std::string clear_endofline (void);

  std::string move_up         (unsigned n);
  std::string move_down       (unsigned n);
  std::string move_right      (unsigned n);
  std::string move_left       (unsigned n);
  std::string move_home       (void);
  std::string move_xy         (unsigned x, unsigned y);

  std::string save_pos        (void);
  std::string restore_pos     (void);

  std::string set_foreground  (Color c);
  std::string set_background  (Color c);
  std::string set_color       (Color f, Color b);

  std::string set_textstyle   (Style s);
  std::string reset_textstyle (void);
}

#endif
