/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Error codes and functions for handling errors.
 */

#pragma once

#include "../Compression/MiniZ/miniz.h"
#include "../Foundation/LSNMacros.h"
#include "../OS/LSNOs.h"
#include "../Strings/LSNStrings.h"

#include <chrono>
#include <cstdint>
#include <ctime>
#ifdef LSN_USE_CURL
#include <curl/curl.h>
#endif	// #ifdef LSN_USE_CURL
#include <iomanip>
#include <errno.h>
#include <string>


namespace lsn {

	// == Types.
	/** Error codes. */
	enum LSN_ERRORS : uint16_t {
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			ENUM,
#include "LSNErrorEnum.inl"
#undef LSN_E_ENUM
	};


	/**
	 * Class CErrors
	 * \brief Provides functionality for working with errors and error codes.
	 *
	 * Description: Provides functionality for working with errors and error codes.
	 */
	class CErrors {
	public :
		// == Functions.
		/**
		 * Converts an errno_t to one of our error codes.
		 * 
		 * \param _eCode The code to convert.
		 * \return Returns the converted error code.
		 **/
		static inline LSN_ERRORS									ErrNo_T_To_Native( errno_t _eCode );

		/**
		 * Converts a mz_zip_error error code to one of our error codes.
		 * 
		 * \param _zeCode The code to convert.
		 * \return Returns the converted error code.
		 **/
		static inline LSN_ERRORS									ZipError_To_Native( mz_zip_error _zeCode );

#ifdef LSN_USE_CURL
		/**
		 * Converts a libcurl error to one of our error codes.
		 * 
		 * \param _cCode The code to convert.
		 * \return Returns the converted error code.
		 **/
		static inline LSN_ERRORS									LibCurl_To_Native( CURLcode _cCode );
#endif	// #ifdef LSN_USE_CURL

#ifdef _WIN32
		/**
		 * Calls ::GetLastError() and converts the error code to one of our error codes.
		 * 
		 * \return Returns the converted error code.
		 **/
		static inline LSN_ERRORS									GetLastError_To_Native();

		/**
		 * Displays the current ::GetLastError() error with a description.
		 * 
		 * \param _dwErr The error code to translate.  If -1, ::GetLastError() is called.
		 **/
		static inline void											DisplayLastError( DWORD _dwErr = DWORD( -1 ) );

#endif	// #ifdef _WIN32
	
		/**
		 * Gets the string description of an error code.
		 * 
		 * \param _eCode The error code whose description is to be gotten.
		 * \return Returns the text description for the given error.
		 **/
		static inline const char *									ToStr( LSN_ERRORS _eCode );

		/**
		 * Gets the string description of an error code.
		 * 
		 * \param _eCode The error code whose description is to be gotten.
		 * \return Returns the text description for the given error.
		 **/
		static inline const char8_t *								ToStrPU8( LSN_ERRORS _eCode );

		/**
		 * Gets the string description of an error code.
		 * 
		 * \param _eCode The error code whose description is to be gotten.
		 * \return Returns the text description for the given error.
		 **/
		static inline std::string									ToStrStr( LSN_ERRORS _eCode );

		/**
		 * Gets the string description of an error code.
		 * 
		 * \param _eCode The error code whose description is to be gotten.
		 * \return Returns the text description for the given error.
		 **/
		static inline std::u8string									ToStrU8( LSN_ERRORS _eCode );

		/**
		 * Gets the string description of an error code.
		 * 
		 * \param _eCode The error code whose description is to be gotten.
		 * \return Returns the text description for the given error.
		 **/
		static inline const wchar_t *								ToStrPWStr( LSN_ERRORS _eCode );

		/**
		 * Gets the string description of an error code.
		 * 
		 * \param _eCode The error code whose description is to be gotten.
		 * \return Returns the text description for the given error.
		 **/
		static inline const char16_t *								ToStrPU16( LSN_ERRORS _eCode );

		/**
		 * Gets the string description of an error code.
		 * 
		 * \param _eCode The error code whose description is to be gotten.
		 * \return Returns the text description for the given error.
		 **/
		static inline std::wstring									ToStrWStr( LSN_ERRORS _eCode );

		/**
		 * Gets the string description of an error code.
		 * 
		 * \param _eCode The error code whose description is to be gotten.
		 * \return Returns the text description for the given error.
		 **/
		static inline std::u16string								ToStrU16( LSN_ERRORS _eCode );

		/**
		 * Gets the name of an error code.
		 * 
		 * \param _eCode The error code whose name is to be gotten.
		 * \return Returns the text name for the given error.
		 **/
		static inline const char *									Name( LSN_ERRORS _eCode );

		/**
		 * Gets the name of an error code.
		 * 
		 * \param _eCode The error code whose name is to be gotten.
		 * \return Returns the text name for the given error.
		 **/
		static inline const char8_t *								NamePU8( LSN_ERRORS _eCode );

		/**
		 * Gets the name of an error code.
		 * 
		 * \param _eCode The error code whose name is to be gotten.
		 * \return Returns the text name for the given error.
		 **/
		static inline const wchar_t *								NamePWS( LSN_ERRORS _eCode );

		/**
		 * Gets the name of an error code.
		 * 
		 * \param _eCode The error code whose name is to be gotten.
		 * \return Returns the text name for the given error.
		 **/
		static inline const char16_t *								NamePU16( LSN_ERRORS _eCode );

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// DEFINITIONS
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// == Functions.
	/**
	 * Converts an errno_t to one of our error codes.
	 * 
	 * \param _eCode The code to convert.
	 * \return Returns the converted error code.
	 **/
	inline LSN_ERRORS CErrors::ErrNo_T_To_Native( errno_t _eCode ) {
		switch ( _eCode ) {
			case 0 : { return LSN_E_SUCCESS; }
			case EINVAL : { return LSN_E_INVALID_PARAMETER; }
			case EACCES : { return LSN_E_INVALID_PERMISSIONS; }
			case ENOENT : { return LSN_E_FILE_NOT_FOUND; }
			case EMFILE : { return LSN_E_TOO_MANY_FILES_OPENED; }
			case ENOMEM : { return LSN_E_OUT_OF_MEMORY; }
			case EEXIST : { return LSN_E_FILES_EXISTS; }
			case EOVERFLOW : { return LSN_E_FILE_ATTRIBUTE_TOO_LARGE; }
			case EPERM : { return LSN_E_OPERATION_NOT_PERMITTED; }
				
#ifdef EBADF
			case EBADF : { return LSN_E_INVALID_HANDLE; }
#endif

#ifdef ENFILE
			case ENFILE : { return LSN_E_TOO_MANY_FILES; }
#endif

#ifdef ENOSPC
			case ENOSPC : { return LSN_E_DISK_FULL; }
#endif

#ifdef EFBIG
			case EFBIG : { return LSN_E_FILE_TOO_LARGE; }
#endif

#ifdef ENAMETOOLONG
			case ENAMETOOLONG : { return LSN_E_INVALID_NAME; }
#endif

#ifdef ENOTDIR
			case ENOTDIR : { return LSN_E_INVALID_NAME; }
#endif

#ifdef EISDIR
			case EISDIR : { return LSN_E_INVALID_NAME; }
#endif

#ifdef ELOOP
			case ELOOP : { return LSN_E_INVALID_NAME; }
#endif

#ifdef EROFS
			case EROFS : { return LSN_E_INVALID_PERMISSIONS; }
#endif

#ifdef EBUSY
			case EBUSY : { return LSN_E_LOCK_VIOLATION; }
#endif

#ifdef ETXTBSY
			case ETXTBSY : { return LSN_E_LOCK_VIOLATION; }
#endif

#ifdef ENODEV
			case ENODEV : { return LSN_E_NO_SUCH_DEVICE; }
#endif

#ifdef ENXIO
			case ENXIO : { return LSN_E_NO_SUCH_DEVICE; }
#endif

#ifdef EAGAIN
			case EAGAIN : { return LSN_E_TIMEOUT; }
#endif

#ifdef EINTR
			case EINTR : { return LSN_E_TIMEOUT; }
#endif

#ifdef EIO
			case EIO : { return LSN_E_READ_FAILED; }
#endif

#ifdef EPIPE
			case EPIPE : { return LSN_E_WRITE_FAILED; }
#endif
				
			default : { return LSN_E_OTHER; }
		}
	}

	/**
	 * Converts a mz_zip_error error code to one of our error codes.
	 * 
	 * \param _zeCode The code to convert.
	 * \return Returns the converted error code.
	 **/
	inline LSN_ERRORS CErrors::ZipError_To_Native( mz_zip_error _zeCode ) {
		switch ( _zeCode ) {
			case MZ_ZIP_NO_ERROR : { return LSN_E_SUCCESS; }
			case MZ_ZIP_UNDEFINED_ERROR : { return LSN_E_OTHER; }
			case MZ_ZIP_TOO_MANY_FILES : { return LSN_E_TOO_MANY_FILES; }
			case MZ_ZIP_FILE_TOO_LARGE : { return LSN_E_FILE_TOO_LARGE; }
			case MZ_ZIP_UNSUPPORTED_METHOD : { return LSN_E_INVALID_OPERATION; }
			case MZ_ZIP_UNSUPPORTED_ENCRYPTION : { return LSN_E_INVALID_ENCRYPTION; }
			case MZ_ZIP_UNSUPPORTED_FEATURE : { return LSN_E_UNSUPPORTED_FEATURE; }
			case MZ_ZIP_FAILED_FINDING_CENTRAL_DIR : { return LSN_E_FAILED_FINDING_CENTRAL_DIR; }
			case MZ_ZIP_NOT_AN_ARCHIVE : { return LSN_E_NOT_AN_ARCHIVE; }
			case MZ_ZIP_INVALID_HEADER_OR_CORRUPTED : { return LSN_E_INVALID_HEADER_OR_CORRUPTED; }
			case MZ_ZIP_UNSUPPORTED_MULTIDISK : { return LSN_E_UNSUPPORTED_MULTI_DISK; }
			case MZ_ZIP_DECOMPRESSION_FAILED : { return LSN_E_DECOMPRESSION_FAILED; }
			case MZ_ZIP_COMPRESSION_FAILED : { return LSN_E_COMPRESSION_FAILED; }
			case MZ_ZIP_UNEXPECTED_DECOMPRESSED_SIZE : { return LSN_E_UNEXPECTED_DECOMPRESSED_SIZE; }
			case MZ_ZIP_CRC_CHECK_FAILED : { return LSN_E_BAD_CRC; }
			case MZ_ZIP_UNSUPPORTED_CDIR_SIZE : { return LSN_E_UNSUPPORTED_CDIR_SIZE; }
			case MZ_ZIP_ALLOC_FAILED : { return LSN_E_OUT_OF_MEMORY; }
			case MZ_ZIP_FILE_OPEN_FAILED : { return LSN_E_OPEN_FAILED; }
			case MZ_ZIP_FILE_CREATE_FAILED : { return LSN_E_CREATE_FAILED; }
			case MZ_ZIP_FILE_WRITE_FAILED : { return LSN_E_WRITE_FAILED; }
			case MZ_ZIP_FILE_READ_FAILED : { return LSN_E_READ_FAILED; }
			case MZ_ZIP_FILE_CLOSE_FAILED : { return LSN_E_CLOSE_FAILED; }
			case MZ_ZIP_FILE_SEEK_FAILED : { return LSN_E_SEEK_FAILED; }
			case MZ_ZIP_FILE_STAT_FAILED : { return LSN_E_STAT_FAILED; }
			case MZ_ZIP_INVALID_PARAMETER : { return LSN_E_INVALID_PARAMETER; }
			case MZ_ZIP_INVALID_FILENAME : { return LSN_E_INVALID_NAME; }
			case MZ_ZIP_BUF_TOO_SMALL : { return LSN_E_INSUFFICIENT_BUFFER; }
			case MZ_ZIP_INTERNAL_ERROR : { return LSN_E_INTERNAL_ERROR; }
			case MZ_ZIP_FILE_NOT_FOUND : { return LSN_E_ARCHIVE_FILE_NOT_FOUND; }
			case MZ_ZIP_ARCHIVE_TOO_LARGE : { return LSN_E_ARCHIVE_TOO_LARGE; }
			case MZ_ZIP_VALIDATION_FAILED : { return LSN_E_VALIDATION_FAILED; }
			case MZ_ZIP_WRITE_CALLBACK_FAILED : { return LSN_E_WRITE_CALLBACK_FAILED; }
			default : { return LSN_E_OTHER; }
		}
	}

#ifdef LSN_USE_CURL
	/**
	 * Converts a libcurl error to one of our error codes.
	 * 
	 * \param _cCode The code to convert.
	 * \return Returns the converted error code.
	 **/
	inline LSN_ERRORS CErrors::LibCurl_To_Native( CURLcode _cCode ) {
#define LSN_CHECK( ERROR )				case ERROR : { return LSN_E_ ## ERROR; }
		switch ( _cCode ) {
			case CURLE_OK : { return LSN_E_SUCCESS; }
			LSN_CHECK( CURLE_UNSUPPORTED_PROTOCOL )
			LSN_CHECK( CURLE_FAILED_INIT )
			LSN_CHECK( CURLE_URL_MALFORMAT )
			LSN_CHECK( CURLE_NOT_BUILT_IN )
			LSN_CHECK( CURLE_COULDNT_RESOLVE_PROXY )
			LSN_CHECK( CURLE_COULDNT_RESOLVE_HOST )
			LSN_CHECK( CURLE_COULDNT_CONNECT )
			LSN_CHECK( CURLE_WEIRD_SERVER_REPLY )
			LSN_CHECK( CURLE_REMOTE_ACCESS_DENIED )
			LSN_CHECK( CURLE_FTP_ACCEPT_FAILED )
			LSN_CHECK( CURLE_FTP_WEIRD_PASS_REPLY )
			LSN_CHECK( CURLE_FTP_ACCEPT_TIMEOUT )
			LSN_CHECK( CURLE_FTP_WEIRD_PASV_REPLY )
			LSN_CHECK( CURLE_FTP_WEIRD_227_FORMAT )
			LSN_CHECK( CURLE_FTP_CANT_GET_HOST )
			LSN_CHECK( CURLE_HTTP2 )
			LSN_CHECK( CURLE_FTP_COULDNT_SET_TYPE )
			LSN_CHECK( CURLE_PARTIAL_FILE )
			LSN_CHECK( CURLE_FTP_COULDNT_RETR_FILE )
			LSN_CHECK( CURLE_OBSOLETE20 )
			LSN_CHECK( CURLE_QUOTE_ERROR )
			LSN_CHECK( CURLE_HTTP_RETURNED_ERROR )
			LSN_CHECK( CURLE_WRITE_ERROR )
			LSN_CHECK( CURLE_OBSOLETE24 )
			LSN_CHECK( CURLE_UPLOAD_FAILED )
			LSN_CHECK( CURLE_READ_ERROR )
			LSN_CHECK( CURLE_OUT_OF_MEMORY )
			LSN_CHECK( CURLE_OPERATION_TIMEDOUT )
			LSN_CHECK( CURLE_OBSOLETE29 )
			LSN_CHECK( CURLE_FTP_PORT_FAILED )
			LSN_CHECK( CURLE_FTP_COULDNT_USE_REST )
			LSN_CHECK( CURLE_OBSOLETE32 )
			LSN_CHECK( CURLE_RANGE_ERROR )
			LSN_CHECK( CURLE_HTTP_POST_ERROR )
			LSN_CHECK( CURLE_SSL_CONNECT_ERROR )
			LSN_CHECK( CURLE_BAD_DOWNLOAD_RESUME )
			LSN_CHECK( CURLE_FILE_COULDNT_READ_FILE )
			LSN_CHECK( CURLE_LDAP_CANNOT_BIND )
			LSN_CHECK( CURLE_LDAP_SEARCH_FAILED )
			LSN_CHECK( CURLE_OBSOLETE40 )
			LSN_CHECK( CURLE_FUNCTION_NOT_FOUND )
			LSN_CHECK( CURLE_ABORTED_BY_CALLBACK )
			LSN_CHECK( CURLE_BAD_FUNCTION_ARGUMENT )
			LSN_CHECK( CURLE_OBSOLETE44 )
			LSN_CHECK( CURLE_INTERFACE_FAILED )
			LSN_CHECK( CURLE_OBSOLETE46 )
			LSN_CHECK( CURLE_TOO_MANY_REDIRECTS )
			LSN_CHECK( CURLE_UNKNOWN_OPTION )
			LSN_CHECK( CURLE_SETOPT_OPTION_SYNTAX )
			LSN_CHECK( CURLE_OBSOLETE50 )
			LSN_CHECK( CURLE_OBSOLETE51 )
			LSN_CHECK( CURLE_GOT_NOTHING )
			LSN_CHECK( CURLE_SSL_ENGINE_NOTFOUND )
			LSN_CHECK( CURLE_SSL_ENGINE_SETFAILED )
			LSN_CHECK( CURLE_SEND_ERROR )
			LSN_CHECK( CURLE_RECV_ERROR )
			LSN_CHECK( CURLE_OBSOLETE57 )
			LSN_CHECK( CURLE_SSL_CERTPROBLEM )
			LSN_CHECK( CURLE_SSL_CIPHER )
			LSN_CHECK( CURLE_PEER_FAILED_VERIFICATION )
			LSN_CHECK( CURLE_BAD_CONTENT_ENCODING )
			LSN_CHECK( CURLE_OBSOLETE62 )
			LSN_CHECK( CURLE_FILESIZE_EXCEEDED )
			LSN_CHECK( CURLE_USE_SSL_FAILED )
			LSN_CHECK( CURLE_SEND_FAIL_REWIND )
			LSN_CHECK( CURLE_SSL_ENGINE_INITFAILED )
			LSN_CHECK( CURLE_LOGIN_DENIED )
			LSN_CHECK( CURLE_TFTP_NOTFOUND )
			LSN_CHECK( CURLE_TFTP_PERM )
			LSN_CHECK( CURLE_REMOTE_DISK_FULL )
			LSN_CHECK( CURLE_TFTP_ILLEGAL )
			LSN_CHECK( CURLE_TFTP_UNKNOWNID )
			LSN_CHECK( CURLE_REMOTE_FILE_EXISTS )
			LSN_CHECK( CURLE_TFTP_NOSUCHUSER )
			LSN_CHECK( CURLE_OBSOLETE75 )
			LSN_CHECK( CURLE_OBSOLETE76 )
			LSN_CHECK( CURLE_SSL_CACERT_BADFILE )
			LSN_CHECK( CURLE_REMOTE_FILE_NOT_FOUND )
			LSN_CHECK( CURLE_SSH )
			LSN_CHECK( CURLE_SSL_SHUTDOWN_FAILED )
			LSN_CHECK( CURLE_AGAIN )
			LSN_CHECK( CURLE_SSL_CRL_BADFILE )
			LSN_CHECK( CURLE_SSL_ISSUER_ERROR )
			LSN_CHECK( CURLE_FTP_PRET_FAILED )
			LSN_CHECK( CURLE_RTSP_CSEQ_ERROR )
			LSN_CHECK( CURLE_RTSP_SESSION_ERROR )
			LSN_CHECK( CURLE_FTP_BAD_FILE_LIST )
			LSN_CHECK( CURLE_CHUNK_FAILED )
			LSN_CHECK( CURLE_NO_CONNECTION_AVAILABLE )
			LSN_CHECK( CURLE_SSL_PINNEDPUBKEYNOTMATCH )
			LSN_CHECK( CURLE_SSL_INVALIDCERTSTATUS )
			LSN_CHECK( CURLE_HTTP2_STREAM )
			LSN_CHECK( CURLE_RECURSIVE_API_CALL )
			LSN_CHECK( CURLE_AUTH_ERROR )
			LSN_CHECK( CURLE_HTTP3 )
			LSN_CHECK( CURLE_QUIC_CONNECT_ERROR )
			LSN_CHECK( CURLE_PROXY )
			LSN_CHECK( CURLE_SSL_CLIENTCERT )
			LSN_CHECK( CURLE_UNRECOVERABLE_POLL )
#if !defined( __APPLE__ )
			LSN_CHECK( CURLE_TOO_LARGE )
			LSN_CHECK( CURLE_ECH_REQUIRED )
#endif	// #if !defined( __APPLE__ )
			//LSN_CHECK( CURL_LAST )

			default : { return LSN_E_OTHER; }
		}
#undef LSN_CHECK
	}
#endif	// #ifdef LSN_USE_CURL

#ifdef _WIN32
	/**
	 * Calls ::GetLastError() and converts the error code to one of our error codes.
	 * 
	 * \return Returns the converted error code.
	 **/
	inline LSN_ERRORS CErrors::GetLastError_To_Native() {
		HRESULT dwError = ::GetLastError();
		DisplayLastError( dwError );
		switch ( dwError ) {
			// Success
			case ERROR_SUCCESS : { return LSN_E_SUCCESS; }

			// Memory CErrors.
			case ERROR_NOT_ENOUGH_MEMORY : {}	LSN_FALLTHROUGH
			case ERROR_OUTOFMEMORY : { return LSN_E_OUT_OF_MEMORY; }

			// File (read) CErrors
			case ERROR_FILE_NOT_FOUND : { return LSN_E_FILE_NOT_FOUND; }
			case ERROR_ACCESS_DENIED : { return LSN_E_INVALID_PERMISSIONS; }
			case ERROR_TOO_MANY_OPEN_FILES : { return LSN_E_TOO_MANY_FILES_OPENED; }
			case ERROR_ALREADY_EXISTS : {}		LSN_FALLTHROUGH
			case ERROR_FILE_EXISTS : { return LSN_E_FILES_EXISTS; }
			case ERROR_FILE_TOO_LARGE : { return LSN_E_FILE_TOO_LARGE; }
			case ERROR_PATH_NOT_FOUND : { return LSN_E_FILE_NOT_FOUND; }
			case ERROR_INVALID_NAME : { return LSN_E_INVALID_NAME; }
			case ERROR_SHARING_VIOLATION : {}	LSN_FALLTHROUGH
			case ERROR_LOCK_VIOLATION : { return LSN_E_LOCK_VIOLATION; }
			case ERROR_DISK_FULL : { return LSN_E_DISK_FULL; }
			case ERROR_BUFFER_OVERFLOW : {}		LSN_FALLTHROUGH
			case ERROR_INSUFFICIENT_BUFFER : { return LSN_E_INSUFFICIENT_BUFFER; }
			case ERROR_SHARING_BUFFER_EXCEEDED : { return LSN_E_SHARING_BUFFER_EXCEEDED; }
			case ERROR_NOT_READY : { return LSN_E_NOT_READY; }
			case ERROR_DEVICE_NOT_CONNECTED : { return LSN_E_DEVICE_NOT_CONNECTED; }
			case ERROR_NO_SUCH_DEVICE : { return LSN_E_NO_SUCH_DEVICE; }
			case ERROR_NETWORK_ACCESS_DENIED : { return LSN_E_NETWORK_ACCESS_DENIED; }
			case ERROR_NETWORK_BUSY : { return LSN_E_NETWORK_BUSY; }
			case ERROR_INVALID_HANDLE : { return LSN_E_INVALID_HANDLE; }
			case ERROR_TIMEOUT : { return LSN_E_TIMEOUT; }

#define LSN_CHECK( ERROR )				case ERROR : { return LSN_E_ ## ERROR; }
			LSN_CHECK( INET_E_DOWNLOAD_FAILURE )
			LSN_CHECK( INET_E_INVALID_CERTIFICATE )
			LSN_CHECK( WININET_E_OUT_OF_HANDLES )
			LSN_CHECK( WININET_E_TIMEOUT )
			LSN_CHECK( WININET_E_EXTENDED_ERROR )
			LSN_CHECK( WININET_E_INTERNAL_ERROR )
			LSN_CHECK( WININET_E_INVALID_URL )
			LSN_CHECK( WININET_E_UNRECOGNIZED_SCHEME )
			LSN_CHECK( WININET_E_NAME_NOT_RESOLVED )
			LSN_CHECK( WININET_E_PROTOCOL_NOT_FOUND )
			LSN_CHECK( WININET_E_INVALID_OPTION )
			LSN_CHECK( WININET_E_BAD_OPTION_LENGTH )
			LSN_CHECK( WININET_E_OPTION_NOT_SETTABLE )
			LSN_CHECK( WININET_E_SHUTDOWN )
			LSN_CHECK( WININET_E_LOGIN_FAILURE )
			LSN_CHECK( WININET_E_OPERATION_CANCELLED )
			LSN_CHECK( WININET_E_INCORRECT_HANDLE_TYPE )
			LSN_CHECK( WININET_E_INCORRECT_HANDLE_STATE )
			LSN_CHECK( WININET_E_NOT_PROXY_REQUEST )
			LSN_CHECK( WININET_E_CANNOT_CONNECT )
			LSN_CHECK( WININET_E_CONNECTION_ABORTED )
			LSN_CHECK( WININET_E_CONNECTION_RESET )
			LSN_CHECK( WININET_E_FORCE_RETRY )
			LSN_CHECK( WININET_E_INVALID_PROXY_REQUEST )
			LSN_CHECK( WININET_E_NEED_UI )
			LSN_CHECK( WININET_E_HANDLE_EXISTS )
			LSN_CHECK( WININET_E_SEC_CERT_DATE_INVALID )
			LSN_CHECK( WININET_E_SEC_CERT_CN_INVALID )
			LSN_CHECK( WININET_E_HTTP_TO_HTTPS_ON_REDIR )
			LSN_CHECK( WININET_E_HTTPS_TO_HTTP_ON_REDIR )
			LSN_CHECK( WININET_E_MIXED_SECURITY )
			LSN_CHECK( WININET_E_CHG_POST_IS_NON_SECURE )
			LSN_CHECK( WININET_E_POST_IS_NON_SECURE )
			LSN_CHECK( WININET_E_CLIENT_AUTH_CERT_NEEDED )
			LSN_CHECK( WININET_E_INVALID_CA )
			LSN_CHECK( WININET_E_CLIENT_AUTH_NOT_SETUP )
			LSN_CHECK( WININET_E_ASYNC_THREAD_FAILED )
			LSN_CHECK( WININET_E_REDIRECT_SCHEME_CHANGE )
			LSN_CHECK( WININET_E_DIALOG_PENDING )
			LSN_CHECK( WININET_E_RETRY_DIALOG )
			LSN_CHECK( WININET_E_SEC_CERT_ERRORS )
			LSN_CHECK( WININET_E_SEC_CERT_REV_FAILED )

			//LSN_CHECK( ERROR_WINHTTP_INTERNAL_ERROR )
#undef LSN_CHECK
			default : { return LSN_E_OTHER; }
		}

	}

	/**
	 * Displays the current ::GetLastError() error with a description.
	 * 
	 * \param _dwErr The error code to translate.  If -1, ::GetLastError() is called.
	 **/
	inline void CErrors::DisplayLastError( DWORD _dwErr ) {
		DWORD dwError = _dwErr == DWORD( -1 ) ? _dwErr : ::GetLastError();

		LPVOID lpMsgBuf = nullptr;
#if 0
		HMODULE hWinInet = ::LoadLibraryExW( L"wininet.dll", NULL, LOAD_LIBRARY_AS_DATAFILE );

		if ( hWinInet ) {
			::FormatMessageW(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS,
				hWinInet,
				dwError,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				reinterpret_cast<LPWSTR>(&lpMsgBuf),
				0,
				NULL
			);

			::wprintf( L"Error %d: %s\n", dwError, reinterpret_cast<LPWSTR>(lpMsgBuf) );

			::LocalFree( lpMsgBuf );
			::FreeLibrary( hWinInet );
		}
		else 
#endif
		{
			// Fallback to system messages.
			::FormatMessageW(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dwError,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				reinterpret_cast<LPWSTR>(&lpMsgBuf),
				0,
				NULL
			);

			::wprintf( L"Error %d: %s\n", dwError, reinterpret_cast<LPWSTR>(&lpMsgBuf) );

			::LocalFree( lpMsgBuf );
		}



		//LPWSTR lpMsgBuf = nullptr;

		//::FormatMessageW(
		//	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		//	NULL,
		//	dwError,
		//	0, // Default language
		//	reinterpret_cast<LPWSTR>(&lpMsgBuf),
		//	0,
		//	NULL
		//);

		//::wprintf( L"Error %d: %s\n", dwError, lpMsgBuf );
		//::LocalFree( lpMsgBuf );
	}
#endif	// #ifdef _WIN32

	/**
	 * Gets the string description of an error code.
	 * 
	 * \param _eCode The error code whose description is to be gotten.
	 * \return Returns the text description for the given error.
	 **/
	inline const char * CErrors::ToStr( LSN_ERRORS _eCode ) {
		switch ( _eCode ) {
#if defined( LSN_JAPANESE )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return JPN; }
#elif defined( LSN_FRENCH )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return FR; }
#elif defined( LSN_SPANISH )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return SP; }
#elif defined( LSN_CHINESE )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return CH; }
#else
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return TXT; }
#endif	// #if defined( LSN_JAPANESE )
#include "LSNErrorEnum.inl"
#undef LSN_E_ENUM
		}
		return Str( LSN_STR_INVALID_ERROR_CODE );
	}

	/**
	 * Gets the string description of an error code.
	 * 
	 * \param _eCode The error code whose description is to be gotten.
	 * \return Returns the text description for the given error.
	 **/
	inline const char8_t * CErrors::ToStrPU8( LSN_ERRORS _eCode ) {
		switch ( _eCode ) {
#if defined( LSN_JAPANESE )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return u8##JPN; }
#elif defined( LSN_FRENCH )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return u8##FR; }
#elif defined( LSN_SPANISH )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return u8##SP; }
#elif defined( LSN_CHINESE )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return u8##CH; }
#else
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return u8##TXT; }
#endif	// #if defined( LSN_JAPANESE )
#include "LSNErrorEnum.inl"
#undef LSN_E_ENUM
		}
		return StrU8( LSN_STR_INVALID_ERROR_CODE );
	}

	/**
	 * Gets the string description of an error code.
	 * 
	 * \param _eCode The error code whose description is to be gotten.
	 * \return Returns the text description for the given error.
	 **/
	inline std::string CErrors::ToStrStr( LSN_ERRORS _eCode ) {
		return ToStr( _eCode );
	}

	/**
	 * Gets the string description of an error code.
	 * 
	 * \param _eCode The error code whose description is to be gotten.
	 * \return Returns the text description for the given error.
	 **/
	inline std::u8string CErrors::ToStrU8( LSN_ERRORS _eCode ) {
		return ToStrPU8( _eCode );
	}

	/**
	 * Gets the string description of an error code.
	 * 
	 * \param _eCode The error code whose description is to be gotten.
	 * \return Returns the text description for the given error.
	 **/
	inline const wchar_t * CErrors::ToStrPWStr( LSN_ERRORS _eCode ) {
		switch ( _eCode ) {
#if defined( LSN_JAPANESE )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return L ## JPN; }
#elif defined( LSN_FRENCH )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return L ## FR; }
#elif defined( LSN_SPANISH )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return L ## SP; }
#elif defined( LSN_CHINESE )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return L ## CH; }
#else
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return L ## TXT; }
#endif	// #if defined( LSN_JAPANESE )
#include "LSNErrorEnum.inl"
#undef LSN_E_ENUM
		}
		return StrL( LSN_STR_INVALID_ERROR_CODE );
	}

	/**
	 * Gets the string description of an error code.
	 * 
	 * \param _eCode The error code whose description is to be gotten.
	 * \return Returns the text description for the given error.
	 **/
	inline const char16_t * CErrors::ToStrPU16( LSN_ERRORS _eCode ) {
		switch ( _eCode ) {
#if defined( LSN_JAPANESE )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return u ## JPN; }
#elif defined( LSN_FRENCH )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return u ## FR; }
#elif defined( LSN_SPANISH )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return u ## SP; }
#elif defined( LSN_CHINESE )
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return u ## CH; }
#else
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return u ## TXT; }
#endif	// #if defined( LSN_JAPANESE )
#include "LSNErrorEnum.inl"
#undef LSN_E_ENUM
		}
		return StrU( LSN_STR_INVALID_ERROR_CODE );
	}

	/**
	 * Gets the string description of an error code.
	 * 
	 * \param _eCode The error code whose description is to be gotten.
	 * \return Returns the text description for the given error.
	 **/
	inline std::wstring CErrors::ToStrWStr( LSN_ERRORS _eCode ) {
		return ToStrPWStr( _eCode );
	}

	/**
	 * Gets the string description of an error code.
	 * 
	 * \param _eCode The error code whose description is to be gotten.
	 * \return Returns the text description for the given error.
	 **/
	inline std::u16string CErrors::ToStrU16( LSN_ERRORS _eCode ) {
		return ToStrPU16( _eCode );
	}

	/**
	 * Gets the name of an error code.
	 * 
	 * \param _eCode The error code whose name is to be gotten.
	 * \return Returns the text name for the given error.
	 **/
	inline const char * CErrors::Name( LSN_ERRORS _eCode ) {
		switch ( _eCode ) {
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return & ## # ENUM[6]; }
#include "LSNErrorEnum.inl"
#undef LSN_E_ENUM
		}

		return "";
	}

	/**
	 * Gets the name of an error code.
	 * 
	 * \param _eCode The error code whose name is to be gotten.
	 * \return Returns the text name for the given error.
	 **/
	inline const char8_t * CErrors::NamePU8( LSN_ERRORS _eCode ) {
		switch ( _eCode ) {
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return &u8 ## # ENUM[6]; }
#include "LSNErrorEnum.inl"
#undef LSN_E_ENUM
		}

		return u8"";
	}

	/**
	 * Gets the name of an error code.
	 * 
	 * \param _eCode The error code whose name is to be gotten.
	 * \return Returns the text name for the given error.
	 **/
	inline const wchar_t * CErrors::NamePWS( LSN_ERRORS _eCode ) {
		switch ( _eCode ) {
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return &L ## # ENUM[6]; }
#include "LSNErrorEnum.inl"
#undef LSN_E_ENUM
		}

		return L"";
	}

	/**
	 * Gets the name of an error code.
	 * 
	 * \param _eCode The error code whose name is to be gotten.
	 * \return Returns the text name for the given error.
	 **/
	inline const char16_t * CErrors::NamePU16( LSN_ERRORS _eCode ) {
		switch ( _eCode ) {
#define LSN_E_ENUM( ENUM, TXT, JPN, FR, SP, CH )			case ENUM : { return &u ## # ENUM[6]; }
#include "LSNErrorEnum.inl"
#undef LSN_E_ENUM
		}

		return u"";
	}

}	// namespace lsn
