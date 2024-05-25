#ifndef WMEDIUMD_WMEDIUMD_DYNAMIC_H
#define WMEDIUMD_WMEDIUMD_DYNAMIC_H

#define SPECIFIC_MATRIX_MAX_SIZE_IDX (12)
#define SPECIFIC_MATRIX_MAX_RATE_IDX (12)

#include <stdint.h>
#include <pthread.h>
#include "wmediumd.h"

typedef uint8_t u8;
typedef int32_t i32;

/**
 * Add a station
 * @param ctx The wmediumd context
 * @param addr The MAC address of the station
 * @return The station ID or a negative errno value
 */
int add_station(struct wmediumd *ctx, const u8 addr[]);

/**
 * Delete a station
 * @param ctx The wmediumd context
 * @param station The station to delete
 * @return 0 on success otherwise a negative errno value
 */
int del_station(struct wmediumd *ctx, struct station *station);

/**
 * Delete a station by its id
 * @param ctx The wmediumd context
 * @param id The ID of the station
 * @return 0 on success otherwise a negative errno value
 */
int del_station_by_id(struct wmediumd *ctx, const i32 id);

/**
 * Delete a station by its address
 * @param ctx The wmediumd context
 * @param addr The MAC address of the station
 * @return 0 on success otherwise a negative errno value
 */
int del_station_by_mac(struct wmediumd *ctx, const u8 *addr);

/**
 * Lock for the snr matrix/station list
 */
extern pthread_rwlock_t snr_lock;

#endif //WMEDIUMD_WMEDIUMD_DYNAMIC_H
