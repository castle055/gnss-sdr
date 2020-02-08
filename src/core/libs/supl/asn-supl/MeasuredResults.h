/*
 * SPDX-FileCopyrightText: (c) 2003, 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * SPDX-License-Identifier: BSD-1-Clause
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "ULP-Components"
 *     found in "../supl-common.asn"
 */

#ifndef _MeasuredResults_H_
#define _MeasuredResults_H_

#include <asn_application.h>

/* Including external dependencies */
#include "UTRA-CarrierRSSI.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* Forward declarations */
    struct FrequencyInfo;
    struct CellMeasuredResultsList;

    /* MeasuredResults */
    typedef struct MeasuredResults
    {
        struct FrequencyInfo *frequencyInfo /* OPTIONAL */;
        UTRA_CarrierRSSI_t *utra_CarrierRSSI /* OPTIONAL */;
        struct CellMeasuredResultsList *cellMeasuredResultsList /* OPTIONAL */;

        /* Context for parsing across buffer boundaries */
        asn_struct_ctx_t _asn_ctx;
    } MeasuredResults_t;

    /* Implementation */
    extern asn_TYPE_descriptor_t asn_DEF_MeasuredResults;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "CellMeasuredResultsList.h"
#include "FrequencyInfo.h"

#endif /* _MeasuredResults_H_ */
#include <asn_internal.h>
