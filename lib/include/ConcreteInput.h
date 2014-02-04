#ifndef CONCRETEINPUT_H_INCLUDED
#define CONCRETEINPUT_H_INCLUDED
#include <CommandSender.h>
#include <UserInput.h>
#include <Colors.h>
#include <Move.h>
#include <memory>
#include <vector>
template <typename ITag>
class ConcreteInput  : public UserInput{
public:
    ConcreteInput(Game & game);
private:
    Color color_;
    virtual CommandSender const & selectSender();
    std::vector<std::unique_ptr<CommandSender>> allSenders_;
};


#endif
