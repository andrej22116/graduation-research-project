#ifndef DATATYPEINTERACTIONRULES_HPP
#define DATATYPEINTERACTIONRULES_HPP

#include <QHash>

namespace QtNodes {
    class NodeDataType;
}

using QtNodes::NodeDataType;

class DataTypeInteractionRules
{
    DataTypeInteractionRules() = default;

public:
    static NodeDataType
    summaryType( const NodeDataType& firstDataType
               , const NodeDataType& secondDataType );

    static bool
    canBeMultiped(const NodeDataType& dataType);

    static bool
    canBeMultiped( const NodeDataType& dataType
                 , const NodeDataType& whitDataType );

    static bool
    canBeDivided(const NodeDataType& dataType);

    static bool
    canBeDivided( const NodeDataType& dataType
                , const NodeDataType& whitDataType );

    static bool
    canBeAdded(const NodeDataType& dataType);

    static bool
    canBeAdded( const NodeDataType& dataType
              , const NodeDataType& whitDataType );

    static bool
    canBeSubtracted(const NodeDataType& dataType);

    static bool
    canBeSubtracted( const NodeDataType& dataType
                   , const NodeDataType& whitDataType );

    static bool
    canBeCompared(const NodeDataType& dataType);

    static bool
    canBeCompared( const NodeDataType& dataType
                 , const NodeDataType& whitDataType );

    static bool
    canBeEqual(const NodeDataType& dataType);

    static bool
    canBeEqual( const NodeDataType& dataType
              , const NodeDataType& whitDataType );

    static bool
    canBeIncremented(const NodeDataType& dataType);

    static bool
    canBeDecrimented(const NodeDataType& dataType);

    static bool
    canBeNegative(const NodeDataType& dataType);

    static bool
    canBeNegation(const NodeDataType& dataType);

private:
    /// convertor
    template<typename From, typename To>
    static std::pair<int, int>
    c() { return { _typesLevels[From{}.id], _typesLevels[To{}.id] }; }

private:
    static QHash<QString, int> _typesLevels;
};

#endif // DATATYPEINTERACTIONRULES_HPP
