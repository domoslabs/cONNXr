//this file was generated by ../../../scripts/onnx_generator/OperatorSets.py
#include "operators/operator_sets.h"

#include "operators/ai.onnx/MatMul/9/operator__ai_onnx__matmul__9.h"
#include "operators/ai.onnx/Identity/1/operator__ai_onnx__identity__1.h"
#include "operators/ai.onnx/MaxPool/12/operator__ai_onnx__maxpool__12.h"
#include "operators/ai.onnx/Transpose/1/operator__ai_onnx__transpose__1.h"
#include "operators/ai.onnx/Clip/12/operator__ai_onnx__clip__12.h"
#include "operators/ai.onnx/Elu/6/operator__ai_onnx__elu__6.h"
#include "operators/ai.onnx/Relu/6/operator__ai_onnx__relu__6.h"
#include "operators/ai.onnx/Conv/11/operator__ai_onnx__conv__11.h"
#include "operators/ai.onnx/ArgMax/12/operator__ai_onnx__argmax__12.h"
#include "operators/ai.onnx/Add/7/operator__ai_onnx__add__7.h"
#include "operators/ai.onnx/LeakyRelu/6/operator__ai_onnx__leakyrelu__6.h"
#include "operators/ai.onnx/Reshape/5/operator__ai_onnx__reshape__5.h"
#include "operators/ai.onnx/GlobalAveragePool/1/operator__ai_onnx__globalaveragepool__1.h"
#include "operators/ai.onnx/Mul/7/operator__ai_onnx__mul__7.h"
#include "operators/ai.onnx/Constant/12/operator__ai_onnx__constant__12.h"
#include "operators/ai.onnx/BatchNormalization/9/operator__ai_onnx__batchnormalization__9.h"
#include "operators/ai.onnx/Sigmoid/6/operator__ai_onnx__sigmoid__6.h"
#include "operators/ai.onnx/Softmax/11/operator__ai_onnx__softmax__11.h"

operator_set operator_set__ai_onnx__1 = {
  .version = 1,
  .domain  = "ai.onnx",
  .length  = 3,
  .entries = {
    {
  .name     = "Identity",
  .preparer = prepare_operator__ai_onnx__identity__1,
  .info     = &info_operator__ai_onnx__identity__1
},{
  .name     = "Transpose",
  .preparer = prepare_operator__ai_onnx__transpose__1,
  .info     = &info_operator__ai_onnx__transpose__1
},{
  .name     = "GlobalAveragePool",
  .preparer = prepare_operator__ai_onnx__globalaveragepool__1,
  .info     = &info_operator__ai_onnx__globalaveragepool__1
}
  }
};

operator_set operator_set__ai_onnx__5 = {
  .version = 5,
  .domain  = "ai.onnx",
  .length  = 4,
  .entries = {
    {
  .name     = "Identity",
  .preparer = prepare_operator__ai_onnx__identity__1,
  .info     = &info_operator__ai_onnx__identity__1
},{
  .name     = "Transpose",
  .preparer = prepare_operator__ai_onnx__transpose__1,
  .info     = &info_operator__ai_onnx__transpose__1
},{
  .name     = "Reshape",
  .preparer = prepare_operator__ai_onnx__reshape__5,
  .info     = &info_operator__ai_onnx__reshape__5
},{
  .name     = "GlobalAveragePool",
  .preparer = prepare_operator__ai_onnx__globalaveragepool__1,
  .info     = &info_operator__ai_onnx__globalaveragepool__1
}
  }
};

operator_set operator_set__ai_onnx__6 = {
  .version = 6,
  .domain  = "ai.onnx",
  .length  = 8,
  .entries = {
    {
  .name     = "Identity",
  .preparer = prepare_operator__ai_onnx__identity__1,
  .info     = &info_operator__ai_onnx__identity__1
},{
  .name     = "Transpose",
  .preparer = prepare_operator__ai_onnx__transpose__1,
  .info     = &info_operator__ai_onnx__transpose__1
},{
  .name     = "Elu",
  .preparer = prepare_operator__ai_onnx__elu__6,
  .info     = &info_operator__ai_onnx__elu__6
},{
  .name     = "Relu",
  .preparer = prepare_operator__ai_onnx__relu__6,
  .info     = &info_operator__ai_onnx__relu__6
},{
  .name     = "LeakyRelu",
  .preparer = prepare_operator__ai_onnx__leakyrelu__6,
  .info     = &info_operator__ai_onnx__leakyrelu__6
},{
  .name     = "Reshape",
  .preparer = prepare_operator__ai_onnx__reshape__5,
  .info     = &info_operator__ai_onnx__reshape__5
},{
  .name     = "GlobalAveragePool",
  .preparer = prepare_operator__ai_onnx__globalaveragepool__1,
  .info     = &info_operator__ai_onnx__globalaveragepool__1
},{
  .name     = "Sigmoid",
  .preparer = prepare_operator__ai_onnx__sigmoid__6,
  .info     = &info_operator__ai_onnx__sigmoid__6
}
  }
};

operator_set operator_set__ai_onnx__7 = {
  .version = 7,
  .domain  = "ai.onnx",
  .length  = 10,
  .entries = {
    {
  .name     = "Identity",
  .preparer = prepare_operator__ai_onnx__identity__1,
  .info     = &info_operator__ai_onnx__identity__1
},{
  .name     = "Transpose",
  .preparer = prepare_operator__ai_onnx__transpose__1,
  .info     = &info_operator__ai_onnx__transpose__1
},{
  .name     = "Elu",
  .preparer = prepare_operator__ai_onnx__elu__6,
  .info     = &info_operator__ai_onnx__elu__6
},{
  .name     = "Relu",
  .preparer = prepare_operator__ai_onnx__relu__6,
  .info     = &info_operator__ai_onnx__relu__6
},{
  .name     = "Add",
  .preparer = prepare_operator__ai_onnx__add__7,
  .info     = &info_operator__ai_onnx__add__7
},{
  .name     = "LeakyRelu",
  .preparer = prepare_operator__ai_onnx__leakyrelu__6,
  .info     = &info_operator__ai_onnx__leakyrelu__6
},{
  .name     = "Reshape",
  .preparer = prepare_operator__ai_onnx__reshape__5,
  .info     = &info_operator__ai_onnx__reshape__5
},{
  .name     = "GlobalAveragePool",
  .preparer = prepare_operator__ai_onnx__globalaveragepool__1,
  .info     = &info_operator__ai_onnx__globalaveragepool__1
},{
  .name     = "Mul",
  .preparer = prepare_operator__ai_onnx__mul__7,
  .info     = &info_operator__ai_onnx__mul__7
},{
  .name     = "Sigmoid",
  .preparer = prepare_operator__ai_onnx__sigmoid__6,
  .info     = &info_operator__ai_onnx__sigmoid__6
}
  }
};

operator_set operator_set__ai_onnx__9 = {
  .version = 9,
  .domain  = "ai.onnx",
  .length  = 12,
  .entries = {
    {
  .name     = "MatMul",
  .preparer = prepare_operator__ai_onnx__matmul__9,
  .info     = &info_operator__ai_onnx__matmul__9
},{
  .name     = "Identity",
  .preparer = prepare_operator__ai_onnx__identity__1,
  .info     = &info_operator__ai_onnx__identity__1
},{
  .name     = "Transpose",
  .preparer = prepare_operator__ai_onnx__transpose__1,
  .info     = &info_operator__ai_onnx__transpose__1
},{
  .name     = "Elu",
  .preparer = prepare_operator__ai_onnx__elu__6,
  .info     = &info_operator__ai_onnx__elu__6
},{
  .name     = "Relu",
  .preparer = prepare_operator__ai_onnx__relu__6,
  .info     = &info_operator__ai_onnx__relu__6
},{
  .name     = "Add",
  .preparer = prepare_operator__ai_onnx__add__7,
  .info     = &info_operator__ai_onnx__add__7
},{
  .name     = "LeakyRelu",
  .preparer = prepare_operator__ai_onnx__leakyrelu__6,
  .info     = &info_operator__ai_onnx__leakyrelu__6
},{
  .name     = "Reshape",
  .preparer = prepare_operator__ai_onnx__reshape__5,
  .info     = &info_operator__ai_onnx__reshape__5
},{
  .name     = "GlobalAveragePool",
  .preparer = prepare_operator__ai_onnx__globalaveragepool__1,
  .info     = &info_operator__ai_onnx__globalaveragepool__1
},{
  .name     = "Mul",
  .preparer = prepare_operator__ai_onnx__mul__7,
  .info     = &info_operator__ai_onnx__mul__7
},{
  .name     = "BatchNormalization",
  .preparer = prepare_operator__ai_onnx__batchnormalization__9,
  .info     = &info_operator__ai_onnx__batchnormalization__9
},{
  .name     = "Sigmoid",
  .preparer = prepare_operator__ai_onnx__sigmoid__6,
  .info     = &info_operator__ai_onnx__sigmoid__6
}
  }
};

operator_set operator_set__ai_onnx__11 = {
  .version = 11,
  .domain  = "ai.onnx",
  .length  = 14,
  .entries = {
    {
  .name     = "MatMul",
  .preparer = prepare_operator__ai_onnx__matmul__9,
  .info     = &info_operator__ai_onnx__matmul__9
},{
  .name     = "Identity",
  .preparer = prepare_operator__ai_onnx__identity__1,
  .info     = &info_operator__ai_onnx__identity__1
},{
  .name     = "Transpose",
  .preparer = prepare_operator__ai_onnx__transpose__1,
  .info     = &info_operator__ai_onnx__transpose__1
},{
  .name     = "Elu",
  .preparer = prepare_operator__ai_onnx__elu__6,
  .info     = &info_operator__ai_onnx__elu__6
},{
  .name     = "Relu",
  .preparer = prepare_operator__ai_onnx__relu__6,
  .info     = &info_operator__ai_onnx__relu__6
},{
  .name     = "Conv",
  .preparer = prepare_operator__ai_onnx__conv__11,
  .info     = &info_operator__ai_onnx__conv__11
},{
  .name     = "Add",
  .preparer = prepare_operator__ai_onnx__add__7,
  .info     = &info_operator__ai_onnx__add__7
},{
  .name     = "LeakyRelu",
  .preparer = prepare_operator__ai_onnx__leakyrelu__6,
  .info     = &info_operator__ai_onnx__leakyrelu__6
},{
  .name     = "Reshape",
  .preparer = prepare_operator__ai_onnx__reshape__5,
  .info     = &info_operator__ai_onnx__reshape__5
},{
  .name     = "GlobalAveragePool",
  .preparer = prepare_operator__ai_onnx__globalaveragepool__1,
  .info     = &info_operator__ai_onnx__globalaveragepool__1
},{
  .name     = "Mul",
  .preparer = prepare_operator__ai_onnx__mul__7,
  .info     = &info_operator__ai_onnx__mul__7
},{
  .name     = "BatchNormalization",
  .preparer = prepare_operator__ai_onnx__batchnormalization__9,
  .info     = &info_operator__ai_onnx__batchnormalization__9
},{
  .name     = "Sigmoid",
  .preparer = prepare_operator__ai_onnx__sigmoid__6,
  .info     = &info_operator__ai_onnx__sigmoid__6
},{
  .name     = "Softmax",
  .preparer = prepare_operator__ai_onnx__softmax__11,
  .info     = &info_operator__ai_onnx__softmax__11
}
  }
};

operator_set operator_set__ai_onnx__12 = {
  .version = 12,
  .domain  = "ai.onnx",
  .length  = 18,
  .entries = {
    {
  .name     = "MatMul",
  .preparer = prepare_operator__ai_onnx__matmul__9,
  .info     = &info_operator__ai_onnx__matmul__9
},{
  .name     = "Identity",
  .preparer = prepare_operator__ai_onnx__identity__1,
  .info     = &info_operator__ai_onnx__identity__1
},{
  .name     = "MaxPool",
  .preparer = prepare_operator__ai_onnx__maxpool__12,
  .info     = &info_operator__ai_onnx__maxpool__12
},{
  .name     = "Transpose",
  .preparer = prepare_operator__ai_onnx__transpose__1,
  .info     = &info_operator__ai_onnx__transpose__1
},{
  .name     = "Clip",
  .preparer = prepare_operator__ai_onnx__clip__12,
  .info     = &info_operator__ai_onnx__clip__12
},{
  .name     = "Elu",
  .preparer = prepare_operator__ai_onnx__elu__6,
  .info     = &info_operator__ai_onnx__elu__6
},{
  .name     = "Relu",
  .preparer = prepare_operator__ai_onnx__relu__6,
  .info     = &info_operator__ai_onnx__relu__6
},{
  .name     = "Conv",
  .preparer = prepare_operator__ai_onnx__conv__11,
  .info     = &info_operator__ai_onnx__conv__11
},{
  .name     = "ArgMax",
  .preparer = prepare_operator__ai_onnx__argmax__12,
  .info     = &info_operator__ai_onnx__argmax__12
},{
  .name     = "Add",
  .preparer = prepare_operator__ai_onnx__add__7,
  .info     = &info_operator__ai_onnx__add__7
},{
  .name     = "LeakyRelu",
  .preparer = prepare_operator__ai_onnx__leakyrelu__6,
  .info     = &info_operator__ai_onnx__leakyrelu__6
},{
  .name     = "Reshape",
  .preparer = prepare_operator__ai_onnx__reshape__5,
  .info     = &info_operator__ai_onnx__reshape__5
},{
  .name     = "GlobalAveragePool",
  .preparer = prepare_operator__ai_onnx__globalaveragepool__1,
  .info     = &info_operator__ai_onnx__globalaveragepool__1
},{
  .name     = "Mul",
  .preparer = prepare_operator__ai_onnx__mul__7,
  .info     = &info_operator__ai_onnx__mul__7
},{
  .name     = "Constant",
  .preparer = prepare_operator__ai_onnx__constant__12,
  .info     = &info_operator__ai_onnx__constant__12
},{
  .name     = "BatchNormalization",
  .preparer = prepare_operator__ai_onnx__batchnormalization__9,
  .info     = &info_operator__ai_onnx__batchnormalization__9
},{
  .name     = "Sigmoid",
  .preparer = prepare_operator__ai_onnx__sigmoid__6,
  .info     = &info_operator__ai_onnx__sigmoid__6
},{
  .name     = "Softmax",
  .preparer = prepare_operator__ai_onnx__softmax__11,
  .info     = &info_operator__ai_onnx__softmax__11
}
  }
};

operator_sets all_operator_sets = {
  .length = 7,
  .sets   = {
    &operator_set__ai_onnx__1,
&operator_set__ai_onnx__5,
&operator_set__ai_onnx__6,
&operator_set__ai_onnx__7,
&operator_set__ai_onnx__9,
&operator_set__ai_onnx__11,
&operator_set__ai_onnx__12
  }
};