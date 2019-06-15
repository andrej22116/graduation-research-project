#ifndef DEFAULTDATAMODELREGISTRY_HPP
#define DEFAULTDATAMODELREGISTRY_HPP

#include <nodes/DataModelRegistry>

class DefaultDataModelRegistry : public QtNodes::DataModelRegistry
{
public:
    DefaultDataModelRegistry();

    void
    registerModels();

    void
    postRegisterModels();
};

#endif // DEFAULTDATAMODELREGISTRY_HPP
