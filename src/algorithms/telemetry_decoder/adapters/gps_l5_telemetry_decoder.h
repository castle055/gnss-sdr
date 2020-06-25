/*!
 * \file gps_l5_telemetry_decoder.h
 * \brief Interface of an adapter of a GPS L5 (CNAV) data decoder block
 * to a TelemetryDecoderInterface
 * \author Antonio Ramos, 2017. antonio.ramos(at)cttc.es
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2019  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * -------------------------------------------------------------------------
 */


#ifndef GNSS_SDR_GPS_L5_TELEMETRY_DECODER_H
#define GNSS_SDR_GPS_L5_TELEMETRY_DECODER_H


#include "gnss_satellite.h"
#include "gps_l5_telemetry_decoder_gs.h"
#include "telemetry_decoder_interface.h"
#include <gnuradio/runtime_types.h>  // for basic_block_sptr, top_block_sptr
#include <cstddef>                   // for size_t
#include <string>


class ConfigurationInterface;

/*!
 * \brief This class implements a NAV data decoder for GPS L5
 */
class GpsL5TelemetryDecoder : public TelemetryDecoderInterface
{
public:
    GpsL5TelemetryDecoder(ConfigurationInterface* configuration,
        const std::string& role,
        unsigned int in_streams,
        unsigned int out_streams);

    ~GpsL5TelemetryDecoder() = default;

    inline std::string role() override
    {
        return role_;
    }

    //! Returns "GPS_L5_Telemetry_Decoder"
    inline std::string implementation() override
    {
        return "GPS_L5_Telemetry_Decoder";
    }

    void connect(gr::top_block_sptr top_block) override;
    void disconnect(gr::top_block_sptr top_block) override;
    gr::basic_block_sptr get_left_block() override;
    gr::basic_block_sptr get_right_block() override;

    void set_satellite(const Gnss_Satellite& satellite) override;

    inline void set_channel(int channel) override { telemetry_decoder_->set_channel(channel); }

    inline void reset() override
    {
        telemetry_decoder_->reset();
    }

    inline size_t item_size() override
    {
        return 0;
    }

private:
    gps_l5_telemetry_decoder_gs_sptr telemetry_decoder_;
    Gnss_Satellite satellite_;
    std::string dump_filename_;
    std::string role_;
    int channel_;
    unsigned int in_streams_;
    unsigned int out_streams_;
    bool dump_;
};

#endif
