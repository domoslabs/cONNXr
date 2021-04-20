//this file was generated by ../../../../../../scripts/onnx_generator/OperatorHeader.py
# ifndef OPERATOR_OPERATOR__AI_ONNX__ADD__7_H
# define OPERATOR_OPERATOR__AI_ONNX__ADD__7_H

# include "operators/operator.h"
# include "operators/operator_stub.h"
# include "operators/operator_info.h"

/**
 * ai.onnx operator 'Add' version 7
 *
 * @param[in]  ctx  Operator context
 * @return          Status code
 *
 * Performs element-wise binary addition (with Numpy-style broadcasting support).
 *
 * This operator supports **multidirectional (i.e., Numpy-style) broadcasting**; for more details please check [the doc](Broadcasting.md).
 *
 * Constraint T:
 *   Constrain input and output types to high-precision numeric tensors.
 *   Allowed Types: tensor_double, tensor_float, tensor_float16, tensor_int32,
 *                  tensor_int64, tensor_uint32, tensor_uint64
 * Input T A:
 *   First operand.
 *   Allowed Types: tensor_double, tensor_float, tensor_float16, tensor_int32,
 *                  tensor_int64, tensor_uint32, tensor_uint64
 *
 * Input T B:
 *   Second operand.
 *   Allowed Types: tensor_double, tensor_float, tensor_float16, tensor_int32,
 *                  tensor_int64, tensor_uint32, tensor_uint64
 * Output T C:
 *   Result, has same element type as two inputs
 *   Allowed Types: tensor_double, tensor_float, tensor_float16, tensor_int32,
 *                  tensor_int64, tensor_uint32, tensor_uint64

 *
 * @since version 7
 *
 * @see io/onnx/onnx/defs/math/defs.cc:124
 * @see https://github.com/onnx/onnx/blob/master/docs/Operators.md#Add
 */

operator_status
prepare_operator__ai_onnx__add__7(
    node_context *ctx
);

extern operator_info info_operator__ai_onnx__add__7;

typedef struct {
// no attributes
} context_operator__ai_onnx__add__7;

operator_executer
resolve_operator__ai_onnx__add__7(
    node_context *ctx
);

operator_status
execute_operator__ai_onnx__add__7__T_tensor_double(
    node_context *ctx
);

operator_status
execute_operator__ai_onnx__add__7__T_tensor_float(
    node_context *ctx
);

operator_status
execute_operator__ai_onnx__add__7__T_tensor_float16(
    node_context *ctx
);

operator_status
execute_operator__ai_onnx__add__7__T_tensor_int32(
    node_context *ctx
);

operator_status
execute_operator__ai_onnx__add__7__T_tensor_int64(
    node_context *ctx
);

operator_status
execute_operator__ai_onnx__add__7__T_tensor_uint32(
    node_context *ctx
);

operator_status
execute_operator__ai_onnx__add__7__T_tensor_uint64(
    node_context *ctx
);

# endif