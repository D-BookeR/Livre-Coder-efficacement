#ifndef TOUPPERFUNCTION_H_INCLUDED
#define TOUPPERFUNCTION_H_INCLUDED
#include <string>
/** Convertit une chaîne de caractères en majuscules.
  *
  * Convertit toutes les lettres minuscules de la chaîne de
  * caractères fournie en majuscules afin de faciliter les
  * comparaisons ultérieures.
  *
  * @param[in,out] str La chaîne de caractères à convertir.
  */
void toUpper(std::string & str);
#endif
