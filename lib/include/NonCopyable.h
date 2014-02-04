#ifndef NONCOPYABLE_H_INCLUDED
#define NONCOPYABLE_H_INCLUDED
/** Le concept d'élément non copiable et non affectable.
  *
  * De nombreux éléments devront n'être ni copiables ni affectables,
  * soit de par leur sémantique d'entité, soit parce qu'il ne fait
  * simplement aucun sens d'en permettre la copie et l'affectation.
  *
  * Cette classe représente le concept en question et permet de
  * s'assurer que la classe qui en hérite de manière privée (afin de
  * ne pas créer une "méga hiérarchie de classes non copiables et
  * non affectables" qui n'aurait aucun sens), ainsi que toutes ses
  * classes dérivées est non copiable et non affectable.
  *
  * @note Cette manière de travailler permet d'éviter la redondance
  * des informations qui seraient nécessaires s'il fallait rendre
  * explicitement toutes les classes non copiables et non
  * affectables tout en étant finalement beaucoup plus explicite
  * quant au fait qu'elles le sont.
  */
class NonCopyable{
    public:
        /** Constructeur de copie, supprimé pour éviter la copie.
          */
        NonCopyable(NonCopyable const &) = delete;
        /** Opérateur d'affectation, supprimé pour éviter
          * l'affectation.
          */
        NonCopyable & operator = (NonCopyable const & ) = delete;
    protected:
        /** Constructeur par défaut, protégé car utilisable
          * uniquement par les classes dérivées.
          */
        NonCopyable(){}
        /** Destructeur, protégé car utilisable uniquement par
          * les classes dérivées.
          */
        ~NonCopyable(){}
};
#endif
