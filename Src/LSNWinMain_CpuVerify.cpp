#ifdef _WIN32

#include "LSNBirdSNES.h"


#ifdef LSN_CPU_VERIFY
#include "Files/LSNStdFile.h"


#include "Bus/LSNBusA.h"
#include "Cpu/LSNRicoh5A22.h"
#include "LSONJson.h"
int WINAPI wWinMain( _In_ HINSTANCE /*_hInstance*/, _In_opt_ HINSTANCE /*_hPrevInstance*/, _In_ LPWSTR /*_lpCmdLine*/, _In_ int /*_nCmdShow*/ ) {
	std::unique_ptr<lsn::CBusA> pbBus = std::make_unique<lsn::CBusA>();
	pbBus->ApplyBasicMapping();
	std::unique_ptr<lsn::CRicoh5A22> pcCpu = std::make_unique<lsn::CRicoh5A22>( (*pbBus.get()) );
	std::vector<uint8_t> vRam( 0x1000000 );
	pbBus->SetMemory( vRam.data() );

	auto pRoot = GetThisPath().remove_filename();
	const std::filesystem::path pTests = std::filesystem::path( ".." ) / ".." / "Research" / "65816" / "v1";
	{
		static wchar_t wChars[2] = { L'n', L'e' };
		for ( uint32_t I = 1; I < 2; ++I ) {
			std::wstring wsFile;
			lson::CJson jSon;
			std::vector<uint8_t> vBytes;
			lsn::CStdFile sfFile;
			
			for ( size_t N = 0; N < std::size( wChars ); ++N ) {
				wchar_t wcFile[MAX_PATH];
				std::swprintf( wcFile, std::size( wcFile ), L"%.2X.%c.json", I, wChars[N] );
				const std::filesystem::path pFull = pRoot / pTests / wcFile;
				
				if ( sfFile.Open( pFull ) == lsn::LSN_E_SUCCESS ) {
					sfFile.LoadToMemory( vBytes );
					vBytes.push_back( 0 );

					if ( !jSon.SetJson( reinterpret_cast<const char *>(vBytes.data()) ) ) {
						::OutputDebugStringA( "JSON FAIL\r\n" );
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

						::OutputDebugStringA( "JSON NOT FAIL\r\n" );
						::OutputDebugStringW( wcFile );
						::OutputDebugStringA( "\r\n" );
					}
				}
			}
		}
	}
	return 0;
}

#endif	// #ifdef LSN_CPU_VERIFY

#endif	// #ifdef _WIN32
