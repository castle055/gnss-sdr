/*
 * SPDX-FileCopyrightText: (c) 2003, 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * SPDX-License-Identifier: BSD-1-Clause
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "SUPL-RESPONSE"
 *     found in "../supl-response.asn"
 */

#ifndef _KeyIdentity4_H_
#define _KeyIdentity4_H_

#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* KeyIdentity4 */
    typedef BIT_STRING_t KeyIdentity4_t;

    /* Implementation */
    extern asn_TYPE_descriptor_t asn_DEF_KeyIdentity4;
    asn_struct_free_f KeyIdentity4_free;
    asn_struct_print_f KeyIdentity4_print;
    asn_constr_check_f KeyIdentity4_constraint;
    ber_type_decoder_f KeyIdentity4_decode_ber;
    der_type_encoder_f KeyIdentity4_encode_der;
    xer_type_decoder_f KeyIdentity4_decode_xer;
    xer_type_encoder_f KeyIdentity4_encode_xer;
    per_type_decoder_f KeyIdentity4_decode_uper;
    per_type_encoder_f KeyIdentity4_encode_uper;

#ifdef __cplusplus
}
#endif

#endif /* _KeyIdentity4_H_ */
#include <asn_internal.h>
