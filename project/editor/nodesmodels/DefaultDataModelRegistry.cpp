#include "DefaultDataModelRegistry.hpp"

#include <nodes/FunctionalNodes.hpp>
#include <variableconverters/VectorConverter/VectorConverterDataModel.hpp>
#include <variableconverters/VectorDecomposConverter/VectorDecomposConverter.hpp>
#include <variableconverters/BaseTypesConverters/BaseTypesConverters.hpp>
#include <nodes/VariableNode/VariableNode.hpp>
#include <nodes/LogickalNodes.hpp>
#include <nodes/ConstVariables/ConstVariablesNodes.hpp>
#include <nodes/GeometrycFunctionalNodes.hpp>
#include <nodes/CommonFunctionalNodes.hpp>

DefaultDataModelRegistry::DefaultDataModelRegistry()
{
    registerModels();
}


void
DefaultDataModelRegistry::
registerModels()
{
    registerModel<AdderFunctionalNode>("Math");
    registerModel<SubtractorFunctionalNode>("Math");
    registerModel<MultiplyFunctionalNode>("Math");
    registerModel<DivisionFunctionalNode>("Math");

///////////////////////////////////////////////////////////////////////////////
    //registerModel<ConditionFunctionalNode>("Logick");

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
    registerModel<FloatConstVariableNode>("Constants");
    registerModel<DoubleConstVariableNode>("Constants");
    registerModel<IntegerConstVariableNode>("Constants");
    registerModel<UnsignedIntegerConstVariableNode>("Constants");
    registerModel<BooleanConstVariableNode>("Constants");
    registerModel<Vec2ConstVariableNode>("Constants");
    registerModel<Vec3ConstVariableNode>("Constants");
    registerModel<Vec4ConstVariableNode>("Constants");

///////////////////////////////////////////////////////////////////////////////
    registerModel<NormalizeFunctionalNode>("Geometry");
    registerModel<LengthFunctionalNode>("Geometry");
    registerModel<DistanceFunctionalNode>("Geometry");
    registerModel<DotFunctionalNode>("Geometry");
    registerModel<CrossFunctionalNode>("Geometry");
    registerModel<ReflectFunctionalNode>("Geometry");

///////////////////////////////////////////////////////////////////////////////
    registerModel<AbsoluteFunctionalNode>("Common");
    registerModel<SignFunctionalNode>("Common");
    registerModel<FloorFunctionalNode>("Common");
    registerModel<CeilingFunctionalNode>("Common");
    registerModel<FractionalFunctionalNode>("Common");
    registerModel<ModuloFunctionalNode>("Common");
    registerModel<MinimumFunctionalNode>("Common");
    registerModel<MaximumFunctionalNode>("Common");

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
    /*registerModel<VectorDecomposConverter>(
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
    );*/

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

///////////////////////////////////////////////////////////////////////////////
    registerModel<LogickalEqualsNode> (
                LogickalEqualsNode::equalityFactory(),
                "Boolean logick"
    );
    registerModel<LogickalEqualsNode> (
                LogickalEqualsNode::notEqualityFactory(),
                "Boolean logick"
    );
    registerModel<LogickalCompareNode> (
                LogickalCompareNode::lessFactory(),
                "Boolean logick"
    );
    registerModel<LogickalCompareNode> (
                LogickalCompareNode::lessOrEqualFactory(),
                "Boolean logick"
    );
    registerModel<LogickalEqualsNode> (
                LogickalCompareNode::greaterFactory(),
                "Boolean logick"
    );
    registerModel<LogickalEqualsNode> (
                LogickalCompareNode::greaterOrEqualFactory(),
                "Boolean logick"
    );
    registerModel<LogickalBooleanNode> (
                LogickalBooleanNode::logicalOrFactory(),
                "Boolean logick"
    );
    registerModel<LogickalBooleanNode> (
                LogickalBooleanNode::logicalAndFactory(),
                "Boolean logick"
                );
}


void
DefaultDataModelRegistry::
postRegisterModels()
{
    registerModel<BeginNode>("Base");
    registerModel<VariableNode>("Base");
}
