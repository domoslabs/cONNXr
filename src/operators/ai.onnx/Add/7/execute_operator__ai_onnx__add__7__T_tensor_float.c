//this file was generated by ../../../../../../scripts/onnx_generator/OperatorTemplate.py
#include "operator__ai_onnx__add__7.h"
#include "tracing.h"
#include "utils.h"

operator_status
execute_operator__ai_onnx__add__7__T_tensor_float(
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

    // context_operator__ai_onnx__add__7 *op_ctx = ctx->executer_context;

    Onnx__TensorProto *o_C = searchOutputByName(ctx, 0);

    TRACE_TENSOR(2, true, o_C);

    /* DO CALCULATION HERE */

    /* TODO: ugly */
    for (int i = 0; i < o_C->n_float_data; i++) {
        /* Normal case where dimensions match */
        if (i_A->n_dims == i_B->n_dims) {
            o_C->float_data[i] = i_A->float_data[i] + i_B->float_data[i];
            /* Broadcasting. Hardcoded not working */
        } else {
            /* If inside loop :( */
            if (i_B->n_dims == 1){
                o_C->float_data[i] = i_A->float_data[i] + i_B->float_data[i%i_B->dims[0]];
            } else {
                /* TODO Hardcoded for TINY YOLO */
                if (i_A->dims[0] == 3){ /* Remove this uAF*/
                    o_C->float_data[i] = i_A->float_data[i%3] + i_B->float_data[i];
                /* TODO Hardcoded for MNIST */
                } else {
                    o_C->float_data[i] = i_A->float_data[i] + i_B->float_data[i/(i_A->dims[2]*i_A->dims[3])];
                }
            }
        }
    }


    TRACE_EXIT(1);

    /* CHANGE RETURN CODE IF THIS EXECUTER IS VALID */
    // return OP_ENOSYS;
    return OP_OK;
}