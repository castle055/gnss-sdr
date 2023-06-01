/*!
 * \file osnma_msg_receiver.h
 * \brief GNU Radio block that processes Galileo OSNMA data received from
 * Galileo E1B telemetry blocks. After successful decoding, sends the content to
 * the PVT block.
 * \author Carles Fernandez-Prades, 2023. cfernandez(at)cttc.es
 *
 * -----------------------------------------------------------------------------
 *
 * GNSS-SDR is a Global Navigation Satellite System software-defined receiver.
 * This file is part of GNSS-SDR.
 *
 * Copyright (C) 2010-2023  (see AUTHORS file for a list of contributors)
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * -----------------------------------------------------------------------------
 */

#ifndef GNSS_SDR_OSNMA_MSG_RECEIVER_H
#define GNSS_SDR_OSNMA_MSG_RECEIVER_H

#include "galileo_inav_message.h"  // for OSNMA_msg
#include "gnss_block_interface.h"  // for gnss_shared_ptr
#include "osnma_data.h"            // for OSNMA_data
#include <gnuradio/block.h>        // for gr::block
#include <pmt/pmt.h>               // for pmt::pmt_t
#include <array>                   // for std::array
#include <memory>                  // for std::shared_ptr
#include <vector>

/** \addtogroup Core
 * \{ */
/** \addtogroup Core_Receiver_Library
 * \{ */

class osnma_msg_receiver;

using osnma_msg_receiver_sptr = gnss_shared_ptr<osnma_msg_receiver>;

osnma_msg_receiver_sptr osnma_msg_receiver_make();

/*!
 * \brief GNU Radio block that receives asynchronous OSNMA messages
 * from the telemetry blocks, stores them in memory, and decodes OSNMA info
 * when enough data have been received.
 * The decoded OSNMA data is sent to the PVT block.
 */
class osnma_msg_receiver : public gr::block
{
public:
    ~osnma_msg_receiver() = default;  //!< Default destructor

private:
    friend osnma_msg_receiver_sptr osnma_msg_receiver_make();
    osnma_msg_receiver();

    void msg_handler_osnma(const pmt::pmt_t& msg);
    void process_osnma_message(const std::shared_ptr<OSNMA_msg>& osnma_msg);
    void read_nma_header(uint8_t nma_header);
    void read_dsm_header(uint8_t dsm_header);
    void read_dsm_block(const std::shared_ptr<OSNMA_msg>& osnma_msg);
    void read_mack_block(const std::shared_ptr<OSNMA_msg>& osnma_msg);
    void process_dsm_message(const std::vector<uint8_t>& dsm_msg);

    void read_mack_header();
    void read_mack_info_and_tags();
    void read_mack_key();
    void read_mack_padding();

    std::array<std::array<uint8_t, 256>, 16> d_dsm_message{};
    std::array<std::array<uint8_t, 16>, 16> d_dsm_id_received{};
    std::array<uint16_t, 16> d_number_of_blocks{};
    std::array<uint8_t, 60> d_mack_message{};

    OSNMA_data d_osnma_data{};
    bool d_new_data{false};
};


/** \} */
/** \} */
#endif  // GNSS_SDR_OSNMA_MSG_RECEIVER_H
