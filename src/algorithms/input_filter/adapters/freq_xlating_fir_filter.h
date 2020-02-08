/*!
 * \file freq_xlating_fir_filter.h
 * \brief Adapts a gnuradio gr_freq_xlating_fir_filter designed with gr_remez
 * \author Luis Esteve, 2012. luis(at)epsilon-formacion.com
 *
 * Detailed description of the file here if needed.
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

#ifndef GNSS_SDR_FREQ_XLATING_FIR_FILTER_H_
#define GNSS_SDR_FREQ_XLATING_FIR_FILTER_H_

#include "complex_float_to_complex_byte.h"
#include "gnss_block_interface.h"
#include "short_x2_to_cshort.h"
#ifdef GR_GREATER_38
#include <gnuradio/filter/freq_xlating_fir_filter.h>
#else
#include <gnuradio/filter/freq_xlating_fir_filter_ccf.h>
#include <gnuradio/filter/freq_xlating_fir_filter_fcf.h>
#include <gnuradio/filter/freq_xlating_fir_filter_scf.h>
#endif
#include <gnuradio/blocks/char_to_short.h>
#include <gnuradio/blocks/complex_to_float.h>
#include <gnuradio/blocks/file_sink.h>
#include <gnuradio/blocks/float_to_short.h>
#include <string>
#include <vector>

class ConfigurationInterface;

/*!
 * \brief This class adapts a gnuradio gr_freq_xlating_fir_filter designed with pm_remez
 *
 * Construct a FIR filter with the given taps and a composite frequency
 * translation that shifts intermediate_freq_ down to zero Hz. The frequency
 * translation logically comes before the filtering operation.
 *
 * See Parks-McClellan FIR filter design, https://en.wikipedia.org/wiki/Parks-McClellan_filter_design_algorithm
 * Calculates the optimal (in the Chebyshev/minimax sense) FIR filter impulse response
 * given a set of band edges, the desired response on those bands, and the weight given
 * to the error in those bands.
 */
class FreqXlatingFirFilter : public GNSSBlockInterface
{
public:
    FreqXlatingFirFilter(ConfigurationInterface* configuration,
        std::string role, unsigned int in_streams,
        unsigned int out_streams);

    ~FreqXlatingFirFilter() = default;

    inline std::string role() override
    {
        return role_;
    }

    //! Returns "Freq_Xlating_Fir_Filter"
    inline std::string implementation() override
    {
        return "Freq_Xlating_Fir_Filter";
    }

    inline size_t item_size() override
    {
        return 0;
    }

    void connect(gr::top_block_sptr top_block) override;
    void disconnect(gr::top_block_sptr top_block) override;
    gr::basic_block_sptr get_left_block() override;
    gr::basic_block_sptr get_right_block() override;

private:
    gr::filter::freq_xlating_fir_filter_ccf::sptr freq_xlating_fir_filter_ccf_;
    gr::filter::freq_xlating_fir_filter_fcf::sptr freq_xlating_fir_filter_fcf_;
    gr::filter::freq_xlating_fir_filter_scf::sptr freq_xlating_fir_filter_scf_;
    ConfigurationInterface* config_;
    int decimation_factor_;
    bool dump_;
    std::string dump_filename_;
    std::string input_item_type_;
    size_t input_size_;
    std::string output_item_type_;
    std::string taps_item_type_;
    std::vector<float> taps_;
    double intermediate_freq_;
    double sampling_freq_;
    std::string role_;
    unsigned int in_streams_;
    unsigned int out_streams_;
    gr::blocks::file_sink::sptr file_sink_;
    gr::blocks::complex_to_float::sptr complex_to_float_;
    gr::blocks::char_to_short::sptr gr_char_to_short_;
    gr::blocks::float_to_short::sptr float_to_short_1_;
    gr::blocks::float_to_short::sptr float_to_short_2_;
    short_x2_to_cshort_sptr short_x2_to_cshort_;
    complex_float_to_complex_byte_sptr complex_to_complex_byte_;
};

#endif  // GNSS_SDR_FREQ_XLATING_FIR_FILTER_H_
