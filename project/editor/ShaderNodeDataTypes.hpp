#ifndef SHADERNODEDATATYPES_HPP
#define SHADERNODEDATATYPES_HPP

#include <nodes/NodeData>

using QtNodes::NodeDataType;

//
// SCALAR
//

struct ActionDataType : public NodeDataType {
    ActionDataType() {
        id = "a";
        name = "Action";
    }
};

struct IntegerDataType : public NodeDataType {
    IntegerDataType() {
        id = "int";
        name = "Integer";
    }
};

struct UnsignedIntegerDataType : public NodeDataType {
    UnsignedIntegerDataType() {
        id = "uint";
        name = "Unsigned integer";
    }
};

struct BooleanDataType : public NodeDataType {
    BooleanDataType() {
        id = "bool";
        name = "Boolean";
    }
};

struct FloatDataType : public NodeDataType {
    FloatDataType() {
        id = "float";
        name = "Float";
    }
};

struct DoubleDataType : public NodeDataType {
    DoubleDataType() {
        id = "double";
        name = "Double";
    }
};

//
// VECTORS
//

struct Vec2DataType : public NodeDataType {
    Vec2DataType() {
        id = "v2";
        name = "Vec2";
    }
};

struct Vec3DataType : public NodeDataType {
    Vec3DataType() {
        id = "v3";
        name = "Vec3";
    }
};

struct Vec4DataType : public NodeDataType {
    Vec4DataType() {
        id = "v4";
        name = "Vec4";
    }
};

struct DoubleVec2DataType : public NodeDataType {
    DoubleVec2DataType() {
        id = "dv2";
        name = "DVec2";
    }
};

struct DoubleVec3DataType : public NodeDataType {
    DoubleVec3DataType() {
        id = "dv3";
        name = "DVec3";
    }
};

struct DoubleVec4DataType : public NodeDataType {
    DoubleVec4DataType() {
        id = "dv4";
        name = "DVec4";
    }
};

struct BooleanVec2DataType : public NodeDataType {
    BooleanVec2DataType() {
        id = "bv2";
        name = "BVec2";
    }
};

struct BooleanVec3DataType : public NodeDataType {
    BooleanVec3DataType() {
        id = "bv3";
        name = "BVec3";
    }
};

struct BooleanVec4DataType : public NodeDataType {
    BooleanVec4DataType() {
        id = "bv4";
        name = "BVec4";
    }
};

struct IntegerVec2DataType : public NodeDataType {
    IntegerVec2DataType() {
        id = "iv2";
        name = "IVec2";
    }
};

struct IntegerVec3DataType : public NodeDataType {
    IntegerVec3DataType() {
        id = "iv3";
        name = "IVec3";
    }
};

struct IntegerVec4DataType : public NodeDataType {
    IntegerVec4DataType() {
        id = "iv4";
        name = "IVec4";
    }
};

struct UnsignedIntegerVec2DataType : public NodeDataType {
    UnsignedIntegerVec2DataType() {
        id = "uv2";
        name = "UVec2";
    }
};

struct UnsignedIntegerVec3DataType : public NodeDataType {
    UnsignedIntegerVec3DataType() {
        id = "uv3";
        name = "UVec3";
    }
};

struct UnsignedIntegerVec4DataType : public NodeDataType {
    UnsignedIntegerVec4DataType() {
        id = "uv4";
        name = "UVec4";
    }
};

//
// MATRIX
//

struct Matrix2DataType : public NodeDataType {
    Matrix2DataType() {
        id = "mat2";
        name = "Mat2x2";
    }
};

struct Matrix3DataType : public NodeDataType {
    Matrix3DataType() {
        id = "mat3";
        name = "Mat3x3";
    }
};

struct Matrix4DataType : public NodeDataType {
    Matrix4DataType() {
        id = "mat4";
        name = "Mat4x4";
    }
};

struct DoubleMatrix2DataType : public NodeDataType {
    DoubleMatrix2DataType() {
        id = "dmat2";
        name = "DMat2x2";
    }
};

struct DoubleMatrix3DataType : public NodeDataType {
    DoubleMatrix3DataType() {
        id = "dmat3";
        name = "DMat3x3";
    }
};

struct DoubleMatrix4DataType : public NodeDataType {
    DoubleMatrix4DataType() {
        id = "dmat4";
        name = "DMat4x4";
    }
};

//
// Textures
//
struct Texture1D_DataType : public NodeDataType {
    Texture1D_DataType() {
        id = "tex1d";
        name = "Texture 1D";
    }
};

struct Texture2D_DataType : public NodeDataType {
    Texture2D_DataType() {
        id = "tex2d";
        name = "Texture 2D";
    }
};

struct Texture3D_DataType : public NodeDataType {
    Texture3D_DataType() {
        id = "tex3d";
        name = "Texture 3D";
    }
};

struct TextureCube_DataType : public NodeDataType {
    TextureCube_DataType() {
        id = "cube";
        name = "Cube texture";
    }
};

//
// ARRAYS
//

struct IntegerArrayDataType : public NodeDataType {
    IntegerArrayDataType() {
        id = "int[]";
        name = "Integer array";
    }
};

struct UnsignedIntegerArrayDataType : public NodeDataType {
    UnsignedIntegerArrayDataType() {
        id = "uint[]";
        name = "Unsigned integer array";
    }
};

struct BooleanArrayDataType : public NodeDataType {
    BooleanArrayDataType() {
        id = "bool[]";
        name = "Boolean array";
    }
};

struct FloatArrayDataType : public NodeDataType {
    FloatArrayDataType() {
        id = "float[]";
        name = "Float array";
    }
};

struct DoubleArrayDataType : public NodeDataType {
    DoubleArrayDataType() {
        id = "double[]";
        name = "Double array";
    }
};

#endif // SHADERNODEDATATYPES_HPP
