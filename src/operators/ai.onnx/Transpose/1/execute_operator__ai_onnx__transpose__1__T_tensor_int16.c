//this file was generated by ../../../../../../scripts/onnx_generator/OperatorTemplate.py
#include "operator__ai_onnx__transpose__1.h"
#include "tracing.h"
#include "utils.h"

operator_status
execute_operator__ai_onnx__transpose__1__T_tensor_int16(
    node_context *ctx
)
{
    TRACE_ENTRY(1);

    TRACE_NODE(2, true, ctx->onnx_node);

    /* UNCOMMENT AS NEEDED */

    // Onnx__TensorProto *i_data = searchInputByName(ctx, 0);

    // TRACE_TENSOR(2, true, i_data);

    // context_operator__ai_onnx__transpose__1 *op_ctx = ctx->executer_context;

    // size_t n_perm = op_ctx->n_perm;
    // int64_t* perm = op_ctx->perm;

    // TRACE_ARRAY(2, true, perm, , n_perm, "%" PRId64);

    // Onnx__TensorProto *o_transposed = searchOutputByName(ctx, 0);

    // TRACE_TENSOR(2, true, o_transposed);

    /* DO CALCULATION HERE */


    TRACE_EXIT(1);

    /* CHANGE RETURN CODE IF THIS EXECUTER IS VALID */
    return OP_ENOSYS;
    // return OP_OK;
}