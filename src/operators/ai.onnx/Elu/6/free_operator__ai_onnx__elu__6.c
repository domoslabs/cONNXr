//this file was generated by ../../../../../../scripts/onnx_generator/OperatorTemplate.py
#include "operator__ai_onnx__elu__6.h"
#include "tracing.h"
#include "utils.h"

void
free_operator__ai_onnx__elu__6(
    node_context *ctx
)
{
    TRACE_ENTRY(1);

    TRACE_NODE(2, true, ctx->onnx_node);

    /* UNCOMMENT AS NEEDED */

    // Onnx__TensorProto *i_X = searchInputByName(ctx, 0);

    // TRACE_TENSOR(2, true, i_X);

    // Onnx__AttributeProto *a_alpha = searchAttributeNyName(ctx->onnx_node->n_attribute,ctx->onnx_node->attribute,"alpha");

    // TRACE_ATTRIBUTE(2, a_alpha, a_alpha);

    // Onnx__TensorProto *o_Y = searchOutputByName(ctx, 0);

    // TRACE_TENSOR(2, true, o_Y);

    /* FREE CONTEXT HERE IF NEEDED */

    // context_operator__ai_onnx__elu__6 *op_ctx = ctx->executer_context;

    // TRACE_VAR(2, true, op_ctx->alpha, "%f");

    

    // free(op_ctx);


    /* FREE OUTPUT DATA_TYPE AND SHAPE HERE */
    /* DO NOT FREE THE TENSOR ITSELF */

    // freeTensorData(o_Y);
    // free(o_Y->dims);

    TRACE_EXIT(1);
}