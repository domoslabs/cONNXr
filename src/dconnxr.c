#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "onnx.pb-c.h"
#include "tracing.h"
#include "inference.h"
#include "utils.h"
#include "csv.h"


// build/connxr test/broadcom_small.onnx test/domos/broadcom_small_input.pb
int main(int argc, char **argv){

  /* TODO: Number of inputs is hardcoded to 1. The CLI is used with
  two parameters:
    - ONNX model to use
    - .pb input to feed (This has to be modified to support an arbitrary number)
  Example: connxr model.onnx input.pb
  */
  if (argc <  3){
    fprintf(stderr, "not enough arguments! %s model.onnx input.csv [--dump-file]\n", argv[0]);
    return 1;
  }
  printf("Loading model %s...\n", argv[1]);
  Onnx__ModelProto *model = openOnnxFile(argv[1]);
  if (model != NULL){
    printf("ok!\n");
  }else{
    printf("Failed to load model!\n");
  }
  TRACE_MODEL(2, true, model);

  printf("Loading input %s...\n", argv[2]);
  // Onnx__TensorProto *inp0set0 = openTensorProtoFile(argv[2]);

  Onnx__TensorProto *inp0set0 = NULL;

  FILE *csv = fopen(argv[2],"r");

  char static_fpingdq_splited_header[MAX_FIELDS][MAX_FIELD_LEN] = {0};
  char *fpingdq_splited_header[MAX_FIELDS];
  char static_tmp_splited_csv[MAX_FIELDS][MAX_FIELD_LEN] = {0};
  char *tmp_splited_csv[MAX_FIELDS];

  for(int i = 0; i < MAX_FIELDS; i++){
    tmp_splited_csv[i] = static_tmp_splited_csv[i];
    fpingdq_splited_header[i] = static_fpingdq_splited_header[i];
  }

  int header_fields = 0;
  struct brcm_csv_data test[120];
  int counter = 0;
  int buff_len = 1024;
  char buffer[buff_len];
  while(fgets(buffer, buff_len, csv)) {
    if(counter == 0) {
      header_fields = csv_split_line(buffer, fpingdq_splited_header, MAX_FIELDS);
    } else {
      int csvlen = csv_split_line(buffer,tmp_splited_csv,MAX_FIELDS);
      brcm_csv_to_structs(fpingdq_splited_header,header_fields,tmp_splited_csv,csvlen,&test[counter-1]);
    }
    counter++;
    if(counter > 120) {
      break;
    }
  }
  fclose(csv);

  Onnx__TensorProto tmp_proto = {0};
  Onnx__TensorProto *input2 = &tmp_proto;
  onnx__tensor_proto__init(input2);

  input2->n_dims = 3;
  input2->dims = malloc(input2->n_dims*sizeof(int64_t));
  input2->dims[0] = 1;
  input2->dims[1] = 49;
  input2->dims[2] = 120;

  printf("n_dims %ld \n",input2->n_dims);
  for(int i = 0; i<input2->n_dims; i++){
    printf(" %ld ",input2->dims[i]);
  }
  printf("\n");

  int row_len = input2->dims[1];
  int cols = input2->dims[2];
  input2->n_float_data = cols * row_len;
  input2->float_data = malloc(sizeof(float)* input2->n_float_data);

  for(int i = 0; i < cols; i++){
    struct brcm_csv_data *row = &test[i];
    input2->float_data[row_len*i + 0] = (float)row->chanim.tx;
    input2->float_data[row_len*i + 1] = (float)row->chanim.inbss;
    input2->float_data[row_len*i + 2] = (float)row->chanim.obss;
    input2->float_data[row_len*i + 3] = (float)row->chanim.nocat;
    input2->float_data[row_len*i + 4] = (float)row->chanim.nopkt;
    input2->float_data[row_len*i + 5] = (float)row->chanim.doze;
    input2->float_data[row_len*i + 6] = (float)row->chanim.txop;
    input2->float_data[row_len*i + 7] = (float)row->chanim.goodtx;
    input2->float_data[row_len*i + 8] = (float)row->chanim.badtx;
    input2->float_data[row_len*i + 9] = (float)row->chanim.glitch;
    input2->float_data[row_len*i + 10] = (float)row->chanim.badplcp;
    input2->float_data[row_len*i + 11] = (float)row->chanim.knoise;
    input2->float_data[row_len*i + 12] = (float)row->chanim.idle;
    input2->float_data[row_len*i + 13] = (float)row->sta_info.tx_pkts;
    input2->float_data[row_len*i + 14] = (float)row->sta_info.tx_bytes;
    input2->float_data[row_len*i + 15] = (float)row->sta_info.tx_ucast_pkts;
    input2->float_data[row_len*i + 16] = (float)row->sta_info.tx_ucast_bytes;
    input2->float_data[row_len*i + 17] = (float)row->sta_info.tx_mcast_pkts;
    input2->float_data[row_len*i + 18] = (float)row->sta_info.tx_mcast_pkts;
    input2->float_data[row_len*i + 19] = (float)row->sta_info.tx_failures;
    input2->float_data[row_len*i + 20] = (float)row->sta_info.rx_pkts;
    input2->float_data[row_len*i + 21] = (float)row->sta_info.rx_bytes;
    input2->float_data[row_len*i + 22] = (float)row->sta_info.rx_ucast_pkts;
    input2->float_data[row_len*i + 23] = (float)row->sta_info.rx_ucast_bytes;
    input2->float_data[row_len*i + 24] = (float)row->sta_info.rx_mcast_pkts;
    input2->float_data[row_len*i + 25] = (float)row->sta_info.rx_mcast_bytes;
    input2->float_data[row_len*i + 26] = (float)row->sta_info.rate_of_last_tx_pkt[0];
    input2->float_data[row_len*i + 27] = (float)row->sta_info.rx_rate;
    input2->float_data[row_len*i + 28] = (float)row->sta_info.rx_decrypt_succeeds;
    input2->float_data[row_len*i + 29] = (float)row->sta_info.rx_decrypt_failures;
    input2->float_data[row_len*i + 30] = (float)row->sta_info.tx_data_pkts_retried;
    input2->float_data[row_len*i + 31] = (float)row->sta_info.antenna_rssi_last_rx_frame[0];
    input2->float_data[row_len*i + 32] = (float)row->sta_info.antenna_rssi_last_rx_frame[1];
    input2->float_data[row_len*i + 33] = (float)row->sta_info.antenna_rssi_last_rx_frame[2];
    input2->float_data[row_len*i + 34] = (float)row->sta_info.antenna_rssi_last_rx_frame[3];
    input2->float_data[row_len*i + 35] = (float)row->sta_info.antenna_rssi_avg[0];
    input2->float_data[row_len*i + 36] = (float)row->sta_info.antenna_rssi_avg[0];
    input2->float_data[row_len*i + 37] = (float)row->sta_info.antenna_rssi_avg[0];
    input2->float_data[row_len*i + 38] = (float)row->sta_info.antenna_rssi_avg[0];
    input2->float_data[row_len*i + 39] = (float)row->sta_info.antenna_noise_floor[0];
    input2->float_data[row_len*i + 40] = (float)row->sta_info.antenna_noise_floor[0];
    input2->float_data[row_len*i + 41] = (float)row->sta_info.antenna_noise_floor[0];
    input2->float_data[row_len*i + 42] = (float)row->sta_info.antenna_noise_floor[0];
    input2->float_data[row_len*i + 43] = (float)row->sta_info.tx_retries;
    input2->float_data[row_len*i + 44] = (float)row->sta_info.tx_pkts_retry_exhausted;
    input2->float_data[row_len*i + 45] = (float)row->sta_info.tx_fw_total_pkts_sent;
    input2->float_data[row_len*i + 46] = (float)row->sta_info.tx_fw_pkts_retries;
    input2->float_data[row_len*i + 47] = (float)row->sta_info.tx_fw_pkts_retry_exhausted;
    input2->float_data[row_len*i + 48] = (float)row->sta_info.rx_retries;
  }

  input2->data_type = ONNX__TENSOR_PROTO__DATA_TYPE__FLOAT;
  inp0set0 = input2;

  if (inp0set0 != NULL){printf("ok!\n");}
  TRACE_TENSOR(2, true, inp0set0);

  //Debug_PrintModelInformation(model);
  //debug_prettyprint_model(model);
  convertRawDataOfTensorProto(inp0set0);

  printf("values = %d\n", inp0set0->data_type);

  inp0set0->name = model->graph->input[0]->name;

  Onnx__TensorProto *inputs[] = { inp0set0 };
  clock_t start, end;
  double cpu_time_used;

  printf("Resolving model...\n");
  resolve(model, inputs, 1);
  printf("Running inference on %s model...\n", model->graph->name);
  start = clock();
  inference(model, inputs, 1);
  end = clock();
  printf("finished!\n");

  // TODO Is CLOCKS_PER_SEC ok to use?
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Predicted in %f cycles or %f seconds\n", (double) (end - start), cpu_time_used);

  /* Print the last output which should be the model output */
  for (int i = 0; i < all_context[_populatedIdx].outputs[0]->n_float_data; i++){
    printf("n_float_data[%d] = %f\n", i, all_context[_populatedIdx].outputs[0]->float_data[i]);
  }

  if ((argc == 4) && !strcmp(argv[3], "--dump-file")){
    printf("Writing dump file with intermediate outputs\n");
    //int max_print = 10;
    FILE *fp = fopen("dump.txt", "w+");
    for (int i = 0; i < _populatedIdx + 1; i++){
      fprintf(fp, "name=%s\n", all_context[i].outputs[0]->name);
      fprintf(fp, "shape=");
      for (int dim_index = 0; dim_index < all_context[i].outputs[0]->n_dims; dim_index++){
        fprintf(fp, "%" PRId64 ",", all_context[i].outputs[0]->dims[dim_index]);
      }
      fprintf(fp, "\n");
      //int float_to_print = all_context[i].outputs[0]->n_float_data > max_print ? max_print : all_context[i].outputs[0]->n_float_data;
      fprintf(fp, "tensor=");
      /* TODO: Just implemented for float */
      for (int data_index = 0; data_index < all_context[i].outputs[0]->n_float_data; data_index++){
        fprintf(fp, "%f,", all_context[i].outputs[0]->float_data[data_index]);
      }
      fprintf(fp, "\n");
    }
    fclose(fp);
  }
}
