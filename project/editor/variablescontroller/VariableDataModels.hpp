#ifndef VARIABLEDATAMODELS_HPP
#define VARIABLEDATAMODELS_HPP

#include <cinttypes>
#include <QString>
#include <QMetaType>
#include <array>
#include <memory>

enum class VariableLogickType {
    Input,  /// Input shader pipline variable
    User,   /// User defined variable
    Output, /// Output shader pipline variable
};


struct VariableDataModel
{
    QString name;
    VariableLogickType logickType;
    bool isConst;
    bool canBeEdited;
};

Q_DECLARE_METATYPE(VariableDataModel)
Q_DECLARE_METATYPE(std::shared_ptr<VariableDataModel>)
Q_DECLARE_OPAQUE_POINTER(VariableDataModel*)


template<typename T>
struct VariableDataModelTemplate : public VariableDataModel {
    T value;
};

typedef VariableDataModelTemplate<bool> BooleanDataModel;
Q_DECLARE_METATYPE(BooleanDataModel)
Q_DECLARE_METATYPE(std::shared_ptr<BooleanDataModel>)
Q_DECLARE_OPAQUE_POINTER(BooleanDataModel*)

typedef VariableDataModelTemplate<int32_t> IntegerDataModel;
Q_DECLARE_METATYPE(IntegerDataModel)
Q_DECLARE_METATYPE(std::shared_ptr<IntegerDataModel>)
Q_DECLARE_OPAQUE_POINTER(IntegerDataModel*)

typedef VariableDataModelTemplate<uint32_t> UnsignedIntegerDataModel;
Q_DECLARE_METATYPE(UnsignedIntegerDataModel)
Q_DECLARE_METATYPE(std::shared_ptr<UnsignedIntegerDataModel>)
Q_DECLARE_OPAQUE_POINTER(UnsignedIntegerDataModel*)

/*
typedef VariableDataModel<int64_t> LongDataModel;
Q_DECLARE_METATYPE(LongDataModel)

typedef VariableDataModel<uint64_t> UnsignedLongDataModel;
Q_DECLARE_METATYPE(UnsignedLongDataModel)
*/

typedef VariableDataModelTemplate<float> FloatDataModel;
Q_DECLARE_METATYPE(FloatDataModel)
Q_DECLARE_METATYPE(std::shared_ptr<FloatDataModel>)
Q_DECLARE_OPAQUE_POINTER(FloatDataModel*)

typedef VariableDataModelTemplate<double> DoubleDataModel;
Q_DECLARE_METATYPE(DoubleDataModel)
Q_DECLARE_METATYPE(std::shared_ptr<DoubleDataModel>)
Q_DECLARE_OPAQUE_POINTER(DoubleDataModel*)


using Array2 = std::array<float, 2>;
using Array3 = std::array<float, 3>;
using Array4 = std::array<float, 4>;

typedef VariableDataModelTemplate<Array2> Vec2DataModel;
Q_DECLARE_METATYPE(Vec2DataModel)
Q_DECLARE_METATYPE(std::shared_ptr<Vec2DataModel>)
Q_DECLARE_OPAQUE_POINTER(Vec2DataModel*)

typedef VariableDataModelTemplate<Array3> Vec3DataModel;
Q_DECLARE_METATYPE(Vec3DataModel)
Q_DECLARE_METATYPE(std::shared_ptr<Vec3DataModel>)
Q_DECLARE_OPAQUE_POINTER(Vec3DataModel*)

typedef VariableDataModelTemplate<Array4> Vec4DataModel;
Q_DECLARE_METATYPE(Vec4DataModel)
Q_DECLARE_METATYPE(std::shared_ptr<Vec4DataModel>)
Q_DECLARE_OPAQUE_POINTER(Vec4DataModel*)


using Mat2x2 = std::array<float, 4>;
using Mat3x3 = std::array<float, 9>;
using Mat4x4 = std::array<float, 16>;

typedef VariableDataModelTemplate<Mat2x2> Mat2x2DataModel;
//Q_DECLARE_METATYPE(Mat2x2DataModel)
//Q_DECLARE_METATYPE(std::shared_ptr<Mat2x2DataModel>)
//Q_DECLARE_OPAQUE_POINTER(Mat2x2DataModel*)

typedef VariableDataModelTemplate<Mat3x3> Mat3x3DataModel;
Q_DECLARE_METATYPE(Mat3x3DataModel)
Q_DECLARE_METATYPE(std::shared_ptr<Mat3x3DataModel>)
Q_DECLARE_OPAQUE_POINTER(Mat3x3DataModel*)

typedef VariableDataModelTemplate<Mat4x4> Mat4x4DataModel;
Q_DECLARE_METATYPE(Mat4x4DataModel)
Q_DECLARE_METATYPE(std::shared_ptr<Mat4x4DataModel>)
Q_DECLARE_OPAQUE_POINTER(Mat4x4DataModel*)


#endif // VARIABLEDATAMODELS_HPP
