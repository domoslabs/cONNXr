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
  char fullpath[128]={0};
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
  sprintf(fullpath, "%s/%s", opts.path, opts.model_config_filename);
  json_object *settings_jobj = json_object_from_file(fullpath);
  if (!settings_jobj) {
    fprintf(stderr, "failed to parse or load input settings json file %s\n", fullpath);
    return 1;
  }

  json_object *jobj;
  if(!json_object_object_get_ex(settings_jobj, "ModelFileName", &jobj)) {
    fprintf(stderr, "failed to find ModelFileName in json\n");
    return 1;
  }
  strcpy(opts.model_filename, json_object_get_string(jobj));

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
  for(int i=0; i<dimensions; i++) {
    input2->dims[i] = json_object_get_int64(json_object_array_get_idx(jarray,i));
  }

  printf("n_dims %ld \n",input2->n_dims);
  for(int i = 0; i<input2->n_dims; i++){
    printf(" %"PRId64" ", input2->dims[i]);
  }
  printf("\n");

  strcpy(opts.model_filename, json_object_get_string(jobj));

  sprintf(fullpath, "%s/%s", opts.path, opts.model_filename);
  printf("object file from json is %s\n", fullpath);

  printf("Loading model %s...\n", fullpath);
  Onnx__ModelProto *model = openOnnxFile(fullpath);
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
  
  // prepare 2D array
  char static_fpingdq_splitted_header[MAX_FIELDS][MAX_FIELD_LEN] = {0};
  char *fpingdq_splitted_header[MAX_FIELDS];
  char static_tmp_splitted_csv[MAX_FIELDS][MAX_FIELD_LEN] = {0};
  char *tmp_splitted_csv[MAX_FIELDS];
  char static_feature_field_names[MAX_FIELDS][MAX_FIELD_LEN] = {0};
  char *feature_field_names[MAX_FIELDS];

  for(int i = 0; i < MAX_FIELDS; i++){
    tmp_splitted_csv[i] = static_tmp_splitted_csv[i];
    fpingdq_splitted_header[i] = static_fpingdq_splitted_header[i];
    feature_field_names[i] = static_feature_field_names[i];
  }

  // extract  model features field names and
  if(!json_object_object_get_ex(settings_jobj, "Features", &jarray)) {
    fprintf(stderr, "failed to find Features array in json\n");
    return 1;
  }
  int feature_fields = json_object_array_length(jarray);
  if (feature_fields!=(int)(input2->dims[1])) {
    fprintf(stderr, "feature fields array length %d does not match dimensions %"PRId64"\n", feature_fields, input2->dims[1]);
    return 1;
  }
  for(int i = 0; i < feature_fields; i++){
    strncpy(feature_field_names[i],
    json_object_get_string(json_object_array_get_idx(jarray,i)), MAX_FIELDS);
  }
  json_object_put(settings_jobj);

  // copy data from csv into input->float data.
  int row_len = (int)(input2->dims[1]);
  int cols = (int)(input2->dims[2]);
  input2->n_float_data = cols * row_len;
  input2->float_data = malloc(sizeof(float)* input2->n_float_data);

  //int colidx = 0; // column index of float_data
  int header_fields = 0;
  //struct brcm_csv_data test[120];
  int counter = 0;
  int buff_len = 1024;
  char buffer[buff_len];
  int index_of_mac=0;
  while(fgets(buffer, buff_len, csv)) {
    if(counter == 0) {
      header_fields = csv_split_line(buffer, fpingdq_splitted_header, MAX_FIELDS);
      index_of_mac = csv_get_index_from_field_name(fpingdq_splitted_header, header_fields, "mac");
      counter++;
      if(counter > cols){
        break;
    }
    } else {
      int csvlen = csv_split_line(buffer,tmp_splitted_csv,MAX_FIELDS);
      //brcm_csv_to_structs(fpingdq_splitted_header,header_fields,tmp_splitted_csv,csvlen,&test[counter-1]);
      if (strlen(opts.mac)>0) {
        //printf("csv line has mac %s\nopts.mac =       %s\n", tmp_splitted_csv[index_of_mac], opts.mac);
        if (strcasecmp(opts.mac, tmp_splitted_csv[index_of_mac])!=0) {
          //printf("mac not match\n");
          continue;
        }
      }
      csv_to_model_vector(
        fpingdq_splitted_header, header_fields,
        feature_field_names, feature_fields,
        tmp_splitted_csv, csvlen,
        &(input2->float_data[row_len*(counter-1) + 0])
      );
      // &(input2->float_data[row_len*colidx + 0]) = (float)row->chanim.tx;
      counter++;
      if(counter > cols){
        break;
      }
    }
  }
  fclose(csv);

  // print first and second row...
  for (int i = 0; i < row_len; i++)
    printf(" %02f", input2->float_data[row_len*0 + i]);
  printf("\n");
  for (int i = 0; i < row_len; i++)
    printf(" %2f", input2->float_data[row_len*1 + i]);
  
  printf("\n");

  if (counter<cols) {
    fprintf(stderr, "not enough lines in the csv file\n");
    return 1;
  }

    // input2->float_data[row_len*i + 48] = (float)row->sta_info.rx_retries;

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
