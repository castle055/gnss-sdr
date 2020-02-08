/*
 * SPDX-FileCopyrightText: (c) 2003, 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * SPDX-License-Identifier: BSD-1-Clause
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "SUPL-POS-INIT"
 *     found in "../supl-posinit.asn"
 */

#ifndef _RequestedAssistData_H_
#define _RequestedAssistData_H_

#include <asn_application.h>

/* Including external dependencies */
#include <BOOLEAN.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* Forward declarations */
    struct XNavigationModel;

    /* RequestedAssistData */
    typedef struct RequestedAssistData
    {
        BOOLEAN_t almanacRequested;
        BOOLEAN_t utcModelRequested;
        BOOLEAN_t ionosphericModelRequested;
        BOOLEAN_t dgpsCorrectionsRequested;
        BOOLEAN_t referenceLocationRequested;
        BOOLEAN_t referenceTimeRequested;
        BOOLEAN_t acquisitionAssistanceRequested;
        BOOLEAN_t realTimeIntegrityRequested;
        BOOLEAN_t navigationModelRequested;
        struct XNavigationModel *navigationModelData /* OPTIONAL */;
        /*
         * This type is extensible,
         * possible extensions are below.
         */

        /* Context for parsing across buffer boundaries */
        asn_struct_ctx_t _asn_ctx;
    } RequestedAssistData_t;

    /* Implementation */
    extern asn_TYPE_descriptor_t asn_DEF_RequestedAssistData;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "XNavigationModel.h"

#endif /* _RequestedAssistData_H_ */
#include <asn_internal.h>
