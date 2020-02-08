/*
 * SPDX-FileCopyrightText: (c) 2003, 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * SPDX-License-Identifier: BSD-1-Clause
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "SUPL-START"
 *     found in "../supl-start.asn"
 */

#ifndef _PrefMethod_H_
#define _PrefMethod_H_

#include <asn_application.h>

/* Including external dependencies */
#include <ENUMERATED.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* Dependencies */
    typedef enum PrefMethod
    {
        PrefMethod_agpsSETassistedPreferred = 0,
        PrefMethod_agpsSETBasedPreferred = 1,
        PrefMethod_noPreference = 2
    } e_PrefMethod;

    /* PrefMethod */
    typedef ENUMERATED_t PrefMethod_t;

    /* Implementation */
    extern asn_TYPE_descriptor_t asn_DEF_PrefMethod;
    asn_struct_free_f PrefMethod_free;
    asn_struct_print_f PrefMethod_print;
    asn_constr_check_f PrefMethod_constraint;
    ber_type_decoder_f PrefMethod_decode_ber;
    der_type_encoder_f PrefMethod_encode_der;
    xer_type_decoder_f PrefMethod_decode_xer;
    xer_type_encoder_f PrefMethod_encode_xer;
    per_type_decoder_f PrefMethod_decode_uper;
    per_type_encoder_f PrefMethod_encode_uper;

#ifdef __cplusplus
}
#endif

#endif /* _PrefMethod_H_ */
#include <asn_internal.h>
