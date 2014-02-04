#ifndef CONCRETECOMMANDSENDER_H_INCLUDED
#define CONCRETECOMMANDSENDER_H_INCLUDED
#include <CommandSender.h>
#include <CommandTraits.h>
#include <type_traits>
template <typename ITag>
class ConcreteInput;
/** L'émetteur réel d'une commande spécifique dans un contexte
  * d'entrées/sorties spécifique
  */
template <typename ITag, typename CTag>
class ConcreteCommandSender : public CommandSender{
public:
    using ctorPolicy = typename CTag::CtorPolicy;
    using updatePolicy = typename CTag::UpdatePolicy;
    /** Permet de s'assurer que l'on utilise les bons
      * traits pour les politiques de création de commande
      */
    static_assert(
        std::is_same<ctorPolicy,OnlyOutputTrait>::value ||
        std::is_same<ctorPolicy ,OutputAndChessboardTrait>::value ||
        std::is_same<ctorPolicy ,OutputAndGameTrait>::value,
    "Les seuls tags admis comme politique de création sont"
    "OnlyOutputTrait, OutputAndChessboardTrait "
    "et OutputAndGameTrait");
    /** Permet de s'assurer que l'on utilise les bons traits
      * de politique pour la mise à jour des données des
      * différentes commandes
      */
    static_assert(
        std::is_same<updatePolicy, NoUpdateNeeded>::value ||
        std::is_same<updatePolicy, NeedColorUpdate>::value ||
        std::is_same<updatePolicy, NeedColorAndMoveUpdate>::value,
    "Les seuls tags admis comme politique de mise à jour sont"
    "NeedColorUpdate et NeedColorAndMoveUpdate");
    /** Sélectionne le constructeur qui n'a besoin que du système
      * d'affichage
      */
    template < typename T = typename CTag::CtorPolicy,
                   typename   = typename
                        std::enable_if<
                        std::is_same<T, OnlyOutputTrait>::value>::type>
    ConcreteCommandSender(ConcreteInput<ITag> & input,OnlyOutputTrait const &):
        CommandSender(input),command_(toConcreteOutput<ITag>
                             (input.game(),ITag())){}
    /** Sélectionne le constructeur qui a besoin du système
      * d'affichage et de l'échiquier
      */
    template < typename T = typename CTag::CtorPolicy,
                   typename   = typename
                        std::enable_if<
                        std::is_same<T, OutputAndChessboardTrait>::value>::type>
    ConcreteCommandSender(ConcreteInput<ITag> & input, OutputAndChessboardTrait const &):
        CommandSender(input),
        command_(toConcreteOutput<ITag>
                 (input.game(),ITag()),input.game().board()){}
    /** Sélectionne le constructeur qui a besoin du système
      * d'affichage et de la partie
      */
    template < typename T = typename CTag::CtorPolicy,
                   typename   = typename
                        std::enable_if<
                        std::is_same<T, OutputAndGameTrait>::value>::type>
    ConcreteCommandSender(ConcreteInput<ITag> & input, OutputAndGameTrait const &):
        CommandSender(input),
        command_(toConcreteOutput<ITag>
                 (input.game(),ITag()),input.game()){}
    /** Veille à ce que la commande dispose d'informations mises à
      * jour si besoin avant de l'émettre
      */
    Command const & emitCommand() const {
        const_cast<ConcreteCommandSender &>(*this).updateCommand(updatePolicy());
        return command_;
    }
private:
    template <typename T= updatePolicy,
              typename = typename std::enable_if<
                    std::is_same<T, NoUpdateNeeded>::value>::type>
    void updateCommand(NoUpdateNeeded const &){
    }
    template <typename T= updatePolicy,
              typename = typename std::enable_if<
                    std::is_same<T, NeedColorUpdate>::value>::type>
    void updateCommand(NeedColorUpdate const &){
        command_.color = system_.playerColor();
    }
    template <typename T= updatePolicy,
              typename = typename std::enable_if<
                    std::is_same<T, NeedColorAndMoveUpdate>::value>::type>
    void updateCommand(NeedColorAndMoveUpdate const &){
        command_.color =system_.playerColor();
        command_.move = system_.selectedMove();
    }
    ConcreteCommand<ITag,CTag> command_;
};
#endif
