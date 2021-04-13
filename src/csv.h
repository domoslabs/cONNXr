#ifndef __UTILS_H
#define __UTILS_H

#include <sys/sysinfo.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAX_FIELD_LEN 256
#define MAX_FIELDS 256


struct fpingdq_ping
{
    int delta_time;
    char mac[24];
    char radio[64];
    uint64_t time;
    char ip[64];
    int snd;
    float nwrtd;
    int plen;
    int ping2;
};
struct domos_ll_wlctl_chanim_info 
{
    char chanspec[10];
    int tx;
    int inbss;
    int obss;
    int nocat;
    int nopkt;
    int doze;
    int txop;
    int goodtx;
    int badtx;
    uint32_t glitch;
    uint32_t badplcp;
    int knoise;
    int idle;
	uint32_t timestamp;
    uint32_t epochstamp; // not the one in chanim
};

struct domos_ll_wlctl_sta_info
{
    uint32_t version; // wlctl-sta_info versionc
    char rateset[128];
    uint32_t rx_rate;
    uint64_t tx_bytes;
    uint64_t rx_bytes;
    uint32_t tx_pkts;
	uint32_t rx_pkts;
    uint32_t tx_failures;
    uint32_t tx_retries;
    uint32_t rx_retries;
	uint32_t flags;
    uint32_t htcaps;
    uint32_t vhtcaps;
	uint32_t idle;
	uint32_t in_network;
	char state[70];
	uint32_t tx_ucast_pkts;
	uint64_t tx_ucast_bytes;
	uint32_t tx_mcast_pkts;
	uint64_t tx_mcast_bytes;
	uint32_t rx_ucast_pkts;
	uint64_t rx_ucast_bytes;
	uint32_t rx_mcast_pkts;
	uint64_t rx_mcast_bytes;
	uint32_t rate_of_last_tx_pkt[2];
	uint32_t rx_decrypt_succeeds;
	uint32_t rx_decrypt_failures;
	uint32_t tx_data_pkts_retried;
	int32_t antenna_rssi_last_rx_frame[4];
	int32_t antenna_rssi_avg[4];
	int32_t antenna_noise_floor[4];
	uint32_t tx_pkts_retry_exhausted;
	uint32_t tx_fw_total_pkts_sent;
	uint32_t tx_fw_pkts_retries;
	uint32_t tx_fw_pkts_retry_exhausted;
};

struct brcm_csv_data
{
    struct domos_ll_wlctl_sta_info sta_info;
    struct domos_ll_wlctl_chanim_info chanim;
    struct fpingdq_ping ping;
};

int csv_split_line(char *csv_line, char **fields, int max_fields);
int csv_get_index_from_field_name(char **header_fields, int num_fields, char *field);
int csv_get_string_from_name(char **header_fields, int num_fields, char *field_name, char ** splited_csv, int csv_len, char *out);
float csv_get_float_from_name(char **header_fields, int num_fields, char *field_name, char ** splited_csv, int csv_len);
int csv_get_int_from_name_helper(char **header_fields, int num_fields, char *field_name, char ** splited_csv, int csv_len, int print_error);
int csv_get_int_from_name(char **header_fields, int num_fields, char *field_name, char ** splited_csv, int csv_len);
int csv_get_line_from_idexes(char * line, int * indexes, int indexes_len, char * tmp_splited_csv[MAX_FIELDS], char *out);
void brcm_csv_to_structs(char **header_fields, int num_fields, char ** splitted_csv, int csv_len, struct brcm_csv_data *data_out);
void csv_to_model_vector(
        char **header_fields,  int num_header_fields,
        char **feature_fields, int num_feature_fields,
        char **splitted_csv,   int csv_len,
        float *floatdata
);

#endif // __UTILS_H
