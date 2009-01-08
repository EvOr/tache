#include "ansi.h"

namespace ansi
{
  // constantes locales
  //static const int FG_OFFSET = 30;
  //static const int BG_OFFSET = 40;
  enum {FG_OFFSET = 30, BG_OFFSET = 40};

  // meilleur qu'une string const : evite souvent une copie
  #define PREFIX "\033["

  std::string itoa (int value, int base = 10)
  {
    // test de validite
    if ((base < 2) || (base > 16))
      return std::string();

    std::string buffer; // buffer de travail
    buffer.reserve(35); // prealloue suffisamment d'espace

    // conversion dans la base voulue
    int quotient = value;
    do
    {
      buffer += "0123456789abcdef"[std::abs(quotient % base)];
      quotient /= base;
    } while (quotient);

    // ajoute le signe dans la base 10
    if ((value < 0) && (base == 10))
      buffer += '-';

    std::reverse(buffer.begin(), buffer.end());
    return buffer;
  }


  //std::string clear_screen (void) { return (std::string(PREFIX"2J")); }
  std::string clear_screen (void) { return (std::string(PREFIX"H"PREFIX"2J")); }
  std::string clear_line (void) { return (std::string(PREFIX"K")); }
  std::string clear_endofline (void) { return (std::string(PREFIX"0K")); }

  std::string move_up (unsigned n) { return (std::string(PREFIX).append(itoa(n)).append("A")); }
  std::string move_down (unsigned n) { return (std::string(PREFIX).append(itoa(n)).append("B")); }
  std::string move_right (unsigned n) { return (std::string(PREFIX).append(itoa(n)).append("C")); }
  std::string move_left (unsigned n) { return (std::string(PREFIX).append(itoa(n)).append("D")); }
  std::string move_home (void) { return (std::string(PREFIX"1;0H")); }
  std::string move_xy (unsigned x, unsigned y) { return (std::string(PREFIX).append(itoa(y)).append(";").append(itoa(x)).append("H")); }

  std::string save_pos (void) { return (std::string(PREFIX"u")); }
  std::string restore_pos (void) { return (std::string(PREFIX"s")); }

  std::string set_foreground (Color c) { return (std::string(PREFIX).append(itoa(FG_OFFSET+c)).append("m")); }
  std::string set_background (Color c) { return (std::string(PREFIX).append(itoa(BG_OFFSET+c)).append("m")); }
  std::string set_color (Color f, Color b) { return (std::string(PREFIX).append(itoa(BG_OFFSET+b)).append(";").append(itoa(FG_OFFSET+f)).append("m")); }

  std::string set_textstyle (Style s) { return (std::string(PREFIX).append(itoa(s)).append("m")); }
  std::string reset_textstyle (void) { return (std::string(PREFIX"0m")); }

}
