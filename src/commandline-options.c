#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "commandline-options.h"

void print_usage();

void print_usage(){
    printf("Usage: dconnxr [options]\n");
    printf("\n");
    printf("options:\n");
    printf("    -d  Path to config and ONNX model\n");
    printf("    -s  ONNX model config filename\n");
    printf("    -c  CSV file path\n");
    printf("    -m  macaddress\n");
    printf("    -h  print this\n");
}

int parse_options(cmdoptions *cmdopts, int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "d:c:s:m:h")) != -1) {
        switch (opt) {
        case 'd':
            strncpy(cmdopts->path, optarg, sizeof(cmdopts->path));
            int len = strlen(cmdopts->path);
            if (len>0)
                if (cmdopts->path[len-1]=='/')
                    cmdopts->path[len-1]=0; // remove trailing slash
            break;
        case 'c':
            strncpy(cmdopts->csv_file, optarg, sizeof(cmdopts->csv_file));
            break;
        case 's':
            strncpy(cmdopts->model_config_filename, optarg, sizeof(cmdopts->model_config_filename));
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
