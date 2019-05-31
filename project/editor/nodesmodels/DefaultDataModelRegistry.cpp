#include "DefaultDataModelRegistry.hpp"

#include <FunctionalNodes.hpp>
#include <VariableNodes.hpp>
#include <variableconvertors/VectorConveroter/VectorConverterDataModel.hpp>
#include <variableconvertors/VectorDecomposConverter/VectorDecomposConverter.hpp>

DefaultDataModelRegistry::DefaultDataModelRegistry()
{
    registerModel<AdderFunctionalNode>("Math");
    registerModel<SubtractorFunctionalNode>("Math");

    registerModel<ConditionFunctionalNode>("Logick");

    registerModel<RadiansFunctionalNode>("Trigonometry");
    registerModel<DegreesFunctionalNode>("Trigonometry");
    registerModel<SinFunctionalNode>("Trigonometry");
    registerModel<CosFunctionalNode>("Trigonometry");
    registerModel<TanFunctionalNode>("Trigonometry");
    registerModel<CtanFunctionalNode>("Trigonometry");
    registerModel<ArcSinFunctionalNode>("Trigonometry");
    registerModel<ArcCosFunctionalNode>("Trigonometry");
    registerModel<ArcTanFunctionalNode>("Trigonometry");
    registerModel<PowFunctionalNode>("Exponential");
    registerModel<ExpFunctionalNode>("Exponential");
    registerModel<Exp2FunctionalNode>("Exponential");
    registerModel<LogFunctionalNode>("Exponential");
    registerModel<Log2FunctionalNode>("Exponential");
    registerModel<SqrtFunctionalNode>("Exponential");
    registerModel<InverseSqrtFunctionalNode>("Exponential");
    registerModel<ConstUserVariableNode>("SuperTest");
    registerModel<UserVariableNode>("SuperTest");
    registerModel<VectorConverterDataModel>(
                VectorConverterDataModel::Vector2Factory(), "Convertors" );
    registerModel<VectorConverterDataModel>(
                VectorConverterDataModel::Vector3Factory(), "Convertors" );
    registerModel<VectorConverterDataModel>(
                VectorConverterDataModel::Vector4Factory(), "Convertors" );
    /*registerModel<VectorDecomposConverter>( VectorDecomposConverter::Vector2Factory()
                                               , "Convertors" );
    registerModel<VectorDecomposConverter>( VectorDecomposConverter::Vector3Factory()
                                               , "Convertors" );
    registerModel<VectorDecomposConverter>( VectorDecomposConverter::Vector4Factory()
                                               , "Convertors" );*/
}
