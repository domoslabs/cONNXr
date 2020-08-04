//this file was generated by ../../../../../../scripts/onnx_generator/OperatorTemplate.py
#include "operator__ai_onnx__mul__7.h"
#include "tracing.h"
#include "utils.h"

operator_status
execute_operator__ai_onnx__mul__7__T_tensor_float(
    node_context *ctx
)
{
    TRACE_ENTRY(1);

    TRACE_NODE(2, true, ctx->onnx_node);

    /* UNCOMMENT AS NEEDED */

    Onnx__TensorProto *i_A = searchInputByName(ctx, 0);
    Onnx__TensorProto *i_B = searchInputByName(ctx, 1);

    TRACE_TENSOR(2, true, i_A);
    TRACE_TENSOR(2, true, i_B);

    // context_operator__ai_onnx__mul__7 *op_ctx = ctx->executer_context;

    Onnx__TensorProto *o_C = searchOutputByName(ctx, 0);

    TRACE_TENSOR(2, true, o_C);

    /* DO CALCULATION HERE */

    for (int i = 0; i < o_C->n_float_data; i++){
        float A = i_A->float_data[i];
        float B = (i_B->n_float_data > 1)?i_B->float_data[i]:i_B->float_data[0];
        o_C->float_data[i] = A * B;
    }

    TRACE_EXIT(1);

    /* CHANGE RETURN CODE IF THIS EXECUTER IS VALID */
    // return OP_ENOSYS;
    return OP_OK;
}