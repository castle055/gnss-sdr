/*
 * SPDX-FileCopyrightText: (c) 2003, 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * SPDX-License-Identifier: BSD-1-Clause
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "RRLP-Components"
 *     found in "../rrlp-components.asn"
 */

#ifndef _BTSPosition_H_
#define _BTSPosition_H_

#include <asn_application.h>

/* Including external dependencies */
#include "Ext-GeographicalInformation.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* BTSPosition */
    typedef Ext_GeographicalInformation_t BTSPosition_t;

    /* Implementation */
    extern asn_TYPE_descriptor_t asn_DEF_BTSPosition;
    asn_struct_free_f BTSPosition_free;
    asn_struct_print_f BTSPosition_print;
    asn_constr_check_f BTSPosition_constraint;
    ber_type_decoder_f BTSPosition_decode_ber;
    der_type_encoder_f BTSPosition_encode_der;
    xer_type_decoder_f BTSPosition_decode_xer;
    xer_type_encoder_f BTSPosition_encode_xer;
    per_type_decoder_f BTSPosition_decode_uper;
    per_type_encoder_f BTSPosition_encode_uper;

#ifdef __cplusplus
}
#endif

#endif /* _BTSPosition_H_ */
#include <asn_internal.h>
