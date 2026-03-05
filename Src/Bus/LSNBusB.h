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

#pragma warning( push )
#pragma warning( disable : 26495 )	// warning C26495: Variable 'lsn::CBusB::m_ui8LastRead' is uninitialized. Always initialize a member variable (type.6).

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
			void *									pvParm0 = nullptr;					/**< The user-supplied pointer to pass back to this function. */
			uint8_t *								pui8Data = nullptr;					/**< A pointer to the default bus memory. */
			uint16_t								ui16Parm1 = 0;						/**< The user-supplied parameter to pass back to this function. */
			uint16_t								ui16Address = 0;					/**< The actual 16-bit address being accessed. */
			uint8_t									ui8OpenBusMask = 0;					/**< The open-bus mask. */
		};

		/** An address-reading function. */
		typedef void (LSN_FASTCALL *				PfReadFunc)( LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t &_ui8Ret );

		/** An address-writing function. */
		typedef void (LSN_FASTCALL *				PfWriteFunc)( LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t _ui8Val );

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
			const LSN_ADDR_ACCESSOR & aaAcc = m_aaAccessors[_ui16Addr>>8];
			m_afpAccessParms.ui16Address = _ui16Addr;
			m_afpAccessParms.pvParm0 = aaAcc.pvReaderParm0;
			m_afpAccessParms.ui16Parm1 = aaAcc.ui16ReaderParm1;
			m_afpAccessParms.ui8OpenBusMask = 0xFF;
			aaAcc.pfReader( m_afpAccessParms, ui8Ret );
			m_ui8LastRead = (m_ui8LastRead & ~m_afpAccessParms.ui8OpenBusMask) | (ui8Ret & m_afpAccessParms.ui8OpenBusMask);

#ifdef LSN_SPC700_CPU_VERIFY
			//m_vReadWriteLog.push_back( { .ui16Address = _ui16Addr, .ui8Value = ui8Ret, .bRead = true } );
			if ( m_vReadWriteLog.size() ) {
				m_vReadWriteLog[m_vReadWriteLog.size()-1].ui16Address = _ui16Addr;
				m_vReadWriteLog[m_vReadWriteLog.size()-1].ui8Value = ui8Ret;
				m_vReadWriteLog[m_vReadWriteLog.size()-1].bRead = true;
			}
#endif	// #ifdef LSN_SPC700_CPU_VERIFY
			return ui8Ret;
		}

		/**
		 * Performs a write of a given address.
		 *
		 * \param _ui16Addr The address to write.
		 * \param _ui8Val The value to write.
		 */
		inline void									Write( uint16_t _ui16Addr, uint8_t _ui8Val ) {
			const LSN_ADDR_ACCESSOR & aaAcc = m_aaAccessors[_ui16Addr>>8];
			m_afpAccessParms.ui16Address = _ui16Addr;
			m_afpAccessParms.pvParm0 = aaAcc.pvWriterParm0;
			m_afpAccessParms.ui16Parm1 = aaAcc.ui16WriterParm1;
			m_afpAccessParms.ui8OpenBusMask = 0xFF;
			aaAcc.pfWriter( m_afpAccessParms, _ui8Val );
			m_ui8LastRead = (m_ui8LastRead & ~m_afpAccessParms.ui8OpenBusMask) | (_ui8Val & m_afpAccessParms.ui8OpenBusMask);
#ifdef LSN_SPC700_CPU_VERIFY
			//m_vReadWriteLog.push_back( { .ui16Address = _ui16Addr, .ui8Value = _ui8Val, .bRead = false } );
			if ( m_vReadWriteLog.size() ) {
				m_vReadWriteLog[m_vReadWriteLog.size()-1].ui16Address = _ui16Addr;
				m_vReadWriteLog[m_vReadWriteLog.size()-1].ui8Value = _ui8Val;
				m_vReadWriteLog[m_vReadWriteLog.size()-1].bRead = false;
			}
#endif	// #ifdef LSN_SPC700_CPU_VERIFY
		}

		/**
		 * Sets a set of accessor functions for a given chunk of addresses.
		 * 
		 * \param _ui16Chunk The chunk whose function pointers etc. are to be set.  Each chunk is 256 bytes long, and can be indexed via the full 24-bit address divided by 256.
		 * \param _pfReadFunc The function for reading the assigned address range.
		 * \param _pvReadParm0 The readers’ first parameter.
		 * \param _ui16ReadParm1 The readers’ second parameter.
		 * \param _pfWriteFunc The function for writing the assigned address range.
		 * \param _pvWriteParm0 The writers’ first parameter.
		 * \param _ui16WriteParm1 The writers’ second parameter.
		 * \param _pfDebugReadFunc The debug function for reading the assigned address range.
		 * \param _pfDebugWriteFunc The debug function for writing the assigned address range.
		 **/
		void										SetAccessor( uint16_t _ui16Chunk, PfReadFunc _pfReadFunc, void * _pvReadParm0, uint16_t _ui16ReadParm1,
			PfWriteFunc _pfWriteFunc, void * _pvWriteParm0, uint16_t _ui16WriteParm1,
			PfDebugReadFunc _pfDebugReadFunc, PfDebugWriteFunc _pfDebugWriteFunc ) {
			LSN_ADDR_ACCESSOR & aaAccessMe = m_aaAccessors[_ui16Chunk];
			aaAccessMe.pfReader = _pfReadFunc;
			aaAccessMe.pvReaderParm0 = _pvReadParm0;
			aaAccessMe.ui16ReaderParm1 = _ui16ReadParm1;
			aaAccessMe.pfWriter = _pfWriteFunc;
			aaAccessMe.pvWriterParm0 = _pvWriteParm0;
			aaAccessMe.ui16WriterParm1 = _ui16WriteParm1;
			aaAccessMe.pfDebugReader = _pfDebugReadFunc;
			aaAccessMe.pfDebugWriter = _pfDebugWriteFunc;
		}

		/**
		 * Applies a basic direct-access mapping to the memory.
		 **/
		void										ApplyBasicMapping() {
#ifdef LSN_SPC700_CPU_VERIFY
			m_vReadWriteLog.clear();
#endif	// #ifdef LSN_SPC700_CPU_VERIFY
			for ( size_t I = 0; I < 0x10000; I += 0x100 ) {
				SetAccessor( uint16_t( I >> 8 ), &CBusB::StdRead, nullptr, uint16_t( I ), &CBusB::StdWrite, nullptr, uint16_t( I ),
					&CBusB::StdDebugRead, &CBusB::StdDebugWrite );
			}
		}

		/**
		 * A standard read function.
		 *
		 * \param _rfpParms The parameters for the read operation.
		 * \param _ui8Ret The read value.
		 */
		static void LSN_FASTCALL					StdRead( LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t &_ui8Ret ) {
			_ui8Ret = _rfpParms.pui8Data[_rfpParms.ui16Address];
		}

		/**
		 * A standard write function.
		 *
		 * \param _rfpParms The parameters for the write operation.
		 * \param _ui8Val The value to write.
		 */
		static void LSN_FASTCALL					StdWrite( LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t _ui8Val ) {
			_rfpParms.pui8Data[_rfpParms.ui16Address] = _ui8Val;
		}

		/**
		 * A function usable for addresses that can't be read.
		 *
		 * \param _rfpParms The parameters for the read operation.
		 * \param _ui8Ret The read value.
		 */
		static void LSN_FASTCALL					NoRead( LSN_ACCESSFUNCPARMS &/*_rfpParms*/, uint8_t &/*_ui8Ret*/ ) {
		}

		/**
		 * A function usable for addresses that can't be written.
		 *
		 * \param _rfpParms The parameters for the write operation.
		 * \param _ui8Val The value to write.
		 */
		static void LSN_FASTCALL					NoWrite( LSN_ACCESSFUNCPARMS &/*_rfpParms*/, uint8_t /*_ui8Val*/ ) {
		}

		/**
		 * A standard debug read function.
		 *
		 * \param _rfpParms The parameters for the read operation.
		 * \param _ui8Ret The read value.
		 */
		static void LSN_FASTCALL					StdDebugRead( const LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t &_ui8Ret ) {
			_ui8Ret = _rfpParms.pui8Data[_rfpParms.ui16Address];
		}

		/**
		 * A standard debug write function.
		 *
		 * \param _rfpParms The parameters for the write operation.
		 * \param _ui8Val The value to write.
		 */
		static void LSN_FASTCALL					StdDebugWrite( const LSN_ACCESSFUNCPARMS &_rfpParms, uint8_t _ui8Val ) {
			_rfpParms.pui8Data[_rfpParms.ui16Address] = _ui8Val;
		}

#ifdef LSN_SPC700_CPU_VERIFY
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
#endif	// #ifdef LSN_SPC700_CPU_VERIFY

	
	protected :
		// == Types.
		/** Per-page information. */
		struct LSN_ADDR_ACCESSOR {
			PfReadFunc								pfReader = nullptr;					/**< The function for reading the assigned address range. */
			void *									pvReaderParm0 = nullptr;			/**< The readers’ first parameter. */
			PfWriteFunc								pfWriter = nullptr;					/**< The function for writing the assigned address range. */
			void *									pvWriterParm0 = nullptr;			/**< The writers’ first parameter. */
			PfDebugReadFunc							pfDebugReader = nullptr;			/**< The debug function for reading the assigned address range. */
			PfDebugWriteFunc						pfDebugWriter = nullptr;			/**< The debug function for writing the assigned address range. */
			uint16_t								ui16ReaderParm1 = 0;				/**< The reader's second parameter. */
			uint16_t								ui16WriterParm1 = 0;				/**< The writer's second parameter. */
		};


		// == Members.
		LSN_ALIGN( 0x100 )
		uint8_t										m_ui8Ram[0x10000];					/**< Memory of _uSize bytes. */
		LSN_ADDR_ACCESSOR							m_aaAccessors[0x10000>>8] {};		/**< Access functions. */
		LSN_ACCESSFUNCPARMS							m_afpAccessParms;					/**< Parameters sent to the access functions. */
		uint8_t										m_ui8LastRead;						/**< The floating value. */

#ifdef LSN_SPC700_CPU_VERIFY
		std::vector<LSN_READ_WRITE_LOG>				m_vReadWriteLog;					/**< Access log for JSON tests. */
#endif	// #ifdef LSN_SPC700_CPU_VERIFY
	};

#pragma warning( pop )

}	// namespace lsn
