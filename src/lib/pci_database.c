// SPDX-FileCopyrightText: none
// SPDX-License-Identifier: CC0-1.0

#include "pci_database.h"

#define unknown "unknown"

// List of vendor and devices' can be found at:
// * https://pci-ids.ucw.cz/read/PC/10de (NVIDIA Corporation vendor and its devices list)

#define VENDOR_NVIDIA_CORP 0x10DE
#define DEVICE_NFORCE_APU 0x01B0
#define DEVICE_NFORCE_AC97_AUDIO 0x01B1
#define DEVICE_NFORCE_ISA_BRIDGE 0x01B2
#define DEVICE_NFORCE_PCI_SYSTEM_MANAGEMENT 0x01B4
#define DEVICE_NFORCE_AGP2PCI_BRIDGE 0x01B7
#define DEVICE_NFORCE_PCI2PCI_BRIDGE 0x01B8
#define DEVICE_NFORCE_IDE 0x01BC
#define DEVICE_NFORCE_AC97_MODEM 0x01C1
#define DEVICE_NFORCE_USB 0x01C2
#define DEVICE_NFORCE_ETHERNET 0x01C3
#define DEVICE_NV2A_XGPU 0x02A0
#define DEVICE_MCPX_CPU_BRIDGE 0x02A5
#define DEVICE_MCPX_MEMORY 0x02A6

const char* pci_get_vendor_name(
	uint16_t vendor_id)
{
	switch (vendor_id) {
		case VENDOR_NVIDIA_CORP:
			return "NVIDIA Corporation";
	}
	return unknown;
}


const char* pci_get_device_name(
	uint16_t vendor_id,
	uint16_t device_id)
{
	switch (vendor_id) {
		case VENDOR_NVIDIA_CORP:
			switch (device_id) {
				case DEVICE_NFORCE_APU:
					return "nForce Audio Processing Unit";
				case DEVICE_NFORCE_AC97_AUDIO:
					return "nForce AC'97 Audio Controller";
				case DEVICE_NFORCE_ISA_BRIDGE:
					return "nForce ISA Bridge";
				case DEVICE_NFORCE_PCI_SYSTEM_MANAGEMENT:
					return "nForce PCI System Management";
				case DEVICE_NFORCE_AGP2PCI_BRIDGE:
					return "nForce AGP to PCI Bridge";
				case DEVICE_NFORCE_PCI2PCI_BRIDGE:
					return "nForce PCI-to-PCI bridge";
				case DEVICE_NFORCE_IDE:
					return "nForce IDE";
				case DEVICE_NFORCE_AC97_MODEM:
					return "nForce AC'97 Modem Controller";
				case DEVICE_NFORCE_USB:
					return "nForce USB Controller";
				case DEVICE_NFORCE_ETHERNET:
					return "nForce Ethernet Controller";
				case DEVICE_NV2A_XGPU:
					return "NV2A [XGPU]";
				case DEVICE_MCPX_CPU_BRIDGE:
					return "MCPX CPU Bridge";
				case DEVICE_MCPX_MEMORY:
					return "MCPX Memory Controller";
			}
			break;
	}
	return unknown;
}

#define multifunction_header "Multi-Function"
#define unknown_header "Unknown Header"
#define standard_header "Standard Header"
#define pci2pci_bridge "PCI-to-PCI Bridge"
#define cardbus_bridge "CardBus Bridge"
const char* pci_get_header_type_str(
	uint8_t header_type)
{
	if (header_type & 0x80) {
		switch (header_type & 0x7F) {
			case 0x00:
				return standard_header " " multifunction_header;
			case 0x01:
				return pci2pci_bridge " " multifunction_header;
			case 0x02:
				return cardbus_bridge " " multifunction_header;
		}
		return "MF " unknown_header;
	}
	switch (header_type & 0x7F) {
		case 0x00:
			return standard_header;
		case 0x01:
			return pci2pci_bridge;
		case 0x02:
			return cardbus_bridge;
	}
	return unknown_header;
}

// List of Class Code, Subclass, and Prog IF can be found at:
// * https://wiki.osdev.org/PCI#Class_Codes
// NOTE: Not all values are extracted into here due to most
//       likely does not exist or incompatible with xbox hardware.

#define PCI_SUBCLASS_OTHER 0x80

#define PCI_CLASS_UNCLASSIFIED 0x00
#define PCI_SUBCLASS_UNCLASSIFIED_NONVGA_COMPATIBLE 0x00
#define PCI_SUBCLASS_UNCLASSIFIED_VGA_COMPATIBLE 0x01

#define PCI_CLASS_MASS_STORAGE 0x01
#define PCI_SUBCLASS_MASS_STORAGE_SCSI_BUS 0x00
#define PCI_SUBCLASS_MASS_STORAGE_IDE 0x01
#define PCI_SUBCLASS_MASS_STORAGE_FLOPPY_DISK 0x02
#define PCI_SUBCLASS_MASS_STORAGE_IPI_BUS 0x03
#define PCI_SUBCLASS_MASS_STORAGE_RAID 0x04
#define PCI_SUBCLASS_MASS_STORAGE_ATA 0x05
#define PCI_SUBCLASS_MASS_STORAGE_SERIAL_ATA 0x06
#define PCI_SUBCLASS_MASS_STORAGE_SERIAL_ATTACHED_SCSI 0x07
#define PCI_SUBCLASS_MASS_STORAGE_NONVOLATILE_MEMORY 0x08

#define PCI_CLASS_NETWORK 0x02
#define PCI_SUBCLASS_NETWORK_ETHERNET 0x00
#define PCI_SUBCLASS_NETWORK_TOKEN_RING 0x01
#define PCI_SUBCLASS_NETWORK_FDDI 0x02
#define PCI_SUBCLASS_NETWORK_ATM 0x03
#define PCI_SUBCLASS_NETWORK_ISDN 0x04
#define PCI_SUBCLASS_NETWORK_WORLDFIP 0x05
#define PCI_SUBCLASS_NETWORK_PICMG_2_14_MULTI_COMPUTING 0x06
#define PCI_SUBCLASS_NETWORK_INFINIBAND 0x07
#define PCI_SUBCLASS_NETWORK_FABRIC 0x08

#define PCI_CLASS_DISPLAY 0x03
#define PCI_SUBCLASS_DISPLAY_VGA_COMPATIBLE 0x00
#define PCI_SUBCLASS_DISPLAY_XGA 0x01
#define PCI_SUBCLASS_DISPLAY_3D 0x02

#define PCI_CLASS_MULTIMEDIA 0x04
#define PCI_SUBCLASS_MULTIMEDIA_VIDEO 0x00
#define PCI_SUBCLASS_MULTIMEDIA_AUDIO 0x01
#define PCI_SUBCLASS_MULTIMEDIA_COMPUTER_TELEPHONY 0x02
#define PCI_SUBCLASS_MULTIMEDIA_AUDIO_DEVICE 0x03

#define PCI_CLASS_MEMORY 0x05
#define PCI_SUBCLASS_MEMORY_RAM 0x00
#define PCI_SUBCLASS_MEMORY_FLASH 0x01

#define PCI_CLASS_BRIDGE 0x06
#define PCI_SUBCLASS_BRIDGE_HOST 0x00
#define PCI_SUBCLASS_BRIDGE_ISA 0x01
#define PCI_SUBCLASS_BRIDGE_EISA 0x02
#define PCI_SUBCLASS_BRIDGE_MCA 0x03
#define PCI_SUBCLASS_BRIDGE_PCI2PCI_DECODE 0x04
#define PCI_SUBCLASS_BRIDGE_PCMCIA 0x05
#define PCI_SUBCLASS_BRIDGE_NUBUS 0x06
#define PCI_SUBCLASS_BRIDGE_CARDBUS 0x07
#define PCI_SUBCLASS_BRIDGE_RACEWAY 0x08
#define PCI_SUBCLASS_BRIDGE_PCI2PCI_SEMITRANSPARENT 0x09
#define PCI_SUBCLASS_BRIDGE_INFINIBAND2PCI_HOST 0x0A

#define PCI_CLASS_SIMPLE_COMMUNICATION 0x07
#define PCI_SUBCLASS_SIMPLE_COMMUNICATION_SERIAL 0x00
#define PCI_SUBCLASS_SIMPLE_COMMUNICATION_PARALLEL 0x01
#define PCI_SUBCLASS_SIMPLE_COMMUNICATION_MULTIPORT_SERIAL 0x02
#define PCI_SUBCLASS_SIMPLE_COMMUNICATION_MODEM 0x03
#define PCI_SUBCLASS_SIMPLE_COMMUNICATION_IEEE_488_1_2_GPIB 0x04
#define PCI_SUBCLASS_SIMPLE_COMMUNICATION_SMART_CARD 0x05

#define PCI_CLASS_BASE_SYSTEM_PERIPHERAL 0x08
#define PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_PIC 0x00
#define PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_DMA 0x01
#define PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_TIMER 0x02
#define PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_RTC 0x03
#define PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_PCI_HOTPLUG 0x04
#define PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_SD_HOST 0x05
#define PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_IOMMU 0x06

#define PCI_CLASS_INPUT_DEVICE 0x09
#define PCI_SUBCLASS_INPUT_DEVICE_KEYBOARD 0x00
#define PCI_SUBCLASS_INPUT_DEVICE_DIGITIZER_PEN 0x01
#define PCI_SUBCLASS_INPUT_DEVICE_MOUSE 0x02
#define PCI_SUBCLASS_INPUT_DEVICE_SCANNER 0x03
#define PCI_SUBCLASS_INPUT_DEVICE_GAMEPORT 0x04

#define PCI_CLASS_DOCKING_STATION 0x0A
#define PCI_SUBCLASS_DOCKING_STATION_GENERIC 0x00

#define PCI_CLASS_PROCESSOR 0x0B
#define PCI_SUBCLASS_PROCESSOR_386 0x00
#define PCI_SUBCLASS_PROCESSOR_486 0x01
#define PCI_SUBCLASS_PROCESSOR_PENTIUM 0x02
#define PCI_SUBCLASS_PROCESSOR_PENTIUM_PRO 0x03
#define PCI_SUBCLASS_PROCESSOR_ALPHA 0x10
#define PCI_SUBCLASS_PROCESSOR_POWERPC 0x20
#define PCI_SUBCLASS_PROCESSOR_MIPS 0x30
#define PCI_SUBCLASS_PROCESSOR_COPROCESSOR 0x40

#define PCI_CLASS_SERIAL_BUS 0x0C
#define PCI_SUBCLASS_SERIAL_BUS_FIREWIRE_IEEE_1394 0x00
#define PCI_SUBCLASS_SERIAL_BUS_ACCESS_BUS 0x01
#define PCI_SUBCLASS_SERIAL_BUS_SSA 0x02
#define PCI_SUBCLASS_SERIAL_BUS_USB 0x03
#define PCI_SUBCLASS_SERIAL_BUS_FIBRE 0x04
#define PCI_SUBCLASS_SERIAL_BUS_SMBUS 0x05
#define PCI_SUBCLASS_SERIAL_BUS_INFINIBAND 0x06
#define PCI_SUBCLASS_SERIAL_BUS_IPMI 0x07
#define PCI_SUBCLASS_SERIAL_BUS_SERCOS_INTERFACE_IEC_61491 0x08
#define PCI_SUBCLASS_SERIAL_BUS_CANBUS 0x09

#define PCI_CLASS_WIRELESS 0x0D
#define PCI_SUBCLASS_WIRELESS_IRDA_COMPATIBLE 0x00
#define PCI_SUBCLASS_WIRELESS_CONSUMER_IR 0x01
#define PCI_SUBCLASS_WIRELESS_RF 0x10
#define PCI_SUBCLASS_WIRELESS_BLUETOOTH 0x11
#define PCI_SUBCLASS_WIRELESS_BROADBAND 0x12
#define PCI_SUBCLASS_WIRELESS_ETHERNET_802_1A 0x20
#define PCI_SUBCLASS_WIRELESS_ETHERNET_802_1B 0x21

#define PCI_CLASS_INTELLIGENT 0x0E
#define PCI_SUBCLASS_INTELLIGENT_I20 0x00

#define PCI_CLASS_ENCRYPTION 0x10
#define PCI_SUBCLASS_ENCRYPTION_ENTERTAINMENT 0x10

#define PCI_CLASS_SIGNAL_PROCESSING 0x11
#define PCI_SUBCLASS_PROCESSING_DPIO 0x00
#define PCI_SUBCLASS_PROCESSING_PERFORMANCE 0x01
#define PCI_SUBCLASS_PROCESSING_COMMUNICATION_SYNCHRONIZER 0x10
#define PCI_SUBCLASS_PROCESSING_SIGNAL_PROCESSING_MANAGEMENT 0x20

#define PCI_CLASS_PROCESSING_ACCELERATOR 0x12
#define PCI_CLASS_NONESSENTIAL_INSTRUMENTATION 0x13
#define PCI_CLASS_COPROCESSOR 0x40
#define PCI_CLASS_UNASSIGNED_CLASS 0xFF

const char* pci_get_class_code_str(
	uint8_t class_code)
{
	switch (class_code) {
		case PCI_CLASS_UNCLASSIFIED:
			return "Unclassified";
		case PCI_CLASS_MASS_STORAGE:
			return "Mass Storage Controller";
		case PCI_CLASS_NETWORK:
			return "Network Controller";
		case PCI_CLASS_DISPLAY:
			return "Display Controller";
		case PCI_CLASS_MULTIMEDIA:
			return "Multimedia Controller";
		case PCI_CLASS_MEMORY:
			return "Memory Controller";
		case PCI_CLASS_BRIDGE:
			return "Bridge";
		case PCI_CLASS_SIMPLE_COMMUNICATION:
			return "Simple Communication Controller";
		case PCI_CLASS_BASE_SYSTEM_PERIPHERAL:
			return "Base System Peripheral";
		case PCI_CLASS_INPUT_DEVICE:
			return "Input Device Controller";
		case PCI_CLASS_DOCKING_STATION:
			return "Docking Station";
		case PCI_CLASS_PROCESSOR:
			return "Processor";
		case PCI_CLASS_SERIAL_BUS:
			return "Serial Bus Controller";
		case PCI_CLASS_WIRELESS:
			return "Wireless Controller";
		case PCI_CLASS_INTELLIGENT:
			return "Intelligent Controller";
		case PCI_CLASS_ENCRYPTION:
			return "Encryption Controller";
		case PCI_CLASS_SIGNAL_PROCESSING:
			return "Signal Processing Controller";
		case PCI_CLASS_PROCESSING_ACCELERATOR:
			return "Processing Accelerator";
		case PCI_CLASS_NONESSENTIAL_INSTRUMENTATION:
			return "Non-Essential Instrumentation";
		case PCI_CLASS_COPROCESSOR:
			return "Co-Processor";
		case PCI_CLASS_UNASSIGNED_CLASS:
			return "Unassigned Class";
	}
	return unknown;
}

const char* pci_get_subclass_str(
	uint8_t class_code,
	uint8_t subclass)
{
	switch (class_code) {
		case PCI_CLASS_UNCLASSIFIED:
			switch (subclass) {
				case PCI_SUBCLASS_UNCLASSIFIED_NONVGA_COMPATIBLE:
					return "Non-VGA-Compatible Unclassified Device";
				case PCI_SUBCLASS_UNCLASSIFIED_VGA_COMPATIBLE:
					return "VGA-Compatible Unclassified Device";
			}
			break;
		case PCI_CLASS_MASS_STORAGE:
			switch (subclass) {
				case PCI_SUBCLASS_MASS_STORAGE_SCSI_BUS:
					return "SCSI Bus Controller";
				case PCI_SUBCLASS_MASS_STORAGE_IDE:
					return "IDE Controller";
				case PCI_SUBCLASS_MASS_STORAGE_FLOPPY_DISK:
					return "Floppy Disk Controller";
				case PCI_SUBCLASS_MASS_STORAGE_IPI_BUS:
					return "IPI Bus Controller";
				case PCI_SUBCLASS_MASS_STORAGE_RAID:
					return "RAID Controller";
				case PCI_SUBCLASS_MASS_STORAGE_ATA:
					return "ATA Controller";
				case PCI_SUBCLASS_MASS_STORAGE_SERIAL_ATA:
					return "Serial ATA Controller";
				case PCI_SUBCLASS_MASS_STORAGE_SERIAL_ATTACHED_SCSI:
					return "Serial Attached SCSI Controller";
				case PCI_SUBCLASS_MASS_STORAGE_NONVOLATILE_MEMORY:
					return "Non-Volatile Memory Controller";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_NETWORK:
			switch (subclass) {
				case PCI_SUBCLASS_NETWORK_ETHERNET:
					return "Ethernet Controller";
				case PCI_SUBCLASS_NETWORK_TOKEN_RING:
					return "Token Ring Controller";
				case PCI_SUBCLASS_NETWORK_FDDI:
					return "FDDI Controller";
				case PCI_SUBCLASS_NETWORK_ATM:
					return "ATM Controller";
				case PCI_SUBCLASS_NETWORK_ISDN:
					return "ISDN Controller";
				case PCI_SUBCLASS_NETWORK_WORLDFIP:
					return "WorldFip Controller";
				case PCI_SUBCLASS_NETWORK_PICMG_2_14_MULTI_COMPUTING:
					return "PICMG 2.14 Multi Computing Controller";
				case PCI_SUBCLASS_NETWORK_INFINIBAND:
					return "Infiniband Controller";
				case PCI_SUBCLASS_NETWORK_FABRIC:
					return "Fabric Controller";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_DISPLAY:
			switch (subclass) {
				case PCI_SUBCLASS_DISPLAY_VGA_COMPATIBLE:
					return "VGA Compatible Controller";
				case PCI_SUBCLASS_DISPLAY_XGA:
					return "XGA Controller";
				case PCI_SUBCLASS_DISPLAY_3D:
					return "3D Controller (Not VGA-Compatible)";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_MULTIMEDIA:
			switch (subclass) {
				case PCI_SUBCLASS_MULTIMEDIA_VIDEO:
					return "Multimedia Video Controller";
				case PCI_SUBCLASS_MULTIMEDIA_AUDIO:
					return "Multimedia Audio Controller";
				case PCI_SUBCLASS_MULTIMEDIA_COMPUTER_TELEPHONY:
					return "Computer Telephony Device";
				case PCI_SUBCLASS_MULTIMEDIA_AUDIO_DEVICE:
					return "Audio Device";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_MEMORY:
			switch (subclass) {
				case PCI_SUBCLASS_MEMORY_RAM:
					return "RAM Controller";
				case PCI_SUBCLASS_MEMORY_FLASH:
					return "Flash Controller";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_BRIDGE:
			switch (subclass) {
				case PCI_SUBCLASS_BRIDGE_HOST:
					return "Host Bridge";
				case PCI_SUBCLASS_BRIDGE_ISA:
					return "ISA Bridge";
				case PCI_SUBCLASS_BRIDGE_EISA:
					return "EISA Bridge";
				case PCI_SUBCLASS_BRIDGE_MCA:
					return "MCA Bridge";
				case PCI_SUBCLASS_BRIDGE_PCI2PCI_DECODE:
					return "PCI-to-PCI Bridge";
				case PCI_SUBCLASS_BRIDGE_PCMCIA:
					return "PCMCIA Bridge";
				case PCI_SUBCLASS_BRIDGE_NUBUS:
					return "NuBus Bridge";
				case PCI_SUBCLASS_BRIDGE_CARDBUS:
					return "CardBus Bridge";
				case PCI_SUBCLASS_BRIDGE_RACEWAY:
					return "RACEway Bridge";
				case PCI_SUBCLASS_BRIDGE_PCI2PCI_SEMITRANSPARENT:
					return "PCI-to-PCI Bridge";
				case PCI_SUBCLASS_BRIDGE_INFINIBAND2PCI_HOST:
					return "InfiniBand-to-PCI Host Bridge";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_SIMPLE_COMMUNICATION:
			switch (subclass) {
				case PCI_SUBCLASS_SIMPLE_COMMUNICATION_SERIAL:
					return "Serial Controller";
				case PCI_SUBCLASS_SIMPLE_COMMUNICATION_PARALLEL:
					return "Parallel Controller";
				case PCI_SUBCLASS_SIMPLE_COMMUNICATION_MULTIPORT_SERIAL:
					return "Multiport Serial Controller";
				case PCI_SUBCLASS_SIMPLE_COMMUNICATION_MODEM:
					return "Modem";
				case PCI_SUBCLASS_SIMPLE_COMMUNICATION_IEEE_488_1_2_GPIB:
					return "IEEE 488.1/2 (GPIB) Controller";
				case PCI_SUBCLASS_SIMPLE_COMMUNICATION_SMART_CARD:
					return "Smart Card Controller";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_BASE_SYSTEM_PERIPHERAL:
			switch (subclass) {
				case PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_PIC:
					return "PIC";
				case PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_DMA:
					return "DMA Controller";
				case PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_TIMER:
					return "Timer";
				case PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_RTC:
					return "RTC Controller";
				case PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_PCI_HOTPLUG:
					return "PCI Hot-Plug Controller";
				case PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_SD_HOST:
					return "SD Host Controller";
				case PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_IOMMU:
					return "IOMMU";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_INPUT_DEVICE:
			switch (subclass) {
				case PCI_SUBCLASS_INPUT_DEVICE_KEYBOARD:
					return "Keyboard Controller";
				case PCI_SUBCLASS_INPUT_DEVICE_DIGITIZER_PEN:
					return "Digitizer Pen";
				case PCI_SUBCLASS_INPUT_DEVICE_MOUSE:
					return "Mouse Controller";
				case PCI_SUBCLASS_INPUT_DEVICE_SCANNER:
					return "Scanner Controller";
				case PCI_SUBCLASS_INPUT_DEVICE_GAMEPORT:
					return "Gameport Controller";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_DOCKING_STATION:
			switch (subclass) {
				case PCI_SUBCLASS_DOCKING_STATION_GENERIC:
					return "Generic";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_PROCESSOR:
			switch (subclass) {
				case PCI_SUBCLASS_PROCESSOR_386:
					return "386";
				case PCI_SUBCLASS_PROCESSOR_486:
					return "486";
				case PCI_SUBCLASS_PROCESSOR_PENTIUM:
					return "Pentium";
				case PCI_SUBCLASS_PROCESSOR_PENTIUM_PRO:
					return "Pentium Pro";
				case PCI_SUBCLASS_PROCESSOR_ALPHA:
					return "Alpha";
				case PCI_SUBCLASS_PROCESSOR_POWERPC:
					return "PowerPC";
				case PCI_SUBCLASS_PROCESSOR_MIPS:
					return "MIPS";
				case PCI_SUBCLASS_PROCESSOR_COPROCESSOR:
					return "";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_SERIAL_BUS:
			switch (subclass) {
				case PCI_SUBCLASS_SERIAL_BUS_FIREWIRE_IEEE_1394:
					return "FireWire (IEEE 1394) Controller";
				case PCI_SUBCLASS_SERIAL_BUS_ACCESS_BUS:
					return "ACCESS Bus Controller";
				case PCI_SUBCLASS_SERIAL_BUS_SSA:
					return "SSA";
				case PCI_SUBCLASS_SERIAL_BUS_USB:
					return "USB Controller";
				case PCI_SUBCLASS_SERIAL_BUS_FIBRE:
					return "Fibre Channel";
				case PCI_SUBCLASS_SERIAL_BUS_SMBUS:
					return "SMBus Controller";
				case PCI_SUBCLASS_SERIAL_BUS_INFINIBAND:
					return "InfiniBand Controller";
				case PCI_SUBCLASS_SERIAL_BUS_IPMI:
					return "IPMI Interface";
				case PCI_SUBCLASS_SERIAL_BUS_SERCOS_INTERFACE_IEC_61491:
					return "SERCOS Interface (IEC 61491)";
				case PCI_SUBCLASS_SERIAL_BUS_CANBUS:
					return "CANbus Controller";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_WIRELESS:
			switch (subclass) {
				case PCI_SUBCLASS_WIRELESS_IRDA_COMPATIBLE:
					return "iRDA Compatible Controller";
				case PCI_SUBCLASS_WIRELESS_CONSUMER_IR:
					return "Consumer IR Controller";
				case PCI_SUBCLASS_WIRELESS_RF:
					return "RF Controller";
				case PCI_SUBCLASS_WIRELESS_BLUETOOTH:
					return "Bluetooth Controller";
				case PCI_SUBCLASS_WIRELESS_BROADBAND:
					return "Broadband Controller";
				case PCI_SUBCLASS_WIRELESS_ETHERNET_802_1A:
					return "Ethernet Controller (802.1a)";
				case PCI_SUBCLASS_WIRELESS_ETHERNET_802_1B:
					return "Ethernet Controller (802.1b)";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_INTELLIGENT:
			switch (subclass) {
				case PCI_SUBCLASS_INTELLIGENT_I20:
					return "I20";
			}
			break;
		case PCI_CLASS_ENCRYPTION:
			switch (subclass) {
				case PCI_SUBCLASS_ENCRYPTION_ENTERTAINMENT:
					return "Entertainment Encryption/Decryption";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
		case PCI_CLASS_SIGNAL_PROCESSING:
			switch (subclass) {
				case PCI_SUBCLASS_PROCESSING_DPIO:
					return "DPIO Modules";
				case PCI_SUBCLASS_PROCESSING_PERFORMANCE:
					return "Performance Counters";
				case PCI_SUBCLASS_PROCESSING_COMMUNICATION_SYNCHRONIZER:
					return "Communication Synchronizer";
				case PCI_SUBCLASS_PROCESSING_SIGNAL_PROCESSING_MANAGEMENT:
					return "Signal Processing Management";
				case PCI_SUBCLASS_OTHER:
					return "Other";
			}
			break;
	}
	return "-";
}

const char* pci_get_prog_if_str(
	uint8_t class_code,
	uint8_t subclass,
	uint8_t prog_if)
{
	switch (class_code) {
		case PCI_CLASS_MASS_STORAGE:
			switch (subclass) {
				case PCI_SUBCLASS_MASS_STORAGE_IDE:
					switch (prog_if) {
						case 0x00:
							return "ISA Compatibility mode-only controller";
						case 0x05:
							return "PCI native mode-only controller";
						case 0x0A:
							return "ISA Compatibility mode controller";
						case 0x0F:
							return "PCI native mode controller";
						case 0x80:
							return "ISA Compatibility mode-only controller";
						case 0x85:
							return "PCI native mode-only controller";
						case 0x8A:
							return "ISA Compatibility mode controller";
						case 0x8F:
							return "PCI native mode controller";
					}
					break;
				case PCI_SUBCLASS_MASS_STORAGE_ATA:
					switch (prog_if) {
						case 0x20:
							return "Single DMA";
						case 0x30:
							return "Chained DMA";
					}
					break;
				case PCI_SUBCLASS_MASS_STORAGE_SERIAL_ATA:
					switch (prog_if) {
						case 0x00:
							return "Vendor Specific Interface";
						case 0x01:
							return "AHCI 1.0";
						case 0x02:
							return "Serial Storage Bus";
					}
					break;
				case PCI_SUBCLASS_MASS_STORAGE_SERIAL_ATTACHED_SCSI:
					switch (prog_if) {
						case 0x00:
							return "SAS";
						case 0x01:
							return "Serial Storage Bus";
					}
					break;
				case PCI_SUBCLASS_MASS_STORAGE_NONVOLATILE_MEMORY:
					switch (prog_if) {
						case 0x01:
							return "NVMHCI";
						case 0x02:
							return "NVM Express";
					}
					break;
			}
			break;
		case PCI_CLASS_DISPLAY:
			switch (subclass) {
				case PCI_SUBCLASS_DISPLAY_VGA_COMPATIBLE:
					switch (prog_if) {
						case 0x00:
							return "VGA Controller";
						case 0x01:
							return "8514-Compatible Controller";
					}
					break;
			}
			break;
		case PCI_CLASS_BRIDGE:
			switch (subclass) {
				case PCI_SUBCLASS_BRIDGE_PCI2PCI_DECODE:
					switch (prog_if) {
						case 0x00:
							return "Normal Decode";
						case 0x01:
							return "Subtractive Decode";
					}
					break;
				case PCI_SUBCLASS_BRIDGE_RACEWAY:
					switch (prog_if) {
						case 0x00:
							return "Transparent Mode";
						case 0x01:
							return "Endpoint Mode";
					}
					break;
				case PCI_SUBCLASS_BRIDGE_PCI2PCI_SEMITRANSPARENT:
					switch (prog_if) {
						case 0x40:
							return "Semi-Transparent, Primary bus towards host CPU";
						case 0x80:
							return "Semi-Transparent, Secondary bus towards host CPU";
					}
					break;
			}
			break;
		case PCI_CLASS_SIMPLE_COMMUNICATION: // Simple Communication
			switch (subclass) {
				case PCI_SUBCLASS_SIMPLE_COMMUNICATION_SERIAL:
					switch (prog_if) {
						case 0x00:
							return "8250-Compatible (Generic XT)";
						case 0x01:
							return "16450-Compatible";
						case 0x02:
							return "16550-Compatible";
						case 0x03:
							return "16650-Compatible";
						case 0x04:
							return "16750-Compatible";
						case 0x05:
							return "16850-Compatible";
						case 0x06:
							return "16950-Compatible";
					}
					break;
				case PCI_SUBCLASS_SIMPLE_COMMUNICATION_PARALLEL:
					switch (prog_if) {
						case 0x00:
							return "Standard Parallel Port";
						case 0x01:
							return "Bi-Directional Parallel Port";
						case 0x02:
							return "ECP 1.X Compliant Parallel Port";
						case 0x03:
							return "IEEE 1284 Controller";
						case 0xFE:
							return "IEEE 1284 Target Device";
					}
					break;
				case PCI_SUBCLASS_SIMPLE_COMMUNICATION_MODEM:
					switch (prog_if) {
						case 0x00:
							return "Generic Modem";
						case 0x01:
							return "Hayes 16450-Compatible Interface";
						case 0x02:
							return "Hayes 16550-Compatible Interface";
						case 0x03:
							return "Hayes 16650-Compatible Interface";
						case 0x04:
							return "Hayes 16750-Compatible Interface";
					}
					break;
			}
			break;
		case PCI_CLASS_BASE_SYSTEM_PERIPHERAL:
			switch (subclass) {
				case PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_PIC:
					switch (prog_if) {
						case 0x00:
							return "Generic 8259-Compatible";
						case 0x01:
							return "ISA-Compatible";
						case 0x02:
							return "EISA-Compatible";
						case 0x10:
							return "I/O APIC Interrupt Controller";
						case 0x20:
							return "I/O(x) APIC Interrupt Controller";
					}
					break;
				case PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_DMA:
					switch (prog_if) {
						case 0x00:
							return "Generic 8237-Compatible";
						case 0x01:
							return "ISA-Compatible";
						case 0x02:
							return "EISA-Compatible";
					}
					break;
				case PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_TIMER:
					switch (prog_if) {
						case 0x00:
							return "Generic 8254-Compatible";
						case 0x01:
							return "ISA-Compatible";
						case 0x02:
							return "EISA-Compatible";
						case 0x03:
							return "HPET";
					}
					break;
				case PCI_SUBCLASS_BASE_SYSTEM_PERIPHERAL_RTC:
					switch (prog_if) {
						case 0x00:
							return "Generic RTC";
						case 0x01:
							return "ISA-Compatible";
					}
					break;
			}
			break;
		case PCI_CLASS_INPUT_DEVICE:
			switch (subclass) {
				case PCI_SUBCLASS_INPUT_DEVICE_GAMEPORT:
					switch (prog_if) {
						case 0x00:
							return "Generic";
						case 0x10:
							return "Extended";
					}
					break;
			}
			break;
		case PCI_CLASS_SERIAL_BUS:
			switch (subclass) {
				case PCI_SUBCLASS_SERIAL_BUS_FIREWIRE_IEEE_1394:
					switch (prog_if) {
						case 0x00:
							return "Generic";
						case 0x10:
							return "OHCI";
					}
					break;
				case PCI_SUBCLASS_SERIAL_BUS_USB:
					switch (prog_if) {
						case 0x00:
							return "UHCI Controller";
						case 0x10:
							return "OHCI Controller";
						case 0x20:
							return "EHCI (USB2) Controller";
						case 0x30:
							return "XHCI (USB3) Controller";
						case 0x80:
							return "Unspecified";
						case 0xFE:
							return "USB Device (Not a host controller)";
					}
					break;
				case PCI_SUBCLASS_SERIAL_BUS_IPMI:
					switch (prog_if) {
						case 0x00:
							return "SMIC";
						case 0x01:
							return "Keyboard Controller Style";
						case 0x02:
							return "Block Transfer";
					}
					break;
			}
			break;
	}
	return "-";
}

const char* pci_get_interrupt_pin_str(
	uint8_t interrupt_pin)
{
	switch (interrupt_pin) {
		case 0:
			return "N/A";
		case 1:
			return "INTA#";
		case 2:
			return "INTB#";
		case 3:
			return "INTC#";
		case 4:
			return "INTD#";
	}
	return unknown;
}
