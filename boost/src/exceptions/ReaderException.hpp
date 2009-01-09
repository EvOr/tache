#ifndef __IOEXCEPTION_HPP__
#define __IOEXCEPTION_HPP__

class ReaderException
{
   public:
      ReaderException(std::string d, std::string f, int t):details(d),filename(f),type(t){;};
      inline std::string display(){return "Erreur lors de la lecture du fichier " + filename + " : " + details;};
      enum {NON_BLOCKING, CRITICAL};
      inline int getType() {return type;};
   protected:
      std::string details;
      std::string filename;
      int type;
};

#endif
