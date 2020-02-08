/*!
 * \file file_signal_source_test.cc
 * \brief  This class implements a Unit Test for the class FileSignalSource.
 * \author Carlos Avilés, 2010. carlos.avilesr(at)googlemail.com
 *
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

#include "concurrent_queue.h"
#include "file_signal_source.h"
#include "in_memory_configuration.h"
#include <gnuradio/top_block.h>
#include <gtest/gtest.h>
#include <stdexcept>

TEST(FileSignalSource, Instantiate)
{
    std::shared_ptr<Concurrent_Queue<pmt::pmt_t>> queue = std::make_shared<Concurrent_Queue<pmt::pmt_t>>();
    std::shared_ptr<InMemoryConfiguration> config = std::make_shared<InMemoryConfiguration>();

    config->set_property("Test.samples", "0");
    config->set_property("Test.sampling_frequency", "0");
    std::string path = std::string(TEST_PATH);
    std::string filename = path + "signal_samples/GPS_L1_CA_ID_1_Fs_4Msps_2ms.dat";
    config->set_property("Test.filename", filename);
    config->set_property("Test.item_type", "gr_complex");
    config->set_property("Test.repeat", "false");

    std::unique_ptr<FileSignalSource> signal_source(new FileSignalSource(config.get(), "Test", 0, 1, queue));

    EXPECT_STREQ("gr_complex", signal_source->item_type().c_str());
    EXPECT_TRUE(signal_source->repeat() == false);
}

TEST(FileSignalSource, InstantiateFileNotExists)
{
    std::shared_ptr<Concurrent_Queue<pmt::pmt_t>> queue = std::make_shared<Concurrent_Queue<pmt::pmt_t>>();
    std::shared_ptr<InMemoryConfiguration> config = std::make_shared<InMemoryConfiguration>();

    config->set_property("Test.samples", "0");
    config->set_property("Test.sampling_frequency", "0");
    config->set_property("Test.filename", "./signal_samples/i_dont_exist.dat");
    config->set_property("Test.item_type", "gr_complex");
    config->set_property("Test.repeat", "false");

    EXPECT_THROW({ auto uptr = std::make_shared<FileSignalSource>(config.get(), "Test", 0, 1, queue); }, std::exception);
}
