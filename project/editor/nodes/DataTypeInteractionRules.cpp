#include "DataTypeInteractionRules.hpp"

#include <nodes/NodeData>
#include <QHash>
#include <QSet>
#include <ShaderNodeDataTypes.hpp>
#include <array>
#include <initializer_list>

QHash<QString, int> DataTypeInteractionRules::_typesLevels {
    {NO_DATA_TYPE.id, 0},
    {ActionDataType{}.id, 1},
    {BooleanDataType{}.id, 2},
    {UnsignedIntegerDataType{}.id, 3},
    {IntegerDataType{}.id, 4},
    {FloatDataType{}.id, 5},
    {DoubleDataType{}.id, 6},
    {UnsignedIntegerVec2DataType{}.id, 7},
    {UnsignedIntegerVec3DataType{}.id, 8},
    {UnsignedIntegerVec4DataType{}.id, 9},
    {IntegerVec2DataType{}.id, 10},
    {IntegerVec3DataType{}.id, 11},
    {IntegerVec4DataType{}.id, 12},
    {Vec2DataType{}.id, 13},
    {Vec3DataType{}.id, 14},
    {Vec4DataType{}.id, 15},
    {DoubleVec2DataType{}.id, 16},
    {DoubleVec3DataType{}.id, 17},
    {DoubleVec4DataType{}.id, 18},
    {Matrix2DataType{}.id, 19},
    {Matrix3DataType{}.id, 20},
    {Matrix4DataType{}.id, 21},
    {DoubleMatrix2DataType{}.id, 22},
    {DoubleMatrix3DataType{}.id, 23},
    {DoubleMatrix4DataType{}.id, 24},
};

class Graph {
    std::array<std::array<int, 24>, 24> _adjacencyMatrix;

public:
    Graph() {
        for ( auto& row : _adjacencyMatrix ) {
            for ( auto& item : row ) {
                item = 0;
            }
        }
    }

    Graph(std::initializer_list<std::pair<int, int>> initializer) {
        Graph();

        for ( auto&[from, to] : initializer ) {
            _adjacencyMatrix[static_cast<size_t>(from)]
                            [static_cast<size_t>(to)] = 1;
            _adjacencyMatrix[static_cast<size_t>(to)]
                            [static_cast<size_t>(from)] = 1;
        }
    }

    bool adjacentTo(int from, int to) {
        return _adjacencyMatrix[static_cast<size_t>(from)]
                               [static_cast<size_t>(to)] > 0;
    }
};

///////////////////////////////////////////////////////////////////////////////

QtNodes::NodeDataType
DataTypeInteractionRules::
summaryType( const QtNodes::NodeDataType& firstDataType
           , const QtNodes::NodeDataType& secondDataType )
{
    return _typesLevels[firstDataType.id] > _typesLevels[secondDataType.id]
           ? firstDataType
           : secondDataType;
}

bool
DataTypeInteractionRules::
canBeMultiped(const QtNodes::NodeDataType& dataType)
{
    return canBeMultiped(dataType, NO_DATA_TYPE);
}


bool
DataTypeInteractionRules::
canBeMultiped( const QtNodes::NodeDataType& dataType
             , const QtNodes::NodeDataType& whitDataType )
{
    static Graph _supportedInteractions {
        c<IntegerDataType, IntegerDataType>(),
        c<UnsignedIntegerDataType, UnsignedIntegerDataType>(),
        c<FloatDataType, FloatDataType>(),
        c<DoubleDataType, DoubleDataType>(),

        c<IntegerDataType, UnsignedIntegerDataType>(),
        c<IntegerDataType, FloatDataType>(),
        c<IntegerDataType, DoubleDataType>(),

        c<UnsignedIntegerDataType, FloatDataType>(),
        c<UnsignedIntegerDataType, DoubleDataType>(),

        c<FloatDataType, DoubleDataType>(),

        c<Vec2DataType, Vec2DataType>(),
        c<Vec3DataType, Vec3DataType>(),
        c<Vec4DataType, Vec4DataType>(),
        c<Matrix2DataType, Matrix2DataType>(),
        c<Matrix3DataType, Matrix3DataType>(),
        c<Matrix4DataType, Matrix4DataType>(),

        c<Vec2DataType, IntegerDataType>(),
        c<Vec2DataType, UnsignedIntegerDataType>(),
        c<Vec2DataType, FloatDataType>(),
        c<Vec2DataType, DoubleDataType>(),

        c<Vec3DataType, IntegerDataType>(),
        c<Vec3DataType, UnsignedIntegerDataType>(),
        c<Vec3DataType, FloatDataType>(),
        c<Vec3DataType, DoubleDataType>(),

        c<Vec4DataType, IntegerDataType>(),
        c<Vec4DataType, UnsignedIntegerDataType>(),
        c<Vec4DataType, FloatDataType>(),
        c<Vec4DataType, DoubleDataType>(),

        c<Matrix2DataType, IntegerDataType>(),
        c<Matrix2DataType, UnsignedIntegerDataType>(),
        c<Matrix2DataType, FloatDataType>(),
        c<Matrix2DataType, DoubleDataType>(),

        c<Matrix3DataType, IntegerDataType>(),
        c<Matrix3DataType, UnsignedIntegerDataType>(),
        c<Matrix3DataType, FloatDataType>(),
        c<Matrix3DataType, DoubleDataType>(),

        c<Matrix4DataType, IntegerDataType>(),
        c<Matrix4DataType, UnsignedIntegerDataType>(),
        c<Matrix4DataType, FloatDataType>(),
        c<Matrix4DataType, DoubleDataType>(),

        c<Matrix2DataType, Vec2DataType>(),
        c<Matrix3DataType, Vec3DataType>(),
        c<Matrix4DataType, Vec4DataType>(),
    };

    int firstDataIndex = _typesLevels[dataType.id];
    int secondDataIndex = _typesLevels[whitDataType.id];

    if ( !_supportedInteractions.adjacentTo(firstDataIndex, firstDataIndex) ) {
        return false;
    }

    if ( secondDataIndex == 0 ) {
        return true;
    }

    return _supportedInteractions.adjacentTo(firstDataIndex, secondDataIndex);
}


bool
DataTypeInteractionRules::
canBeDivided(const QtNodes::NodeDataType& dataType)
{
    return canBeDivided(dataType, NO_DATA_TYPE);
}


bool
DataTypeInteractionRules::
canBeDivided( const QtNodes::NodeDataType& dataType
            , const QtNodes::NodeDataType& whitDataType )
{
    static Graph _supportedInteractions {
        c<IntegerDataType, IntegerDataType>(),
        c<UnsignedIntegerDataType, UnsignedIntegerDataType>(),
        c<FloatDataType, FloatDataType>(),
        c<DoubleDataType, DoubleDataType>(),

        c<IntegerDataType, UnsignedIntegerDataType>(),
        c<IntegerDataType, FloatDataType>(),
        c<IntegerDataType, DoubleDataType>(),

        c<UnsignedIntegerDataType, FloatDataType>(),
        c<UnsignedIntegerDataType, DoubleDataType>(),

        c<FloatDataType, DoubleDataType>(),

        c<Vec2DataType, Vec2DataType>(),
        c<Vec3DataType, Vec3DataType>(),
        c<Vec4DataType, Vec4DataType>(),

        c<Vec2DataType, IntegerDataType>(),
        c<Vec2DataType, UnsignedIntegerDataType>(),
        c<Vec2DataType, FloatDataType>(),
        c<Vec2DataType, DoubleDataType>(),

        c<Vec3DataType, IntegerDataType>(),
        c<Vec3DataType, UnsignedIntegerDataType>(),
        c<Vec3DataType, FloatDataType>(),
        c<Vec3DataType, DoubleDataType>(),

        c<Vec4DataType, IntegerDataType>(),
        c<Vec4DataType, UnsignedIntegerDataType>(),
        c<Vec4DataType, FloatDataType>(),
        c<Vec4DataType, DoubleDataType>(),

        c<Matrix2DataType, IntegerDataType>(),
        c<Matrix2DataType, UnsignedIntegerDataType>(),
        c<Matrix2DataType, FloatDataType>(),
        c<Matrix2DataType, DoubleDataType>(),

        c<Matrix3DataType, IntegerDataType>(),
        c<Matrix3DataType, UnsignedIntegerDataType>(),
        c<Matrix3DataType, FloatDataType>(),
        c<Matrix3DataType, DoubleDataType>(),

        c<Matrix4DataType, IntegerDataType>(),
        c<Matrix4DataType, UnsignedIntegerDataType>(),
        c<Matrix4DataType, FloatDataType>(),
        c<Matrix4DataType, DoubleDataType>(),
    };

    int firstDataIndex = _typesLevels[dataType.id];
    int secondDataIndex = _typesLevels[whitDataType.id];

    if ( !_supportedInteractions.adjacentTo(firstDataIndex, firstDataIndex) ) {
        return false;
    }

    if ( secondDataIndex == 0 ) {
        return true;
    }

    return _supportedInteractions.adjacentTo(firstDataIndex, secondDataIndex);
}


bool
DataTypeInteractionRules::
canBeAdded(const QtNodes::NodeDataType& dataType)
{
    return canBeAdded( dataType, NO_DATA_TYPE );
}


bool
DataTypeInteractionRules::
canBeAdded( const QtNodes::NodeDataType& dataType
          , const QtNodes::NodeDataType& whitDataType )
{
    static Graph _supportedInteractions {
        c<IntegerDataType, IntegerDataType>(),
        c<UnsignedIntegerDataType, UnsignedIntegerDataType>(),
        c<FloatDataType, FloatDataType>(),
        c<DoubleDataType, DoubleDataType>(),

        c<IntegerDataType, UnsignedIntegerDataType>(),
        c<IntegerDataType, FloatDataType>(),
        c<IntegerDataType, DoubleDataType>(),

        c<UnsignedIntegerDataType, FloatDataType>(),
        c<UnsignedIntegerDataType, DoubleDataType>(),

        c<FloatDataType, DoubleDataType>(),

        c<Vec2DataType, Vec2DataType>(),
        c<Vec3DataType, Vec3DataType>(),
        c<Vec4DataType, Vec4DataType>(),
        c<Matrix2DataType, Matrix2DataType>(),
        c<Matrix3DataType, Matrix3DataType>(),
        c<Matrix4DataType, Matrix4DataType>(),
    };

    int firstDataIndex = _typesLevels[dataType.id];
    int secondDataIndex = _typesLevels[whitDataType.id];

    if ( !_supportedInteractions.adjacentTo(firstDataIndex, firstDataIndex) ) {
        return false;
    }

    if ( secondDataIndex == 0 ) {
        return true;
    }

    return _supportedInteractions.adjacentTo(firstDataIndex, secondDataIndex);
}


bool
DataTypeInteractionRules::
canBeSubtracted(const QtNodes::NodeDataType& dataType)
{

    return canBeAdded( dataType, NO_DATA_TYPE );
}


bool
DataTypeInteractionRules::
canBeSubtracted( const QtNodes::NodeDataType& dataType
               , const QtNodes::NodeDataType& whitDataType )
{
    return canBeAdded( dataType, whitDataType );
}


bool
DataTypeInteractionRules::
canBeCompared(const QtNodes::NodeDataType& dataType)
{
    return canBeCompared(dataType, NO_DATA_TYPE);
}


bool
DataTypeInteractionRules::
canBeCompared( const QtNodes::NodeDataType& dataType
             , const QtNodes::NodeDataType& whitDataType )
{
    static Graph _supportedInteractions {
        c<IntegerDataType, IntegerDataType>(),
        c<UnsignedIntegerDataType, UnsignedIntegerDataType>(),
        c<FloatDataType, FloatDataType>(),
        c<DoubleDataType, DoubleDataType>(),

        c<IntegerDataType, UnsignedIntegerDataType>(),
        c<IntegerDataType, FloatDataType>(),
        c<IntegerDataType, DoubleDataType>(),

        c<UnsignedIntegerDataType, FloatDataType>(),
        c<UnsignedIntegerDataType, DoubleDataType>(),

        c<FloatDataType, DoubleDataType>(),
    };

    int firstDataIndex = _typesLevels[dataType.id];
    int secondDataIndex = _typesLevels[whitDataType.id];

    if ( !_supportedInteractions.adjacentTo(firstDataIndex, firstDataIndex) ) {
        return false;
    }

    if ( secondDataIndex == 0 ) {
        return true;
    }

    return _supportedInteractions.adjacentTo(firstDataIndex, secondDataIndex);
}


bool
DataTypeInteractionRules::
canBeEqual(const QtNodes::NodeDataType& dataType)
{
    return canBeEqual(dataType, NO_DATA_TYPE);
}


bool
DataTypeInteractionRules::
canBeEqual( const QtNodes::NodeDataType& dataType
          , const QtNodes::NodeDataType& whitDataType )
{
    static Graph _supportedInteractions {
        c<IntegerDataType, IntegerDataType>(),
        c<UnsignedIntegerDataType, UnsignedIntegerDataType>(),
        c<FloatDataType, FloatDataType>(),
        c<DoubleDataType, DoubleDataType>(),

        c<IntegerDataType, UnsignedIntegerDataType>(),
        c<IntegerDataType, FloatDataType>(),
        c<IntegerDataType, DoubleDataType>(),

        c<UnsignedIntegerDataType, FloatDataType>(),
        c<UnsignedIntegerDataType, DoubleDataType>(),

        c<FloatDataType, DoubleDataType>(),

        c<Vec2DataType, Vec2DataType>(),
        c<Vec3DataType, Vec3DataType>(),
        c<Vec4DataType, Vec4DataType>(),
        c<Matrix2DataType, Matrix2DataType>(),
        c<Matrix3DataType, Matrix3DataType>(),
        c<Matrix4DataType, Matrix4DataType>(),
    };

    int firstDataIndex = _typesLevels[dataType.id];
    int secondDataIndex = _typesLevels[whitDataType.id];

    if ( !_supportedInteractions.adjacentTo(firstDataIndex, firstDataIndex) ) {
        return false;
    }

    if ( secondDataIndex == 0 ) {
        return true;
    }

    return _supportedInteractions.adjacentTo(firstDataIndex, secondDataIndex);
}


bool
DataTypeInteractionRules::
canBeIncremented(const QtNodes::NodeDataType& dataType)
{
    return _typesLevels[dataType.id] > 1;
}


bool
DataTypeInteractionRules::
canBeDecrimented(const QtNodes::NodeDataType& dataType)
{
    return _typesLevels[dataType.id] > 1;
}


bool
DataTypeInteractionRules::
canBeNegative(const QtNodes::NodeDataType& dataType)
{
    return _typesLevels[dataType.id] > 1;
}


bool
DataTypeInteractionRules::
canBeNegation(const QtNodes::NodeDataType& dataType)
{
    return _typesLevels[dataType.id] == 1;
}
