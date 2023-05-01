// SPDX-FileCopyrightText: none
// SPDX-License-Identifier: CC0-1.0

#pragma once

#include <stdint.h>

const char* pci_get_vendor_name(
	uint16_t vendor_id);

const char* pci_get_device_name(
	uint16_t vendor_id,
	uint16_t device_id);

const char* pci_get_header_type_str(
	uint8_t header_type);

const char* pci_get_class_code_str(
	uint8_t class_code);

const char* pci_get_subclass_str(
	uint8_t class_code,
	uint8_t subclass);

const char* pci_get_prog_if_str(
	uint8_t class_code,
	uint8_t subclass,
	uint8_t prog_if);

const char* pci_get_interrupt_pin_str(
	uint8_t interrupt_pin);