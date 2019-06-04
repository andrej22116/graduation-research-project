#include "DefaultDataModelRegistry.hpp"

#include <nodes/FunctionalNodes.hpp>
#include <variableconverters/VectorConverter/VectorConverterDataModel.hpp>
#include <variableconverters/VectorDecomposConverter/VectorDecomposConverter.hpp>
#include <variableconverters/BaseTypesConverters/BaseTypesConverters.hpp>

DefaultDataModelRegistry::DefaultDataModelRegistry()
{
    registerModel<AdderFunctionalNode>("Math");
    registerModel<SubtractorFunctionalNode>("Math");

///////////////////////////////////////////////////////////////////////////////
    registerModel<ConditionFunctionalNode>("Logick");

///////////////////////////////////////////////////////////////////////////////
    registerModel<RadiansFunctionalNode>("Trigonometry");
    registerModel<DegreesFunctionalNode>("Trigonometry");
    registerModel<SinFunctionalNode>("Trigonometry");
    registerModel<CosFunctionalNode>("Trigonometry");
    registerModel<TanFunctionalNode>("Trigonometry");
    registerModel<CtanFunctionalNode>("Trigonometry");
    registerModel<ArcSinFunctionalNode>("Trigonometry");
    registerModel<ArcCosFunctionalNode>("Trigonometry");
    registerModel<ArcTanFunctionalNode>("Trigonometry");

///////////////////////////////////////////////////////////////////////////////
    registerModel<PowFunctionalNode>("Exponential");
    registerModel<ExpFunctionalNode>("Exponential");
    registerModel<Exp2FunctionalNode>("Exponential");
    registerModel<LogFunctionalNode>("Exponential");
    registerModel<Log2FunctionalNode>("Exponential");
    registerModel<SqrtFunctionalNode>("Exponential");
    registerModel<InverseSqrtFunctionalNode>("Exponential");

///////////////////////////////////////////////////////////////////////////////
    registerModel<VectorConverterDataModel>(
                VectorConverterDataModel::Vector2Factory(),
                "Vector convertors"
    );
    registerModel<VectorConverterDataModel>(
                VectorConverterDataModel::Vector3Factory(),
                "Vector convertors"
    );
    registerModel<VectorConverterDataModel>(
                VectorConverterDataModel::Vector4Factory(),
                "Vector convertors"
    );
    registerModel<VectorDecomposConverter>(
                VectorDecomposConverter::Vector2Factory(),
                "Vector convertors"
    );
    registerModel<VectorDecomposConverter>(
                VectorDecomposConverter::Vector3Factory(),
                "Vector convertors"
    );
    registerModel<VectorDecomposConverter> (
                VectorDecomposConverter::Vector4Factory(),
                "Vector convertors"
    );

///////////////////////////////////////////////////////////////////////////////
    registerModel<PrimitiveNodeTypeConverter> (
                PrimitiveNodeTypeConverter::toFloatFactory(),
                "Primitive convertors"
    );
    registerModel<PrimitiveNodeTypeConverter> (
                PrimitiveNodeTypeConverter::toDoubleFactory(),
                "Primitive convertors"
    );
    registerModel<PrimitiveNodeTypeConverter> (
                PrimitiveNodeTypeConverter::toIntegerFactory(),
                "Primitive convertors"
    );
    registerModel<PrimitiveNodeTypeConverter> (
                PrimitiveNodeTypeConverter::toUnsignedIntegerFactory(),
                "Primitive convertors"
    );
    registerModel<PrimitiveNodeTypeConverter> (
                PrimitiveNodeTypeConverter::toBooleanFactory(),
                "Primitive convertors"
    );
}
