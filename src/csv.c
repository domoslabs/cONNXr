#include <stdio.h>
#include <string.h>
#include <time.h>
#include "csv.h"


// split header into fields array and return nuber of fields
int csv_split_line(char *csv_line, char **fields, int max_fields) 
{
    // PRINT_DBG("csv_split_line: %s", csv_line);
    char * token = strtok(csv_line, ",");
    int counter = 0;
    while(token != NULL)
    {
        if(counter >= max_fields) {
            break;
        }
        strncpy(fields[counter], token, MAX_FIELD_LEN);
        token = strtok(NULL,",");
        counter++;
    }
    return counter;
}

// return -1 if not found else index
int csv_get_index_from_field_name(char **header_fields, int num_fields, char *field)
{
    for(int i = 0; i<num_fields; i++){
        if(strcasecmp(header_fields[i], field) == 0) {
            return i;
        }
    }
    return -1;
}

int csv_get_line_from_idexes(char * line, int * indexes,int indexes_len, char * tmp_splited_csv[MAX_FIELDS], char *out)
{
    int len = csv_split_line(line, tmp_splited_csv, MAX_FIELDS);
    out[0] = 0;
    for(int i = 0; i<indexes_len; i++) {
        if(indexes[i] > len){
            // PRINT_ERR("Error indexes larger than len");
        }else{
            char *field = tmp_splited_csv[indexes[i]];
            strcat(out, field);
            if(i != indexes_len-1){
                strcat(out,",");
            }
        }
    }
    return 0;
}

int csv_get_string_from_name(char **header_fields, int num_fields, char *field_name, char ** splited_csv, int csv_len, char *out)
{
    int idx = csv_get_index_from_field_name(header_fields,num_fields,field_name);
    if(idx != -1){
        char *field_value = splited_csv[idx];
        strcpy(out,field_value);
        return 0;
    }else{
        printf("ERROR: getting string from %s\n", field_name);
    }
    return 1;
}

float csv_get_float_from_name(char **header_fields, int num_fields, char *field_name, char ** splited_csv, int csv_len)
{
    //printf("%s: header_fields 0/%d: %s - splited_csv 0/%d: %s\n", __func__, num_fields, header_fields[0], csv_len, splited_csv[0]);
    int idx = csv_get_index_from_field_name(header_fields,num_fields,field_name);
    if(idx != -1) {
        char *field_value = splited_csv[idx];
        return atof(field_value);
    }else{
        printf("ERROR: getting float from %s\n", field_name);
    }
    return 0;
}

int csv_get_int_from_name(char **header_fields, int num_fields, char *field_name, char ** splited_csv, int csv_len)
{
    return csv_get_int_from_name_helper(header_fields, num_fields, field_name, splited_csv, csv_len, 1);
}

int csv_get_int_from_name_helper(char **header_fields, int num_fields, char *field_name, char ** splited_csv, int csv_len, int print_error)
{
    int idx = csv_get_index_from_field_name(header_fields,num_fields,field_name);
    if(idx != -1) {
        char *field_value = splited_csv[idx];
        return atoi(field_value);
    }else{
        if(print_error){
            printf("ERROR: getting index for field: %s\n", field_name);
        }
    }
    return 0;
}

void csv_to_model_vector(
        char **header_fields,  int num_header_fields,
        char **feature_fields, int num_feature_fields,
        char **splitted_csv,   int csv_len,
        float *floatdata
)
{
    for(int i = 0; i < num_feature_fields; i++) {
        //printf("%s: i=%d, %s/%d, %s/%d\n", __func__, i, header_fields[i], num_header_fields, feature_fields[i], num_feature_fields);
        floatdata[i] = csv_get_float_from_name(
            header_fields, num_header_fields, feature_fields[i],
            splitted_csv, csv_len);
    }
}

void brcm_csv_to_structs(char **header_fields, int num_fields, char ** splitted_csv, int csv_len, struct brcm_csv_data *data_out)
{
    struct domos_ll_wlctl_sta_info *sta_info = &(data_out->sta_info);
    struct domos_ll_wlctl_chanim_info * chanim =  &(data_out->chanim);
    struct fpingdq_ping *ping = &(data_out->ping);

    csv_get_string_from_name(header_fields,num_fields, "chanspec", splitted_csv, csv_len, chanim->chanspec);
    chanim->tx =  csv_get_int_from_name(header_fields, num_fields, "tx", splitted_csv, csv_len);
    chanim->inbss =  csv_get_int_from_name(header_fields, num_fields, "inbss", splitted_csv, csv_len);
    chanim->obss =  csv_get_int_from_name(header_fields,num_fields, "obss", splitted_csv, csv_len);
    chanim->nocat =  csv_get_int_from_name(header_fields,num_fields, "nocat", splitted_csv, csv_len);
    chanim->nopkt =  csv_get_int_from_name(header_fields,num_fields, "nopkt", splitted_csv, csv_len);
    chanim->doze =  csv_get_int_from_name(header_fields,num_fields, "doze", splitted_csv, csv_len);
    chanim->txop =  csv_get_int_from_name(header_fields, num_fields, "txop", splitted_csv, csv_len);
    chanim->goodtx =  csv_get_int_from_name(header_fields,num_fields, "goodtx", splitted_csv, csv_len);
    chanim->badtx =  csv_get_int_from_name(header_fields,num_fields, "badtx", splitted_csv, csv_len);
    chanim->glitch =  csv_get_int_from_name(header_fields,num_fields, "glitch", splitted_csv, csv_len);
    chanim->badplcp =  csv_get_int_from_name(header_fields,num_fields, "badplcp", splitted_csv, csv_len);
    chanim->knoise =  csv_get_int_from_name(header_fields,num_fields, "knoise", splitted_csv, csv_len);
    chanim->idle =  csv_get_int_from_name(header_fields,num_fields, "idle", splitted_csv, csv_len);
	chanim->timestamp =  csv_get_int_from_name(header_fields,num_fields, "timestamp", splitted_csv, csv_len);
    chanim->epochstamp =  csv_get_int_from_name(header_fields,num_fields, "Time", splitted_csv, csv_len);

    // sta_info->version =  csv_get_int_from_name(header_fields,num_fields, "version", splitted_csv, csv_len);
    // csv_get_string_from_name(header_fields,num_fields, "rateset", splitted_csv, csv_len, sta_info->rateset);
    sta_info->rx_rate =  csv_get_int_from_name(header_fields,num_fields, "rate_of_last_rx_pkt", splitted_csv, csv_len);
    sta_info->tx_bytes =  csv_get_int_from_name(header_fields,num_fields, "tx_total_bytes", splitted_csv, csv_len);
    sta_info->rx_bytes =  csv_get_int_from_name(header_fields,num_fields, "rx_data_bytes", splitted_csv, csv_len);
    sta_info->tx_pkts =  csv_get_int_from_name(header_fields,num_fields, "tx_total_pkts", splitted_csv, csv_len);
	sta_info->rx_pkts =  csv_get_int_from_name(header_fields,num_fields, "rx_data_pkts", splitted_csv, csv_len);
    sta_info->tx_failures =  csv_get_int_from_name(header_fields,num_fields, "tx_failures", splitted_csv, csv_len);
    sta_info->tx_retries =  csv_get_int_from_name(header_fields,num_fields, "tx_pkts_retries", splitted_csv, csv_len);
    sta_info->rx_retries =  csv_get_int_from_name(header_fields,num_fields, "rx_total_pkts_retried", splitted_csv, csv_len);
	sta_info->flags =  csv_get_int_from_name(header_fields,num_fields, "flags", splitted_csv, csv_len);
    sta_info->htcaps =  csv_get_int_from_name(header_fields,num_fields, "htcaps", splitted_csv, csv_len);
    sta_info->vhtcaps =  csv_get_int_from_name(header_fields,num_fields, "vhtcaps", splitted_csv, csv_len);
	sta_info->idle =  csv_get_int_from_name(header_fields,num_fields, "idle", splitted_csv, csv_len);
	// sta_info->in_network =  csv_get_int_from_name(header_fields,num_fields, "in_network", splitted_csv, csv_len);
	// csv_get_string_from_name(header_fields,num_fields, "state", splitted_csv, csv_len, sta_info->state);
	// sta_info->tx_ucast_pkts =  csv_get_int_from_name(header_fields,num_fields, "tx_ucast_pkts", splitted_csv, csv_len);
	// sta_info->tx_ucast_bytes =  csv_get_int_from_name(header_fields,num_fields, "tx_ucast_bytes", splitted_csv, csv_len);
	// sta_info->tx_mcast_pkts =  csv_get_int_from_name(header_fields,num_fields, "tx_mcast_pkts", splitted_csv, csv_len);
	// sta_info->tx_mcast_bytes =  csv_get_int_from_name(header_fields,num_fields, "tx_mcast_bytes", splitted_csv, csv_len);
	// sta_info->rx_ucast_pkts =  csv_get_int_from_name(header_fields,num_fields, "rx_ucast_pkts", splitted_csv, csv_len);
	// sta_info->rx_ucast_bytes =  csv_get_int_from_name(header_fields,num_fields, "rx_ucast_bytes", splitted_csv, csv_len);
	// sta_info->rx_mcast_pkts =  csv_get_int_from_name(header_fields,num_fields, "rx_mcast_pkts", splitted_csv, csv_len);
	// sta_info->rx_mcast_bytes =  csv_get_int_from_name(header_fields,num_fields, "rx_mcast_bytes", splitted_csv, csv_len);
	sta_info->rate_of_last_tx_pkt[0] =  csv_get_int_from_name(header_fields,num_fields, "rate_of_last_tx_pkt", splitted_csv, csv_len);
    sta_info->rate_of_last_tx_pkt[1] =  csv_get_int_from_name(header_fields,num_fields, "rate_of_last_tx_pkt", splitted_csv, csv_len);
	sta_info->rx_decrypt_succeeds =  csv_get_int_from_name(header_fields,num_fields, "rx_decrypt_succeeds", splitted_csv, csv_len);
	sta_info->rx_decrypt_failures =  csv_get_int_from_name(header_fields,num_fields, "rx_decrypt_failures", splitted_csv, csv_len);
	sta_info->tx_data_pkts_retried =  csv_get_int_from_name(header_fields,num_fields, "tx_data_pkts_retried", splitted_csv, csv_len);
	sta_info->antenna_rssi_last_rx_frame[0] =  csv_get_int_from_name(header_fields,num_fields, "rx_last_rssi_1", splitted_csv, csv_len);
    sta_info->antenna_rssi_last_rx_frame[1] =  csv_get_int_from_name(header_fields,num_fields, "rx_last_rssi_2", splitted_csv, csv_len);
    sta_info->antenna_rssi_last_rx_frame[2] =  csv_get_int_from_name(header_fields,num_fields, "rx_last_rssi_3", splitted_csv, csv_len);
    sta_info->antenna_rssi_last_rx_frame[3] =  csv_get_int_from_name(header_fields,num_fields, "rx_last_rssi_4", splitted_csv, csv_len);
	sta_info->antenna_rssi_avg[0] =  csv_get_int_from_name(header_fields,num_fields, "rx_average_rssi_1", splitted_csv, csv_len);
    sta_info->antenna_rssi_avg[1] =  csv_get_int_from_name(header_fields,num_fields, "rx_average_rssi_2", splitted_csv, csv_len);
    sta_info->antenna_rssi_avg[2] =  csv_get_int_from_name(header_fields,num_fields, "rx_average_rssi_3", splitted_csv, csv_len);
    sta_info->antenna_rssi_avg[3] =  csv_get_int_from_name(header_fields,num_fields, "rx_average_rssi_4", splitted_csv, csv_len);
	sta_info->antenna_noise_floor[0] =  csv_get_int_from_name(header_fields,num_fields, "noise_floor_1", splitted_csv, csv_len);
    sta_info->antenna_noise_floor[1] =  csv_get_int_from_name(header_fields,num_fields, "noise_floor_2", splitted_csv, csv_len);
    sta_info->antenna_noise_floor[2] =  csv_get_int_from_name(header_fields,num_fields, "noise_floor_3", splitted_csv, csv_len);
    // sta_info->antenna_noise_floor[3] =  csv_get_int_from_name(header_fields,num_fields, "noise_floor_4", splitted_csv, csv_len);
	sta_info->tx_pkts_retry_exhausted =  csv_get_int_from_name(header_fields,num_fields, "tx_pkts_retry_exhausted", splitted_csv, csv_len);
	sta_info->tx_fw_total_pkts_sent =  csv_get_int_from_name(header_fields,num_fields, "tx_fw_total_pkts_sent", splitted_csv, csv_len);
	sta_info->tx_fw_pkts_retries =  csv_get_int_from_name(header_fields,num_fields, "tx_fw_pkts_retries", splitted_csv, csv_len);
	sta_info->tx_fw_pkts_retry_exhausted =  csv_get_int_from_name(header_fields,num_fields, "tx_fw_pkts_retry_exhausted", splitted_csv, csv_len);


    // delta_time,mac,radio,Time,IP,Snd#,NwRTD,PLEN,Ping2
    ping->delta_time =  csv_get_int_from_name(header_fields,num_fields, "delta_time", splitted_csv, csv_len);
    csv_get_string_from_name(header_fields,num_fields, "mac", splitted_csv, csv_len, ping->mac);
    csv_get_string_from_name(header_fields,num_fields, "radio", splitted_csv, csv_len, ping->radio);
    ping->time =  csv_get_int_from_name(header_fields,num_fields, "Time", splitted_csv, csv_len);
    csv_get_string_from_name(header_fields,num_fields, "IP", splitted_csv, csv_len, ping->ip);
    ping->snd =  csv_get_int_from_name(header_fields,num_fields, "Snd#", splitted_csv, csv_len);
    ping->nwrtd =  csv_get_float_from_name(header_fields,num_fields, "NwRTD", splitted_csv, csv_len);
    ping->plen =  csv_get_int_from_name(header_fields,num_fields, "PLEN", splitted_csv, csv_len);

    // we want this to be scielence since the ping2 column sometimes doesent exist
    ping->ping2 =  csv_get_int_from_name_helper(header_fields,num_fields, "Ping2", splitted_csv, csv_len, 0);

}
