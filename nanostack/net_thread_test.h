/*
 * Copyright (c) 2014-2015 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: LicenseRef-PBL
 *
 * Licensed under the Permissive Binary License, Version 1.0 (the "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * https://www.mbed.com/licenses/PBL-1.0
 *
 * See the License for the specific language governing permissions and limitations under the License.
 *
 */
/**
 * \file net_thread_test.h
 * \brief Thread Library Test API.
 *
 * \warning NOTICE! This is test API must not be used externally.
 *
 * \warning This file is not part of the version number control and can change any time.
 *
 */

#ifndef NET_THREAD_TEST_H_
#define NET_THREAD_TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ns_types.h"


/**
  * \brief Add a static neighbour
  *
  * Test API: Add a neighbour. Adds, or updates, a non-expiring neighbour to the
  * Thread Link Set, and updates the Route Set accordingly. Basically equivalent
  * to receiving an MLE advertisement with a Route TLV, except it doesn't expire.
  *
  * See draft-kelsey-thread-routing-00 for more info on data format.
  *
  * \param interface_id Interface to modify
  * \param neighbour_addr Neighbour short address (must be a router address)
  * \param link_margin_db Notional link margin for reception from this neighbour.
  * \param id_sequence Sequence number for id_mask
  * \param id_mask Bit mask of router IDs
  * \param route_data One octet per set bit in id_mask
  *
  * \return  0 Success
  * \return <0 Failure
  */
int_fast8_t arm_nwk_6lowpan_thread_test_add_neighbour(
    int8_t interface_id,
    uint16_t neighbour_short_addr,
    uint_fast8_t link_margin_db,
    uint8_t id_sequence,
    const uint8_t *id_mask,
    const uint8_t *route_data);

/**
 * Api to set reed advertisement interval
 * \param interface_id Interface to modify
 * \param advertisement_interval Interval between advertisements to be set
 * \param jitter_interval Maximum value of random jitter interval to be added to advertisement_interval
 * \return   0 Success
 * \return < 0 Other errors
 */
int8_t thread_reed_set_advertisement_interval(int8_t interface_id, uint16_t advertisement_interval, uint16_t jitter_interval);

/**
  * \brief Remove a static neighbour
  *
  * Test API: Remove a neighbour. Remove a neighbour from the Thread Link Set
  * (whether added through arm_nwk_6lowpan_thread_test_add_neighbour, or
  * automatically through MLE).
  *
  * \param interface_id Interface to modify
  * \param neighbour_addr Neighbour short address (must be a router address)
  *
  * \return  0 Success
  * \return -1 Not an existing neighbour
  * \return <-1 Other errors
  */
int_fast8_t arm_nwk_6lowpan_thread_test_remove_neighbour(
    int8_t interface_id,
    uint16_t neighbour_short_addr);

/**
  * \brief Print routing database
  *
  * Test API: Dump the routing data base (Router ID Set, Link Set and Route
  * Set) to the debug channel.
  *
  * \param interface_id Interface to interrogate
  */
void arm_nwk_6lowpan_thread_test_print_routing_database(int8_t interface_id);


/**
 * Thread Leader max router Id limit set
 *
 * This function should use just for test purpose Thread define this by default to 32
 *
 * \param interface_id Network Interface
 * \param maxRouterLimit Min Accepted value is 1 and max 32
 *
 * return 0, Set OK
 * return <0 Set Fail
 */
int thread_test_max_accepted_router_id_limit_set(
    int8_t interface_id,
    uint8_t maxRouterLimit);

/**
  * \brief Set Thread network id timeout
  *
  * \param interface_id Interface to modify
  * \param network_id_timeout network timeout as seconds
  *
  * \return  0 Success
  * \return -1 Invalid interface id
  * \return -2 Thread not active
  * \return -3 invalid timeout value
  */
int8_t thread_routing_set_network_id_timeout(int8_t interface_id, uint16_t network_id_timeout);

/**
  * \brief Get Thread network id timeout
  *
  * \param interface_id Interface to modify
  * \param network_id_timeout pointer, where current network id timeout will be saved as seconds
  *
  * \return  0 Success
  * \return -1 Invalid interface id
  * \return -2 Thread not active
  * \return -3 invalid pointer
  */
int8_t thread_routing_get_network_id_timeout(int8_t interface_id, uint16_t *network_id_timeout);

/**
 * Print thread network data
 *
 * \param interface_id Network Interface
 *
 * \return 0, OK
 * \return <0 Not OK
 */

int thread_test_print_network_data(int8_t interface_id);

/**
 * Thread Leader Context ID re use timeout set
 *
 * This function should be used to change default 48 hours to shorter one
 *
 * \param interface_id Network Interface
 * \param timeout Min Accepted value is 60 seconds and max  48 hours (48*3600)
 *
 * \return 0, Set OK
 * \return <0 Set Fail
 */
int thread_test_set_context_id_reuse_timeout(
    int8_t interface_id,
    uint32_t timeout);

/**
 * Leader of thread network can kick Router out from Network.
 *
 * \param interface_id Network Interface
 * \param routerId Routter id of router that is kicked
 *
 * \return 0, Remove OK
 * \return <0 Remove fail
 */
int thread_test_remove_router_by_id(int8_t interface_id, uint8_t routerId);

/**
 * Set Thread Security Material. Terms are defined in Thread security specification
 *
 * \param interface_id Network Interface
 * \param enableSecurity Boolean for enable security or disable
 * \param thrMasterKey Master Key material which will be used for generating new key
 * \param thrKeySequenceCounter Periodic counter used to generate new MAC and MLE keys
 * \param thrKeyRotation Update period (in seconds) for thrKeySequenceCounter
 *
 * \return 0, ADD OK
 * \return <0 Add Not OK
 */
int thread_test_security_material_set(int8_t nwk_interface_id, bool enableSecurity, uint8_t *thrMasterKey, uint32_t thrKeySequenceCounter, uint32_t thrKeyRotation);

/**
 * Increment Thread key sequence counter
 *
 * \param nwk_interface_id Network Interface
 *
 * \return 0, OK
 * \return <0 Error
 */
int thread_test_increment_key_sequence_counter(int8_t nwk_interface_id);

/**
 * Set new Thread key sequency counter
 *
 * Call define new key and next key same time
 *
 * \param nwk_interface_id Network Interface
 * \param thrKeySequenceCounter this need to be bigger than current sequence
 *
 * \return 0, OK
 * \return <0 Error
 */
int thread_test_key_sequence_counter_update(int8_t nwk_interface_id, uint32_t thrKeySequenceCounter);

/**
 * Thread router select threshold values set
 *
 * \param interface_id Network Interface
 * \param upgradeThreshold Set REED up grade to router threshold
 * \param downgradeThreshold Set Router down grade to REED threshold
 *
 * \return 0, Set OK
 * \return <0 Set Fail
 */
int thread_test_router_select_threshold_values_set(
    int8_t interface_id,
    uint8_t upgradeThreshold,
    uint8_t downgradeThreshold);

/**
 * Send panid query message to destination
 *
 * \param interface_id Network Interface
 *
 * \return 0, Set OK
 * \return <0 Set Fail
 */
int thread_test_panid_query_send(int8_t nwk_interface_id, uint8_t *address_ptr, uint16_t session_id, uint16_t panid, uint8_t channel_page, uint8_t *mask_ptr);

/**
 * Send energy scan message to destination
 *
 * \param interface_id Network Interface
 *
 * \return 0, Set OK
 * \return <0 Set Fail
 */
int thread_test_energy_scan_send(int8_t nwk_interface_id, uint8_t *address_ptr, uint16_t session_id, uint8_t channel_page, uint8_t *mask_ptr, uint16_t period, uint8_t count, uint16_t duration);

/**
 * Send Announcement message
 *
 * \param interface_id Network Interface
 * \param channel high uint16 is channel page lower part is the channel number on that page
 *
 * \return 0, Set OK
 * \return <0 Set Fail
 */
int thread_test_announce_ntf_send(int8_t nwk_interface_id, uint8_t *address_ptr, uint32_t channel, uint16_t panid, uint64_t timestamp);

/**
 * Send energy scan message to destination
 *
 * \param interface_id Network Interface
 *
 * \return 0, Set OK
 * \return <0 Set Fail
 */
int thread_test_announce_begin_send(int8_t nwk_interface_id, uint8_t *address_ptr, uint16_t session_id, uint8_t channel_page, uint8_t *mask_ptr, uint16_t period, uint8_t count);

/**
 * Get partition info
 *
 * \param interface_id Network Interface
 * \param partition_id Current partition id can be NULL if not needed.
 * \param weighting Current weighting can be NULL if not needed.
 * \param data_version Current data version can be NULL if not needed.
 * \param stable_data_version Current stable data version can be NULL if not needed.
 * \param leader_id Current leader id can be NULL if not needed.
 *
 * \return 0, Set OK
 * \return <0 Set Fail
 */
int thread_test_partition_info_get(int8_t nwk_interface_id, uint32_t *partition_id, uint8_t *weighting, uint8_t *data_version, uint8_t *stable_data_version, uint8_t *leader_id);

/**
 * Set next partition id when we next time partition. This is used to control specific behaviour in tests.
 *
 * \param interface_id Network Interface
 *
 * \return 0, Set OK
 * \return <0 Set Fail
 */
int thread_test_partition_info_set(int8_t nwk_interface_id, uint32_t partition_id);

/**
 * Get child count
 *
 * \param interface_id Network Interface
 *
 * \return 0, Set OK
 * \return <0 Set Fail
 */
int8_t thread_test_child_count_get(int8_t nwk_interface_id);

/**
 * Get child information
 *
 * get information for index child. if found returns 0 with correct information.
 *
 * \param interface_id Network Interface
 *
 * \return 0, OK
 * \return <0 Fail no child with this index found
 */
int8_t thread_test_child_info_get(int8_t nwk_interface_id, uint8_t index, uint16_t *short_addr, bool *sleepy, uint8_t *mac64, uint8_t *margin);

/**
 * Get neighbour information
 *
 * \param interface_id Network Interface
 *
 * \return 0, Set OK
 * \return <0 Set Fail
 */
int8_t thread_test_neighbour_info_get(int8_t nwk_interface_id, uint8_t index, uint16_t *short_addr, uint8_t *mac64, uint8_t *margin);

#ifdef __cplusplus
}
#endif

#endif /* NET_THREAD_TEST_H_ */
