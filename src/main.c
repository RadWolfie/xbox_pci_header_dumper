// SPDX-FileCopyrightText: none
// SPDX-License-Identifier: CC0-1.0

#include <pbkit/pbkit.h>
#include <hal/video.h>
#include <hal/xbox.h>
#include <string.h>
#include <windows.h>
#include "output.h"
#include "lib/pci.h"

void pci_dump_header(
	uint8_t bus,
	uint8_t device,
	uint8_t func,
	pci_header_base* pci_header)
{
	if (pci_header->vendor_id == 0xFFFF || pci_header->device_id == 0xFFFF) {
		return;
	}
	print("=======%02hhX.%02hhX:%hhX=======", bus, device, func);
	print("vendor_id      =%04hX %s", pci_header->vendor_id, pci_get_vendor_name(pci_header->vendor_id));
	print("device_id      =%04hX %s", pci_header->device_id, pci_get_device_name(pci_header->vendor_id, pci_header->device_id));
	print("command        =%04hX", pci_header->command);
	print("status         =%04hX", pci_header->status);
	print("revision_id    =%02hhX", pci_header->revision_id);
	print("prog_if        =%02hhX   %s", pci_header->prog_if, pci_get_prog_if_str(pci_header->class_code, pci_header->subclass, pci_header->prog_if));
	print("subclass       =%02hhX   %s", pci_header->subclass, pci_get_subclass_str(pci_header->class_code, pci_header->subclass));
	print("class_code     =%02hhX   %s", pci_header->class_code, pci_get_class_code_str(pci_header->class_code));
	print("cache_line_size=%02hhX", pci_header->cache_line_size);
	print("latency_timer  =%02hhX", pci_header->latency_timer);
	print("header_type    =%02hhX   %s", pci_header->header_type, pci_get_header_type_str(pci_header->header_type));
	print("bist           =%02hhX", pci_header->bist);

	uint8_t header_type = (pci_header->header_type & 0x7F);
	if (header_type == 0x00) {
		pci_header_extended_standard pci_header_standard;
		pci_read_extended_header_standard(bus, device, func, &pci_header_standard);

		print("BAR0                       =%08X", pci_header_standard.BAR0);
		print("BAR1                       =%08X", pci_header_standard.BAR1);
		print("BAR2                       =%08X", pci_header_standard.BAR2);
		print("BAR3                       =%08X", pci_header_standard.BAR3);
		print("BAR4                       =%08X", pci_header_standard.BAR4);
		print("BAR5                       =%08X", pci_header_standard.BAR5);
		print("cardbus_cis_pointer        =%08X", pci_header_standard.cardbus_cis_pointer);
		print("subsystem_vendor_id        =%04hX", pci_header_standard.subsystem_vendor_id);
		print("subsystem_id               =%04hX", pci_header_standard.subsystem_id);
		print("expansion_rom_base_address =%08X", pci_header_standard.expansion_rom_base_address);
		print("capabilities_pointer       =%02hhX", pci_header_standard.capabilities_pointer);
		print("reserved0                  =%02hhX", pci_header_standard.reserved0);
		print("reserved1                  =%04hX", pci_header_standard.reserved1);
		print("reserved2                  =%08X", pci_header_standard.reserved2);
		print("interrupt_line             =%02hhX", pci_header_standard.interrupt_line);
		print("interrupt_pin              =%02hhX", pci_header_standard.interrupt_pin);
		print("min_grant                  =%02hhX", pci_header_standard.min_grant);
		print("max_latency                =%02hhX", pci_header_standard.max_latency);
	}
	else if (header_type == 0x01) {
		pci_header_extended_pci2pci_bridge pci_header_pci2pci_bridge;
		pci_read_extended_header_pci2pci_bridge(bus, device, func, &pci_header_pci2pci_bridge);
		print("BAR0                            = %08X", pci_header_pci2pci_bridge.BAR0);
		print("BAR1                            = %08X", pci_header_pci2pci_bridge.BAR1);
		print("bus_number_primary              = %02hhX", pci_header_pci2pci_bridge.bus_number_primary);
		print("bus_number_secondary            = %02hhX", pci_header_pci2pci_bridge.bus_number_secondary);
		print("bus_number_subordinate          = %02hhX", pci_header_pci2pci_bridge.bus_number_subordinate);
		print("latency_timer_secondary         = %02hhX", pci_header_pci2pci_bridge.latency_timer_secondary);
		print("io_base                         = %02hhX", pci_header_pci2pci_bridge.io_base);
		print("io_limit                        = %02hhX", pci_header_pci2pci_bridge.io_limit);
		print("status_secondary                = %04hX", pci_header_pci2pci_bridge.status_secondary);
		print("memory_base                     = %04hX", pci_header_pci2pci_bridge.memory_base);
		print("memory_limit                    = %04hX", pci_header_pci2pci_bridge.memory_limit);
		print("memory_base_prefetchable        = %04hX", pci_header_pci2pci_bridge.memory_base_prefetchable);
		print("memory_limit_prefetchable       = %04hX", pci_header_pci2pci_bridge.memory_limit_prefetchable);
		print("upper_32bits_base_prefetchable  = %08X", pci_header_pci2pci_bridge.upper_32bits_base_prefetchable);
		print("upper_32bits_limit_prefetchable = %08X", pci_header_pci2pci_bridge.upper_32bits_limit_prefetchable);
		print("upper_16bits_base_io            = %04hX", pci_header_pci2pci_bridge.upper_16bits_base_io);
		print("upper_16bits_limit_io           = %04hX", pci_header_pci2pci_bridge.upper_16bits_limit_io);
		print("capabilities_pointer            = %02hhX", pci_header_pci2pci_bridge.capabilities_pointer);
		print("reserved0                       = %02hhX", pci_header_pci2pci_bridge.reserved0);
		print("reserved1                       = %04hX", pci_header_pci2pci_bridge.reserved1);
		print("expansion_rom_base_address      = %08X", pci_header_pci2pci_bridge.expansion_rom_base_address);
		print("interrupt_line                  = %02hhX", pci_header_pci2pci_bridge.interrupt_line);
		print("interrupt_pin                   = %02hhX", pci_header_pci2pci_bridge.interrupt_pin);
		print("bridge_control                  = %04hX", pci_header_pci2pci_bridge.bridge_control);
	}
	else if (header_type == 0x02) {
		pci_header_extended_pci2cardbus_bridge pci_header_pci2cardbus_bridge;
		pci_read_extended_header_pci2cardbus_bridge(bus, device, func, &pci_header_pci2cardbus_bridge);
		print("cardbus_socket_exca_base_address = %08X", pci_header_pci2cardbus_bridge.cardbus_socket_exca_base_address);
		print("capabilities_list_offset         = %02hhX", pci_header_pci2cardbus_bridge.capabilities_list_offset);
		print("reserved0                        = %02hhX", pci_header_pci2cardbus_bridge.reserved0);
		print("status_secondary                 = %04hX", pci_header_pci2cardbus_bridge.status_secondary);
		print("bus_number_pci                   = %02hhX", pci_header_pci2cardbus_bridge.bus_number_pci);
		print("bus_number_cardbus               = %02hhX", pci_header_pci2cardbus_bridge.bus_number_cardbus);
		print("bus_number_subordinate           = %02hhX", pci_header_pci2cardbus_bridge.bus_number_subordinate);
		print("latency_timer_cardbus            = %02hhX", pci_header_pci2cardbus_bridge.latency_timer_cardbus);
		print("memory_base_address_0            = %08X", pci_header_pci2cardbus_bridge.memory_base_address_0);
		print("memory_limit_0                   = %08X", pci_header_pci2cardbus_bridge.memory_limit_0);
		print("memory_base_address_1            = %08X", pci_header_pci2cardbus_bridge.memory_base_address_1);
		print("memory_limit_1                   = %08X", pci_header_pci2cardbus_bridge.memory_limit_1);
		print("io_base_address_0                = %08X", pci_header_pci2cardbus_bridge.io_base_address_0);
		print("io_limit_0                       = %08X", pci_header_pci2cardbus_bridge.io_limit_0);
		print("io_base_address_1                = %08X", pci_header_pci2cardbus_bridge.io_base_address_1);
		print("io_limit_1                       = %08X", pci_header_pci2cardbus_bridge.io_limit_1);
		print("interrupt_line                   = %02hhX", pci_header_pci2cardbus_bridge.interrupt_line);
		print("interrupt_pin                    = %02hhX", pci_header_pci2cardbus_bridge.interrupt_pin);
		print("bridge_control                   = %04hX", pci_header_pci2cardbus_bridge.bridge_control);
		print("subsystem_device_id              = %04hX", pci_header_pci2cardbus_bridge.subsystem_device_id);
		print("subsystem_vendor_id              = %04hX", pci_header_pci2cardbus_bridge.subsystem_vendor_id);
		print("legacy_mode_base_16bit_pc_card   = %08X", pci_header_pci2cardbus_bridge.legacy_mode_base_16bit_pc_card);
	}

	print("---------HEX DUMP---------");
	uint32_t pci_get;
	uint8_t offset = 0;
	do {
		pci_get = pci_read_config_32(bus, device, func, offset);
		print("%02hhX.%02hhX:%hhX.%02hhX=%08X", bus, device, func, offset, pci_get);
		offset += 4;
	} while (offset != 0);
	print("==========================\n");
}

void pci_dump_list()
{
	pci_header_base pci_header;
	uint8_t bus = 0;
	do {
		for (uint8_t device = 0; device < 32; device++) {
			pci_read_base_header(bus, device, 0, &pci_header);
			if (pci_header.vendor_id == 0xFFFF || pci_header.device_id == 0xFFFF) {
				// skip invalid pci device
				continue;
			}
			pci_dump_header(bus, device, 0, &pci_header);
			if (pci_header.header_type & 0x80) {
				// multi-function found, go through loops then.
				for (int8_t func = 1; func < 8; func++) {
					if (bus == 0 && device == 0) {
						// NOTE: Skip both functions as they will freeze console due to DRAM controllers aren't complete.
						if (func == 1 || func == 2) {
							continue;
						}
					}
					pci_read_base_header(bus, device, func, &pci_header);
					if (pci_header.vendor_id == 0xFFFF || pci_header.device_id == 0xFFFF) {
						// skip invalid pci device
						continue;
					}
					pci_dump_header(bus, device, func, &pci_header);
				}
			}
			// NOTE: Skip duplicate device for each device... wtf? Only list it once, period.
			if (pci_header.device_id == 0x02A0 && pci_header.vendor_id == 0x10DE) {
				break;
			}
		}
		bus++;
	} while (bus != 0);
}

void main(
	void)
{
	XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);

	switch (pb_init()) {
		case 0:
			break;
		default:
			Sleep(2000);
			XReboot();
			return;
	}

	pb_show_debug_screen();

	open_output_file("D:\\xbox_pci_header_dumper.log");

	pci_dump_list();

	close_output_file();

	Sleep(10000);
	pb_kill();
	XReboot();
}
