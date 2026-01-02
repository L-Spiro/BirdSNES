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
	class BusA {
	public :
		BusA() {
			BuildSpeedTable();
			ApplyBasicMapping();
		}
		~BusA() {
		}


		// == Types.
		/** Reader parameters. */
		struct LSN_ACCESSFUNCPARMS {
			void *									pvParm0;						/**< The user-supplied pointer to pass back to this function. */
			uint32_t								ui32FullAddress;				/**< The full address being accessed. */
			uint8_t *								pui8Data;						/**< A pointer to the default bus memory. */
			LSN_ACCESS_SOURCE						asAccessSource;					/**< The source of the memory access (CPU vs DMA). */
			uint16_t								ui16Address;					/**< The 16-bit address being accessed. */
			uint8_t									ui8Bank;						/**< The bank being accessed. */
		};

		/** An address-reading function. */
		typedef void (LSN_FASTCALL *				PfReadFunc)( const LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t &_ui8Ret, uint8_t &_ui8OpenMask );

		/** An address-writing function. */
		typedef void (LSN_FASTCALL *				PfWriteFunc)( const LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t _ui8Val );

		/** A debug address-reading function. */
		typedef void (LSN_FASTCALL *				PfDebugReadFunc)( const LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t &_ui8Ret );

		/** A debug address-writing function. */
		typedef void (LSN_FASTCALL *				PfDebugWriteFunc)( const LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t _ui8Val );


		// == Functions.
		/**
		 * Performs a read.
		 * 
		 * \tparam _asAccessSource The read source.
		 * 
		 * \param _ui16Address The address to read.
		 * \param _ui8Bank The bank from which to read the given address.
		 * \param _ui8Speed Returns the master-clock divisor for the given address.
		 * \return Returns the value read.
		 **/
		template <LSN_ACCESS_SOURCE _asAccessSource = LSN_AS_CPU, uint8_t _ui8SpeedOverride = 0>
		inline uint8_t								Read( uint16_t _ui16Address, uint8_t _ui8Bank, uint8_t &_ui8Speed ) {
			static_assert( _ui8SpeedOverride < 16, "_ui8SpeedOverride must fit in 4 bits." );

			m_rfpAccessFuncParms.ui16Address = _ui16Address;
			m_rfpAccessFuncParms.ui8Bank = _ui8Bank;
			m_rfpAccessFuncParms.ui32FullAddress = uint32_t( _ui16Address ) | (uint32_t( _ui8Bank ) << 16);
			m_rfpAccessFuncParms.asAccessSource = _asAccessSource;
			uint16_t ui16SpdAddr = uint16_t( m_rfpAccessFuncParms.ui32FullAddress >> 8 );
			uint8_t * pui8Spd;
			if constexpr ( _ui8SpeedOverride != 0 ) {
				pui8Spd = m_ui8Speeds + ui16SpdAddr;
				LSN_PREFETCH_LINE( pui8Spd );
			}
			uint8_t ui8Mask = 0xFF;
			uint8_t ui8Ret = m_ui8DataBus;
			auto & aaAccessor = m_aaAccessors[ui16SpdAddr];
			m_rfpAccessFuncParms.pvParm0 = aaAccessor.pvReaderParm0;
			aaAccessor.pfReader( m_rfpAccessFuncParms, ui8Ret, ui8Mask );
			m_ui8DataBus = (m_ui8DataBus & ~ui8Mask) | (ui8Ret & ui8Mask);
			if constexpr ( _ui8SpeedOverride != 0 ) {
				_ui8Speed = ((*pui8Spd) >> ((m_ui8MemSel & 1) << 2)) & 0b1111;
			}
			else {
				_ui8Speed = _ui8SpeedOverride;
			}
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
		template <LSN_ACCESS_SOURCE _asAccessSource = LSN_AS_CPU, uint8_t _ui8SpeedOverride = 0>
		inline void									Write( uint16_t _ui16Address, uint8_t _ui8Bank, uint8_t _ui8Val, uint8_t &_ui8Speed ) {
			static_assert( _ui8SpeedOverride < 16, "_ui8SpeedOverride must fit in 4 bits." );

			m_rfpAccessFuncParms.ui16Address = _ui16Address;
			m_rfpAccessFuncParms.ui8Bank = _ui8Bank;
			m_rfpAccessFuncParms.ui32FullAddress = uint32_t( _ui16Address ) | (uint32_t( _ui8Bank ) << 16);
			m_rfpAccessFuncParms.asAccessSource = _asAccessSource;
			uint16_t ui16SpdAddr = uint16_t( m_rfpAccessFuncParms.ui32FullAddress >> 8 );
			uint8_t * pui8Spd;
			if constexpr ( _ui8SpeedOverride != 0 ) {
				pui8Spd = m_ui8Speeds + ui16SpdAddr;
				LSN_PREFETCH_LINE( pui8Spd );
			}
			auto & aaAccessor = m_aaAccessors[ui16SpdAddr];
			aaAccessor.pfWriter( m_rfpAccessFuncParms, _ui8Val );
			m_ui8DataBus = _ui8Val;
			if constexpr ( _ui8SpeedOverride != 0 ) {
				_ui8Speed = ((*pui8Spd) >> ((m_ui8MemSel & 1) << 2)) & 0b1111;
			}
			else {
				_ui8Speed = _ui8SpeedOverride;
			}
#ifdef LSN_CPU_VERIFY
			m_vReadWriteLog.push_back( { .ui32Address = _ui16Address | (uint32_t( _ui8Bank ) << 16), .ui8Value = _ui8Val, .bRead = false } );
#endif	// #ifdef LSN_CPU_VERIFY
		}

		/**
		 * Performs a read from bank 0.
		 * 
		 * \param _ui16Address The address to read.
		 * \param _ui8Speed Returns the master-clock divisor for the given address.
		 * \return Returns the value read.
		 **/
		template <LSN_ACCESS_SOURCE _asAccessSource = LSN_AS_CPU, uint8_t _ui8SpeedOverride = 0>
		inline uint8_t								ReadBank0( uint16_t _ui16Address, uint8_t &_ui8Speed ) {
			static_assert( _ui8SpeedOverride < 16, "_ui8SpeedOverride must fit in 4 bits." );

			m_rfpAccessFuncParms.ui16Address = _ui16Address;
			m_rfpAccessFuncParms.ui8Bank = 0;
			m_rfpAccessFuncParms.ui32FullAddress = uint32_t( _ui16Address );
			m_rfpAccessFuncParms.asAccessSource = _asAccessSource;
			uint16_t ui16SpdAddr = uint16_t( _ui16Address >> 8 );
			uint8_t * pui8Spd;
			if constexpr ( _ui8SpeedOverride != 0 ) {
				pui8Spd = m_ui8Speeds + ui16SpdAddr;
				LSN_PREFETCH_LINE( pui8Spd );
			}
			uint8_t ui8Mask = 0xFF;
			uint8_t ui8Ret = m_ui8DataBus;
			auto & aaAccessor = m_aaAccessors[ui16SpdAddr];
			aaAccessor.pfReader( m_rfpAccessFuncParms, ui8Ret, ui8Mask );
			m_ui8DataBus = (m_ui8DataBus & ~ui8Mask) | (ui8Ret & ui8Mask);
			if constexpr ( _ui8SpeedOverride != 0 ) {
				_ui8Speed = ((*pui8Spd) >> ((m_ui8MemSel & 1) << 2)) & 0b1111;
			}
			else {
				_ui8Speed = _ui8SpeedOverride;
			}
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
		template <LSN_ACCESS_SOURCE _asAccessSource = LSN_AS_CPU, uint8_t _ui8SpeedOverride = 0>
		inline void									WriteBank0( uint16_t _ui16Address, uint8_t _ui8Val, uint8_t &_ui8Speed ) {
			static_assert( _ui8SpeedOverride < 16, "_ui8SpeedOverride must fit in 4 bits." );

			m_rfpAccessFuncParms.ui16Address = _ui16Address;
			m_rfpAccessFuncParms.ui8Bank = 0;
			m_rfpAccessFuncParms.ui32FullAddress = uint32_t( _ui16Address );
			m_rfpAccessFuncParms.asAccessSource = _asAccessSource;
			uint16_t ui16SpdAddr = uint16_t( _ui16Address >> 8 );
			uint8_t * pui8Spd;
			if constexpr ( _ui8SpeedOverride != 0 ) {
				pui8Spd = m_ui8Speeds + ui16SpdAddr;
				LSN_PREFETCH_LINE( pui8Spd );
			}
			auto & aaAccessor = m_aaAccessors[ui16SpdAddr];
			aaAccessor.pfWriter( m_rfpAccessFuncParms, _ui8Val );
			m_ui8DataBus = _ui8Val;
			if constexpr ( _ui8SpeedOverride != 0 ) {
				_ui8Speed = ((*pui8Spd) >> ((m_ui8MemSel & 1) << 2)) & 0b1111;
			}
			else {
				_ui8Speed = _ui8SpeedOverride;
			}
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
		 * Sets (or unsets) the MESEL flag.
		 * 
		 * \param _bSet If true the flag is set, otherwise it is not.
		 **/
		inline void									SetMemSel( bool _bSet ) {
			m_ui8MemSel = _bSet ? 1 : 0;
		}

		/**
		 * Sets the memory pointer.
		 * 
		 * \param _pui8Ram A pointer to the memory used by the bus.
		 **/
		inline void									SetMemory( uint8_t * _pui8Ram ) {
			m_pui8Memory = _pui8Ram;
			m_rfpAccessFuncParms.pui8Data = m_pui8Memory;
		}

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
		 * \param _ui8XSlowRam The DMA divisor.
		 */
		void										BuildSpeedTable( uint16_t _ui8FastRam = LSN_CS_NTSC_CPU_DIVISOR_FAST, uint16_t _ui8SlowRam = LSN_CS_NTSC_CPU_DIVISOR_SLOW, uint16_t _ui8XSlowRam = LSN_CS_NTSC_CPU_DIVISOR_XSLOW ) {
			assert( _ui8FastRam < 16 );
			assert( _ui8SlowRam < 16 );
			assert( _ui8XSlowRam < 16 );

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
					SetRamSpeed( 0x4000, ui8Bank, uint8_t( _ui8XSlowRam ) );	// page 0x40
					SetRamSpeed( 0x4100, ui8Bank, uint8_t( _ui8XSlowRam ) );	// page 0x41

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

		/**
		 * Sets a set of accessor functions for a given chunk of addresses.
		 * 
		 * \param _ui16Chunk The chunk whose function pointers etc. are to be set.  Each chunk is 256 bytes long, and can be indexed via the full 24-bit address divided by 256.
		 * \param _pfReadFunc The function for reading the assigned address range.
		 * \param _pvReadParm The readers’ first parameter.
		 * \param _pfWriteFunc The function for writing the assigned address range.
		 * \param _pvWriteParm The writers’ first parameter.
		 * \param _pfReadFunc The debug function for reading the assigned address range.
		 * \param _pfReadFunc The debug function for writing the assigned address range.
		 **/
		void										SetAccessor( uint16_t _ui16Chunk, PfReadFunc _pfReadFunc, void * _pvReadParm,
			PfWriteFunc _pfWriteFunc, void * _pvWriteParm,
			PfDebugReadFunc _pfDebugReadFunc, PfDebugWriteFunc _pfDebugWriteFunc ) {
			LSN_ADDR_ACCESSOR & aaAccessMe = m_aaAccessors[_ui16Chunk];
			aaAccessMe.pfReader = _pfReadFunc;
			aaAccessMe.pvReaderParm0 = _pvReadParm;
			aaAccessMe.pfWriter = _pfWriteFunc;
			aaAccessMe.pvWriterParm0 = _pvWriteParm;
			aaAccessMe.pfDebugReader = _pfDebugReadFunc;
			aaAccessMe.pfDebugWriter = _pfDebugWriteFunc;
		}

		/**
		 * Applies a basic direct-access mapping to the memory.
		 **/
		void										ApplyBasicMapping() {
			for ( size_t I = 0; I < 0x1000000; I += 0x100 ) {
				SetAccessor( uint16_t( I >> 8 ), &BusA::StdRead, nullptr, &BusA::StdWrite, nullptr,
					&BusA::StdDebugRead, &BusA::StdDebugWrite );
			}
		}

		/**
		 * A default read function.
		 * 
		 * \param _rfpParms A reference to all of the parameters to be passed to this function.
		 * \param _ui8Ret Holds the return value.
		 * \param _ui8OpenMask Holds a mask for the return value.
		 **/
		static void LSN_FASTCALL					StdRead( const LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t &_ui8Ret, uint8_t &/*_ui8OpenMask*/ ) {
			_ui8Ret = _rfpParms.pui8Data[_rfpParms.ui32FullAddress];
		}

		/**
		 * A default write function.
		 * 
		 * \param _rfpParms A reference to all of the parameters to be passed to this function.
		 * \param _ui8Val The value to write to the target address.
		 **/
		static void LSN_FASTCALL					StdWrite( const LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t _ui8Val ) {
			_rfpParms.pui8Data[_rfpParms.ui32FullAddress] = _ui8Val;
		}

		/**
		 * A default debug read function.
		 * 
		 * \param _rfpParms A reference to all of the parameters to be passed to this function.
		 * \param _ui8Ret Holds the return value.
		 **/
		static void LSN_FASTCALL					StdDebugRead( const LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t &_ui8Ret ) {
			_ui8Ret = _rfpParms.pui8Data[_rfpParms.ui32FullAddress];
		}

		/**
		 * A default debug write function.
		 * 
		 * \param _rfpParms A reference to all of the parameters to be passed to this function.
		 * \param _ui8Val The value to write to the target address.
		 **/
		static void LSN_FASTCALL					StdDebugWrite( const LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t _ui8Val ) {
			_rfpParms.pui8Data[_rfpParms.ui32FullAddress] = _ui8Val;
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
			PfReadFunc								pfReader;							/**< The function for reading the assigned address range. */
			void *									pvReaderParm0;						/**< The readers’ first parameter. */
			PfWriteFunc								pfWriter;							/**< The function for writing the assigned address range. */
			void *									pvWriterParm0;						/**< The writers’ first parameter. */
			PfDebugReadFunc							pfDebugReader;						/**< The debug function for reading the assigned address range. */
			PfDebugWriteFunc						pfDebugWriter;						/**< The debug function for writing the assigned address range. */
			//uint32_t								ui32ReaderParm1;					/**< The reader's second parameter. */
			//uint32_t								ui32WriterParm1;					/**< The writer's second parameter. */
		};


		// == Members.
		uint8_t										m_ui8Speeds[0x10000];				/**< The speed table. 64 kibibytes. */
		LSN_ADDR_ACCESSOR							m_aaAccessors[0x1000000>>8];		/**< An accessor per logical page. 3.0 mebibytes on x64, 1.5 on x86. */
		uint8_t *									m_pui8Memory = nullptr;				/**< A pointer to the RAM memory. 8/4 bytes */
		LSN_ACCESSFUNCPARMS							m_rfpAccessFuncParms;				/**< Parameters to pass to read/write functions. */
		uint8_t										m_ui8DataBus = 0;					/**< The data-bus value. 1 byte. */
		uint8_t										m_ui8MemSel = 0;					/**< The MEMSEL flag. */


		// == Functions.
		

	};

}	// namespace lsn
