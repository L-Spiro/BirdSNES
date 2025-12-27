/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A class for opening files using the standard C library (FILE).
 */


#pragma once

#include "../OS/NN9Os.h"
#include "../Utilities/NN9Crc.h"
#include "NN9FileBase.h"

namespace nn9 {

	/**
	 * Class StdFile
	 * \brief A class for opening files using the standard C library (FILE).
	 *
	 * Description: A class for opening files using the standard C library (FILE).
	 */
	class StdFile : public FileBase {
	public :
		StdFile();
		virtual ~StdFile();


		// == Functions.
		/**
		 * Opens a file.
		 *
		 * \param _pFile Path to the file to open.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual NN9_ERRORS									Open( const std::filesystem::path &_pFile );

		/**
		 * Creates a file.
		 *
		 * \param _pFile Path to the file to create.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual NN9_ERRORS									Create( const std::filesystem::path &_pFile );

		/**
		 * Opens a file for appending.  If it does not exist it is created.
		 *
		 * \param _pFile Path to the file to open for appending.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual NN9_ERRORS									Append( const std::filesystem::path &_pFile );

		/**
		 * Closes the opened file.
		 */
		virtual void										Close();

		/**
		 * Loads the opened file to memory, storing the result in _vResult.
		 *
		 * \param _vResult The location where to store the file in memory.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual NN9_ERRORS									LoadToMemory( std::vector<uint8_t> &_vResult ) const;

		/**
		 * Writes the given data to the created file.  File must have been cerated with Create().
		 *
		 * \param _vData The data to write to the file.
		 * \return Returns true if the data was successfully written to the file.
		 */
		virtual NN9_ERRORS									WriteToFile( const std::vector<uint8_t> &_vData );

		/**
		 * Writes the given data to the created file.  File must have been cerated with Create().
		 *
		 * \param _pui8Data The data to write to the file.
		 * \param _tsSize The size of the buffer to which _pui8Data points.
		 * \return Returns true if the data was successfully written to the file.
		 */
		virtual NN9_ERRORS									WriteToFile( const uint8_t * _pui8Data, size_t _tsSize );

		/**
		 * Gets the size of the file.
		 * 
		 * \return Returns the size of the file.
		 **/
		virtual uint64_t									Size() const { return m_ui64Size; }

		/**
		 * Moves the file pointer from the current position and returns the new position.
		 * 
		 * \param _i64Offset Amount by which to move the file pointer.
		 * \return Returns the new line position.
		 **/
		virtual uint64_t									MovePointerBy( int64_t _i64Offset ) const;

		/**
		 * Moves the file pointer to the given file position.
		 * 
		 * \param _ui64Pos The new file position to set.
		 * \param _bFromEnd Whether _ui64Pos is from the end of the file or not. 
		 * \return Returns the new file position.
		 **/
		virtual uint64_t									MovePointerTo( uint64_t _ui64Pos, bool _bFromEnd = false ) const;

		/**
		 * Loads the opened file to memory, storing the result in _vResult.
		 *
		 * \param _pcFile The file to open.
		 * \param _vResult The location where to store the file in memory.
		 * \return Returns an error code indicating the result of the operation.
		 **/
		template <typename _tStrType>
		static inline NN9_ERRORS							LoadToMemory( const _tStrType * _pcFile, std::vector<uint8_t> &_vResult );

		/**
		 * Writes the given data to a given file.
		 *
		 * \param _pcFile The file to create.
		 * \param _pui8Data The data to write to the file.
		 * \param _tsSize The size of the buffer to which _pui8Data points.
		 * \return Returns true if the data was successfully written to the file.
		 */
		template <typename _tStrType>
		static inline NN9_ERRORS							WriteToFile( const _tStrType * _pcFile, const uint8_t * _pui8Data, size_t _tsSize );

		/**
		 * Writes the given data to a given file.
		 *
		 * \param _pcFile The file to create.
		 * \param _vData The data to write to the file.
		 * \return Returns true if the data was successfully written to the file.
		 */
		template <typename _tStrType>
		static inline NN9_ERRORS							WriteToFile( const _tStrType * _pcFile, const std::vector<uint8_t> &_vData );

		/**
		 * Appends the given data to a given file.
		 *
		 * \param _pcFile The file to which to append the given data.
		 * \param _ptData The data to write to the file.
		 * \param _tsSize The number of elements in the buffer to which _ptData points.
		 * \return Returns true if the data was successfully written to the file.
		 */
		template <typename _tStrType, typename _tData>
		static inline NN9_ERRORS							AppendToFile( const _tStrType * _pcFile, const _tData * _ptData, size_t _tsSize );

		/**
		 * Appends the given data to a given file.
		 *
		 * \param _pcFile The file to which to append the given data.
		 * \param _pc8Data The data to write to the file.
		 * \param _tsSize The size of the buffer to which _pui8Data points.
		 * \return Returns true if the data was successfully written to the file.
		 */
		template <typename _tStrType>
		static inline NN9_ERRORS							AppendToFile( const _tStrType * _pcFile, const char8_t * _pc8Data, size_t _tsSize = 0 );

		/**
		 * Appends the given data to a given file.
		 *
		 * \param _pcFile The file to which to append the given data.
		 * \param _pcData The data to write to the file.
		 * \param _tsSize The size of the buffer to which _pui8Data points.
		 * \return Returns true if the data was successfully written to the file.
		 */
		template <typename _tStrType>
		static inline NN9_ERRORS							AppendToFile( const _tStrType * _pcFile, const char * _pcData, size_t _tsSize = 0 );

		/**
		 * Appends the given data to a given file.
		 *
		 * \tparam _tStrType The string type (typically char8_t or char16_t).
		 * \param _pcFile The file to which to append the given data.
		 * \param _vData The data to write to the file.
		 * \return Returns true if the data was successfully written to the file.
		 */
		template <typename _tStrType>
		static inline NN9_ERRORS							AppendToFile( const _tStrType * _pcFile, const std::vector<uint8_t> &_vData );

		/**
		 * Gets the CRC of a given file.
		 * 
		 * \param _pcFile The file whose CRC is to be obtained.
		 * \return Returns true if the data was successfully written to the file.
		 **/
		template <typename _tStrType>
		static inline uint32_t								Crc( const _tStrType * _pcFile );


	protected :
		// == Members.
		FILE *												m_pfFile;							/**< The FILE object to maintain. */
		uint64_t											m_ui64Size;							/**< The file size. */


		// == Functions.
		/**
		 * Performs post-loading operations after a successful loading of the file.  m_pfFile will be valid when this is called.  Override to perform additional loading operations on m_pfFile.
		 */
		virtual void										PostLoad();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// DEFINITIONS
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// == Functions.
	/**
	 * Loads the opened file to memory, storing the result in _vResult.
	 *
	 * \param _pcFile The file to open.
	 * \param _vResult The location where to store the file in memory.
	 * \return Returns an error code indicating the result of the operation.
	 **/
	template <typename _tStrType>
	inline NN9_ERRORS StdFile::LoadToMemory( const _tStrType * _pcFile, std::vector<uint8_t> &_vResult ) {
		StdFile sfFile;
		auto aCode = sfFile.Open( _pcFile );
		if ( aCode != NN9_E_SUCCESS ) { return aCode; }
		return sfFile.LoadToMemory( _vResult );
	}

	/**
	 * Writes the given data to a given file.
	 *
	 * \param _pcFile The file to create.
	 * \param _pui8Data The data to write to the file.
	 * \param _tsSize The size of the buffer to which _pui8Data points.
	 * \return Returns true if the data was successfully written to the file.
	 */
	template <typename _tStrType>
	inline NN9_ERRORS StdFile::WriteToFile( const _tStrType * _pcFile, const uint8_t * _pui8Data, size_t _tsSize ) {
		StdFile sfFile;
		auto aCode = sfFile.Create( _pcFile );
		if ( aCode != NN9_E_SUCCESS ) { return aCode; }
		return sfFile.WriteToFile( _pui8Data, _tsSize );
	}

	/**
	 * Writes the given data to a given file.
	 *
	 * \param _pcFile The file to create.
	 * \param _vData The data to write to the file.
	 * \return Returns true if the data was successfully written to the file.
	 */
	template <typename _tStrType>
	inline NN9_ERRORS StdFile::WriteToFile( const _tStrType * _pcFile, const std::vector<uint8_t> &_vData ) {
		return WriteToFile( _pcFile, _vData.data(), _vData.size() );
	}

	/**
	 * Appends the given data to a given file.
	 *
	 * \param _pcFile The file to which to append the given data.
	 * \param _ptData The data to write to the file.
	 * \param _tsSize The number of elements in the buffer to which _ptData points.
	 * \return Returns true if the data was successfully written to the file.
	 */
	template <typename _tStrType, typename _tData>
	inline NN9_ERRORS StdFile::AppendToFile( const _tStrType * _pcFile, const _tData * _ptData, size_t _tsSize ) {
		StdFile sfFile;
		auto aCode = sfFile.Append( _pcFile );
		if ( aCode != NN9_E_SUCCESS ) { return aCode; }
		return sfFile.WriteToFile( _ptData, _tsSize * sizeof( _tData ) );
	}

	/**
	 * Appends the given data to a given file.
	 *
	 * \param _pcFile The file to which to append the given data.
	 * \param _pc8Data The data to write to the file.
	 * \param _tsSize The size of the buffer to which _pui8Data points.
	 * \return Returns true if the data was successfully written to the file.
	 */
	template <typename _tStrType>
	inline NN9_ERRORS StdFile::AppendToFile( const _tStrType * _pcFile, const char8_t * _pc8Data, size_t _tsSize ) {
		if ( !_tsSize ) { _tsSize = std::strlen( reinterpret_cast<const char *>(_pc8Data) ); }
		return AppendToFile( _pcFile, reinterpret_cast<const uint8_t *>(_pc8Data), _tsSize );
	}

	/**
	 * Appends the given data to a given file.
	 *
	 * \param _pcFile The file to which to append the given data.
	 * \param _pcData The data to write to the file.
	 * \param _tsSize The size of the buffer to which _pui8Data points.
	 * \return Returns true if the data was successfully written to the file.
	 */
	template <typename _tStrType>
	inline NN9_ERRORS StdFile::AppendToFile( const _tStrType * _pcFile, const char * _pcData, size_t _tsSize ) {
		if ( !_tsSize ) { _tsSize = std::strlen( _pcData ); }
		return AppendToFile( _pcFile, reinterpret_cast<const uint8_t *>(_pcData), _tsSize );
	}

	/**
	 * Appends the given data to a given file.
	 *
	 * \param _pcFile The file to which to append the given data.
	 * \param _vData The data to write to the file.
	 * \return Returns true if the data was successfully written to the file.
	 */
	template <typename _tStrType>
	inline NN9_ERRORS StdFile::AppendToFile( const _tStrType * _pcFile, const std::vector<uint8_t> &_vData ) {
		return AppendToFile( _pcFile, _vData.data(), _vData.size() );
	}

	/**
	 * Gets the CRC of a given file.
	 * 
	 * \param _pcFile The file whose CRC is to be obtained.
	 * \return Returns true if the data was successfully written to the file.
	 **/
	template <typename _tStrType>
	inline uint32_t StdFile::Crc( const _tStrType * _pcFile ) {
		std::vector<uint8_t> vData;
		auto eErr = LoadToMemory( _pcFile, vData );
		if ( eErr != NN9_E_SUCCESS ) { return 0; }
		return Crc::GetCrc( vData.data(), vData.size() );
	}

}	// namespace nn9
