//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//                 Интерфейсный файл dwarf.hpp                          //
//                                                                      //
//  Файл определяет константы DWARF                                     //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:32p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef _DWARF_H
#define _DWARF_H


const Dwarf_Half DW_TAG_array_type              = 0x01;
const Dwarf_Half DW_TAG_class_type              = 0x02;
const Dwarf_Half DW_TAG_entry_point             = 0x03;
const Dwarf_Half DW_TAG_enumeration_type        = 0x04;
const Dwarf_Half DW_TAG_formal_parameter        = 0x05;
const Dwarf_Half DW_TAG_imported_declaration    = 0x08;
const Dwarf_Half DW_TAG_label                   = 0x0a;
const Dwarf_Half DW_TAG_lexical_block           = 0x0b;
const Dwarf_Half DW_TAG_member                  = 0x0d;
const Dwarf_Half DW_TAG_pointer_type            = 0x0f;
const Dwarf_Half DW_TAG_reference_type          = 0x10;
const Dwarf_Half DW_TAG_compile_unit            = 0x11;
const Dwarf_Half DW_TAG_string_type             = 0x12;
const Dwarf_Half DW_TAG_structure_type          = 0x13;
const Dwarf_Half DW_TAG_subroutine_type         = 0x15;
const Dwarf_Half DW_TAG_typedef                 = 0x16;
const Dwarf_Half DW_TAG_union_type              = 0x17;
const Dwarf_Half DW_TAG_unspecified_parameters  = 0x18;
const Dwarf_Half DW_TAG_variant                 = 0x19;
const Dwarf_Half DW_TAG_common_block            = 0x1a;
const Dwarf_Half DW_TAG_common_inclusion        = 0x1b;
const Dwarf_Half DW_TAG_inheritance             = 0x1c;
const Dwarf_Half DW_TAG_inlined_subroutine      = 0x1d;
const Dwarf_Half DW_TAG_module                  = 0x1e;
const Dwarf_Half DW_TAG_ptr_to_member_type      = 0x1f;
const Dwarf_Half DW_TAG_set_type                = 0x20;
const Dwarf_Half DW_TAG_subrange_type           = 0x21;
const Dwarf_Half DW_TAG_with_stmt               = 0x22;
const Dwarf_Half DW_TAG_access_declaration      = 0x23;
const Dwarf_Half DW_TAG_base_type               = 0x24;
const Dwarf_Half DW_TAG_catch_block             = 0x25;
const Dwarf_Half DW_TAG_const_type              = 0x26;
const Dwarf_Half DW_TAG_constant                = 0x27;
const Dwarf_Half DW_TAG_enumerator              = 0x28;
const Dwarf_Half DW_TAG_file_type               = 0x29;
const Dwarf_Half DW_TAG_friend                  = 0x2a;
const Dwarf_Half DW_TAG_namelist                = 0x2b;
const Dwarf_Half DW_TAG_namelist_item           = 0x2c;
const Dwarf_Half DW_TAG_packed_type             = 0x2d;
const Dwarf_Half DW_TAG_subprogram              = 0x2e;
const Dwarf_Half DW_TAG_template_type_parameter   = 0x2f;
const Dwarf_Half DW_TAG_template_value_parameter  = 0x30;
const Dwarf_Half DW_TAG_thrown_type             = 0x31;
const Dwarf_Half DW_TAG_try_block               = 0x32;
const Dwarf_Half DW_TAG_variant_part            = 0x33;
const Dwarf_Half DW_TAG_variable                = 0x34;
const Dwarf_Half DW_TAG_volatile_type           = 0x35;
const Dwarf_Half DW_TAG_lo_user                 = 0x4080;
const Dwarf_Half DW_TAG_NC_namespace            = 0x4081;
const Dwarf_Half DW_TAG_NC_using                = 0x4082;
const Dwarf_Half DW_TAG_hi_user                 = 0xffff;

const Dwarf_Small DW_children_no    = 0;
const Dwarf_Small DW_children_yes   = 1;


const Dwarf_Half DW_FORM_addr       = 0x01;
const Dwarf_Half DW_FORM_block2     = 0x03;
const Dwarf_Half DW_FORM_block4     = 0x04;
const Dwarf_Half DW_FORM_data2      = 0x05;
const Dwarf_Half DW_FORM_data4      = 0x06;
const Dwarf_Half DW_FORM_data8      = 0x07;
const Dwarf_Half DW_FORM_string     = 0x08;
const Dwarf_Half DW_FORM_block      = 0x09;
const Dwarf_Half DW_FORM_block1     = 0x0a;
const Dwarf_Half DW_FORM_data1      = 0x0b;
const Dwarf_Half DW_FORM_flag       = 0x0c;
const Dwarf_Half DW_FORM_sdata      = 0x0d;
const Dwarf_Half DW_FORM_strp       = 0x0e;
const Dwarf_Half DW_FORM_udata      = 0x0f;
const Dwarf_Half DW_FORM_ref_addr   = 0x10;
const Dwarf_Half DW_FORM_ref1       = 0x11;
const Dwarf_Half DW_FORM_ref2       = 0x12;
const Dwarf_Half DW_FORM_ref4       = 0x13;
const Dwarf_Half DW_FORM_ref8       = 0x14;
const Dwarf_Half DW_FORM_ref_udata  = 0x15;
const Dwarf_Half DW_FORM_indirect   = 0x16;

const Dwarf_Half DW_AT_sibling              = 0x01;
const Dwarf_Half DW_AT_location             = 0x02;
const Dwarf_Half DW_AT_name                 = 0x03;
const Dwarf_Half DW_AT_ordering             = 0x09;
const Dwarf_Half DW_AT_subscr_data          = 0x0a;
const Dwarf_Half DW_AT_byte_size            = 0x0b;
const Dwarf_Half DW_AT_bit_offset           = 0x0c;
const Dwarf_Half DW_AT_bit_size             = 0x0d;
const Dwarf_Half DW_AT_element_list         = 0x0f;
const Dwarf_Half DW_AT_stmt_list            = 0x10;
const Dwarf_Half DW_AT_low_pc               = 0x11;
const Dwarf_Half DW_AT_high_pc              = 0x12;
const Dwarf_Half DW_AT_language             = 0x13;
const Dwarf_Half DW_AT_member               = 0x14;
const Dwarf_Half DW_AT_discr                = 0x15;
const Dwarf_Half DW_AT_discr_value          = 0x16;
const Dwarf_Half DW_AT_visibility           = 0x17;
const Dwarf_Half DW_AT_import               = 0x18;
const Dwarf_Half DW_AT_string_length        = 0x19;
const Dwarf_Half DW_AT_common_reference     = 0x1a;
const Dwarf_Half DW_AT_comp_dir             = 0x1b;
const Dwarf_Half DW_AT_const_value          = 0x1c;
const Dwarf_Half DW_AT_containing_type      = 0x1d;
const Dwarf_Half DW_AT_default_value        = 0x1e;
const Dwarf_Half DW_AT_inline               = 0x20;
const Dwarf_Half DW_AT_is_optional          = 0x21;
const Dwarf_Half DW_AT_lower_bound          = 0x22;
const Dwarf_Half DW_AT_producer             = 0x25;
const Dwarf_Half DW_AT_prototyped           = 0x27;
const Dwarf_Half DW_AT_return_addr          = 0x2a;
const Dwarf_Half DW_AT_start_scope          = 0x2c;
const Dwarf_Half DW_AT_stride_size          = 0x2e;
const Dwarf_Half DW_AT_upper_bound          = 0x2f;
const Dwarf_Half DW_AT_abstract_origin      = 0x31;
const Dwarf_Half DW_AT_accessibility        = 0x32;
const Dwarf_Half DW_AT_address_class        = 0x33;
const Dwarf_Half DW_AT_artificial           = 0x34;
const Dwarf_Half DW_AT_base_types           = 0x35;
const Dwarf_Half DW_AT_calling_convention   = 0x36;
const Dwarf_Half DW_AT_count                = 0x37;
const Dwarf_Half DW_AT_data_member_location = 0x38;
const Dwarf_Half DW_AT_decl_column          = 0x39;
const Dwarf_Half DW_AT_decl_file            = 0x3a;
const Dwarf_Half DW_AT_decl_line            = 0x3b;
const Dwarf_Half DW_AT_declaration          = 0x3c;
const Dwarf_Half DW_AT_discr_list           = 0x3d;
const Dwarf_Half DW_AT_encoding             = 0x3e;
const Dwarf_Half DW_AT_external             = 0x3f;
const Dwarf_Half DW_AT_frame_base           = 0x40;
const Dwarf_Half DW_AT_friend               = 0x41;
const Dwarf_Half DW_AT_identifier_case      = 0x42;
const Dwarf_Half DW_AT_macro_info           = 0x43;
const Dwarf_Half DW_AT_namelist_items       = 0x44;
const Dwarf_Half DW_AT_priority             = 0x45;
const Dwarf_Half DW_AT_segment              = 0x46;
const Dwarf_Half DW_AT_specification        = 0x47;
const Dwarf_Half DW_AT_static_link          = 0x48;
const Dwarf_Half DW_AT_type                 = 0x49;
const Dwarf_Half DW_AT_use_location         = 0x4a;
const Dwarf_Half DW_AT_variable_parameter   = 0x4b;
const Dwarf_Half DW_AT_virtuality           = 0x4c;
const Dwarf_Half DW_AT_vtable_elem_location = 0x4d;
const Dwarf_Half DW_AT_lo_user              = 0x2000;
const Dwarf_Half DW_AT_NC_using             = 0x2001;
const Dwarf_Half DW_AT_hi_user              = 0x3fff;


const Dwarf_Small DW_OP_addr        = 0x03;
const Dwarf_Small DW_OP_deref       = 0x06;
const Dwarf_Small DW_OP_const1u     = 0x08;
const Dwarf_Small DW_OP_const1s     = 0x09;
const Dwarf_Small DW_OP_const2u     = 0x0a;
const Dwarf_Small DW_OP_const2s     = 0x0b;
const Dwarf_Small DW_OP_const4u     = 0x0c;
const Dwarf_Small DW_OP_const4s     = 0x0d;
const Dwarf_Small DW_OP_const8u     = 0x0e;
const Dwarf_Small DW_OP_const8s     = 0x0f;
const Dwarf_Small DW_OP_constu      = 0x10;
const Dwarf_Small DW_OP_consts      = 0x11;
const Dwarf_Small DW_OP_dup         = 0x12;
const Dwarf_Small DW_OP_drop        = 0x13;
const Dwarf_Small DW_OP_over        = 0x14;
const Dwarf_Small DW_OP_pick        = 0x15;
const Dwarf_Small DW_OP_swap        = 0x16;
const Dwarf_Small DW_OP_rot         = 0x17;
const Dwarf_Small DW_OP_xderef      = 0x18;
const Dwarf_Small DW_OP_abs         = 0x19;
const Dwarf_Small DW_OP_and         = 0x1a;
const Dwarf_Small DW_OP_div         = 0x1b;
const Dwarf_Small DW_OP_minus       = 0x1c;
const Dwarf_Small DW_OP_mod         = 0x1d;
const Dwarf_Small DW_OP_mul         = 0x1e;
const Dwarf_Small DW_OP_neg         = 0x1f;
const Dwarf_Small DW_OP_not         = 0x20;
const Dwarf_Small DW_OP_or          = 0x21;
const Dwarf_Small DW_OP_plus        = 0x22;
const Dwarf_Small DW_OP_plus_uconst = 0x23;
const Dwarf_Small DW_OP_shl         = 0x24;
const Dwarf_Small DW_OP_shr         = 0x25;
const Dwarf_Small DW_OP_shra        = 0x26;
const Dwarf_Small DW_OP_xor         = 0x27;
const Dwarf_Small DW_OP_bra         = 0x28;
const Dwarf_Small DW_OP_eq          = 0x29;
const Dwarf_Small DW_OP_ge          = 0x2a;
const Dwarf_Small DW_OP_gt          = 0x2b;
const Dwarf_Small DW_OP_le          = 0x2c;
const Dwarf_Small DW_OP_lt          = 0x2d;
const Dwarf_Small DW_OP_ne          = 0x2e;
const Dwarf_Small DW_OP_skip        = 0x2f;
const Dwarf_Small DW_OP_lit0        = 0x30;
const Dwarf_Small DW_OP_lit1        = 0x31;
const Dwarf_Small DW_OP_lit2        = 0x32;
const Dwarf_Small DW_OP_lit3        = 0x33;
const Dwarf_Small DW_OP_lit4        = 0x34;
const Dwarf_Small DW_OP_lit5        = 0x35;
const Dwarf_Small DW_OP_lit6        = 0x36;
const Dwarf_Small DW_OP_lit7        = 0x37;
const Dwarf_Small DW_OP_lit8        = 0x38;
const Dwarf_Small DW_OP_lit9        = 0x39;
const Dwarf_Small DW_OP_lit10       = 0x3a;
const Dwarf_Small DW_OP_lit11       = 0x3b;
const Dwarf_Small DW_OP_lit12       = 0x3c;
const Dwarf_Small DW_OP_lit13       = 0x3d;
const Dwarf_Small DW_OP_lit14       = 0x3e;
const Dwarf_Small DW_OP_lit15       = 0x3f;
const Dwarf_Small DW_OP_lit16       = 0x40;
const Dwarf_Small DW_OP_lit17       = 0x41;
const Dwarf_Small DW_OP_lit18       = 0x42;
const Dwarf_Small DW_OP_lit19       = 0x43;
const Dwarf_Small DW_OP_lit20       = 0x44;
const Dwarf_Small DW_OP_lit21       = 0x45;
const Dwarf_Small DW_OP_lit22       = 0x46;
const Dwarf_Small DW_OP_lit23       = 0x47;
const Dwarf_Small DW_OP_lit24       = 0x48;
const Dwarf_Small DW_OP_lit25       = 0x49;
const Dwarf_Small DW_OP_lit26       = 0x4a;
const Dwarf_Small DW_OP_lit27       = 0x4b;
const Dwarf_Small DW_OP_lit28       = 0x4c;
const Dwarf_Small DW_OP_lit29       = 0x4d;
const Dwarf_Small DW_OP_lit30       = 0x4e;
const Dwarf_Small DW_OP_lit31       = 0x4f;
const Dwarf_Small DW_OP_reg0        = 0x50;
const Dwarf_Small DW_OP_reg1        = 0x51;
const Dwarf_Small DW_OP_reg2        = 0x52;
const Dwarf_Small DW_OP_reg3        = 0x53;
const Dwarf_Small DW_OP_reg4        = 0x54;
const Dwarf_Small DW_OP_reg5        = 0x55;
const Dwarf_Small DW_OP_reg6        = 0x56;
const Dwarf_Small DW_OP_reg7        = 0x57;
const Dwarf_Small DW_OP_reg8        = 0x58;
const Dwarf_Small DW_OP_reg9        = 0x59;
const Dwarf_Small DW_OP_reg10       = 0x5a;
const Dwarf_Small DW_OP_reg11       = 0x5b;
const Dwarf_Small DW_OP_reg12       = 0x5c;
const Dwarf_Small DW_OP_reg13       = 0x5d;
const Dwarf_Small DW_OP_reg14       = 0x5e;
const Dwarf_Small DW_OP_reg15       = 0x5f;
const Dwarf_Small DW_OP_reg16       = 0x60;
const Dwarf_Small DW_OP_reg17       = 0x61;
const Dwarf_Small DW_OP_reg18       = 0x62;
const Dwarf_Small DW_OP_reg19       = 0x63;
const Dwarf_Small DW_OP_reg20       = 0x64;
const Dwarf_Small DW_OP_reg21       = 0x65;
const Dwarf_Small DW_OP_reg22       = 0x66;
const Dwarf_Small DW_OP_reg23       = 0x67;
const Dwarf_Small DW_OP_reg24       = 0x68;
const Dwarf_Small DW_OP_reg25       = 0x69;
const Dwarf_Small DW_OP_reg26       = 0x6a;
const Dwarf_Small DW_OP_reg27       = 0x6b;
const Dwarf_Small DW_OP_reg28       = 0x6c;
const Dwarf_Small DW_OP_reg29       = 0x6d;
const Dwarf_Small DW_OP_reg30       = 0x6e;
const Dwarf_Small DW_OP_reg31       = 0x6f;
const Dwarf_Small DW_OP_breg0       = 0x70;
const Dwarf_Small DW_OP_breg1       = 0x71;
const Dwarf_Small DW_OP_breg2       = 0x72;
const Dwarf_Small DW_OP_breg3       = 0x73;
const Dwarf_Small DW_OP_breg4       = 0x74;
const Dwarf_Small DW_OP_breg5       = 0x75;
const Dwarf_Small DW_OP_breg6       = 0x76;
const Dwarf_Small DW_OP_breg7       = 0x77;
const Dwarf_Small DW_OP_breg8       = 0x78;
const Dwarf_Small DW_OP_breg9       = 0x79;
const Dwarf_Small DW_OP_breg10      = 0x7a;
const Dwarf_Small DW_OP_breg11      = 0x7b;
const Dwarf_Small DW_OP_breg12      = 0x7c;
const Dwarf_Small DW_OP_breg13      = 0x7d;
const Dwarf_Small DW_OP_breg14      = 0x7e;
const Dwarf_Small DW_OP_breg15      = 0x7f;
const Dwarf_Small DW_OP_breg16      = 0x80;
const Dwarf_Small DW_OP_breg17      = 0x81;
const Dwarf_Small DW_OP_breg18      = 0x82;
const Dwarf_Small DW_OP_breg19      = 0x83;
const Dwarf_Small DW_OP_breg20      = 0x84;
const Dwarf_Small DW_OP_breg21      = 0x85;
const Dwarf_Small DW_OP_breg22      = 0x86;
const Dwarf_Small DW_OP_breg23      = 0x87;
const Dwarf_Small DW_OP_breg24      = 0x88;
const Dwarf_Small DW_OP_breg25      = 0x89;
const Dwarf_Small DW_OP_breg26      = 0x8a;
const Dwarf_Small DW_OP_breg27      = 0x8b;
const Dwarf_Small DW_OP_breg28      = 0x8c;
const Dwarf_Small DW_OP_breg29      = 0x8d;
const Dwarf_Small DW_OP_breg30      = 0x8e;
const Dwarf_Small DW_OP_breg31      = 0x8f;
const Dwarf_Small DW_OP_regx        = 0x90;
const Dwarf_Small DW_OP_fbreg       = 0x91;
const Dwarf_Small DW_OP_bregx       = 0x92;
const Dwarf_Small DW_OP_piece       = 0x93;
const Dwarf_Small DW_OP_deref_size  = 0x94;
const Dwarf_Small DW_OP_xderef_size = 0x95;
const Dwarf_Small DW_OP_nop         = 0x96;
const Dwarf_Small DW_OP_lo_user     = 0xe0;
const Dwarf_Small DW_OP_hi_user     = 0xff;

const Dwarf_Small DW_ATE_address        = 0x1;
const Dwarf_Small DW_ATE_boolean        = 0x2;
const Dwarf_Small DW_ATE_complex_float  = 0x3;
const Dwarf_Small DW_ATE_float          = 0x4;
const Dwarf_Small DW_ATE_signed         = 0x5;
const Dwarf_Small DW_ATE_signed_char    = 0x6;
const Dwarf_Small DW_ATE_unsigned       = 0x7;
const Dwarf_Small DW_ATE_unsigned_char  = 0x8;
const Dwarf_Small DW_ATE_lo_user        = 0x80;
const Dwarf_Small DW_ATE_hi_user        = 0xff;

const Dwarf_Small DW_ACCESS_public      = 1;
const Dwarf_Small DW_ACCESS_protected   = 2;
const Dwarf_Small DW_ACCESS_private     = 3;

const Dwarf_Small DW_VIS_local          = 1;
const Dwarf_Small DW_VIS_exported       = 2;
const Dwarf_Small DW_VIS_qualified      = 3;

const Dwarf_Small DW_VIRTUALITY_none            = 0;
const Dwarf_Small DW_VIRTUALITY_virtual         = 1;
const Dwarf_Small DW_VIRTUALITY_pure_virtual    = 2;

const Dwarf_Half DW_LANG_C89            = 0x0001;
const Dwarf_Half DW_LANG_C              = 0x0002;
const Dwarf_Half DW_LANG_Ada83          = 0x0003;
const Dwarf_Half DW_LANG_C_plus_plus    = 0x0004;
const Dwarf_Half DW_LANG_Cobol74        = 0x0005;
const Dwarf_Half DW_LANG_Cobol85        = 0x0006;
const Dwarf_Half DW_LANG_Fortran77      = 0x0007;
const Dwarf_Half DW_LANG_Fortran90      = 0x0008;
const Dwarf_Half DW_LANG_Pascal83       = 0x0009;
const Dwarf_Half DW_LANG_Modula2        = 0x000a;
const Dwarf_Half DW_LANG_lo_user        = 0x8000;
const Dwarf_Half DW_LANG_Mips_Assembler = 0x8001;
const Dwarf_Half DW_LANG_NeuroChip_Assembler
                                        = 0xf001;
const Dwarf_Half DW_LANG_hi_user        = 0xffff;


const Dwarf_Small DW_ID_case_sensitive      = 0;
const Dwarf_Small DW_ID_up_case             = 1;
const Dwarf_Small DW_ID_down_case           = 2;
const Dwarf_Small DW_ID_case_insensitive    = 3;

const Dwarf_Small DW_CC_normal      = 0x1;
const Dwarf_Small DW_CC_program     = 0x2;
const Dwarf_Small DW_CC_nocall      = 0x3;
const Dwarf_Small DW_CC_lo_user     = 0x40;
const Dwarf_Small DW_CC_hi_user     = 0xff;

const Dwarf_Small DW_INL_not_inlined            = 0;
const Dwarf_Small DW_INL_inlined                = 1;
const Dwarf_Small DW_INL_declared_not_inlined   = 2;
const Dwarf_Small DW_INL_declared_inlined       = 3;

const Dwarf_Small DW_ORD_row_major  = 0;
const Dwarf_Small DW_ORD_col_major  = 1;

const Dwarf_Small DW_DSC_label      = 0;
const Dwarf_Small DW_DSC_range      = 1;

const Dwarf_Small DW_LNS_copy               = 1;
const Dwarf_Small DW_LNS_advance_pc         = 2;
const Dwarf_Small DW_LNS_advance_line       = 3;
const Dwarf_Small DW_LNS_set_file           = 4;
const Dwarf_Small DW_LNS_set_column         = 5;
const Dwarf_Small DW_LNS_negate_stmt        = 6;
const Dwarf_Small DW_LNS_set_basic_block    = 7;
const Dwarf_Small DW_LNS_const_add_pc       = 8;
const Dwarf_Small DW_LNS_fixed_advance_pc   = 9;

const Dwarf_Small DW_LNE_end_sequence   = 1;
const Dwarf_Small DW_LNE_set_address    = 2;
const Dwarf_Small DW_LNE_define_file    = 3;

const Dwarf_Small DW_MACINFO_define     = 1;
const Dwarf_Small DW_MACINFO_undef      = 2;
const Dwarf_Small DW_MACINFO_start_file = 3;
const Dwarf_Small DW_MACINFO_end_file   = 4;
const Dwarf_Small DW_MACINFO_vendor_ext = 255;

const Dwarf_Small DW_CFA_advance_loc    = 0x40;
const Dwarf_Small DW_CFA_offset         = 0x80;
const Dwarf_Small DW_CFA_restore        = 0xc0;
const Dwarf_Small DW_CFA_extended       = 0;

const Dwarf_Small DW_CFA_nop                = 0x00;
const Dwarf_Small DW_CFA_set_loc            = 0x01;
const Dwarf_Small DW_CFA_advance_loc1       = 0x02;
const Dwarf_Small DW_CFA_advance_loc2       = 0x03;
const Dwarf_Small DW_CFA_advance_loc4       = 0x04;
const Dwarf_Small DW_CFA_offset_extended    = 0x05;
const Dwarf_Small DW_CFA_restore_extended   = 0x06;
const Dwarf_Small DW_CFA_undefined          = 0x07;
const Dwarf_Small DW_CFA_same_value         = 0x08;
const Dwarf_Small DW_CFA_register           = 0x09;
const Dwarf_Small DW_CFA_remember_state     = 0x0a;
const Dwarf_Small DW_CFA_restore_state      = 0x0b;
const Dwarf_Small DW_CFA_def_cfa            = 0x0c;
const Dwarf_Small DW_CFA_def_cfa_register   = 0x0d;
const Dwarf_Small DW_CFA_def_cfa_offset     = 0x0e;

const Dwarf_Small DW_CFA_low_user           = 0x1c;
const Dwarf_Small DW_CFA_high_user          = 0x3f;


//----------------------------------------------------------------------//
//  Отображение регистров нейропроцессора и псевдорегистров в номера 
//  используемые отладчиком для обозначения регистров
//  константы DW_REG машинно-зависимы.
//  Здесь приводятся константы для нейропроцессора ( 1 версия ).
//  Номера регистров соответствуют кодированию регистров нейропроцессором
//  (в команде move).
//
//----------------------------------------------------------------------//

    // 32-битные регистры скалярного процессора

const Dwarf_Small DW_REG_AR0        = 0;  // адресный регистр 0
const Dwarf_Small DW_REG_AR1        = 1;  // адресный регистр 1
const Dwarf_Small DW_REG_AR2        = 2;  // адресный регистр 2
const Dwarf_Small DW_REG_AR3        = 3;  // адресный регистр 3
const Dwarf_Small DW_REG_AR4        = 4;  // адресный регистр 4
const Dwarf_Small DW_REG_AR5	    = 5;  // адресный регистр 5
const Dwarf_Small DW_REG_AR6	    = 6;  // адресный регистр 6
const Dwarf_Small DW_REG_AR7	    = 7;  // адресный регистр 7

const Dwarf_Small DW_REG_SP         = DW_REG_AR7; 
                                          // синоним для AR7

const Dwarf_Small DW_REG_OCA0	    = 8;  // регистр адреса канала вывода 0
const Dwarf_Small DW_REG_ICA0	    = 9;  // регистр адреса канала ввода 0
const Dwarf_Small DW_REG_OCA1	    = 10; // регистр адреса канала вывода 1
const Dwarf_Small DW_REG_ICA1	    = 11; // регистр адреса канала ввода 1

const Dwarf_Small DW_REG_T0         = 12; // таймер 0

const Dwarf_Small DW_REG_LMICR      = 13; // регистр управления интерфейсом с 
                                          // локальной шиной
const Dwarf_Small DW_REG_GMICR      = 14; // регистр управления интерфейсом с 
                                          // глобальной шиной

const Dwarf_Small DW_REG_PC         = 15; // программный счетчик

const Dwarf_Small DW_REG_GR0        = 16; // арифметический регистр 0
const Dwarf_Small DW_REG_GR1        = 17; // арифметический регистр 1
const Dwarf_Small DW_REG_GR2        = 18; // арифметический регистр 2
const Dwarf_Small DW_REG_GR3        = 19; // арифметический регистр 3
const Dwarf_Small DW_REG_GR4        = 20; // арифметический регистр 4
const Dwarf_Small DW_REG_GR5        = 21; // арифметический регистр 5
const Dwarf_Small DW_REG_GR6        = 22; // арифметический регистр 6
const Dwarf_Small DW_REG_GR7        = 23; // арифметический регистр 7

const Dwarf_Small DW_REG_OCC0       = 24; // счетчик канала вывода 0
const Dwarf_Small DW_REG_ICC0       = 25; // счетчик канала ввода  0
const Dwarf_Small DW_REG_OCC1       = 26; // счетчик канала вывода 1
const Dwarf_Small DW_REG_ICC1       = 27; // счетчик канала ввода  1

const Dwarf_Small DW_REG_T1         = 28; // таймер 1

const Dwarf_Small DW_REG_PSWRreset  = 29; // регистр сброса битов слова 
                                          // состояния процессора

const Dwarf_Small DW_REG_INTR       = 30; // регистр запроса на прерывание и ПДП
const Dwarf_Small DW_REG_PSWR       = 31; // слово состояния процессора
                                          // запись и чтение

    // 64-битные регистры и регистровые пары скалярного процессора

const Dwarf_Small DW_REG_GR0AR0     = 32; // регистровая пара AR0, GR0
const Dwarf_Small DW_REG_GR1AR1     = 33; // регистровая пара AR1, GR1
const Dwarf_Small DW_REG_GR2AR2     = 34; // регистровая пара AR2, GR2
const Dwarf_Small DW_REG_GR3AR3     = 35; // регистровая пара AR3, GR3
const Dwarf_Small DW_REG_GR4AR4     = 36; // регистровая пара AR4, GR4
const Dwarf_Small DW_REG_GR5AR5     = 37; // регистровая пара AR5, GR5
const Dwarf_Small DW_REG_GR6AR6     = 38; // регистровая пара AR6, GR6
const Dwarf_Small DW_REG_GR7AR7     = 39; // регистровая пара AR7, GR7

const Dwarf_Small DW_REG_OCC0OCA0   = 40; // регистровая пара OCC0, OCA0
const Dwarf_Small DW_REG_ICC0ICA0   = 41; // регистровая пара ICC0, ICA0
const Dwarf_Small DW_REG_OCC1OCA1   = 42; // регистровая пара OCC1, OCA1
const Dwarf_Small DW_REG_ICC1ICA1   = 43; // регистровая пара ICC1, ICA1

const Dwarf_Small DW_REG_T1T0       = 44; // регистровая пара T1, T0

const Dwarf_Small DW_REG_DOR0       = 45; // 64 битный регистр данных 
                                          // канала вывода 0
const Dwarf_Small DW_REG_DIR0       = 45; // 64 битный регистр данных 
                                          // канала ввода 0
                                          // номер совпадает с DOR0

const Dwarf_Small DW_REG_DOR1       = 46; // 64 битный регистр данных 
                                          // канала вывода 1
const Dwarf_Small DW_REG_DIR1       = 46; // 64 битный регистр данных 
                                          // канала ввода 1
                                          // номер совпадает с DOR1

const Dwarf_Small DW_REG_PSWRPC     = 47; //  регистровая пара PSWR, PC

    // 32-битные регистры векторного процессора

const Dwarf_Small DW_REG_NB1L   = 48; // 1-й регистр границ нейронов, мл. часть
const Dwarf_Small DW_REG_SB1L   = 49; // 1-й регистр границ синапсов, мл. часть
const Dwarf_Small DW_REG_F1CRL  = 50; // 1-й регистр управления функцией 
                                      // активации, младшая часть
const Dwarf_Small DW_REG_F2CRL  = 51; // 2-й регистр управления функцией 
                                      // активации, младшая часть

const Dwarf_Small DW_REG_NB1H   = 52; // 1-й регистр границ нейронов, ст. часть
const Dwarf_Small DW_REG_SB1H   = 53; // 1-й регистр границ синапсов, ст. часть
const Dwarf_Small DW_REG_F1CRH  = 54; // 1-й регистр управления функцией 
                                      // активации, старшая часть
const Dwarf_Small DW_REG_F2CRH  = 55; // 2-й регистр управления функцией 
                                      // активации, старшая часть

    // 64-битные регистры векторного процессора    

const Dwarf_Small DW_REG_NB1    = 56; // 1-й регистр границ нейронов
const Dwarf_Small DW_REG_SB1    = 57; // 1-й регистр границ синапсов
const Dwarf_Small DW_REG_F1CR   = 58; // 1-й регистр управления функцией 
                                      // активации
const Dwarf_Small DW_REG_F2CR   = 59; // 2-й регистр управления функцией 
                                      // активации
const Dwarf_Small DW_REG_VR     = 60; // регистр порога

    // остальные 32-битные регистры

const Dwarf_Small DW_REG_PSWRset    = 61; // регистр установки битов PSWR 

const Dwarf_Small DW_REG_VRL        = 62; // регистр порога младшая часть
const Dwarf_Small DW_REG_VRH        = 63; // регистр порога старшая часть

    // число регистров
const Dwarf_Small DW_REG_LAST_NUM   = DW_REG_VRH + 1;

//------------------------------------------------------------------------------
//  Отображение регистров используемое в таблице .debug_frame
//  константы DW_FRAME машинно-зависимы.
//------------------------------------------------------------------------------

const Dwarf_Small DW_FRAME_AR0  = 0;
const Dwarf_Small DW_FRAME_AR1  = 1;
const Dwarf_Small DW_FRAME_AR2  = 2;
const Dwarf_Small DW_FRAME_AR3  = 3;
const Dwarf_Small DW_FRAME_AR4  = 4;
const Dwarf_Small DW_FRAME_AR5  = 5;
const Dwarf_Small DW_FRAME_AR6  = 6;
const Dwarf_Small DW_FRAME_AR7  = 7;

const Dwarf_Small DW_FRAME_SP   = 7;    // синоним для AR7

const Dwarf_Small DW_FRAME_GR0  = 8;
const Dwarf_Small DW_FRAME_GR1  = 9;
const Dwarf_Small DW_FRAME_GR2  = 10;
const Dwarf_Small DW_FRAME_GR3  = 11;
const Dwarf_Small DW_FRAME_GR4  = 12;
const Dwarf_Small DW_FRAME_GR5  = 13;
const Dwarf_Small DW_FRAME_GR6  = 14;
const Dwarf_Small DW_FRAME_GR7  = 15;

const Dwarf_Small DW_FRAME_RA_COL   = 16;   // колонка для адреса возврата
const Dwarf_Small DW_FRAME_CFA_COL  = 17;   // колонка для CFA

//const Dwarf_Small DW_FRAME_STATIC_LINK = 18;    
                // колонка для записи статической связи функции, 
                // указывающей на объемлющую процедуру
				// используется в Паскале и т.п.

// Число колонок в таблице фреймов.
// Задает размер таблицы фреймов в libdwarf.hpp

const Dwarf_Small DW_FRAME_LAST_REG_NUM = (DW_FRAME_CFA_COL + 1);

// Константы DW_FRAME_UNDEFINED_VAL и DW_FRAME_SAME_VAL не могут существовать 
// на диске, генерируются libdwarf. Значения смотри в libdwarf.hpp

//------------------------------------------------------------------------------
//  Отображение регистров используемое в location descriptors
//  константы DW_LOCREG машинно-зависимы.
//------------------------------------------------------------------------------

const Dwarf_Small DW_LOCREG_AR0  = 0;
const Dwarf_Small DW_LOCREG_AR1  = 1;
const Dwarf_Small DW_LOCREG_AR2  = 2;
const Dwarf_Small DW_LOCREG_AR3  = 3;
const Dwarf_Small DW_LOCREG_AR4  = 4;
const Dwarf_Small DW_LOCREG_AR5  = 5;
const Dwarf_Small DW_LOCREG_AR6  = 6;
const Dwarf_Small DW_LOCREG_AR7  = 7;

const Dwarf_Small DW_LOCREG_SP   = 7;    // синоним для AR7

const Dwarf_Small DW_LOCREG_GR0  = 8;
const Dwarf_Small DW_LOCREG_GR1  = 9;
const Dwarf_Small DW_LOCREG_GR2  = 10;
const Dwarf_Small DW_LOCREG_GR3  = 11;
const Dwarf_Small DW_LOCREG_GR4  = 12;
const Dwarf_Small DW_LOCREG_GR5  = 13;
const Dwarf_Small DW_LOCREG_GR6  = 14;
const Dwarf_Small DW_LOCREG_GR7  = 15;

const Dwarf_Small DW_LOCREG_GR0AR0  = 16;
const Dwarf_Small DW_LOCREG_GR1AR1  = 17;
const Dwarf_Small DW_LOCREG_GR2AR2  = 18;
const Dwarf_Small DW_LOCREG_GR3AR3  = 19;
const Dwarf_Small DW_LOCREG_GR4AR4  = 20;
const Dwarf_Small DW_LOCREG_GR5AR5  = 21;
const Dwarf_Small DW_LOCREG_GR6AR6  = 22;
const Dwarf_Small DW_LOCREG_GR7AR7  = 23;

    // число регистров для location descriptors
const Dwarf_Small DW_LOCREG_NUM = DW_LOCREG_GR7AR7 + 1;

//------------------------------------------------------------------------------
//
// конец отображений регистров
//
//------------------------------------------------------------------------------


const Dwarf_Small DW_CHILDREN_no    = 0x00;
const Dwarf_Small DW_CHILDREN_yes   = 0x01;

const Dwarf_Small DW_ADDR_none = 0;

#endif // _DWARF_H
