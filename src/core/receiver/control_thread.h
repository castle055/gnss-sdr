/*!
 * \file control_thread.h
 * \brief Interface of the receiver control plane
 * \author Carlos Aviles, 2010. carlos.avilesr(at)googlemail.com
 *
 * GNSS Receiver Control Plane: connects the flowgraph, starts running it,
 * and while it does not stop, reads the control messages generated by the blocks,
 * processes them, and applies the corresponding actions.
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

#ifndef GNSS_SDR_CONTROL_THREAD_H_
#define GNSS_SDR_CONTROL_THREAD_H_

#include "agnss_ref_location.h"    // for Agnss_Ref_Location
#include "agnss_ref_time.h"        // for Agnss_Ref_Time
#include "concurrent_queue.h"      // for Concurrent_Queue
#include "gnss_sdr_supl_client.h"  // for Gnss_Sdr_Supl_Client
#include "tcp_cmd_interface.h"     // for TcpCmdInterface
#include <pmt/pmt.h>
#include <array>    // for array
#include <ctime>    // for time_t (gmtime, strftime in implementation)
#include <memory>   // for shared_ptr
#include <string>   // for string
#include <thread>   // for std::thread
#include <utility>  // for pair
#include <vector>   // for vector

#ifdef ENABLE_FPGA
#include <boost/thread.hpp>  // for boost::thread
#endif


class ConfigurationInterface;
class GNSSFlowgraph;
class Gnss_Satellite;

/*!
 * \brief This class represents the main thread of the application, so the name is ControlThread.
 * This is the GNSS Receiver Control Plane: it connects the flowgraph, starts running it,
 * and while it does not stop, reads the control messages generated by the blocks,
 * processes them, and applies the corresponding actions.
 */
class ControlThread
{
public:
    /*!
     * \brief Default constructor
     */
    ControlThread();

    /*!
     * \brief Constructor that initializes the class with parameters
     *
     * \param[in] configuration Pointer to a ConfigurationInterface
     */
    explicit ControlThread(const std::shared_ptr<ConfigurationInterface> &configuration);

    /*!
     * \brief Destructor
     */
    ~ControlThread();

    /*! \brief Runs the control thread
     *
     *  This is the main loop that reads and process the control messages:
     *
     *  - Connect the GNSS receiver flowgraph;
     *
     *  - Start the GNSS receiver flowgraph;
     *
     *  while (flowgraph_->running() && !stop_){
     *
     *  - Read control messages and process them; }
     */
    int run();

    /*!
     * \brief Sets the control_queue
     *
     * \param[in] std::shared_ptr<Concurrent_Queue<pmt::pmt_t>> control_queue
     */
    void set_control_queue(const std::shared_ptr<Concurrent_Queue<pmt::pmt_t>> control_queue);  // NOLINT(performance-unnecessary-value-param)

    unsigned int processed_control_messages() const
    {
        return processed_control_messages_;
    }

    unsigned int applied_actions() const
    {
        return applied_actions_;
    }

    /*!
     * \brief Instantiates a flowgraph
     *
     * \return Returns a smart pointer to a flowgraph object
     */
    std::shared_ptr<GNSSFlowgraph> flowgraph()
    {
        return flowgraph_;
    }

private:
    // Telecommand TCP interface
    TcpCmdInterface cmd_interface_;
    void telecommand_listener();

    /*
     * New receiver event dispatcher
     */
    bool receiver_on_standby_;
    void event_dispatcher(bool &valid_event, pmt::pmt_t &msg);

    std::thread cmd_interface_thread_;

    // SUPL assistance classes
    Gnss_Sdr_Supl_Client supl_client_acquisition_;
    Gnss_Sdr_Supl_Client supl_client_ephemeris_;
    int supl_mcc;  // Current network MCC (Mobile country code), 3 digits.
    int supl_mns;  // Current network MNC (Mobile Network code), 2 or 3 digits.
    int supl_lac;  // Current network LAC (Location area code),16 bits, 1-65520 are valid values.
    int supl_ci;   // Cell Identity (16 bits, 0-65535 are valid values).

    void init();

    // Read {ephemeris, iono, utc, ref loc, ref time} assistance from a local XML file previously recorded
    bool read_assistance_from_XML();

    /*
     * Blocking function that reads the GPS assistance queue
     */
    void gps_acq_assist_data_collector();

    /*
     * Compute elevations for the specified time and position for all the available satellites in ephemeris and almanac queues
     * returns a vector filled with the available satellites ordered from high elevation to low elevation angle.
     */
    std::vector<std::pair<int, Gnss_Satellite>> get_visible_sats(time_t rx_utc_time, const std::array<float, 3> &LLH);

    /*
     * Read initial GNSS assistance from SUPL server or local XML files
     */
    void assist_GNSS();

    void apply_action(unsigned int what);
    std::shared_ptr<GNSSFlowgraph> flowgraph_;
    std::shared_ptr<ConfigurationInterface> configuration_;
    std::shared_ptr<Concurrent_Queue<pmt::pmt_t>> control_queue_;
    bool pre_2009_file_;  // to override the system time to postprocess old gnss records and avoid wrong week rollover
    bool stop_;
    bool restart_;
    bool delete_configuration_;
    unsigned int processed_control_messages_;
    unsigned int applied_actions_;

    std::thread keyboard_thread_;
    std::thread sysv_queue_thread_;
    std::thread gps_acq_assist_data_collector_thread_;

    void keyboard_listener();
    void sysv_queue_listener();
    int msqid;

    // default filename for assistance data
    const std::string eph_default_xml_filename = "./gps_ephemeris.xml";
    const std::string utc_default_xml_filename = "./gps_utc_model.xml";
    const std::string iono_default_xml_filename = "./gps_iono.xml";
    const std::string ref_time_default_xml_filename = "./gps_ref_time.xml";
    const std::string ref_location_default_xml_filename = "./gps_ref_location.xml";
    const std::string eph_gal_default_xml_filename = "./gal_ephemeris.xml";
    const std::string eph_cnav_default_xml_filename = "./gps_cnav_ephemeris.xml";
    const std::string gal_iono_default_xml_filename = "./gal_iono.xml";
    const std::string gal_utc_default_xml_filename = "./gal_utc_model.xml";
    const std::string cnav_utc_default_xml_filename = "./gps_cnav_utc_model.xml";
    const std::string eph_glo_gnav_default_xml_filename = "./glo_gnav_ephemeris.xml";
    const std::string glo_utc_default_xml_filename = "./glo_utc_model.xml";
    const std::string gal_almanac_default_xml_filename = "./gal_almanac.xml";
    const std::string gps_almanac_default_xml_filename = "./gps_almanac.xml";

    Agnss_Ref_Location agnss_ref_location_;
    Agnss_Ref_Time agnss_ref_time_;

#ifdef ENABLE_FPGA
    boost::thread fpga_helper_thread_;
#endif
};

#endif  // GNSS_SDR_CONTROL_THREAD_H_
