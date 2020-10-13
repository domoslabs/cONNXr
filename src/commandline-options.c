#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "commandline-options.h"

void print_usage();

void print_usage(){
    printf("Usage: dconnxr [options]\n");
    printf("\n");
    printf("options:\n");
    printf("    -s  Model input Settings json file\n");
    printf("    -c  CSV file\n");
    // printf("    -m  ONNX model file\n");
    printf("    -h  print this\n");
}

int parse_options(cmdoptions *cmdopts, int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "c:s:m:h")) != -1) {
        switch (opt) {
        case 'c':
            strncpy(cmdopts->csv_file, optarg, sizeof(cmdopts->csv_file));
            break;
        case 's':
            strncpy(cmdopts->input_settings_json_file, optarg, sizeof(cmdopts->input_settings_json_file));
            break;
        // case 'm':
        //     strncpy(cmdopts->model_file, optarg, sizeof(cmdopts->model_file));
        //     break;
        case 'h':
        default:
            print_usage();
            return 1;
        }
    }
    return 0;
}
