#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "commandline-options.h"

void print_usage();

void print_usage(){
    printf("Usage: dconnxr [options]\n");
    printf("\n");
    printf("options:\n");
    printf("    -s  ONNX model config file\n");
    printf("    -c  CSV file\n");
    printf("    -m  macaddress\n");
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
        case 'm':
            strncpy(cmdopts->mac, optarg, sizeof(cmdopts->mac));
            break;
        case 'h':
        default:
            print_usage();
            return 1;
        }
    }
    return 0;
}
