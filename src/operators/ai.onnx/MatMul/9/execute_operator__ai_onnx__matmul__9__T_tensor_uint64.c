//this file was generated by ../../../../../../scripts/onnx_generator/OperatorTemplate.py
#include "operator__ai_onnx__matmul__9.h"
#include "tracing.h"
#include "utils.h"

operator_status
execute_operator__ai_onnx__matmul__9__T_tensor_uint64(
    node_context *ctx
)
{
    TRACE_ENTRY(1);

    TRACE_NODE(2, true, ctx->onnx_node);

    /* UNCOMMENT AS NEEDED */

    // Onnx__TensorProto *i_A = searchInputByName(ctx, 0);
    // Onnx__TensorProto *i_B = searchInputByName(ctx, 1);

    // TRACE_TENSOR(2, true, i_A);
    // TRACE_TENSOR(2, true, i_B);

    // context_operator__ai_onnx__matmul__9 *op_ctx = ctx->executer_context;

    

    

    // Onnx__TensorProto *o_Y = searchOutputByName(ctx, 0);

    // TRACE_TENSOR(2, true, o_Y);

    /* DO CALCULATION HERE */


    TRACE_EXIT(1);

    /* CHANGE RETURN CODE IF THIS EXECUTER IS VALID */
    return OP_ENOSYS;
    // return OP_OK;
}