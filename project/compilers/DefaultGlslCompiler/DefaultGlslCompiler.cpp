#include "DefaultGlslCompiler.hpp"

#include <QJsonObject>
#include <QJsonArray>
#include <QLocale>
#include <QRegExp>
#include <QDebug>
#include <algorithm>

DefaultGlslCompiler::
DefaultGlslCompiler()
    : _textStream(new QTextStream(new QByteArray))
    , _procent(0)
    , _procentScaleSpeed(0)
{
    QLocale::setDefault(QLocale::C);

    _reservedVariablesNames["Result color"] = "FinalColor";

    _nodesTypesHandlers["const_var"] = &DefaultGlslCompiler::handleConstVariableNode;
    _nodesTypesHandlers["var"] = &DefaultGlslCompiler::handleVariableNode;
    _nodesTypesHandlers["fun"] = &DefaultGlslCompiler::handleFunctionalNode;

    _dataTypeAssociation["const_float"] = "float";
    _dataTypeAssociation["const_double"] = "double";
    _dataTypeAssociation["const_bool"] = "bool";
    _dataTypeAssociation["const_integer"] = "int";
    _dataTypeAssociation["const_uinteger"] = "uint";
    _dataTypeAssociation["const_bool"] = "bool";
    _dataTypeAssociation["const_vec2"] = "vec2";
    _dataTypeAssociation["const_vec3"] = "vec3";
    _dataTypeAssociation["const_vec4"] = "vec4";

    _constConvertors["const_float"] = [](const QJsonValue& value){
        return QString::number(value.toDouble());
    };
    _constConvertors["const_double"] = [](const QJsonValue& value){
        return QString::number(value.toDouble());
    };
    _constConvertors["const_bool"] = [](const QJsonValue& value){
        return QString::number(value.toBool());
    };
    _constConvertors["const_integer"] = [](const QJsonValue& value){
        return QString::number(value.toInt());
    };
    _constConvertors["const_uinteger"] = [](const QJsonValue& value){
        return QString::number(value.toString().toUInt());
    };
    _constConvertors["const_bool"] = [](const QJsonValue& value){
        return QString::number(value.toBool());
    };
    _constConvertors["const_vec2"] = [](const QJsonValue& value){
        auto obj = value.toObject();
        return QString("vec2(%1, %2)").arg(obj["r"].toString())
                                      .arg(obj["g"].toString());
    };
    _constConvertors["const_vec3"] = [](const QJsonValue& value){
        auto obj = value.toObject();
        return QString("vec3(%1, %2, %3)").arg(obj["r"].toString())
                                          .arg(obj["g"].toString())
                                          .arg(obj["b"].toString());
    };
    _constConvertors["const_vec4"] = [](const QJsonValue& value){
        auto obj = value.toObject();
        return QString("vec4(%1, %2, %3, %4)").arg(obj["r"].toString())
                                              .arg(obj["g"].toString())
                                              .arg(obj["b"].toString())
                                              .arg(obj["a"].toString());
    };
}


void
DefaultGlslCompiler::
compile(std::shared_ptr<QJsonObject> sources)
{
    _sources = sources;
    _currentFunction = &DefaultGlslCompiler::writeHeader;
}


void
DefaultGlslCompiler::
nextStep()
{
    _currentFunction(this);
}


void
DefaultGlslCompiler::
writeHeader()
{
    int procent = static_cast<int>(_procent);
    emit compileChangeState(procent, "Create header...");

    *_textStream << "#version 420 core" << endl << endl;
    *_textStream << "out vec4 FinalColor;" << endl << endl;
    *_textStream << "void main()" << endl << "{" << endl;


    _procent += 1.0;
    _currentFunction = &DefaultGlslCompiler::hashVariables;
}


void
DefaultGlslCompiler::
hashVariables()
{
    int procent = static_cast<int>(_procent);
    emit compileChangeState(procent, "Hashing variables...");

    auto& sourceObj = *_sources;
    auto variables = sourceObj["variables"].toArray();
    for ( auto variable : variables) {
        auto variableObj = variable.toObject();
        //auto type = variableObj[""].toString();
        //auto name = variableObj[""].toString();
        //auto value =

        //_finalNodesStringValues.push_back( QString("%1 %2 = %3;")
        //                                   .arg(type)
        //                                   .arg(name)
        //                                   .arg(value)
    }

    _procent += 7.0;
    _currentFunction = &DefaultGlslCompiler::hashNodes;
}


void
DefaultGlslCompiler::
hashNodes()
{
    int procent = static_cast<int>(_procent);
    emit compileChangeState(procent, "Hashing nodes...");

    auto& sourceObj = *_sources;
    auto nodes = sourceObj["nodes"].toArray();
    for ( auto node : nodes) {
        auto nodeObj = node.toObject();
        auto model = nodeObj["model"].toObject();
        auto id = QUuid::fromString(nodeObj["id"].toString());

        _models[id] = model;
    }

    _procent += 7.0;
    _currentFunction = &DefaultGlslCompiler::hashDependecis;
}


void
DefaultGlslCompiler::
hashDependecis()
{
    int procent = static_cast<int>(_procent);
    emit compileChangeState(procent, "Hashing connections...");

    auto& sourceObj = *_sources;
    auto connections = sourceObj["connections"].toArray();
    for ( auto connection : connections ) {
        auto connectionObj = connection.toObject();
        auto inId = QUuid::fromString(connectionObj["in_id"].toString());
        auto outId = QUuid::fromString(connectionObj["out_id"].toString());
        auto inIndex = connectionObj["in_index"].toInt();

        _dependencis[inId][inIndex] = outId;
    }

    _procent += 7.0;
    _currentFunction = &DefaultGlslCompiler::calculateNodesWeight;
}


void
DefaultGlslCompiler::
calculateNodesWeight()
{
    int procent = static_cast<int>(_procent);
    emit compileChangeState(procent, "Preparation for sorting nodes...");

    auto calcWeight = [&](QUuid uuid) {
        auto recursiveCalcWeight = [&](QUuid uuid, auto subCalc) -> int {
            auto nodeWeight = _nodesWeights.find(uuid);
            if ( nodeWeight != _nodesWeights.end() ) {
                return *nodeWeight;
            }

            const auto& nodeDependecis = _dependencis[uuid];
            if ( nodeDependecis.size() == 0 ) {
                _nodesWeights[uuid] = 0;
                return 0;
            }

            int weight = nodeDependecis.size();
            for ( auto& id : nodeDependecis ) {
                weight += subCalc(id, subCalc);
            }

            _nodesWeights[uuid] = weight;

            return weight;
        };

        recursiveCalcWeight(uuid, recursiveCalcWeight);
    };

    for ( auto id : _models.keys() ) {
        calcWeight(id);
        qDebug() << "Weight for " << id << " = " << _nodesWeights[id];
    }

    _procent += 45.0;
    _currentFunction = &DefaultGlslCompiler::sortingNodesByWeight;
}


void
DefaultGlslCompiler::
sortingNodesByWeight()
{
    int procent = static_cast<int>(_procent);
    emit compileChangeState(procent, "Sorting nodes...");

    _sortedNodesIds = _models.keys().toVector();
    std::sort( _sortedNodesIds.begin()
             , _sortedNodesIds.end()
             , [&](const QUuid& left, const QUuid& right) {
        return _nodesWeights[left] < _nodesWeights[right];
    });

    _procent += 18.0;
    _currentFunction = &DefaultGlslCompiler::generateSources;
}


void
DefaultGlslCompiler::
generateSources()
{
    int procent = static_cast<int>(_procent);
    emit compileChangeState(procent, "Preparation sources...");

    for ( auto& id : _sortedNodesIds ) {
        auto modelObj = _models[id];
        qDebug() << "Model: " << modelObj;
        _nodesTypesHandlers[modelObj["obj_type"].toString()](this, id, modelObj);
    }

    _procent += 10.0;
    _currentFunction = &DefaultGlslCompiler::buildResult;
}


void
DefaultGlslCompiler::
buildResult()
{
    int procent = static_cast<int>(_procent);
    emit compileChangeState(procent, "Building result...");

    for ( auto& line : _finalNodesStringValues ) {
        *_textStream << "\t" << line << endl;
    }

    _procent += 5.0;
    _currentFunction = &DefaultGlslCompiler::complete;
}


void
DefaultGlslCompiler::
complete()
{
    *_textStream << "}";
    _textStream->seek(0);
    emit compileComplete(_textStream->readAll());
}


void
DefaultGlslCompiler::
handleVariableNode( const QUuid& id
                  , const QJsonObject& obj )
{
    auto name = obj["obj_name"].toString();
    auto type = obj["var_t"].toString();

    if ( _reservedVariablesNames.contains(name) ) {
        name = _reservedVariablesNames[name];
    }
    else {
        name = name.split(QRegExp("\\W+"), QString::SkipEmptyParts).join("");
    }

    if ( type == "get" ) {
        _nodesStringValuesForDeploy[id] = name;
    }
    else if ( type == "set" ) {
        if ( !_dependencis[id].contains(1) ) {
            //emit compileError("Variable " + name + " not used port")
            return;
        }

         const auto& deployValue = _nodesStringValuesForDeploy[_dependencis[id][1]];
        _finalNodesStringValues.push_back( QString("%1 = %2;")
                                           .arg(name)
                                           .arg(deployValue) );
    }
}


void
DefaultGlslCompiler::
handleConstVariableNode( const QUuid& id
                       , const QJsonObject& obj )
{
    auto string = _constConvertors[obj["name"].toString()](obj["val"]);
    _nodesStringValuesForDeploy[id] = string;
}


void
DefaultGlslCompiler::
handleFunctionalNode( const QUuid& id
                    , const QJsonObject& obj )
{
    auto name = obj["name"].toString();

    if ( name == "Adder" ) {
        auto varName = QString("%1_%2")
                       .arg("add_res")
                       .arg(_f_res_index++);
        _nodesStringValuesForDeploy[id] = varName;
        _finalNodesStringValues.push_back(
                    QString("%1 %2 = %3 + %4;")
                    .arg("vec4")
                    .arg(varName)
                    .arg(_nodesStringValuesForDeploy[_dependencis[id][1]])
                    .arg(_nodesStringValuesForDeploy[_dependencis[id][2]]));
    }
}


void
DefaultGlslCompiler::
handleConverterNode( const QUuid& id
                   , const QJsonObject& obj )
{

}
