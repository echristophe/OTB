/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.
  
  Some parts of this code are derived from ITK. See ITKCopyright.txt
  for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otb_openjpeg_mangle_h
#define otb_openjpeg_mangle_h

/*


This header file mangles all symbols exported from the openjpeg library.
It is included in all files while building the openjpeg library.  Due to
namespace pollution, no openjpeg headers should be included in .h files in
OTB.

The following commands were used to obtain the symbol list:

nm libotbopenjpeg.a |grep " T "
nm libotbopenjpeg.a |grep " D "
nm libotbopenjpeg.a |grep " R "

*/

#define tcd_code_block_dec_deallocate otb_openjpeg_tcd_code_block_dec_deallocate
#define tcd_copy_tile_data otb_openjpeg_tcd_copy_tile_data
#define tcd_create otb_openjpeg_tcd_create
#define tcd_dc_level_shift_decode otb_openjpeg_tcd_dc_level_shift_decode
#define tcd_dc_level_shift_encode otb_openjpeg_tcd_dc_level_shift_encode
#define tcd_decode_tile otb_openjpeg_tcd_decode_tile
#define tcd_destroy otb_openjpeg_tcd_destroy
#define tcd_dwt_decode otb_openjpeg_tcd_dwt_decode
#define tcd_dwt_encode otb_openjpeg_tcd_dwt_encode
#define tcd_encode_tile otb_openjpeg_tcd_encode_tile
#define tcd_get_decoded_tile_size otb_openjpeg_tcd_get_decoded_tile_size
#define tcd_get_encoded_tile_size otb_openjpeg_tcd_get_encoded_tile_size
#define tcd_init otb_openjpeg_tcd_init
#define tcd_init_decode_tile otb_openjpeg_tcd_init_decode_tile
#define tcd_init_encode_tile otb_openjpeg_tcd_init_encode_tile
#define tcd_makelayer otb_openjpeg_tcd_makelayer
#define tcd_makelayer_fixed otb_openjpeg_tcd_makelayer_fixed
#define tcd_mct_decode otb_openjpeg_tcd_mct_decode
#define tcd_mct_encode otb_openjpeg_tcd_mct_encode
#define tcd_rateallocate otb_openjpeg_tcd_rateallocate
#define tcd_rate_allocate_encode otb_openjpeg_tcd_rate_allocate_encode
#define tcd_rateallocate_fixed otb_openjpeg_tcd_rateallocate_fixed
#define tcd_t1_decode otb_openjpeg_tcd_t1_decode
#define tcd_t1_encode otb_openjpeg_tcd_t1_encode
#define tcd_t2_decode otb_openjpeg_tcd_t2_decode
#define tcd_t2_encode otb_openjpeg_tcd_t2_encode
#define tcd_update_tile_data otb_openjpeg_tcd_update_tile_data
#define bio_create otb_openjpeg_bio_create
#define bio_destroy otb_openjpeg_bio_destroy
#define bio_flush otb_openjpeg_bio_flush
#define bio_inalign otb_openjpeg_bio_inalign
#define bio_init_dec otb_openjpeg_bio_init_dec
#define bio_init_enc otb_openjpeg_bio_init_enc
#define bio_numbytes otb_openjpeg_bio_numbytes
#define bio_read otb_openjpeg_bio_read
#define bio_write otb_openjpeg_bio_write
#define opj_read_bytes_BE otb_openjpeg_opj_read_bytes_BE
#define opj_read_bytes_LE otb_openjpeg_opj_read_bytes_LE
#define opj_read_double_BE otb_openjpeg_opj_read_double_BE
#define opj_read_double_LE otb_openjpeg_opj_read_double_LE
#define opj_read_float_BE otb_openjpeg_opj_read_float_BE
#define opj_read_float_LE otb_openjpeg_opj_read_float_LE
#define opj_stream_create otb_openjpeg_opj_stream_create
#define opj_stream_default_create otb_openjpeg_opj_stream_default_create
#define opj_stream_default_read otb_openjpeg_opj_stream_default_read
#define opj_stream_default_seek otb_openjpeg_opj_stream_default_seek
#define opj_stream_default_skip otb_openjpeg_opj_stream_default_skip
#define opj_stream_default_write otb_openjpeg_opj_stream_default_write
#define opj_stream_destroy otb_openjpeg_opj_stream_destroy
#define opj_stream_flush otb_openjpeg_opj_stream_flush
#define opj_stream_has_seek otb_openjpeg_opj_stream_has_seek
#define opj_stream_read_data otb_openjpeg_opj_stream_read_data
#define opj_stream_read_seek otb_openjpeg_opj_stream_read_seek
#define opj_stream_read_skip otb_openjpeg_opj_stream_read_skip
#define opj_stream_seek otb_openjpeg_opj_stream_seek
#define opj_stream_set_read_function otb_openjpeg_opj_stream_set_read_function
#define opj_stream_set_seek_function otb_openjpeg_opj_stream_set_seek_function
#define opj_stream_set_skip_function otb_openjpeg_opj_stream_set_skip_function
#define opj_stream_set_user_data otb_openjpeg_opj_stream_set_user_data
#define opj_stream_set_write_function otb_openjpeg_opj_stream_set_write_function
#define opj_stream_skip otb_openjpeg_opj_stream_skip
#define opj_stream_tell otb_openjpeg_opj_stream_tell
#define opj_stream_write_data otb_openjpeg_opj_stream_write_data
#define opj_stream_write_seek otb_openjpeg_opj_stream_write_seek
#define opj_stream_write_skip otb_openjpeg_opj_stream_write_skip
#define opj_write_bytes_BE otb_openjpeg_opj_write_bytes_BE
#define opj_write_bytes_LE otb_openjpeg_opj_write_bytes_LE
#define opj_write_double_BE otb_openjpeg_opj_write_double_BE
#define opj_write_double_LE otb_openjpeg_opj_write_double_LE
#define opj_write_float_BE otb_openjpeg_opj_write_float_BE
#define opj_write_float_LE otb_openjpeg_opj_write_float_LE
#define dwt_calc_explicit_stepsizes otb_openjpeg_dwt_calc_explicit_stepsizes
#define dwt_decode otb_openjpeg_dwt_decode
#define dwt_decode_real otb_openjpeg_dwt_decode_real
#define dwt_encode otb_openjpeg_dwt_encode
#define dwt_encode_real otb_openjpeg_dwt_encode_real
#define dwt_getgain otb_openjpeg_dwt_getgain
#define dwt_getgain_real otb_openjpeg_dwt_getgain_real
#define dwt_getnorm otb_openjpeg_dwt_getnorm
#define dwt_getnorm_real otb_openjpeg_dwt_getnorm_real
#define opj_event_msg otb_openjpeg_opj_event_msg
#define opj_image_comp_update otb_openjpeg_opj_image_comp_update
#define opj_image_create otb_openjpeg_opj_image_create
#define opj_image_create0 otb_openjpeg_opj_image_create0
#define opj_image_destroy otb_openjpeg_opj_image_destroy
#define opj_image_tile_create otb_openjpeg_opj_image_tile_create
#define get_default_stride otb_openjpeg_get_default_stride
#define get_tp_stride otb_openjpeg_get_tp_stride
#define j2k_build_decoder otb_openjpeg_j2k_build_decoder
#define j2k_build_encoder otb_openjpeg_j2k_build_encoder
#define j2k_convert_progression_order otb_openjpeg_j2k_convert_progression_order
#define j2k_copy_default_tcp_and_create_tcd otb_openjpeg_j2k_copy_default_tcp_and_create_tcd
#define j2k_create_compress otb_openjpeg_j2k_create_compress
#define j2k_create_decompress otb_openjpeg_j2k_create_decompress
#define j2k_decode otb_openjpeg_j2k_decode
#define j2k_decode_tile otb_openjpeg_j2k_decode_tile
#define j2k_decode_tiles otb_openjpeg_j2k_decode_tiles
#define j2k_decoding_validation otb_openjpeg_j2k_decoding_validation
#define j2k_destroy otb_openjpeg_j2k_destroy
#define j2k_destroy_header_memory otb_openjpeg_j2k_destroy_header_memory
#define j2k_encode otb_openjpeg_j2k_encode
#define j2k_encoding_validation otb_openjpeg_j2k_encoding_validation
#define j2k_end_compress otb_openjpeg_j2k_end_compress
#define j2k_end_decompress otb_openjpeg_j2k_end_decompress
#define j2k_mct_validation otb_openjpeg_j2k_mct_validation
#define j2k_read_header otb_openjpeg_j2k_read_header
#define j2k_read_header_procedure otb_openjpeg_j2k_read_header_procedure
#define j2k_read_tile_header otb_openjpeg_j2k_read_tile_header
#define j2k_set_decode_area otb_openjpeg_j2k_set_decode_area
#define j2k_setup_decoder otb_openjpeg_j2k_setup_decoder
#define j2k_setup_decoding otb_openjpeg_j2k_setup_decoding
#define j2k_setup_encoder otb_openjpeg_j2k_setup_encoder
#define j2k_setup_header_reading otb_openjpeg_j2k_setup_header_reading
#define j2k_setup_header_writting otb_openjpeg_j2k_setup_header_writting
#define j2k_setup_mct_encoding otb_openjpeg_j2k_setup_mct_encoding
#define j2k_start_compress otb_openjpeg_j2k_start_compress
#define j2k_write_tile otb_openjpeg_j2k_write_tile
#define opj_clock otb_openjpeg_opj_clock
#define jp2_create otb_openjpeg_jp2_create
#define jp2_decode otb_openjpeg_jp2_decode
#define jp2_decode_tile otb_openjpeg_jp2_decode_tile
#define jp2_default_validation otb_openjpeg_jp2_default_validation
#define jp2_destroy otb_openjpeg_jp2_destroy
#define jp2_encode otb_openjpeg_jp2_encode
#define jp2_end_compress otb_openjpeg_jp2_end_compress
#define jp2_end_decompress otb_openjpeg_jp2_end_decompress
#define jp2_read_header otb_openjpeg_jp2_read_header
#define jp2_read_header_procedure otb_openjpeg_jp2_read_header_procedure
#define jp2_read_jp2h otb_openjpeg_jp2_read_jp2h
#define jp2_read_tile_header otb_openjpeg_jp2_read_tile_header
#define jp2_set_decode_area otb_openjpeg_jp2_set_decode_area
#define jp2_setup_decoder otb_openjpeg_jp2_setup_decoder
#define jp2_setup_encoder otb_openjpeg_jp2_setup_encoder
#define jp2_skip_jp2c otb_openjpeg_jp2_skip_jp2c
#define jp2_start_compress otb_openjpeg_jp2_start_compress
#define jp2_write_jp2h otb_openjpeg_jp2_write_jp2h
#define jp2_write_tile otb_openjpeg_jp2_write_tile
#define jpt_init_msg_header otb_openjpeg_jpt_init_msg_header
#define jpt_read_msg_header otb_openjpeg_jpt_read_msg_header
#define jpt_read_VBAS_info otb_openjpeg_jpt_read_VBAS_info
#define jpt_reinit_msg_header otb_openjpeg_jpt_reinit_msg_header
#define get_mct_norms otb_openjpeg_get_mct_norms
#define get_mct_norms_real otb_openjpeg_get_mct_norms_real
#define mct_decode otb_openjpeg_mct_decode
#define mct_decode_custom otb_openjpeg_mct_decode_custom
#define mct_decode_real otb_openjpeg_mct_decode_real
#define mct_encode otb_openjpeg_mct_encode
#define mct_encode_custom otb_openjpeg_mct_encode_custom
#define mct_encode_real otb_openjpeg_mct_encode_real
#define mct_getnorm otb_openjpeg_mct_getnorm
#define mct_getnorm_real otb_openjpeg_mct_getnorm_real
#define opj_calculate_norms otb_openjpeg_opj_calculate_norms
#define mqc_bypass_enc otb_openjpeg_mqc_bypass_enc
#define mqc_bypass_flush_enc otb_openjpeg_mqc_bypass_flush_enc
#define mqc_bypass_init_enc otb_openjpeg_mqc_bypass_init_enc
#define mqc_create otb_openjpeg_mqc_create
#define mqc_decode otb_openjpeg_mqc_decode
#define mqc_destroy otb_openjpeg_mqc_destroy
#define mqc_encode otb_openjpeg_mqc_encode
#define mqc_erterm_enc otb_openjpeg_mqc_erterm_enc
#define mqc_flush otb_openjpeg_mqc_flush
#define mqc_init_dec otb_openjpeg_mqc_init_dec
#define mqc_init_enc otb_openjpeg_mqc_init_enc
#define mqc_numbytes otb_openjpeg_mqc_numbytes
#define mqc_reset_enc otb_openjpeg_mqc_reset_enc
#define mqc_resetstates otb_openjpeg_mqc_resetstates
#define mqc_restart_enc otb_openjpeg_mqc_restart_enc
#define mqc_restart_init_enc otb_openjpeg_mqc_restart_init_enc
#define mqc_segmark_enc otb_openjpeg_mqc_segmark_enc
#define mqc_setstate otb_openjpeg_mqc_setstate
#define opj_create_compress otb_openjpeg_opj_create_compress
#define opj_create_decompress otb_openjpeg_opj_create_decompress
#define opj_decode otb_openjpeg_opj_decode
#define opj_decode_tile_data otb_openjpeg_opj_decode_tile_data
#define opj_default_callback otb_openjpeg_opj_default_callback
#define opj_destroy_codec otb_openjpeg_opj_destroy_codec
#define opj_destroy_cstr_info otb_openjpeg_opj_destroy_cstr_info
#define opj_encode otb_openjpeg_opj_encode
#define opj_end_compress otb_openjpeg_opj_end_compress
#define opj_end_decompress otb_openjpeg_opj_end_decompress
#define opj_read_from_file otb_openjpeg_opj_read_from_file
#define opj_read_header otb_openjpeg_opj_read_header
#define opj_read_tile_header otb_openjpeg_opj_read_tile_header
#define opj_restrict_decoding otb_openjpeg_opj_restrict_decoding
#define opj_seek_from_file otb_openjpeg_opj_seek_from_file
#define opj_set_decode_area otb_openjpeg_opj_set_decode_area
#define opj_set_default_decoder_parameters otb_openjpeg_opj_set_default_decoder_parameters
#define opj_set_default_encoder_parameters otb_openjpeg_opj_set_default_encoder_parameters
#define opj_set_error_handler otb_openjpeg_opj_set_error_handler
#define opj_set_info_handler otb_openjpeg_opj_set_info_handler
#define opj_set_MCT otb_openjpeg_opj_set_MCT
#define opj_set_stdout_handler otb_openjpeg_opj_set_stdout_handler
#define opj_setup_decoder otb_openjpeg_opj_setup_decoder
#define opj_setup_encoder otb_openjpeg_opj_setup_encoder
#define opj_set_warning_handler otb_openjpeg_opj_set_warning_handler
#define opj_skip_from_file otb_openjpeg_opj_skip_from_file
#define opj_start_compress otb_openjpeg_opj_start_compress
#define opj_stdio_callback otb_openjpeg_opj_stdio_callback
#define opj_stream_create_default_file_stream otb_openjpeg_opj_stream_create_default_file_stream
#define opj_stream_create_file_stream otb_openjpeg_opj_stream_create_file_stream
#define opj_version otb_openjpeg_opj_version
#define opj_write_from_file otb_openjpeg_opj_write_from_file
#define opj_write_tile otb_openjpeg_opj_write_tile
#define set_default_event_handler otb_openjpeg_set_default_event_handler
#define get_all_encoding_parameters otb_openjpeg_get_all_encoding_parameters
#define get_encoding_parameters otb_openjpeg_get_encoding_parameters
#define pi_check_next_level otb_openjpeg_pi_check_next_level
#define pi_create otb_openjpeg_pi_create
#define pi_create_decode otb_openjpeg_pi_create_decode
#define pi_create_encode otb_openjpeg_pi_create_encode
#define pi_destroy otb_openjpeg_pi_destroy
#define pi_initialise_encode otb_openjpeg_pi_initialise_encode
#define pi_next otb_openjpeg_pi_next
#define pi_update_decode_not_poc otb_openjpeg_pi_update_decode_not_poc
#define pi_update_decode_poc otb_openjpeg_pi_update_decode_poc
#define pi_update_encode_not_poc otb_openjpeg_pi_update_encode_not_poc
#define pi_update_encode_poc_and_final otb_openjpeg_pi_update_encode_poc_and_final
#define pi_update_encoding_parameters otb_openjpeg_pi_update_encoding_parameters
#define raw_create otb_openjpeg_raw_create
#define raw_decode otb_openjpeg_raw_decode
#define raw_destroy otb_openjpeg_raw_destroy
#define raw_init_dec otb_openjpeg_raw_init_dec
#define raw_numbytes otb_openjpeg_raw_numbytes
#define t1_create otb_openjpeg_t1_create
#define t1_decode_cblks otb_openjpeg_t1_decode_cblks
#define t1_destroy otb_openjpeg_t1_destroy
#define t1_encode_cblks otb_openjpeg_t1_encode_cblks
#define tgt_create otb_openjpeg_tgt_create
#define tgt_decode otb_openjpeg_tgt_decode
#define tgt_destroy otb_openjpeg_tgt_destroy
#define tgt_encode otb_openjpeg_tgt_encode
#define tgt_init otb_openjpeg_tgt_init
#define tgt_reset otb_openjpeg_tgt_reset
#define tgt_setvalue otb_openjpeg_tgt_setvalue
#define _ProfInit otb_openjpeg__ProfInit
#define _ProfPrint otb_openjpeg__ProfPrint
#define _ProfSave otb_openjpeg__ProfSave
#define _ProfStart otb_openjpeg__ProfStart
#define _ProfStop otb_openjpeg__ProfStop
#define opj_lupDecompose otb_openjpeg_opj_lupDecompose
#define opj_lupInvert otb_openjpeg_opj_lupInvert
#define opj_lupSolve otb_openjpeg_opj_lupSolve
#define opj_matrix_inversion_f otb_openjpeg_opj_matrix_inversion_f
#define opj_procedure_list_add_procedure otb_openjpeg_opj_procedure_list_add_procedure
#define opj_procedure_list_clear otb_openjpeg_opj_procedure_list_clear
#define opj_procedure_list_create otb_openjpeg_opj_procedure_list_create
#define opj_procedure_list_destroy otb_openjpeg_opj_procedure_list_destroy
#define opj_procedure_list_get_first_procedure otb_openjpeg_opj_procedure_list_get_first_procedure
#define opj_procedure_list_get_nb_procedures otb_openjpeg_opj_procedure_list_get_nb_procedures
#define t2_create otb_openjpeg_t2_create
#define t2_decode_packets otb_openjpeg_t2_decode_packets
#define t2_destroy otb_openjpeg_t2_destroy
#define t2_encode_packets otb_openjpeg_t2_encode_packets
#define j2k_mct_read_functions_to_float otb_openjpeg_j2k_mct_read_functions_to_float
#define j2k_mct_read_functions_to_int32 otb_openjpeg_j2k_mct_read_functions_to_int32
#define j2k_mct_write_functions_from_float otb_openjpeg_j2k_mct_write_functions_from_float
#define j2k_memory_marker_handler_tab otb_openjpeg_j2k_memory_marker_handler_tab
#define j2k_prog_order_list otb_openjpeg_j2k_prog_order_list
#define MCT_ELEMENT_SIZE otb_openjpeg_MCT_ELEMENT_SIZE
#define jp2_header otb_openjpeg_jp2_header
#define jp2_img_header otb_openjpeg_jp2_img_header

#endif