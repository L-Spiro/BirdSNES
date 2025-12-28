/**
 * Copyright L. Spiro 2025
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The Bus A implementation.
 */

#pragma once

#include "../LSNBirdSNES.h"
#include "../Foundation/LSNMacros.h"

#include <cassert>
#include <cstdint>


namespace lsn {

	/**
	 * Class BusA
	 * \brief The Bus A implementation.
	 *
	 * Description: The Bus A implementation.
	 */
	template <unsigned _uSize = 0x1000000>
	class BusA {
	public :
		BusA() {
			BuildSpeedTable();
		}
		~BusA() {
		}


		// == Types.
		/** An address-reading function. */
		typedef void (LSN_FASTCALL *				PfReadFunc)( void * _pvParm0, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t &_ui8Ret, uint8_t &_ui8OpenMask );

		/** An address-writing function. */
		typedef void (LSN_FASTCALL *				PfWriteFunc)( void * _pvParm0, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t _ui8Val, uint8_t &_ui8OpenMask );

		/** A debug address-reading function. */
		typedef void (LSN_FASTCALL *				PfDebugReadFunc)( void * _pvParm0, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t &_ui8Ret );

		/** A debug address-writing function. */
		typedef void (LSN_FASTCALL *				PfDebugWriteFunc)( void * _pvParm0, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t _ui8Val );


		// == Functions.
		/**
		 * Performs a read.
		 * 
		 * \param _ui16Address The address to read.
		 * \param _ui8Bank The bank from which to read the given address.
		 * \param _ui8Speed Returns the master-clock divisor for the given address.
		 * \return Returns the value read.
		 **/
		inline uint8_t								Read( uint16_t _ui16Address, uint8_t _ui8Bank, uint8_t &_ui8Speed ) {
			uint16_t ui16SpdAddr = (_ui16Address >> 8) | (uint16_t( _ui8Bank ) << 8);
			uint8_t * ui8Spd = m_ui8Speeds + ui16SpdAddr;
			LSN_PREFETCH_LINE( ui8Spd );
			uint8_t ui8Mask = 0xFF;
			uint8_t ui8Ret = m_ui8DataBus;
			auto & aaAccessor = m_aaAccessors[_ui8Bank];
			aaAccessor.pfReader( aaAccessor.pvReaderParm0, _ui16Address, m_pui8Memory, ui8Ret, ui8Mask );
			m_ui8DataBus = (m_ui8DataBus & ~ui8Mask) | (ui8Ret & ui8Mask);
			_ui8Speed = ((*ui8Spd) >> ((m_ui8MemSel & 1) << 2)) & 0b1111;
#ifdef LSN_CPU_VERIFY
			m_vReadWriteLog.push_back( { .ui32Address = _ui16Address | (uint32_t( _ui8Bank ) << 16), .ui8Value = ui8Ret, .bRead = true } );
#endif	// #ifdef LSN_CPU_VERIFY
			return ui8Ret;
		}

		/**
		 * Performs a write.
		 * 
		 * \param _ui16Address The address to write.
		 * \param _ui8Bank The bank to which to write to the given address.
		 * \param _ui8Val The to to write to the given address.
		 * \param _ui8Speed Returns the master-clock divisor for the given address.
		 **/
		inline void									Write( uint16_t _ui16Address, uint8_t _ui8Bank, uint8_t _ui8Val, uint8_t &_ui8Speed ) {
			uint16_t ui16SpdAddr = (_ui16Address >> 8) | (uint16_t( _ui8Bank ) << 8);
			uint8_t * ui8Spd = m_ui8Speeds + ui16SpdAddr;
			LSN_PREFETCH_LINE( ui8Spd );
			uint8_t ui8Mask = 0xFF;
			auto & aaAccessor = m_aaAccessors[_ui8Bank];
			aaAccessor.pfWriter( aaAccessor.pvWriterParm0, _ui16Address, m_pui8Memory, _ui8Val, ui8Mask );
			m_ui8DataBus = (m_ui8DataBus & ~ui8Mask) | (_ui8Val & ui8Mask);
			_ui8Speed = ((*ui8Spd) >> ((m_ui8MemSel & 1) << 2)) & 0b1111;
#ifdef LSN_CPU_VERIFY
			m_vReadWriteLog.push_back( { .ui32Address = _ui16Address | (uint32_t( _ui8Bank ) << 16), .ui8Value = _ui8Val, .bRead = false } );
#endif	// #ifdef LSN_CPU_VERIFY
		}

		/**
		 * Performs a read from bank 0.
		 * 
		 * \param _ui16Address The address to read.
		 * \param _ui8Bank The bank from which to read the given address.
		 * \param _ui8Speed Returns the master-clock divisor for the given address.
		 * \return Returns the value read.
		 **/
		inline uint8_t								ReadBank0( uint16_t _ui16Address, uint8_t &_ui8Speed ) {
			uint16_t ui16SpdAddr = (_ui16Address >> 8);
			uint8_t * ui8Spd = m_ui8Speeds + ui16SpdAddr;
			LSN_PREFETCH_LINE( ui8Spd );
			uint8_t ui8Mask = 0xFF;
			uint8_t ui8Ret = m_ui8DataBus;
			auto & aaAccessor = m_aaAccessors[0];
			aaAccessor.pfReader( aaAccessor.pvReaderParm0, _ui16Address, m_pui8Memory, ui8Ret, ui8Mask );
			m_ui8DataBus = (m_ui8DataBus & ~ui8Mask) | (ui8Ret & ui8Mask);
			_ui8Speed = ((*ui8Spd) >> ((m_ui8MemSel & 1) << 2)) & 0b1111;
#ifdef LSN_CPU_VERIFY
			m_vReadWriteLog.push_back( { .ui32Address = _ui16Address | (uint32_t( _ui8Bank ) << 16), .ui8Value = ui8Ret, .bRead = true } );
#endif	// #ifdef LSN_CPU_VERIFY
			return ui8Ret;
		}

		/**
		 * Performs a write to bank 0.
		 * 
		 * \param _ui16Address The address to write.
		 * \param _ui8Val The to to write to the given address.
		 * \param _ui8Speed Returns the master-clock divisor for the given address.
		 **/
		inline void									WriteBank0( uint16_t _ui16Address, uint8_t _ui8Val, uint8_t &_ui8Speed ) {
			uint16_t ui16SpdAddr = (_ui16Address >> 8);
			uint8_t * ui8Spd = m_ui8Speeds + ui16SpdAddr;
			LSN_PREFETCH_LINE( ui8Spd );
			uint8_t ui8Mask = 0xFF;
			auto & aaAccessor = m_aaAccessors[0];
			aaAccessor.pfWriter( aaAccessor.pvWriterParm0, _ui16Address, m_pui8Memory, _ui8Val, ui8Mask );
			m_ui8DataBus = (m_ui8DataBus & ~ui8Mask) | (_ui8Val & ui8Mask);
			_ui8Speed = ((*ui8Spd) >> ((m_ui8MemSel & 1) << 2)) & 0b1111;
#ifdef LSN_CPU_VERIFY
			m_vReadWriteLog.push_back( { .ui32Address = _ui16Address | (uint32_t( _ui8Bank ) << 16), .ui8Value = _ui8Val, .bRead = false } );
#endif	// #ifdef LSN_CPU_VERIFY
		}

		/**
		 * Gets a reference to the data bus, which is shared with Bus B.
		 * 
		 * \return Returns a reference to the data bus to be shaerd with Bus B.
		 **/
		inline uint8_t &							DataBus() { return m_ui8DataBus; }

		/**
		 * Sets an address speed.
		 * 
		 * \param _ui16Address The address within the given bank whose speed is to be set.
		 * \param _ui8Bank The bank of the address whose speed is to be set.
		 * \param _ui8Speed0 The speed to set for MEMSEL=0.
		 * \param _ui8Speed The speed to set for MEMSEL=1.  0 means to use the same value as _ui8Speed0.
		 **/
		inline void									SetRamSpeed( uint16_t _ui16Address, uint8_t _ui8Bank, uint8_t _ui8Speed0, uint8_t _ui8Speed1 = 0 ) {
			uint16_t ui16SpdAddr = (_ui16Address >> 8) | (uint16_t( _ui8Bank ) << 8);
			uint8_t * ui8Spd = m_ui8Speeds + ui16SpdAddr;
			if ( 0 == _ui8Speed1 ) {
				 _ui8Speed1 = _ui8Speed0;
			}

			(*ui8Spd) = ((_ui8Speed1 & 0xF) << 4) | (_ui8Speed0 & 0xF);
		}

		/**
		 * Fills the address-speed table using SetRamSpeed().
		 *
		 * The table is per 256-byte page (address >> 8) within each bank.
		 * Low nibble  = MEMSEL=0
		 * High nibble = MEMSEL=1 (FastROM)
		 *
		 * \param _ui8FastRam The fast-RAM divisor.
		 * \param _ui8SlowRam The slow-RAM divisor.
		 * \param _ui8DmaRam The DMA divisor.
		 */
		void										BuildSpeedTable( uint16_t _ui8FastRam = LSN_CS_NTSC_CPU_DIVISOR_FAST, uint16_t _ui8SlowRam = LSN_CS_NTSC_CPU_DIVISOR_SLOW, uint16_t _ui8DmaRam = LSN_CS_NTSC_CPU_DIVISOR_DMA ) {
			static_assert( _ui8FastRam < 16, "FAST speed must fit in 4 bits." );
			static_assert( _ui8SlowRam < 16, "SLOW speed must fit in 4 bits." );
			static_assert( _ui8DmaRam < 16, "DMA speed must fit in 4 bits." );

			// Default everything to Slow for both MEMSEL states.
			//	(FastROM only affects specific regions.)
			for ( uint32_t ui32Bank = 0; ui32Bank < 0x100; ++ui32Bank ) {
				for ( uint32_t ui32Page = 0; ui32Page < 0x100; ++ui32Page ) {
					SetRamSpeed( uint16_t( ui32Page << 8 ), uint8_t( ui32Bank ), uint8_t( _ui8SlowRam ) );
				}
			}

			// --- Banks $00-$3F and $80-$BF: page-based map ---
			auto DoLoHiBankGroup = [&]( uint8_t _ui8BaseBank ) {
				for ( uint32_t ui32B = 0; ui32B < 0x40; ++ui32B ) {
					uint8_t ui8Bank = uint8_t( _ui8BaseBank + ui32B );

					// $0000-$1FFF: Slow (WRAM mirror) (already default).

					// $2000-$3FFF: Fast.
					for ( uint32_t ui32Page = 0x20; ui32Page <= 0x3F; ++ui32Page ) {
						SetRamSpeed( uint16_t( ui32Page << 8 ), ui8Bank, uint8_t( _ui8FastRam ) );
					}

					// $4000-$41FF: DMA/XSLOW.
					SetRamSpeed( 0x4000, ui8Bank, uint8_t( _ui8DmaRam ) );	// page 0x40
					SetRamSpeed( 0x4100, ui8Bank, uint8_t( _ui8DmaRam ) );	// page 0x41

					// $4200-$5FFF: Fast.
					for ( uint32_t ui32Page = 0x42; ui32Page <= 0x5F; ++ui32Page ) {
						SetRamSpeed( uint16_t( ui32Page << 8 ), ui8Bank, uint8_t( _ui8FastRam ) );
					}

					// $6000-$7FFF: Slow (already default).

					// $8000-$FFFF:
					// - banks $00-$3F: Slow (default)
					// - banks $80-$BF: FastROM dependent.
					if ( _ui8BaseBank == 0x80 ) {
						for ( uint32_t ui32Page = 0x80; ui32Page <= 0xFF; ++ui32Page ) {
							SetRamSpeed( uint16_t( ui32Page << 8 ), ui8Bank, uint8_t( _ui8SlowRam ), uint8_t( _ui8FastRam ) );
						}
					}
				}
			};

			DoLoHiBankGroup( 0x00 );
			DoLoHiBankGroup( 0x80 );

			// --- Banks $40-$7D: all Slow (already default). ---

			// --- Banks $7E-$7F (WRAM): all Slow (already default). ---

			// --- Banks $C0-$FF: entire bank is FastROM dependent. ---
			for ( uint32_t ui32Bank = 0xC0; ui32Bank <= 0xFF; ++ui32Bank ) {
				for ( uint32_t ui32Page = 0x00; ui32Page <= 0xFF; ++ui32Page ) {
					SetRamSpeed( uint16_t( ui32Page << 8 ), uint8_t( ui32Bank ), uint8_t( _ui8SlowRam ), uint8_t( _ui8FastRam ) );
				}
			}
		}


#ifdef LSN_CPU_VERIFY
		// == Types.
		struct LSN_READ_WRITE_LOG {
			uint32_t								ui32Address;
			uint8_t									ui8Value;
			bool									bRead;
		};


		// == Functions.
		/**
		 * Gets the read/write log.
		 *
		 * \return Returns a constant reference to the read/write log.
		 */
		 std::vector<LSN_READ_WRITE_LOG> &			ReadWriteLog() { return m_vReadWriteLog; }
#endif	// #ifdef LSN_CPU_VERIFY


	protected :
		// == Types.
		/** Per-page information. */
		struct LSN_ADDR_ACCESSOR {
			PfReadFunc								pfReader;							/**< The function for reading the assigned address. */
			void *									pvReaderParm0;						/**< The reader's first parameter. */
			PfWriteFunc								pfWriter;							/**< The function for writing the assigned address. */
			void *									pvWriterParm0;						/**< The writer's first parameter. */
			PfDebugReadFunc							pfDebugReader;						/**< The reader's first parameter. */
			PfDebugWriteFunc						pfDebugWriter;						/**< The writer's first parameter. */
			uint16_t								ui16ReaderParm1;					/**< The reader's second parameter. */
			uint16_t								ui16WriterParm1;					/**< The writer's second parameter. */
		};


		// == Members.
		uint8_t										m_ui8Speeds[0x10000];				/**< The speed table. 64 kibibytes. */
		LSN_ADDR_ACCESSOR							m_aaAccessors[_uSize>>8];			/**< An accessor per logical page. 3.5 mebibytes with padding on x64, 1.75 on x86. */
		uint8_t *									m_pui8Memory = nullptr;				/**< A pointer to the RAM memory. 8/4 bytes */
		uint8_t										m_ui8DataBus = 0;					/**< The data-bus value. 1 byte. */
		uint8_t										m_ui8MemSel = 0;					/**< The MEMSEL flag. */


		// == Functions.
		

	};


	// == Types.
	typedef BusA<0x1000000, lsn::LSN_CS_NTSC_CPU_DIVISOR_FAST, lsn::LSN_CS_NTSC_CPU_DIVISOR_SLOW, lsn::LSN_CS_NTSC_CPU_DIVISOR_DMA>
																						BusANtsc;

	typedef BusA<0x1000000, lsn::LSN_CS_PAL_CPU_DIVISOR_FAST, lsn::LSN_CS_PAL_CPU_DIVISOR_SLOW, lsn::LSN_CS_PAL_CPU_DIVISOR_DMA>
																						BusAPal;

}	// namespace lsn
