/**
 * Copyright L. Spiro 2025
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The Bus B implementation.
 */

#pragma once

#include "../LSNBirdSNES.h"
#include "../Foundation/LSNMacros.h"

#include <cassert>
#include <cstdint>


namespace lsn {

	/**
	 * Class CBusB
	 * \brief The Bus B implementation.
	 *
	 * Description: The Bus B implementation.
	 */
	class CBusB {
	public :
		CBusB() {
			m_afpAccessParms.pui8Data = m_ui8Ram;
		}
		~CBusB() {
		}


		// == Types.
		/** Reader parameters. */
		struct LSN_ACCESSFUNCPARMS {
			void *									pvParm0;							/**< The user-supplied pointer to pass back to this function. */
			uint8_t *								pui8Data;							/**< A pointer to the default bus memory. */
			uint16_t								ui16Parm1;							/**< The user-supplied parameter to pass back to this function. */
			uint16_t								ui16Address;						/**< The 16-bit address being accessed. */
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
		 * Performs a read of a given address.
		 *
		 * \param _ui16Addr The address to read.
		 * \return Returns the requested value.
		 */
		inline uint8_t								Read( uint16_t _ui16Addr ) {
			uint8_t ui8Ret = m_ui8LastRead;
			uint8_t ui8Mask = 0xFF;
			const LSN_ADDR_ACCESSOR & aaAcc = m_aaAccessors[_ui16Addr];
			m_afpAccessParms.ui16Address = _ui16Addr;
			m_afpAccessParms.pvParm0 = aaAcc.pvReaderParm0;
			m_afpAccessParms.ui16Parm1 = aaAcc.ui16ReaderParm1;
			aaAcc.pfReader( m_afpAccessParms,
				ui8Ret, ui8Mask );
			//ui8Mask = m_ui8OpenBusMask[_ui16Addr];
			m_ui8LastRead = (m_ui8LastRead & ~ui8Mask) | (ui8Ret & ui8Mask);

#ifdef LSN_CPU_VERIFY
			m_vReadWriteLog.push_back( { .ui16Address = _ui16Addr, .ui8Value = ui8Ret, .bRead = true } );
#endif	// #ifdef LSN_CPU_VERIFY
			return ui8Ret;
		}

		/**
		 * Performs a write of a given address.
		 *
		 * \param _ui16Addr The address to write.
		 * \param _ui8Val The value to write.
		 */
		inline void									Write( uint16_t _ui16Addr, uint8_t _ui8Val ) {
			const LSN_ADDR_ACCESSOR & aaAcc = m_aaAccessors[_ui16Addr];
			m_afpAccessParms.ui16Address = _ui16Addr;
			m_afpAccessParms.pvParm0 = aaAcc.pvWriterParm0;
			m_afpAccessParms.ui16Parm1 = aaAcc.ui16WriterParm1;
			aaAcc.pfWriter( m_afpAccessParms, _ui8Val );
			m_ui8LastRead = _ui8Val;
#ifdef LSN_CPU_VERIFY
			m_vReadWriteLog.push_back( { .ui16Address = _ui16Addr, .ui8Value = _ui8Val, .bRead = false } );
#endif	// #ifdef LSN_CPU_VERIFY
		}

#ifdef LSN_CPU_VERIFY
		// == Types.
		struct LSN_READ_WRITE_LOG {
			uint16_t								ui16Address;
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
			uint16_t								ui16ReaderParm1;					/**< The reader's second parameter. */
			uint16_t								ui16WriterParm1;					/**< The writer's second parameter. */
		};


		// == Members.
		LSN_ALIGN( 0x100 )
		//uint8_t										m_ui8OpenBusMask[0x10000];					/**< The open-bus update mask.  Usually 0xFF to update all bits, but $4015 is set to 0x00 to update no floating-bus bits. */
		uint8_t										m_ui8Ram[0x10000];					/**< Memory of _uSize bytes. */
		LSN_ADDR_ACCESSOR							m_aaAccessors[0x10000>>8];			/**< Access functions. */
		LSN_ACCESSFUNCPARMS							m_afpAccessParms;					/**< Parameters sent to the access functions. */
		uint8_t										m_ui8LastRead;						/**< The floating value. */

#ifdef LSN_CPU_VERIFY
		std::vector<LSN_READ_WRITE_LOG>				m_vReadWriteLog;					/**< Access log for JSON tests. */
#endif	// #ifdef LSN_CPU_VERIFY
	};

}	// namespace lsn
