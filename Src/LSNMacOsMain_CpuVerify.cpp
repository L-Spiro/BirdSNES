#ifdef __APPLE__
//#ifdef _WIN32

#include "LSNBirdSNES.h"

#ifdef LSN_CPU_VERIFY

#include "Files/LSNStdFile.h"
#include "Bus/LSNBusA.h"
#include "Cpu/LSNRicoh5A22.h"
#include "LSONJson.h"

#include <mach-o/dyld.h>
#include <limits.h>
#include <stdlib.h>
#include <filesystem>
#include <cstdio>
#include <vector>
#include <string>
#include <memory>
#include <codecvt>
#include <locale>

namespace {

	static void											DebugA( const char * _pcStr ) {
		::fputs( _pcStr, stderr );
	}

	static void											DebugLine( const std::string &_sStr ) {
		::fwrite( _sStr.data(), 1, _sStr.size(), stderr );
		::fputc( '\n', stderr );
	}

}	// namespace

int main( int /*_iArgC*/, char ** /*_ppcArgV*/ ) {
	std::unique_ptr<lsn::CBusA> pbBus = std::make_unique<lsn::CBusA>();
	pbBus->ApplyBasicMapping();
	std::unique_ptr<lsn::CRicoh5A22> pcCpu = std::make_unique<lsn::CRicoh5A22>( (*pbBus.get()) );
	std::vector<uint8_t> vRam( 0x1000000 );
	pbBus->SetMemory( vRam.data() );

	const std::filesystem::path pRoot = GetThisPath().remove_filename();
	const std::filesystem::path pTests = std::filesystem::path( ".." ) / ".." / "Research" / "65816" / "v1";

	static const char cChars[2] = { 'n', 'e' };

	for ( uint32_t I = 0x00; I < 256; ++I ) {
		lson::CJson jSon;
		std::vector<uint8_t> vBytes;
		lsn::CStdFile sfFile;

		for ( size_t N = 0; N < std::size( cChars ); ++N ) {
			char szFile[64];
			::snprintf( szFile, sizeof( szFile ), "%.2X.%c.json", I, cChars[N] );

			const std::filesystem::path pFull = pRoot / pTests / szFile;

			const std::string sFullUtf8 = pFull.string();
			const std::u16string u16Full = Utf8ToUtf16( sFullUtf8 );

			if ( sfFile.Open( u16Full.c_str() ) == lsn::LSN_E_SUCCESS ) {
				sfFile.LoadToMemory( vBytes );
				vBytes.push_back( 0 );

				if ( !jSon.SetJson( reinterpret_cast<const char *>(vBytes.data()) ) ) {
					DebugA( "JSON FAIL\n" );
				}
				else {
					pcCpu->Reset<true>();
					pbBus->ApplyBasicMapping();

					const lson::CJsonContainer::LSON_JSON_VALUE & jvRoot = jSon.GetContainer()->GetValue( jSon.GetContainer()->GetRoot() );
					for ( size_t J = 0; J < jvRoot.vArray.size(); ++J ) {
						const lson::CJsonContainer::LSON_JSON_VALUE & jvThis = jSon.GetContainer()->GetValue( jvRoot.vArray[J] );
						if ( !pcCpu->RunJsonTest( jSon, jvThis ) ) {
							volatile int hkhj = 0;
						}
					}

					DebugA( "JSON NOT FAIL\n" );
					DebugLine( sFullUtf8 );
				}
			}
		}
	}
	return 0;
}

#endif	// #ifdef LSN_CPU_VERIFY

#endif	// #ifdef __APPLE__
