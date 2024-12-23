// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

`include "spi_device_base_vseq.sv"
`include "spi_device_common_vseq.sv"
`include "spi_device_csb_read_vseq.sv"
`include "spi_device_mem_parity_vseq.sv"
`include "spi_device_ram_cfg_vseq.sv"
`include "spi_device_tpm_base_vseq.sv"
`include "spi_device_tpm_read_hw_reg_vseq.sv"
`include "spi_device_tpm_all_vseq.sv"
`include "spi_device_tpm_sts_read_vseq.sv"
`include "spi_device_tpm_rw_vseq.sv"
`include "spi_device_pass_base_vseq.sv"
`include "spi_device_pass_cmd_filtering_vseq.sv"
`include "spi_device_pass_addr_payload_swap_vseq.sv"
`include "spi_device_intercept_vseq.sv"
`include "spi_device_mailbox_vseq.sv"
`include "spi_device_upload_vseq.sv"
`include "spi_device_cfg_cmd_vseq.sv"
`include "spi_device_flash_mode_vseq.sv"
`include "spi_device_read_buffer_direct_vseq.sv"
`include "spi_device_flash_all_vseq.sv"
`include "spi_device_flash_mode_ignore_cmds_vseq.sv"
`include "spi_device_flash_and_tpm_vseq.sv"
`include "spi_device_flash_and_tpm_min_idle_vseq.sv"
`include "spi_device_stress_all_vseq.sv"
