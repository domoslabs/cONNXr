//this file was generated by ../../../../../../scripts/onnx_generator/OperatorTemplate.py
#include "operator__ai_onnx__clip__12.h"
#include "tracing.h"
#include "utils.h"

operator_status
execute_operator__ai_onnx__clip__12__T_tensor_uint32(
    node_context *ctx
)
{
    TRACE_ENTRY(1);

    TRACE_NODE(2, true, ctx->onnx_node);

    /* UNCOMMENT AS NEEDED */

    // Onnx__TensorProto *i_input = searchInputByName(ctx, 0);
    // Onnx__TensorProto *i_min = searchInputByName(ctx, 1);
    // Onnx__TensorProto *i_max = searchInputByName(ctx, 2);

    // TRACE_TENSOR(2, true, i_input);
    // TRACE_TENSOR(2, min, i_min);
    // TRACE_TENSOR(2, max, i_max);

    // context_operator__ai_onnx__clip__12 *op_ctx = ctx->executer_context;

    

    

    // Onnx__TensorProto *o_output = searchOutputByName(ctx, 0);

    // TRACE_TENSOR(2, true, o_output);

    /* DO CALCULATION HERE */


    TRACE_EXIT(1);

    /* CHANGE RETURN CODE IF THIS EXECUTER IS VALID */
    return OP_ENOSYS;
    // return OP_OK;
}