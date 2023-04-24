// SPDX-FileCopyrightText: none
// SPDX-License-Identifier: CC0-1.0

#include "pci.h"

static inline void outl(uint16_t port, uint32_t val)
{
	__asm__ __volatile__("outl %0, %w1"
	                     :
	                     : "a"(val), "Nd"(port));
}

static inline uint32_t inl(uint16_t port)
{
	uint32_t ret;
	__asm__ __volatile__("inl %w1, %0"
	                     : "=a"(ret)
	                     : "Nd"(port));
	return ret;
}

#define PCI_CONFIG_ADDR 0x0cf8
#define PCI_CONFIG_DATA 0x0cfc

uint8_t pci_read_config_8(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	uint8_t offset)
{
	outl(PCI_CONFIG_ADDR,
	     0x80000000 | bus << 16 | device << 11 | function << 8 | (offset & 0xFC));
	return (inl(PCI_CONFIG_DATA) >> ((offset & 3) * 8) & 0xFF);
}

uint16_t pci_read_config_16(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	uint8_t offset)
{
	outl(PCI_CONFIG_ADDR,
	     0x80000000 | bus << 16 | device << 11 | function << 8 | (offset & 0xFC));
	return (inl(PCI_CONFIG_DATA) >> ((offset & 2) * 8) & 0xFFFF);
}

uint32_t pci_read_config_32(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	uint8_t offset)
{
	outl(PCI_CONFIG_ADDR,
	     0x80000000 | bus << 16 | device << 11 | function << 8 | (offset & 0xFC));
	return inl(PCI_CONFIG_DATA);
}

void pci_read_base_header(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	pci_header_base* p_header_base)
{
	p_header_base->vendor_id = pci_read_config_16(bus, device, function, 0x00);
	p_header_base->device_id = pci_read_config_16(bus, device, function, 0x02);
	if (p_header_base->vendor_id != 0xFFFF && p_header_base->device_id != 0xFFFF) {
		p_header_base->command = pci_read_config_16(bus, device, function, 0x04);
		p_header_base->status = pci_read_config_16(bus, device, function, 0x06);
		p_header_base->revision_id = pci_read_config_8(bus, device, function, 0x08);
		p_header_base->prog_if = pci_read_config_8(bus, device, function, 0x09);
		p_header_base->subclass = pci_read_config_8(bus, device, function, 0x0A);
		p_header_base->class_code = pci_read_config_8(bus, device, function, 0x0B);
		p_header_base->cache_line_size = pci_read_config_8(bus, device, function, 0x0C);
		p_header_base->latency_timer = pci_read_config_8(bus, device, function, 0x0D);
		p_header_base->header_type = pci_read_config_8(bus, device, function, 0x0E);
		p_header_base->bist = pci_read_config_8(bus, device, function, 0x0F);
	}
}

void pci_read_extended_header_standard(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	pci_header_extended_standard* p_header_ext_std)
{
	p_header_ext_std->BAR0 = pci_read_config_32(bus, device, function, 0x10);
	p_header_ext_std->BAR1 = pci_read_config_32(bus, device, function, 0x14);
	p_header_ext_std->BAR2 = pci_read_config_32(bus, device, function, 0x18);
	p_header_ext_std->BAR3 = pci_read_config_32(bus, device, function, 0x1C);
	p_header_ext_std->BAR4 = pci_read_config_32(bus, device, function, 0x20);
	p_header_ext_std->BAR5 = pci_read_config_32(bus, device, function, 0x24);
	p_header_ext_std->cardbus_cis_pointer = pci_read_config_32(bus, device, function, 0x28);
	p_header_ext_std->subsystem_vendor_id = pci_read_config_16(bus, device, function, 0x2C);
	p_header_ext_std->subsystem_id = pci_read_config_16(bus, device, function, 0x2E);
	p_header_ext_std->expansion_rom_base_address = pci_read_config_32(bus, device, function, 0x30);
	p_header_ext_std->capabilities_pointer = pci_read_config_8(bus, device, function, 0x34);
	p_header_ext_std->reserved0 = pci_read_config_8(bus, device, function, 0x35);
	p_header_ext_std->reserved1 = pci_read_config_16(bus, device, function, 0x36);
	p_header_ext_std->reserved2 = pci_read_config_32(bus, device, function, 0x38);
	p_header_ext_std->interrupt_line = pci_read_config_8(bus, device, function, 0x3C);
	p_header_ext_std->interrupt_pin = pci_read_config_8(bus, device, function, 0x3D);
	p_header_ext_std->min_grant = pci_read_config_8(bus, device, function, 0x3E);
	p_header_ext_std->max_latency = pci_read_config_8(bus, device, function, 0x3F);
}

void pci_read_extended_header_pci2pci_bridge(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	pci_header_extended_pci2pci_bridge* p_header_ext_pci2pci)
{
	p_header_ext_pci2pci->BAR0 = pci_read_config_32(bus, device, function, 0x10);
	p_header_ext_pci2pci->BAR1 = pci_read_config_32(bus, device, function, 0x14);
	p_header_ext_pci2pci->bus_number_primary = pci_read_config_8(bus, device, function, 0x18);
	p_header_ext_pci2pci->bus_number_secondary = pci_read_config_8(bus, device, function, 0x19);
	p_header_ext_pci2pci->bus_number_subordinate = pci_read_config_8(bus, device, function, 0x1A);
	p_header_ext_pci2pci->latency_timer_secondary = pci_read_config_8(bus, device, function, 0x1B);
	p_header_ext_pci2pci->io_base = pci_read_config_8(bus, device, function, 0x1C);
	p_header_ext_pci2pci->io_limit = pci_read_config_8(bus, device, function, 0x1D);
	p_header_ext_pci2pci->status_secondary = pci_read_config_16(bus, device, function, 0x1E);
	p_header_ext_pci2pci->memory_base = pci_read_config_16(bus, device, function, 0x20);
	p_header_ext_pci2pci->memory_limit = pci_read_config_16(bus, device, function, 0x22);
	p_header_ext_pci2pci->memory_base_prefetchable = pci_read_config_16(bus, device, function, 0x24);
	p_header_ext_pci2pci->memory_limit_prefetchable = pci_read_config_16(bus, device, function, 0x26);
	p_header_ext_pci2pci->upper_32bits_base_prefetchable = pci_read_config_32(bus, device, function, 0x28);
	p_header_ext_pci2pci->upper_32bits_limit_prefetchable = pci_read_config_32(bus, device, function, 0x2C);
	p_header_ext_pci2pci->upper_16bits_base_io = pci_read_config_16(bus, device, function, 0x30);
	p_header_ext_pci2pci->upper_16bits_limit_io = pci_read_config_16(bus, device, function, 0x32);
	p_header_ext_pci2pci->capabilities_pointer = pci_read_config_8(bus, device, function, 0x34);
	p_header_ext_pci2pci->reserved0 = pci_read_config_8(bus, device, function, 0x35);
	p_header_ext_pci2pci->reserved1 = pci_read_config_16(bus, device, function, 0x36);
	p_header_ext_pci2pci->expansion_rom_base_address = pci_read_config_32(bus, device, function, 0x38);
	p_header_ext_pci2pci->interrupt_line = pci_read_config_8(bus, device, function, 0x3C);
	p_header_ext_pci2pci->interrupt_pin = pci_read_config_8(bus, device, function, 0x3D);
	p_header_ext_pci2pci->bridge_control = pci_read_config_16(bus, device, function, 0x3E);
}

void pci_read_extended_header_pci2cardbus_bridge(
	uint8_t bus,
	uint8_t device,
	uint8_t function,
	pci_header_extended_pci2cardbus_bridge* p_header_ext_pci2cardbus)
{
	p_header_ext_pci2cardbus->cardbus_socket_exca_base_address = pci_read_config_32(bus, device, function, 0x10);
	p_header_ext_pci2cardbus->capabilities_list_offset = pci_read_config_8(bus, device, function, 0x14);
	p_header_ext_pci2cardbus->reserved0 = pci_read_config_8(bus, device, function, 0x15);
	p_header_ext_pci2cardbus->status_secondary = pci_read_config_16(bus, device, function, 0x16);
	p_header_ext_pci2cardbus->bus_number_pci = pci_read_config_8(bus, device, function, 0x18);
	p_header_ext_pci2cardbus->bus_number_cardbus = pci_read_config_8(bus, device, function, 0x19);
	p_header_ext_pci2cardbus->bus_number_subordinate = pci_read_config_8(bus, device, function, 0x1A);
	p_header_ext_pci2cardbus->latency_timer_cardbus = pci_read_config_8(bus, device, function, 0x1B);
	p_header_ext_pci2cardbus->memory_base_address_0 = pci_read_config_32(bus, device, function, 0x1C);
	p_header_ext_pci2cardbus->memory_limit_0 = pci_read_config_32(bus, device, function, 0x20);
	p_header_ext_pci2cardbus->memory_base_address_1 = pci_read_config_32(bus, device, function, 0x24);
	p_header_ext_pci2cardbus->memory_limit_1 = pci_read_config_32(bus, device, function, 0x28);
	p_header_ext_pci2cardbus->io_base_address_0 = pci_read_config_32(bus, device, function, 0x2C);
	p_header_ext_pci2cardbus->io_limit_0 = pci_read_config_32(bus, device, function, 0x30);
	p_header_ext_pci2cardbus->io_base_address_1 = pci_read_config_32(bus, device, function, 0x34);
	p_header_ext_pci2cardbus->io_limit_1 = pci_read_config_32(bus, device, function, 0x38);
	p_header_ext_pci2cardbus->interrupt_line = pci_read_config_8(bus, device, function, 0x3C);
	p_header_ext_pci2cardbus->interrupt_pin = pci_read_config_8(bus, device, function, 0x3D);
	p_header_ext_pci2cardbus->bridge_control = pci_read_config_16(bus, device, function, 0x3E);
	p_header_ext_pci2cardbus->subsystem_device_id = pci_read_config_16(bus, device, function, 0x40);
	p_header_ext_pci2cardbus->subsystem_vendor_id = pci_read_config_16(bus, device, function, 0x42);
	p_header_ext_pci2cardbus->legacy_mode_base_16bit_pc_card = pci_read_config_32(bus, device, function, 0x44);
}
