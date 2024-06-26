#include <netinet/in.h>
#include <errno.h>
#include "wserver_messages_network.h"

int sendfull(int sock, const void *buf, size_t len, size_t shift, int flags) {
    size_t total = 0;
    size_t bytesleft = len;
    ssize_t currsent = 0;
    while (total < len) {
        currsent = send(sock, buf + shift + total, bytesleft, flags);
        if (currsent == -1) {
            if (errno == EPIPE || errno == ECONNRESET) {
                return WACTION_DISCONNECTED;
            } else {
                return -errno;
            }
        }
        total += currsent;
        bytesleft -= currsent;
    }
    return WACTION_CONTINUE;
}

int recvfull(int sock, void *buf, size_t len, size_t shift, int flags) {
    size_t total = 0;
    size_t bytesleft = len;
    ssize_t currrecv = 0;
    while (total < len) {
        currrecv = recv(sock, buf + shift + total, bytesleft, flags);
        if (currrecv == -1) {
            if (errno == EPIPE || errno == ECONNRESET) {
                return WACTION_DISCONNECTED;
            } else {
                return -errno;
            }
        } else if (currrecv == 0) {
            return WACTION_DISCONNECTED;
        }
        total += currrecv;
        bytesleft -= currrecv;
    }
    return WACTION_CONTINUE;
}

void htonu_wrapper(u32 *value) {
    *value = htonl(*value);
}

void ntohu_wrapper(u32 *value) {
    *value = ntohl(*value);
}

void htoni_wrapper(i32 *value) {
    *value = htonl(*value);
}

void ntohi_wrapper(i32 *value) {
    *value = ntohl(*value);
}

void hton_base(wserver_msg *elem) {
    UNUSED(elem);
}

void hton_snr_update_request(snr_update_request *elem) {
    hton_base(&elem->base);
    htoni_wrapper(&elem->snr);
}

void hton_snr_update_response(snr_update_response *elem) {
    hton_base(&elem->base);
    hton_snr_update_request(&elem->request);
}

void hton_position_update_request(position_update_request *elem) {
    hton_base(&elem->base);
    htoni_wrapper((int32_t*)&elem->posX);
    htoni_wrapper((int32_t*)&elem->posY);
    htoni_wrapper((int32_t*)&elem->posZ);
}

void hton_position_update_response(position_update_response *elem) {
    hton_base(&elem->base);
    hton_position_update_request(&elem->request);
}

void hton_txpower_update_request(txpower_update_request *elem) {
    hton_base(&elem->base);
    htoni_wrapper((int32_t*)&elem->txpower_);
}

void hton_txpower_update_response(txpower_update_response *elem) {
    hton_base(&elem->base);
    hton_txpower_update_request(&elem->request);
}

void hton_gaussian_random_update_request(gaussian_random_update_request *elem) {
    hton_base(&elem->base);
    htoni_wrapper((int32_t*)&elem->gaussian_random_);
}

void hton_gaussian_random_update_response(gaussian_random_update_response *elem) {
    hton_base(&elem->base);
    hton_gaussian_random_update_request(&elem->request);
}

void hton_gain_update_request(gain_update_request *elem) {
    hton_base(&elem->base);
    htoni_wrapper((int32_t*)&elem->gain_);
}

void hton_gain_update_response(gain_update_response *elem) {
    hton_base(&elem->base);
    hton_gain_update_request(&elem->request);
}

void hton_errprob_update_request(errprob_update_request *elem) {
    hton_base(&elem->base);
    htonu_wrapper(&elem->errprob);
}

void hton_errprob_update_response(errprob_update_response *elem) {
    hton_base(&elem->base);
    hton_errprob_update_request(&elem->request);
}

void hton_specprob_update_request(specprob_update_request *elem) {
    hton_base(&elem->base);
    for (int i = 0; i < SPECIFIC_MATRIX_MAX_SIZE_IDX * SPECIFIC_MATRIX_MAX_RATE_IDX; i++) {
        htonu_wrapper(&elem->errprob[i]);
    }
}

void hton_specprob_update_response(specprob_update_response *elem) {
    hton_base(&elem->base);
}

void hton_station_del_by_mac_request(station_del_by_mac_request *elem) {
    hton_base(&elem->base);
}

void hton_station_del_by_mac_response(station_del_by_mac_response *elem) {
    hton_base(&elem->base);
    hton_station_del_by_mac_request(&elem->request);
}

void hton_station_del_by_id_request(station_del_by_id_request *elem) {
    hton_base(&elem->base);
    htoni_wrapper(&elem->id);
}

void hton_station_del_by_id_response(station_del_by_id_response *elem) {
    hton_base(&elem->base);
    hton_station_del_by_id_request(&elem->request);
}

void hton_station_add_request(station_add_request *elem) {
    hton_base(&elem->base);
}

void hton_station_add_response(station_add_response *elem) {
    hton_base(&elem->base);
    hton_station_add_request(&elem->request);
    htoni_wrapper(&elem->created_id);
}

void hton_medium_update_request(medium_update_request *elem) {
    hton_base(&elem->base);
    htoni_wrapper((int32_t*)&elem->medium_id_);
}

void hton_medium_update_response(medium_update_response *elem) {
    hton_base(&elem->base);
    hton_medium_update_request(&elem->request);
}

void ntoh_base(wserver_msg *elem) {
    UNUSED(elem);
}

void ntoh_snr_update_request(snr_update_request *elem) {
    ntoh_base(&elem->base);
    ntohi_wrapper(&elem->snr);
}

void ntoh_snr_update_response(snr_update_response *elem) {
    ntoh_base(&elem->base);
    ntoh_snr_update_request(&elem->request);
}

void ntoh_position_update_request(position_update_request *elem) {
    ntoh_base(&elem->base);
    ntohi_wrapper((int32_t*)&elem->posX);
    ntohi_wrapper((int32_t*)&elem->posY);
    ntohi_wrapper((int32_t*)&elem->posZ);
}

void ntoh_position_update_response(position_update_response *elem) {
    ntoh_base(&elem->base);
    ntoh_position_update_request(&elem->request);
}

void ntoh_txpower_update_request(txpower_update_request *elem) {
    ntoh_base(&elem->base);
    ntohi_wrapper((int32_t*)&elem->txpower_);
}

void ntoh_txpower_update_response(txpower_update_response *elem) {
    ntoh_base(&elem->base);
    ntoh_txpower_update_request(&elem->request);
}

void ntoh_gaussian_random_update_request(gaussian_random_update_request *elem) {
    ntoh_base(&elem->base);
    ntohi_wrapper((int32_t*)&elem->gaussian_random_);
}

void ntoh_gaussian_random_update_response(gaussian_random_update_response *elem) {
    ntoh_base(&elem->base);
    ntoh_gaussian_random_update_request(&elem->request);
}

void ntoh_gain_update_request(gain_update_request *elem) {
    ntoh_base(&elem->base);
    ntohi_wrapper((int32_t*)&elem->gain_);
}

void ntoh_gain_update_response(gain_update_response *elem) {
    ntoh_base(&elem->base);
    ntoh_gain_update_request(&elem->request);
}

void ntoh_errprob_update_request(errprob_update_request *elem) {
    ntoh_base(&elem->base);
    ntohu_wrapper(&elem->errprob);
}

void ntoh_errprob_update_response(errprob_update_response *elem) {
    ntoh_base(&elem->base);
    ntoh_errprob_update_request(&elem->request);
}

void ntoh_specprob_update_request(specprob_update_request *elem) {
    ntoh_base(&elem->base);
    for (int i = 0; i < SPECIFIC_MATRIX_MAX_SIZE_IDX * SPECIFIC_MATRIX_MAX_RATE_IDX; i++) {
        ntohu_wrapper(&elem->errprob[i]);
    }
}

void ntoh_specprob_update_response(specprob_update_response *elem) {
    ntoh_base(&elem->base);
}

void ntoh_station_del_by_mac_request(station_del_by_mac_request *elem) {
    ntoh_base(&elem->base);
}

void ntoh_station_del_by_mac_response(station_del_by_mac_response *elem) {
    ntoh_base(&elem->base);
    ntoh_station_del_by_mac_request(&elem->request);
}

void ntoh_station_del_by_id_request(station_del_by_id_request *elem) {
    ntoh_base(&elem->base);
    ntohi_wrapper(&elem->id);
}

void ntoh_station_del_by_id_response(station_del_by_id_response *elem) {
    ntoh_base(&elem->base);
    ntoh_station_del_by_id_request(&elem->request);
}

void ntoh_station_add_request(station_add_request *elem) {
    ntoh_base(&elem->base);
}

void ntoh_station_add_response(station_add_response *elem) {
    ntoh_base(&elem->base);
    ntoh_station_add_request(&elem->request);
    ntohi_wrapper(&elem->created_id);
}

void ntoh_medium_update_request(medium_update_request *elem) {
    ntoh_base(&elem->base);
    ntohi_wrapper((int32_t*)&elem->medium_id_);
}

void ntoh_medium_update_response(medium_update_response *elem) {
    ntoh_base(&elem->base);
    ntoh_medium_update_request(&elem->request);
}