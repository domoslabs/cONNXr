#ifndef COMMANDLINE_OPTIONS_H
#define COMMANDLINE_OPTIONS_H

typedef struct {
    char path[128];
    char model_filename[128];
    char model_config_filename[128];
    char csv_file[128];
    char mac[128];
} cmdoptions;

int parse_options(cmdoptions *cmdopts, int argc, char *argv[]);

#endif
