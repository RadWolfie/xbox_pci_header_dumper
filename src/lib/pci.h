// SPDX-FileCopyrightText: none
// SPDX-License-Identifier: CC0-1.0

#pragma once

#include <stdint.h>

#include "pci_database.h"

uint8_t pci_read_config_8(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	uint8_t offset);

uint16_t pci_read_config_16(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	uint8_t offset);

uint32_t pci_read_config_32(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	uint8_t offset);

typedef struct _pci_header_generic {
	uint16_t vendor_id;
	uint16_t device_id;
	uint16_t command;
	uint16_t status;
	uint8_t revision_id;
	uint8_t prog_if;
	uint8_t subclass;
	uint8_t class_code;
	uint8_t cache_line_size;
	uint8_t latency_timer;
	uint8_t header_type;
	uint8_t bist;
} pci_header_base;

typedef struct _pci_header_extended_standard {
	uint32_t BAR0;
	uint32_t BAR1;
	uint32_t BAR2;
	uint32_t BAR3;
	uint32_t BAR4;
	uint32_t BAR5;
	uint32_t cardbus_cis_pointer;
	uint16_t subsystem_vendor_id;
	uint16_t subsystem_id;
	uint32_t expansion_rom_base_address;
	uint8_t capabilities_pointer;
	uint8_t reserved0;
	uint16_t reserved1;
	uint32_t reserved2;
	uint8_t interrupt_line;
	uint8_t interrupt_pin;
	uint8_t min_grant;
	uint8_t max_latency;
} pci_header_extended_standard;

typedef struct _pci_header_extended_pci2pci_bridge {
	uint32_t BAR0;
	uint32_t BAR1;
	uint8_t bus_number_primary;
	uint8_t bus_number_secondary;
	uint8_t bus_number_subordinate;
	uint8_t latency_timer_secondary;
	uint8_t io_base;
	uint8_t io_limit;
	uint16_t status_secondary;
	uint16_t memory_base;
	uint16_t memory_limit;
	uint16_t memory_base_prefetchable;
	uint16_t memory_limit_prefetchable;
	uint32_t upper_32bits_base_prefetchable;
	uint32_t upper_32bits_limit_prefetchable;
	uint16_t upper_16bits_base_io;
	uint16_t upper_16bits_limit_io;
	uint8_t capabilities_pointer;
	uint8_t reserved0;
	uint16_t reserved1;
	uint32_t expansion_rom_base_address;
	uint8_t interrupt_line;
	uint8_t interrupt_pin;
	uint16_t bridge_control;
} pci_header_extended_pci2pci_bridge;

typedef struct _pci_header_extended_pci2cardbus_bridge {
	uint32_t cardbus_socket_exca_base_address;
	uint8_t capabilities_list_offset;
	uint8_t reserved0;
	uint16_t status_secondary;
	uint8_t bus_number_pci;
	uint8_t bus_number_cardbus;
	uint8_t bus_number_subordinate;
	uint8_t latency_timer_cardbus;
	uint32_t memory_base_address_0;
	uint32_t memory_limit_0;
	uint32_t memory_base_address_1;
	uint32_t memory_limit_1;
	uint32_t io_base_address_0;
	uint32_t io_limit_0;
	uint32_t io_base_address_1;
	uint32_t io_limit_1;
	uint8_t interrupt_line;
	uint8_t interrupt_pin;
	uint16_t bridge_control;
	uint16_t subsystem_device_id;
	uint16_t subsystem_vendor_id;
	uint32_t legacy_mode_base_16bit_pc_card;
} pci_header_extended_pci2cardbus_bridge;

void pci_read_base_header(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	pci_header_base* p_header_base);

void pci_read_extended_header_standard(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	pci_header_extended_standard* p_header_ext_std);

void pci_read_extended_header_pci2pci_bridge(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	pci_header_extended_pci2pci_bridge* p_header_ext_pci2pci);

void pci_read_extended_header_pci2cardbus_bridge(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	pci_header_extended_pci2cardbus_bridge* p_header_ext_pci2cardbus);
