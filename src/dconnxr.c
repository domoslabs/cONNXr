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
#include "commandline-options.h"
#include <json-c/json.h>


// build/connxr test/broadcom_small.onnx test/domos/broadcom_small_input.pb
int main(int argc, char **argv){

  /* TODO: Number of inputs is hardcoded to 1. The CLI is used with
  two parameters:
    - ONNX model to use
    - .pb input to feed (This has to be modified to support an arbitrary number)
  Example: connxr model.onnx input.pb
  */
  // if (argc <  3){
  //   fprintf(stderr, "not enough arguments! %s model.onnx input.csv [--dump-file]\n", argv[0]);
  //   return 1;
  // }

  cmdoptions opts;
  if (parse_options(&opts, argc, argv)!=0) {
    fprintf(stderr, "Exiting!\n");
    return 1;
  }

/*
{
 "ModelFileName":"domos-model.onnx",
 "Dimensions":[1,49,25],
 "Features": ["tx","inbss","obss","nocat","nopkt","doze","txop","goodtx","badtx","glitch","badplcp","knoise","idle","tx_pkts","tx_bytes","tx_ucast_pkts","tx_ucast_bytes","tx_mcast_pkts","tx_mcast_pkts","tx_failures","rx_pkts","rx_bytes","rx_ucast_pkts","rx_ucast_bytes","rx_mcast_pkts","rx_mcast_bytes","rate_of_last_tx_pkt0","rx_rate","rx_decrypt_succeeds","rx_decrypt_failures","tx_data_pkts_retried","antenna_rssi_last_rx_frame0","antenna_rssi_last_rx_frame1","antenna_rssi_last_rx_frame2","antenna_rssi_last_rx_frame3","antenna_rssi_avg0","antenna_rssi_avg1","antenna_rssi_avg2","antenna_rssi_avg3","antenna_noise_floor0","antenna_noise_floor1","antenna_noise_floor2","antenna_noise_floor3","tx_retries","tx_pkts_retry_exhausted","tx_fw_total_pkts_sent","tx_fw_pkts_retries","tx_fw_pkts_retry_exhausted","rx_retries"]
}
*/

  printf("Parsing model settings json...\n");
  json_object *settings_jobj = json_object_from_file(opts.input_settings_json_file);
  if (!settings_jobj) {
    fprintf(stderr, "failed to parse or load input settings json file\n");
    return 1;
  }

  json_object *jobj;
  if(!json_object_object_get_ex(settings_jobj, "ModelFileName", &jobj)) {
    fprintf(stderr, "failed to find ModelFileName in json\n");
    return 1;
  }
  strcpy(opts.model_file, json_object_get_string(jobj));

  json_object *jarray;
  if(!json_object_object_get_ex(settings_jobj, "Dimensions", &jarray)) {
    fprintf(stderr, "failed to find Dimensions in json\n");
    return 1;
  }
  int dimensions = json_object_array_length(jarray);
  Onnx__TensorProto tmp_proto = {0};
  Onnx__TensorProto *input2 = &tmp_proto;
  onnx__tensor_proto__init(input2);
  input2->n_dims = dimensions; // 3 dimensions
  input2->dims = malloc(input2->n_dims*sizeof(int64_t));
  for(int i=0; i<dimensions; i++)
    input2->dims[i] = json_object_get_int64(json_object_array_get_idx(jarray,i));

  strcpy(opts.model_file, json_object_get_string(jobj));
  printf("object file from json is %s\n", opts.model_file);
  json_object_put(settings_jobj);


  printf("Loading model %s...\n", opts.model_file);
  Onnx__ModelProto *model = openOnnxFile(opts.model_file);
  if (model != NULL){
    printf("ok!\n");
  }else{
    fprintf(stderr, "Failed to load model!\n");
    return 1;
  }
  TRACE_MODEL(2, true, model);

  printf("Loading input %s...\n", opts.csv_file);
  // Onnx__TensorProto *inp0set0 = openTensorProtoFile(argv[2]);

  Onnx__TensorProto *inp0set0 = NULL;

  FILE *csv = fopen(opts.csv_file, "r");
  if (csv==NULL) {
    fprintf(stderr, "Failed to open csv file %s\n", opts.csv_file);
    return 1;
  }
  
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
